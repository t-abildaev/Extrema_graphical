#include <cmath>
#include "Vector.h"


Vector::Vector(int _dimension, double value) :
	dimension(_dimension)
{
	coordinates = new double[dimension];
	for (int i = 0; i < dimension; ++i)
		coordinates[i] = value;
}

Vector::Vector(double * _coordinates, int _dimension) :
	dimension(_dimension)
{
	coordinates = new double[dimension];
	for (int i = 0; i < dimension; ++i)
		coordinates[i] = _coordinates[i];
}

Vector::Vector(const Vector & vector) :
	Vector(vector.coordinates, vector.dimension) {}

double & Vector::operator [](int i)
{
	return(coordinates[i]);
}

Vector Vector::operator -()
{
	Vector vector(dimension);
	for (int i = 0; i < dimension; ++i)
		vector.coordinates[i] = -(*this)[i];
	return(vector);
}

Vector & Vector::operator =(const Vector & vector)
{
	if (dimension == vector.dimension)
		for (int i = 0; i < dimension; ++i)
			coordinates[i] = vector.coordinates[i];
	return(*this);
}

Vector & Vector::operator +=(const Vector & vector)
{
	if (dimension == vector.dimension)
		for (int i = 0; i < dimension; ++i)
			coordinates[i] += vector.coordinates[i];
	return(*this);
}

Vector & Vector::operator -=(const Vector & vector)
{
	if (dimension == vector.dimension)
		for (int i = 0; i < dimension; ++i)
			coordinates[i] -= vector.coordinates[i];
	return(*this);
}

bool Vector::operator ==(const Vector& vector)
{
	if (dimension == vector.dimension)
		for (int i = 0; i < dimension; ++i)
			if (coordinates[i] != vector.coordinates[i])
				return(false);
	return(true);
}

bool Vector::operator <=(const Vector & vector)
{
	if (dimension == vector.dimension)
		for (int i = 0; i < dimension; ++i)
			if (coordinates[i] > vector.coordinates[i])
				return(false);
	return(true);
}

Vector operator +(const Vector & vector1, const Vector & vector2)
{
	Vector vector = vector1;
	return(vector += vector2);
}

Vector operator -(const Vector & vector1, const Vector & vector2)
{
	Vector vector = vector1;
	return(vector -= vector2);
}

Vector operator *(double lambda, const Vector & vector)
{
	Vector _vector = vector;
	for (int i = 0; i < _vector.dimension; ++i)
		_vector.coordinates[i] *= lambda;
	return(_vector);
}

Vector operator *(const Vector & vector, double lambda)
{
	Vector _vector = vector;
	for (int i = 0; i < _vector.dimension; ++i)
		_vector.coordinates[i] *= lambda;
	return(_vector);
}

Vector operator /(const Vector & vector, double lambda)
{
	Vector _vector = vector;
	for (int i = 0; i < _vector.dimension; ++i)
		_vector.coordinates[i] /= lambda;
	return(_vector);
}

Vector operator +(double lambda, const Vector& vector)
{
	Vector _vector = vector;
	for (int i = 0; i < _vector.dimension; ++i)
		_vector.coordinates[i] += lambda;
	return(_vector);
}

Vector operator +(const Vector& vector, double lambda)
{
	Vector _vector = vector;
	for (int i = 0; i < _vector.dimension; ++i)
		_vector.coordinates[i] += lambda;
	return(_vector);
}

double operator *(const Vector & vector1, const Vector & vector2)
{
	double sum = 0;
	if (vector1.dimension == vector2.dimension)
		for (int i = 0; i < vector1.dimension; ++i)
			sum += vector1.coordinates[i] * vector2.coordinates[i];
	return(sum);
}

double norm(const Vector & vector)
{
	double sum = 0;
	for (int i = 0; i < vector.dimension; ++i)
		sum += vector.coordinates[i] * vector.coordinates[i];
	return(sqrt(sum));
}
