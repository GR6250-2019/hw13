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
		size_t i0, i1;
		size_t i = std::lower_bound(x, x + n, a) - x;

		if (j == n) {
			i0 = n - 2;
			i1 = n - 1;
		}
		else if (j == 0) {
			i0 = 0;
			i1 = 1;
		}
		else {
			i0 = i - 1;
			i1 = i;
		}

		auto f[i] = (y[i0] - y[i1])/(x[i0] - x[i1]);

        for (size_t j = 1; j < n - 1; ++j) {
        
			f[j] = f[j + 1] - f[j];
        
		}

		f = f[0];

        auto result = 1;
		
		for (; x[result] < a; ++result) {

		}

		return result;

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
		
		X value = f[0];

		for (size_t j = 1; j < n - 1 && p[j] < f[j]; ++j)
			value += p[j]*std::max(f[j] - p[j], 0.);

		for (size_t j = n - 2; j > 0 && c[j] > f[j]; --j)
			value += c[j]*std::max(c[j] - f[j], 0.);

		return value;
		
		}
}
