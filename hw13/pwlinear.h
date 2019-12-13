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
	inline size_t pwlinear_coefficients(const X & a, size_t n, const X * x, const X * y, X * f)
	{
		//!!! implement
		ensure(n >= 2);
		std::vector<X>array_f(n);
		for (size_t i = 1; i <= n - 1; ++i) {
			size_t t0, t1;
			size_t t = std::lower_bound(x, x + n, a) - x;
			if (t == 0) {
				t0 = 0;
				t1 = 1;
			}
			else if (t == n) {
				t0 = n - 2;
				t1 = n - 1;
			}
			else {
				t0 = t - 1;
				t1 = t;
			}
			array_f[t] = (y[t0] - y[t1]) / (x[t0] - x[t1]);
		}
		for (size_t j = 1; j <= n - 2; ++j) {
			array_f[j] = array_f[j + 1] - array_f[j];
		}
		size_t k = 1;
		while (x[k] < a) {
			k++;
		}
		f = &array_f[0];
		return k;
	}

	// Expected value of payoff.
	// E[f(X)] = f(a) + f'(a)(E[X] - a) 
	//           + sum_{x[i] < a} f''(x[i]) p[i]
	//           + sum_{a < x[i]} f''(x[i]) c[i].
	// The array f[] contains the coefficents from the function above.
	// Assume E[X] = a so the second term is 0.
	template<class X = double>
	inline X pwlinear_value(size_t n, const X * f, size_t i, const X * p, const X * c)
	{
		//!!! implement
		X exp = f[0];
		size_t j = 1;
		while (j <= n - 2 && j <= i) {
			exp += f[j] * p[j];
			j++;
		}
		while (j <= n - 2 && j > i) {
			exp += f[j] * c[j];
			j++;
		}
		return exp;
	}
}
