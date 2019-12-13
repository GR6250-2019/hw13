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
		size_t i0 = (a <= x[0]) ? 0 : n;

		for (size_t i = 1; i < n; ++i) {
			// first derivative
			f[i] = (y[i] - y[i - 1]) / (x[i] - x[i - 1]);
			if (x[i] < a && a < x[i + 1]) {
				i0 = i;
				f[0] = y[i] + f[i] * (a - x[i]);
				f[n - 1] = f[i];
			}
		}
		for (size_t i = 1; i < n - 1; ++i) {
			// second derivative
			f[i] = f[i + 1] - f[i];
		}
		
		return i0;
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
		X v = f[0];

		for (size_t j = 1;  j <= i; ++j) {
			v += f[j] * p[j];
		}
		for (size_t j = i + 1; j < n - 1; ++j) {
			v += f[j] * c[j];
		}

		return v; //!!! implement
	}
}
