#pragma once

#include <chrono>
#include <vector>
#include "Vector.h"
#include "Rect.h"
#include "Function.h"
#include "StopCriterion.h"
#include "Random.h"


/**
@class Method
The class is an abstract class. It represents abstract optimization
method and should be the parent class for class which represents
specific method.
*/
class Method
{
protected:
	///This constant determines closeness of two numbers and exactness of calculating gradient
	const double EPS = 1e-6;
    int total_iter;
	///Dimension of domain of the function
    int dimension;
	///Function to be optimized
	Function & function;
	///Rectangle where the function is optimized
    Rect & rect;
	///Initial guess for optimization process
	Vector initial;
	///Stop criterion for optimization process
	StopCriterion & stopCriterion; 
public:
    Method(int _dimension, Function & _function, Rect & _rectangle, Vector _initial, StopCriterion & _stopCriterion);
    virtual ~Method() {};
	///This method optimizes the function and prints the results
	virtual void optimize() = 0; 

    int get_total_iter() { return(total_iter); };
    std::vector <double> xPath;
    std::vector <double> yPath;
};

/**
@class Method
The class represents Random Search (Simple) method of optimization.
Next vector is being searched in small neighbourhood of current vector
(with probability p) or in the whole area (with probability 1 - p).
Delta determines the smallness of neighbourhood and decreases if search
in neighbourhood were succesfull.
*/
class RSS :
	public Method
{
protected:
	///Must be in (0,1)
	double p = 0.5;
	///Must be in (0,1)
	double delta = 0.25;
public:
    RSS(int _dimension, Function & _function, Rect & _rect, Vector _initial, StopCriterion & _stopCriterion);
    RSS(int _dimension, Function & _function, Rect & _rect, Vector _initial, StopCriterion & _stopCriterion, double _p, double delta);
	void optimize();
};

/**
@class Method
The class represents Polak-Ribiere Conjugate Gradient method of
optimization.
*/
class PRCG :
	public Method
{
protected:
    const double PHI = 0.5 * (1 + sqrt(5));
public:
    PRCG(int _dimension, Function & _function, Rect & _rect, Vector _initial, StopCriterion & _stopCriterion);
    Vector dir_search_II(const Vector & vector, const Vector & direction, double Left, double Right);
    Vector dir_search_I(const Vector & vector, const Vector & direction, double lambda, int n = 3);
    void optimize();
};
