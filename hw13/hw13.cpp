// xllproject.cpp
#include <cmath>
#include <vector>
#include "hw13.h"

using namespace xll;
using namespace std;

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
        L"(x,y) is the curve where x[i] is the ascending strike price and y[i] is the option payoff "
		L"p is the payoff of the put with respect to the strike x[0],x[1]..."
		L"c is the payoff of the call with respect to the strike x[0],x[1]..."
        L"The function XLL.PWLINEAR.VALUE(x, y, f, p, c) computes the value "
        L"of a piecwise linear payoff determinded by x and y "
        L"using put prices (x < f) and call prices (x > f). "
        L"We assume f is par forward value of the underlying. "
    )
);

//!!! Implement XLL.PWLINEAR.VALUE as described above.
AddIn xai_pwlinear(
	Function(XLL_DOUBLE, L"?xll_pwlinear_value", L"XLL.PWLINEAR.VALUE")
	.Arg(XLL_FP, L"x", L"is an array of ascending strike price. ")
	.Arg(XLL_FP, L"y", L"is an array of the corresponding option payoff. ")
	.Arg(XLL_DOUBLE, L"f", L"is par forward value of the underlying. ")
	.Arg(XLL_FP, L"p", L"is an array of the corresponding put payoff. ")
	.Arg(XLL_FP, L"c", L"is an array of the corresponding call payoff.  ")
	.Category(L"XLL")
	.FunctionHelp(L"Return the value of a piecwise linear payoff. ")
	.Documentation(L"Doc")
);
double WINAPI xll_pwlinear_value(_FP12* xa, _FP12* ya, double f, _FP12* pa, _FP12* ca)
{
#pragma XLLEXPORT
	size_t n = size(*xa);
	double* x = &xa->array[0];
	double* p = &pa->array[0];
	double* c = &ca->array[0];
	double* y = &ya->array[0];
	double* coeff=&xa->array[0];
	size_t i = fms::pwlinear_coefficients(f,n,x,y,coeff);
	double result = fms::pwlinear_value(n, coeff, i, p, c);
	return result;
}
// inline size_t pwlinear_coefficients(const X & a, size_t n, const X * x, const X * y, X * f)
//	inline X pwlinear_value(size_t n, const X* f, size_t i, const X* p, const X* c)