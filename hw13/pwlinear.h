// pwlinear.h - Fit a piecewise linear curve.
#pragma once
#include <Eigen/Core>
#include <Eigen/LU>
#include <iostream>
using namespace std;
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
		// Solve m*f = v for f
		Eigen::MatrixXf m(n, n);
		Eigen::VectorXf v(n);

		size_t a_ind = 0;

		// Initialize v with values from y
		v(0) = y[0];
		for (size_t ind = 1; ind < n; ind++) {
			v(ind) = y[ind];
			if (x[ind - 1] < a && x[ind] > a) {
				a_ind = ind - 1;
			}
		}

		for (size_t row = 0; row < n; row++) {
			m(row, 0) = 1.0;
			for (size_t col = 1; col < n - 1; col++) {
				if (x[col] < a) {
					m(row, col) = std::fmax(x[col] - x[row], 0.0);
				}
				else {
					m(row, col) = std::fmax(x[row] - x[col], 0.0);
				}
				m(row, n - 1) = x[row] - a;
			}
		}

		Eigen::MatrixXf m_inv = m.inverse();
		Eigen::VectorXf v_prod = m_inv * v;
		for (size_t ind = 0; ind < n; ind++) {
			f[ind] = v_prod(ind);
		}

		return a_ind;
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
		X E_f = f[0];
		cout << "E_f " << f[0] << endl;
		cout << "E_f " << E_f << endl;
		// Sum the puts
		for (int j = 1; j <= i; j++) {
			E_f += f[j] * p[j];
			cout << "E_p " << (f[j] * p[j - 1]) << endl;
			cout << "E_p " << E_f << endl;
		}
		// Sum the calls
		for (int j = i + 1; j < n - 1; j++) {
			E_f += f[j] * c[j - i - 1];
			cout << "E_c " << (f[j] * c[j-i-1]) << endl;
			cout << "E_c " << E_f << endl;
		}

		return E_f;
	}
}
