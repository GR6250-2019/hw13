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
	Function(XLL_DOUBLE,L"?xll_pwlinear_value",L"XLL.PWLINEAR.VALUE")
	.Arg(XLL_FP, L"f", L"f array")
	.Arg(XLL_FP, L"p", L"put array")
	.Arg(XLL_FP, L"c", L"call array")
	.Arg(XLL_FP, L"x", L"x array")
	.Arg(XLL_FP, L"y", L"y array")
	.Arg(XLL_DOUBLE, L"a", L"forward quotes")
	.Volatile()
	.Category(CATEGORY)
	.FunctionHelp(L"return the piecewise expetation value of the variance swap.")
	.Documentation(L"Implement the piecewise linear value for variance swap.")
);

double WINAPI xll_pwlinear_value(_FP12* pt_f, _FP12* pt_p, _FP12* pt_c, _FP12* pt_x, _FP12* pt_y, double a) {
#pragma XLLEXPORT
	double result;
	size_t n = pt_f->rows;
	try {
		double* f = &pt_f->array[0];
		double* p = &pt_p->array[0];
		double* c = &pt_c->array[0];
		double* x = &pt_x->array[0];
		double* y = &pt_y->array[0];
		size_t i = fms::pwlinear_coefficients(a, n, x, y, f);
		result = fms::pwlinear_value(n, f, i, p, c);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return result;
}

AddIn xai_lmm_par_coupon(
	Function(XLL_DOUBLE, L"?xll_lmm_par_coupon", L"XLL.LMM.PAR_COUPON")	
	.Volatile()
	.Category(CATEGORY)
	.FunctionHelp(L"Return swap par coupons given forwards. ")
	.Documentation(L"Par coupon. ")
);
double WINAPI xll_lmm_par_coupon()
{
#pragma XLLEXPORT
	return 0;
}
