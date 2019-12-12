// xllproject.cpp
#include <cmath>
#include "hw13.h"
#include"pwlinear.h"

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
	.Arg(XLL_FP, L"x", L"is an array of value on x-axis.")
	.Arg(XLL_FP, L"y", L"is an array of value on y_axis.")
	.Arg(XLL_DOUBLE, L"f", L"is par forward value of the underlying.")
	.Arg(XLL_FP, L"p", L"is an array of put prices.")
	.Arg(XLL_FP, L"c", L"is an array of call prices.")
	.Category(L"XLL")
	.Documentation(
		L"Return the expected value of a payoff determined by x and y arrays using call and put prices."
	)
);

double WINAPI xll_pwlinear_value(_FP12* p_x, _FP12* p_y, double f, _FP12* p_p, _FP12* p_c)
{
#pragma XLLEXPORT
	double result;

	double* x = &p_x->array[0];
	double* y = &p_y->array[0];
	double* p = &p_p->array[0];
	double* c = &p_c->array[0];
	double* coef = &p_x->array[0];

	size_t n = size(*p_x);

	size_t loc = fms::pwlinear_coefficients(f, n, x, y, coef);
	result = fms::pwlinear_value(n, coef, loc, p, c);

	return result;
}
