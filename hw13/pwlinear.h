// pwlinear.h - Fit a piecewise linear curve.
#pragma once
#include <vector>

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
		if (n >= 3)
		{
			while (i + 1 <= n - 2 && x[i + 1] < a)
			{
				i++;
			}
		}
		std::vector<X> farray(n);
		farray[0] = (y[i + 1] * (x[i] - a) - y[i] * (x[i + 1] - a)) / (x[i] - x[i + 1]);
		farray[n - 1] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
		for (size_t k = i; k > 0; k--)
		{
			X temp = y[k - 1] - y[k] - farray[n - 1] * (x[k - 1] - x[k]);
			for (size_t j = i; j > k; j--)
			{
				temp -= farray[j] * (x[k] - x[k - 1]);
			}
			farray[k] = temp / (x[k] - x[k - 1]);
		}
		for (size_t k = i + 1; k <= n - 2; k++)
		{
			X temp = y[k + 1] - y[k] - farray[n - 1] * (x[k + 1] - x[k]);
			for (size_t j = i + 1; j < k; j++)
			{
				temp -= farray[j] * (x[k + 1] - x[k]);
			}
			farray[k] = temp / (x[k + 1] - x[k]);
		}
		f = &farray[0];
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
		//!!! implement
		X payoff = f[0];
		if (i >= 1)
		{
			size_t j = 1;
			while (j <= n - 2 && j < i)
			{
				payoff += f[j] * p[j];
				j++;
			}
			while (j <= n - 2 && j > i)
			{
				payoff += f[j] * c[j];
				j++;
			}
		}
		return payoff;
	}


}
