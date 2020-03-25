#pragma once

#include "Vector.h"

/**
@class Function
The class is an abstract class. It represents abstract multivariable
function and should be the parent class for class which
represents specific function.
*/
class Function
{
public:
	Function() {};
	virtual ~Function() {};
	virtual double operator () (const Vector & x) = 0;
	Vector gradient(const Vector & x, double h);
};


/**
@class Exponential
The class represents function f(x,y) = exp(x) + exp(y).
*/
class Exponential : public Function
{
public:
	Exponential() {};
	~Exponential() {};
	double operator ()(const Vector & x) override;
};


/**
@class Trigonometric
The class represents function f(x,y) = sin(x) + cos(y).
*/
class Trigonometric : public Function
{
public:
	Trigonometric() {};
	~Trigonometric() {};
	double operator ()(const Vector & x) override;
};

/**
@class Rosenbrock
The class represents function f(x,y,z) = (1 - x)^2 + 100(y - x^2)^2.
*/
class Rosenbrock : public Function
{
public:
	Rosenbrock() {};
	~Rosenbrock() {};
	double operator ()(const Vector & x) override;
};

/**
@class Quadratic
The class represents function f(x,y,z,t) = 2x^2 + 5xy - y^2.
*/
class Quadratic : public Function
{
public:
	Quadratic() {};
	~Quadratic() {};
	double operator ()(const Vector & x) override;
};
