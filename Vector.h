#pragma once


/**
@class Vector
The class represents vector in R^n. It contains two fields: dimension
of space and coordinates, and some methods providing a user with
operations with vectors. Only "unique" methods are commented.
*/
class Vector
{
public:
	int dimension;
	double * coordinates;
	///Construction of vector with identical coordinates
	Vector(int _dimension, double value = 0);
	///Construction by an array and its size
	Vector(double * _coordinates, int _dimension); 
	Vector(const Vector & vector);
	~Vector() { delete[] coordinates; };
	double & operator [](int i);
	Vector operator -();
	Vector & operator =(const Vector & vector);
	Vector & operator +=(const Vector & vector);
	Vector & operator -=(const Vector & vector);
	bool operator ==(const Vector& vector);
	bool operator <=(const Vector & vector);
	friend Vector operator +(const Vector & vector1, const Vector & vector2);
	friend Vector operator -(const Vector & vector1, const Vector & vector2);
	friend Vector operator *(double lambda, const Vector & vector);
	friend Vector operator *(const Vector & vector, double lambda);
	friend Vector operator /(const Vector & vector, double lambda);
	///Left adding lambda to each coordinate of vector
	friend Vector operator +(double lambda, const Vector & vector);
	///Right adding lambda to each coordinate of vector
	friend Vector operator +(const Vector & vector, double lambda);
	///Returns square of euclidean norm
	friend double operator *(const Vector & vector1, const Vector & vector2); 
	///Returns euclidean norm
	friend double norm(const Vector & vector); 
};