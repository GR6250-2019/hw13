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

AddIn xai_pwlinear_value(
	Function(XLL_DOUBLE, L"?xll_pwlinear_value", L"XLL.PWLINEAR.VALUE")
	.Arg(XLL_FP, L"x", L"is an array of the x values of a piecewise linear payoff. ")
	.Arg(XLL_FP, L"y", L"is an array of the y values of a piecewise linear payoff. ")
	.Arg(XLL_DOUBLE, L"f", L"is the par forward value of the underlying. ")
	.Arg(XLL_FP, L"p", L"is an array of puts for x < f. ")
	.Arg(XLL_FP, L"c", L"is an array of calls for x > f. ")
	.Volatile()
	.Category(CATEGORY)
	.FunctionHelp(L"Return the expected value of the payoff. ")
);

double WINAPI xll_pwlinear_value(_FP12* px, _FP12* py, double a, _FP12* pp, _FP12* pc) {
#pragma XLLEXPORT

	try {
		auto n = size(*px);
		ensure(n == size(*py));

		double* x = &px->array[0];
		double* y = &py->array[0];
		double* p = &pp->array[0];
		double* c = &pc->array[0];

		static xll::FP12 result;
		result.resize(n, 1);

		std::vector<double> fv;
		fv.resize(n);
		double* f = fv.data();

		size_t i = fms::pwlinear_coefficients(a, n, x, y, f);
		return fms::pwlinear_value(n, f, i, p, c);
		return i;
	} catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
		return 0;
	}
}