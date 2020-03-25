#pragma once

#include <cmath>
#include "Vector.h"
#include "Function.h"


/**
@class StopCriterion
The class is an abstract class. It represents abstract stop criterion
of optimization process and should be the parent class for class which
represents specific stop criterion.
*/
class StopCriterion
{
protected:    
	Function & function;
    ///This constant determines exactness of calculating gradient
    const double EPS = 1e-6;
    ///Maximum number of iterations of optimization process
    int num_of_iter = 1000;
    ///This constant determines exactness of optimization
    double eps = 0.001;
public:
    StopCriterion(Function & _function, int _num_of_iter, double _eps);
	virtual ~StopCriterion() {};
	virtual bool if_stop(const Vector & x_current, const Vector & x_previous) = 0; ///This method indicates if optimization process should be stopped
};

/**
@class StopCriterion
The class represents stop criterion that initiates stop if norm
of gradient of function becomes small enough.
*/
class by_gradient : public StopCriterion
{
public:
    by_gradient(Function & _function, int _num_of_iter, double _eps);
	~by_gradient() {};
	bool if_stop(const Vector & x_current, const Vector & x_previous) override;
};

/**
@class StopCriterion
The class represents stop criterion that initiates stop if absolute
difference between value of function in previous vector and value of
function in current vector becomes small enough.
*/
class by_difference : public StopCriterion
{
public:
    by_difference(Function & _function, int _num_of_iter, double _eps);
	~by_difference() {};
	bool if_stop(const Vector & x_current, const Vector & x_previous) override;
};
