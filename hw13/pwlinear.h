// pwlinear.h - Fit a piecewise linear curve.
#pragma once

namespace fms {

	// Given a p.w. linear curve find the Carr-Madan coefficients.
	// Curve is determined by the points (x[i], y[i]), 0 <= i < n.
	// Array f is filled with (f(a), f''(x[1]) ... f''(x[n-2]), f'(a))
	// f(x) = f(a) 
	//        + sum_{i > 0, x[i] < a} f''(x[i]) max{x[i] - x, 0}
	//        + sum_{i < n-1, x[i] > a} f''(x[i]) max{x - x[i], 0} 
	//        + f'(a)(x - a).
	// Return i such that x[i] < a < x[i+1]
	template<class X = double>
	inline size_t pwlinear_coefficients(const X& a, size_t n, const X* x, const X* y, X* f)
	{
		ensure(n >= 2);
		// Get i such that x[i] < a < x[i+1]
		size_t iVal = 0;
		for (size_t i = 0; i <= (n-2); ++i) {
			if (((a > x[i] && a < x[i + 1]) || a == x[i])) {
				iVal = i;
			}
		}

		X fSum;
		X fad = (y[iVal+1] - y[iVal]) / (x[iVal + 1] - x[iVal]); //fad <- f'(a)
		X fa = y[iVal] - fad * (x[iVal] - a);
		X temp;
		for (size_t i = iVal - 1; i >= 0; --i) {
			temp = fad * (x[i] - a) + fa;
			fSum = 0;
			for (size_t j = i + 1; j < iVal; j++) {
				fSum += f[j] * (x[j] - x[i]);
			}
			f[i + 1] = (y[i] - temp - fSum) / (x[i + 1] - x[i]);
		}

		for (size_t i = iVal + 2; i <= n - 1; ++i) {
			temp = fad * (x[i] - a) + fa;
			fSum = 0;
			for (size_t j = i - 1; j > iVal + 1; --j) {
				fSum += f[j] * (x[i] - x[j]);
			}
			f[i - 1] = (y[i] - temp - fSum) / (x[i] - x[i - 1]);
		}
		f[0] = fa;
		f[n - 1] = fad;

		return iVal;
	} 

	// Expected value of payoff.
	// E[f(X)] = f(a) + f'(a)(E[X] - a) 
	//           + sum_{x[i] < a} f''(x[i]) p[i]
	//           + sum_{a < x[i]} f''(x[i]) c[i].
	// The array f[] contains the coefficents from the function above.
	// Assume E[X] = a so the second term is 0.
	template<class X = double>
	inline X pwlinear_value(size_t n, const X* f, size_t i, const X* p, const X* c)
	{
		
		X res = f[0];
		for (size_t j = 1; j <= i; ++j) {
			res += (f[j] * p[j]);
		}
		for (size_t j = i + 1; j <= n - 1; j++) { //j <= n - 2
			res += (f[j] * c[j]);
		}
		return res;

	}
}
