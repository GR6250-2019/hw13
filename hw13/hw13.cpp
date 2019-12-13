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
	.Arg(XLL_FP,L"x", L"is an array of x values.")
	.Arg(XLL_FP, L"y", L"is an array of y values.")
	.Arg(XLL_DOUBLE, L"f", L"is par far foward value of the underlying.")
	.Arg(XLL_FP, L"p", L"is an array of put payoff.")
	.Arg(XLL_FP, L"c", L"is an array of call payoff.")
	.Category(L"XLL")
	.FunctionHelp(L"Return the value of a piecewise linear payoff.")
	.Documentation(
		L"The function XLL.PWLINEAR.VALUE(x, y, f, p, c) computes the value "
		L"of a piecwise linear payoff determinded by x and y "
		L"using put prices (x < f) and call prices (x > f)."
	)
);

double WINAPI xll_pwlinear_value(_FP12* x, _FP12* y, double f, _FP12* p, _FP12* c) {
#pragma XLLEXPORT
	double res;

	size_t n = sizeof(*x);
	double* xv = &x->array[0];
	double* yv = &y->array[0];
	double* pv = &p->array[0];
	double* cv = &c->array[0];
	double* coeff = new double[n];

	size_t j = fms::pwlinear_coefficients(f, n, xv, yv, coeff);
	res = fms::pwlinear_value(n, coeff, j, pv, cv);

	return res;
};