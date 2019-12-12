// xllproject.cpp
#include <cmath>
#include "hw13.h"
#include "pwlinear.h"
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
static AddIn xai_xll_pwlinear_value(
	Function(XLL_DOUBLE, L"?xll_pwlinear_value", L"PWLINEAR.VALUE")
	.Arg(XLL_FP, L"n", L"is the length of a piecewise linear curve .")
	.Arg(XLL_FP, L"f", L"is an array which is filled with (f(a), f''(x[1]) ... f''(x[n-2]), f'(a)).")
	.Arg(XLL_DOUBLE, L"i", L"is a number such that x[i] < a < x[i+1].")
	.Arg(XLL_FP, L"p", L"is payoff of put option.")
	.Arg(XLL_FP, L"c", L"is payoff of call option.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the value of a piecewise linear curve at times.")
);
double WINAPI xll_pwlinear_value(_FP12* x1, _FP12* y1, double f, _FP12* p1, _FP12* c1)
{
#pragma XLLEXPORT
	size_t n = size(*x1);
	double* x = &x1->array[0];
	double* p = &p1->array[0];
	double* c = &c1->array[0];
	double* y = &y1->array[0];
	double* coefficient = &x1->array[0];
	size_t i = pwlinear_coefficients(f, n, x, y, coefficient);
	double result = pwlinear_value(n, coefficient, i, p, c);
	return result;
}