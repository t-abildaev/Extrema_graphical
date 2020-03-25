#include "Rect.h"


Rect::Rect(Vector _a, Vector _b) :
	a(_a), b(_b) {}

Rect::Rect(double * _a, double * _b, int dimension) :
	a(_a, dimension), b(_b, dimension) {}

bool Rect::is_in_rect(const Vector & vector)
{
	return(a <= vector && (Vector) vector <= b);
}

double Rect::how_far(const Vector & vector, const Vector & direction)
{
    double temp = 0;
    double alpha = 0;

    if (direction.coordinates[0] > 0)
        alpha = (b[0] - vector.coordinates[0]) / direction.coordinates[0];
    else if (direction.coordinates[0] < 0)
        alpha = (a[0] - vector.coordinates[0]) / direction.coordinates[0];

    for (int i = 1; i < a.dimension; ++i)
    {
        if (direction.coordinates[i] > 0)
        {
            temp = (b[i] - vector.coordinates[i]) / direction.coordinates[i];
            if (temp < alpha)
                alpha = temp;
        }
        else if (direction.coordinates[i] < 0)
        {
            temp = (a[i] - vector.coordinates[i]) / direction.coordinates[i];
            if (temp < alpha)
                alpha = temp;
        }
    }
    return(alpha);
}

double Rect::min_length()
{
	double temp = 0;
	double value = b[0] - a[0];
	for (int i = 1; i < a.dimension; ++i)
	{
		temp = b[i] - a[i];
		if (value < temp) value = temp;
	}
	return(value);
}
