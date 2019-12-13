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
		int i_ = 0;
		for (int i = 1; i < n - 1; i++) {
			if ((x[i] <= a) && (x[i + 1] > a)) {
				i_ = i;
			}
		}

		f[n-1] = (y[i_] - y[i_ + 1])/(x[i_] - x[i_ + 1]);
		f[0] = y[i_] - f[n-1]*(x[i_] - a);

		X sum = 0;
		X dx =0;


		for (int i = i_; i > 0; i--) {
			sum = 0;
			dx = x[i-1] - x[i];
			for (int j = i + 1; j <= i_; j++) {
				sum = sum + f[j] * dx;
			}
			f[i] = (y[i] - y[i - 1] - f[n - 1] * (-dx) - sum) / dx;
		}

		for (int i = i_ + 1; i < n - 1; i++) {
			sum = 0;
			dx = x[i + 1] - x[i];
			for (int j = i - 1; j >= i_ + 1; j--) {
				sum = sum + f[j] * dx;
			}
			f[i] = (y[i + 1] - y[i] - f[n - 1] * dx - sum) / dx;
		}
		//!!! implement
		return i_;
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
		double E = f[0];
		for (int j = 1; j < n; j++) {
			if (j <= i) {
				E = E + f[j] * p[j];
			}
			else {
				E = E + f[j] * c[j];
			}
		}
		return E; //!!! implement
	}
}
