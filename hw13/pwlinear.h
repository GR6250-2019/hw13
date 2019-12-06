// pwlinear.h - Fit a piecewise linear curve.
#pragma once

namespace fms {

	// Given a p.w. linear curve find the Carr-Madan coefficients.
	// Curve is determined by the points (x[i], y[i]), 0 <= i < n.
	// Array f is filled with (f(a), f''(x[1]) ... f''(x[n-2]), f'(a))
	// f(x) = f(a) + f'(a)(x - a)
	//        + sum_{i > 0, x[i] < a} f''(x[i]) max{x[i] - x, 0}
	//        + sum_{i < n-1, x[i] > a} f''(x[i]) max{x - x[i], 0}.
	template<class X = double, class Y = double, class F = std::common_type<X,Y>>
	inline void pwlinear_coefficients(const X& a, size_t n, const X* x, const Y* y, F* f)
	{
		//!!! implement
	}

	// Expected value of payoff.
	// E[f(X)] = f(a) + f'(a)(E[X] - a) 
	//           + sum_{x < a} f''(x[i]) p[i]
	//           + sum_{x > a} f''(x[i]) c[i].
	template<class X = double, class Y = double, class F = std::common_type<X, Y>>
	inline F pwlinear_value(const X& EX_a, size_t n, const F* f, const V* p, const V* c)
	{
		return 0; //!!! implement
	}
}
