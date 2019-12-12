// xllproject.cpp
#include <cmath>
#include "hw13.h"

using namespace xll;

AddIn xai_project(
    Document(L"hw13")
    .Documentation(
        L"This will generate a Sandcastle Helpfile Builder project file. "
        L"Start Excel with the add-in loaded and run (Alt-F8) the macro MAKE.SHFB. "
    )
);

AddIn xai_xllproject(
    Document(CATEGORY)
    .Category(CATEGORY)
    .Documentation(
        L"Documentation for the " CATEGORY L" category. "
        L"<para>"
        L"The function XLL.PWLINEAR.VALUE(x, y, f, p, c) computes the value "
        L"of a piecwise linear payoff determinded by x and y "
        L"using put prices (x < f) and call prices (x > f). "
        L"</para>"
        L"<para>"
        L"We assume f is par forward value of the underlying. "
        L"</para>"
    )
);

//!!! Implement XLL.PWLINEAR.VALUE as described above.
AddIn xai_pwlinear_value(
	Function(XLL_DOUBLE, L"?xll_pwlinear_value", CATEGORY L".PWLINEAR.VALUE")
	.Arg(XLL_FP, L"x", L"is a sequence")
	.Arg(XLL_FP, L"y", L"is a sequence")
	.Arg(XLL_DOUBLE, L"f", L"is value of a")
	.Arg(XLL_FP, L"p", L"is a sequence")
	.Arg(XLL_FP, L"c", L"is a sequence")
	.Category(CATEGORY)
	.FunctionHelp(L"Return a two column array of cash flow time and amount.")
	.Documentation(
		L"The first column is the cash flow time and the second is the corresponding amount. "
	)
);


double WINAPI xll_pwlinear_value(_FP12* x, _FP12* y, double f, _FP12* p, _FP12* c)
{
#pragma XLLEXPORT
	size_t n = sizeof(x);
	double* x_ = &x->array[0];
	double* y_ = &y->array[0];
	double* p_ = &p->array[0];
	double* c_ = &c->array[0];
	double* fnew = new double[n];

	size_t i = fms::pwlinear_coefficients(f, n, x_, y_, fnew);
	
	double E = fms::pwlinear_value(n, fnew, i, p_, c_);
	return E;

}
