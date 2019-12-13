// xllproject.cpp
#include <cmath>
#include "hw13.h"
#include "pwlinear.h"

using namespace xll;
using namespace fms;
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



AddIn xai_pwlinear_value(
	Function(XLL_DOUBLE, L"?xll_pwlinear_value", CATEGORY L".PWLINEAR.VALUE")
	.Arg(XLL_FP, L"x", L"is the array of x.")
	.Arg(XLL_FP, L"y", L"is the array of y.")
	.Arg(XLL_DOUBLE, L"f", L"is par forward value of the underlying.")
	.Arg(XLL_FP, L"p", L"is the array of prices of put.")
	.Arg(XLL_FP, L"c", L"is the array of prices of call.")
	.Category(L"XLL")
	.FunctionHelp(L"computes the value of a piecwise linear payoff determinded by x and y")
	.Documentation(
		L" using put prices (x < f) and call prices (x > f). "
		L" assume f is par forward value of the underlying. "
	)
);

double WINAPI xll_pwlinear_value(_FP12* x, _FP12* y, double f, _FP12* p, _FP12* c)
{
#pragma XLLEXPORT

	size_t n = size(*x);

	double* x1 = &x->array[0];
	double* y1 = &y->array[0];
	double* p1 = &p->array[0];
	double* c1 = &c->array[0];
	double* coeff = &x->array[0];

	size_t i = pwlinear_coefficients(f, n, x1, y1, coeff);
    
	try {
        auto result = pwlinear_value(n, coeff, i, p1, c1);
		return result;
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
		return 0;
    }