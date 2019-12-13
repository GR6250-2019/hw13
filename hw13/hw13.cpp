// xllproject.cpp
#include <cmath>
#include<vector>
#include "hw13.h"
using namespace std;

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
	.Arg(XLL_FP, L"x", L"is an array with ascending strike prices.")
	.Arg(XLL_FP, L"y", L"is an array with option payoffs.")
	.Arg(XLL_DOUBLE, L"f", L"is the forward value of the underlying.")
	.Arg(XLL_FP, L"p", L"is an array of corresponding put payoffs.")
	.Arg(XLL_FP, L"c", L"is an array of corresponding call payoff.")
	.Category(L"XLL")
	.FunctionHelp(L"Fit a piecewise linear curve.")
	.Documentation(L"Fit a piecewise linear curve.")
);
double WINAPI xll_pwlinear_value(_FP12* xa, _FP12* ya, double f, _FP12* pa, _FP12* ca) {
#pragma XLLEXPORT{}
}
