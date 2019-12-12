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
	.Arg(XLL_FP, L"x", L"x values of the function")
	.Arg(XLL_FP, L"y", L"y values of the function")
	.Arg(XLL_DOUBLE, L"f", L"empty array for calculation")
	.Arg(XLL_FP, L"p", L"y values of the function")
	.Arg(XLL_FP, L"c", L"fixd a value")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(L"Return i such that x[i] < a < x[i+1]")
	.Documentation(
		L"delcare and modifies the array f such that f is composed with "
		L" (f(a), f''(x[1]) ... f''(x[n-2]), f'(a))"
	)
);
double WINAPI xll_pwlinear_value( _FP12* xpt,  _FP12* ypt,  double f,  _FP12* ppt,  _FP12* cpt){
#pragma XLLEXPORT

	double* x = &xpt->array[0];
	double* y = &ypt->array[0];
	double* p = &ppt->array[0];
	double* c = &cpt->array[0];

	size_t n = size(*xpt);
	double* coef = new double[n];
	size_t loc = fms::pwlinear_coefficients(f, n, x, y, coef);
	double result = fms::pwlinear_value(n, coef, loc, p, c);
	
	return result;
}
