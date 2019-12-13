// xllproject.cpp
#include <cmath>
#include "hw13.h"
using namespace fms;
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
AddIn xai_pwlinear(
	Function(XLL_DOUBLE, L"?xll_pwlinear_value", L"XLL.PWLINEAR.VALUE")
	.Arg(XLL_FP, L"x", L"is an array of the strike price. ")
	.Arg(XLL_FP, L"y", L"is an array of the option payoff. ")
	.Arg(XLL_DOUBLE, L"f", L"is the par forward value of the underlying. ")
	.Arg(XLL_FP, L"p", L"is an array of the put payoff when x < f. ")
	.Arg(XLL_FP, L"c", L"is an array of the call payoff when x > f. ")
	.Category(L"XLL")
	.FunctionHelp(L"Return the value of the piecewise linear payoff. ")
	.Documentation(L"Doc")
);
double WINAPI xll_pwlinear_value(_FP12* xx, _FP12* yy, double f, _FP12* pp, _FP12* cc) {
#pragma XLLEXPORT
	size_t n = size(*xx);
	double* x = &xx->array[0];
	double* y = &yy->array[0];
	double* p = &pp->array[0];
	double* c = &cc->array[0];
	double* coef = &xx->array[0];
	size_t m = pwlinear_coefficients(f, n, x, y, coef);
	double result = pwlinear_value(n, coef, m, p, c);
	return result;
}
