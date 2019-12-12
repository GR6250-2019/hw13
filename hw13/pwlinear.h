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
		size_t i;
		for (i = 0; i < n; i++)
			if (a > x[i] && a < x[i + 1])
				break;

		f[n - 1] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
		for (size_t k = i; k > 0; k--)
		{
			X temp = y[k - 1] - y[k] - f[n - 1] * (x[k - 1] - x[k]);
			for (size_t j = i; j > k; j--)
			{
				temp -= f[j] * (x[k] - x[k - 1]);
			}
			f[k] = temp / (x[k] - x[k - 1]);
		}
		for (size_t k = i + 1; k <= n - 2; k++)
		{
			X temp = y[k + 1] - y[k] - f[n - 1] * (x[k + 1] - x[k]);
			for (size_t j = i + 1; j < k; j++)
			{
				temp -= f[j] * (x[k + 1] - x[k]);
			}
			f[k] = temp / (x[k + 1] - x[k]);
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
		//size_t coef = pwlinear_coefficients(a, n, p, c, f);
		X result = f[0];
		for (size_t j = 1; j <= i; j++)
			result += f[j] * p[j];
		for (size_t j = i + 1; j < n; j++)
			result += f[j] * c[j];
		return result; //!!! implement
	}
}
