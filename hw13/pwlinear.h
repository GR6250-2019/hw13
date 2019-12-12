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
		//!!! implement
		size_t res = 0;
 		for (size_t i = 0; i < n-1; i++) {
 			if (x[i]<a && x[i + 1]>a) {
 				res = i;
 				break;
 			}
 		}

 		std::vector<X> temp(n);
 		temp[n - 1] = (y[res + 1] - y[res]) / (x[res + 1] - x[res]);
 		temp[0] = y[res] + temp[n - 1] * (a - x[res]);

 		for (size_t k = res; k > 0; k--) {
 			X ans = y[k - 1] - y[k] -temp[n - 1] * (x[k - 1] - x[k]);
 			for (size_t j = res; j > k; j--) {
 				ans -= temp[j] * (x[k] - x[k - 1]);
 			}
 			temp[k] = ans / (x[k] - x[k - 1]);
 		}

 		for (size_t k = res + 1; k <= n - 2; k++) {
 			X ans = y[k + 1] - y[k] - temp[n - 1] * (x[k + 1] - x[k]);
 			for (size_t j = res + 1; j < k; j++) {
 				ans -= temp[j] * (x[k + 1] - x[k]);
 			}
 			temp[k] = ans / (x[k + 1] - x[k]);
 		}
 		f = &temp[0];

 		return res;
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
		//!!! implement
 		double value = 0;
 		value += f[0];
 		for (size_t j = 1; j <= i; j++) {
 			value += (f[j] * p[j]);
 		}
 		for (size_t j = i + 1; j <= n - 2; j++) {
 			value += (f[j] * c[j]);
 		}
 		return value; 
	}
}
