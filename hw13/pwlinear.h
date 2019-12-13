// pwlinear.h - Fit a piecewise linear curve.
#pragma once
#include<vector>

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
		//!!! implement
		size_t i = 0;
		for (i = 0 ;i < n; i++)
			if (a > x[i] && a < x[i + 1])
				break;
		f[n - 1] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
		for (size_t j = i; j > 0; j--) {
			X temp = y[j - 1] - y[j] - f[n - 1] * (x[j - 1] - x[j]);
			for (size_t k = i; k > j; k--) {
				temp = temp - f[k] * (x[j] - x[j - 1]);
			}
			f[j] = temp / (x[j] - x[j - 1]);
		}

		for (size_t j = i + 1; j <= n - 2; j++) {
			X temp = y[j + 1] - y[j] - f[n - 1] * (x[j + 1] - x[j]);
			for (size_t k = i + 1; k < j; k++) {
				temp = temp - f[k] * (x[j + 1] - x[j]);
			}
			f[j] = temp / (x[j + 1] - x[j]);
		}
		return i;
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
		X result = f[0];
		for (size_t j = 1; j <= i && j <= n - 2; j++) {
			result = result + f[j] * p[j];
		}
		for (size_t j = i + 1; j <= n - 2; j++) {
			result = result + f[j] * c[j];
		}

		return result; //!!! implement
	}
}
