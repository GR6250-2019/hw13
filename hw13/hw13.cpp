// xllproject.cpp
#include <cmath>
#include "hw13.h"
#include "pwlinear.h"

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
	Function(XLL_DOUBLE, L"?xll_pwlinear_value", L"XLL.PWLINEAR.VALUE")
	.Arg(XLL_DOUBLE, L"px", L"is the size of x.")
	.Arg(XLL_FP, L"py", L"is an array of y. ")
	.Arg(XLL_DOUBLE, L"a", L"the the par forwar value.")
	.Arg(XLL_FP, L"pp", L"is an array of puts. ")
	.Arg(XLL_FP, L"pc", L"is an array of calls. ")
	.Category(CATEGORY)
	.FunctionHelp(L"Computes piecewice linear payoff. ")
	.Documentation(L"Implement Carr Madam formula. ")
);

 double WINAPI xll_pwlinear_value(_FP12* px, _FP12* py, double a, _FP12* pp, _FP12* pc)
{
#pragma XLLEXPORT
	 auto n = size(*px);
	 double* x = &px->array[0];
	 double* y = &py->array[0];
	 double* p = &pp->array[0];
	 double* c = &pc->array[0];

	 double* f = &px->array[0];
	 size_t i = fms::pwlinear_coefficients(a, n, x, y, f);

	 return fms::pwlinear_value(n, f, i, p, c);
}