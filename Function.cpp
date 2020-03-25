#include <cmath>
#include "Function.h"


Vector Function::gradient(const Vector & x, double h)
{
	int dimension = x.dimension;
	Vector direction(dimension);
	Vector grad(dimension);
	for (int i = 0; i < dimension; ++i)
	{
		direction[i] = h;
		grad[i] = ((*this)(x + direction) - (*this)(x)) / h;
		direction[i] = 0;
	}
	return(grad);
}

double Exponential::operator ()(const Vector& x)
{
	Vector X((Vector) x);
	return(exp(X[0]) + exp(X[1]));
}

double Trigonometric::operator ()(const Vector & x)
{
    Vector X((Vector) x);
    return(sin(X[0]) + cos(X[1]));
}

double Rosenbrock::operator ()(const Vector & x)
{
	Vector X((Vector) x);
    return((1 - X[0]) * (1 - X[0]) + 100 * (X[1] - X[0] * X[0]) * (X[1] - X[0] * X[0]));
}

double Quadratic::operator ()(const Vector & x)
{
	Vector X((Vector) x);
    return(2 * X[0] * X[0] + 5 * X[0] * X[1] - X[1] * X[1]);
}
