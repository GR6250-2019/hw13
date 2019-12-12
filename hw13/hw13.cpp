// xllproject.cpp
 #include <cmath>
 #include "hw13.h"
 #include "pwlinear.h"

 using namespace xll;

 @@ -28,4 +29,35 @@ AddIn xai_xllproject(
     )
 );

 //!!! Implement XLL.PWLINEAR.VALUE as described above. 
 //!!! Implement XLL.PWLINEAR.VALUE as described above.
 AddIn xai_pwlinear_value(
 	Function(XLL_DOUBLE, L"?xll_pwlinear_value", L"XLL.PWLINEAR.VALUE")
 	.Arg(XLL_FP, L"x",L"is an array of x-axis points.")
 	.Arg(XLL_FP, L"y", L"is an array of y-axis points.")
 	.Arg(XLL_DOUBLE, L"f", L"is par forward value of the underlying.")
 	.Arg(XLL_FP, L"p", L"is an array of put prices.")
 	.Arg(XLL_FP, L"c", L"is an array of call prices.")
 	.Category(L"XLL")
 	.Documentation(
 		L"Return the value of a piecewise linear payoff determined by x and y using put prices (x < f) and call prices ( x > f)."
 	)
 );

 double WINAPI xll_pwlinear_value(_FP12* pt_x, _FP12* pt_y, double f, _FP12* pt_p, _FP12* pt_c)
 {
 #pragma XLLEXPORT
 	double result;

 	double* x = &pt_x->array[0];
 	double* y = &pt_y->array[0];
 	double* p = &pt_p->array[0];
 	double* c = &pt_c->array[0];
 	double* coef = &pt_x->array[0];

 	size_t n = size(*pt_x);

 	size_t loc = fms::pwlinear_coefficients(f, n, x, y, coef);
 	result = fms::pwlinear_value(n, coef, loc, p, c);

 	return result;
 } 
