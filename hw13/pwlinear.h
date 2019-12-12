// pwlinear.h - Fit a piecewise linear curve.
#pragma once
#include <numeric>   
#include <vector>
#include "xll12/xll/ensure.h"
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
		std::vector<X> f_array(n);
		for (size_t q = 1; q < n; ++q) {

			size_t z0, z1;
			size_t z = std::lower_bound(x, x + n, a) - x;

			if (z == n) {
				z0 = n - 2;
				z1 = n - 1;
			}
			else if (z == 0) {
				z0 = 0;
				z1 = 1;
			}
			else {
				z0 = z - 1;
				z1 = z;
			}
			f_array[z] = (y[z0] - y[z1]) / (x[z0] - x[z1]);
		}

		for (size_t i = 1; i < n - 1; ++i) {
			f_array[i] = f_array[i + 1] - f_array[i];
		}
		//Return i such that x[i] < a < x[i+1]
		size_t i = 1;
		while (x[i] < a) {
			i = i + 1;
		}
		f = &f_array[0];


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

		X E = f[0];
		for (size_t j = 1; j < n - 1 && j <= i; ++j) {
			E += f[j] * p[j];
		}
		for (size_t j = n - 2; j > 0 && j > i; --j) {
			E += f[j] * c[j];

		}

		return E; 
	}
}