#include "StopCriterion.h"


StopCriterion::StopCriterion(Function & _function, int _num_of_iter, double _eps) :
    function(_function), num_of_iter(_num_of_iter), eps(_eps) {}

by_gradient::by_gradient(Function & _function, int _num_of_iter, double _eps) :
    StopCriterion(_function, _num_of_iter, _eps) {}

bool by_gradient::if_stop(const Vector & x_current, const Vector & x_previous)
{
    if (num_of_iter == 0 || std::abs(norm(function.gradient(x_current, EPS))) < eps)
		return(true);
	--num_of_iter;
	return(false);
}

by_difference::by_difference(Function & _function, int _num_of_iter, double _eps) :
    StopCriterion(_function, _num_of_iter, _eps) {}

bool by_difference::if_stop(const Vector & x_current, const Vector & x_previous)
{
    if (num_of_iter == 0 || std::abs(function(x_current) - function(x_previous)) < eps)
		return(true);
	--num_of_iter;
	return(false);
}
