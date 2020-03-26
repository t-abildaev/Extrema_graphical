#include "Method.h"


Method::Method(int _dimension, Function & _function, Rect & _rect, Vector _initial, StopCriterion & _stopCriterion) :
    total_iter(0), dimension(_dimension), function(_function), rect(_rect), initial(_initial), stopCriterion(_stopCriterion) {}

RSS::RSS(int _dimension, Function & _function, Rect & _rect, Vector _initial, StopCriterion & _stopCriterion) :
    Method(_dimension, _function, _rect, _initial, _stopCriterion)
{
    mtinit(std::chrono::system_clock::now().time_since_epoch().count());
}

RSS::RSS(int _dimension, Function & _function, Rect & _rect, Vector _initial, StopCriterion & _stopCriterion, double _p, double _delta) :
    Method(_dimension, _function, _rect, _initial, _stopCriterion)
{
    mtinit(std::chrono::system_clock::now().time_since_epoch().count());
	p = _p;
	delta = _delta;
}

void RSS::optimize()
{
	double rand = 0;
    double r = 0.5 * rect.min_length();
    Vector a = rect.get_a();
    Vector b = rect.get_b();

	Vector x_current(initial);
	Vector x_previous(dimension);
	Vector x_next(dimension);
    if (x_current == a) x_previous = b;
	else x_previous = a;

	double value_current = function(x_current);
	double value_next = 0;

	Vector left = x_current - delta * r;
	Vector right = x_current + delta * r;
	for (int i = 0; i < dimension; ++i)
	{
		if (a[i] > left[i]) left[i] = a[i];
		if (b[i] < right[i]) right[i] = b[i];
	}

	while (!(stopCriterion.if_stop(x_current, x_previous)))
	{
        xPath.push_back(x_current[0]);
        yPath.push_back(x_current[1]);

		rand = mtunif();
		if (rand < p)
			for (int j = 0; j < dimension; ++j)
				x_next[j] = (right[j] - left[j]) * mtunif() + left[j];
		else
			for (int j = 0; j < dimension; ++j)
				x_next[j] = (b[j] - a[j]) * mtunif() + a[j];
		value_next = function(x_next);

		if (value_current > value_next)
		{
			x_previous = x_current;
			x_current = x_next;
			value_current = value_next;
			if (rand < p)
			{
                delta *= 0.5;
				left = x_current - delta * r;
				right = x_current + delta * r;
				for (int i = 0; i < dimension; ++i)
				{
					if (a[i] > left[i]) left[i] = a[i];
					if (b[i] < right[i]) right[i] = b[i];
				}
			}
		}

        ++total_iter;
	}

    xPath.push_back(x_current[0]);
    yPath.push_back(x_current[1]);
}

PRCG::PRCG(int _dimension, Function & _function, Rect & _rect, Vector _initial, StopCriterion & _stopCriterion) :
    Method(_dimension, _function, _rect, _initial, _stopCriterion) {}

Vector PRCG::dir_search_II(const Vector & vector, const Vector & direction, double Left, double Right)
{
    double left = Left;
    double right = Right;
    double _left = right - (right - left) / PHI;
    double _right = left + (right - left) / PHI;
    double f_left = function(vector + _left * direction);
    double f_right = function(vector + _right * direction);

    while (std::abs(right - left) > EPS)
    //while (abs(right - left) * norm(direction) > EPS)
    {
        if (f_left < f_right)
        {
            right = _right;
            _right = _left;
            f_right = f_left;
            _left = right - (right - left) / PHI;
            f_left = function(vector + _left * direction);
        }
        else
        {
            left = _left;
            _left = _right;
            f_left = f_right;
            _right = left + (right - left) / PHI;
            f_right = function(vector + _right * direction);
        }
    }

    return(vector + 0.5 * (left + right) * direction);
}

Vector PRCG::dir_search_I(const Vector & vector, const Vector & direction, double lambda, int n)
{
    double temp = 0;
    Vector temp_vect(dimension);
    double step = lambda / n;

    Vector vect = dir_search_II(vector, direction, 0, step);
    double value = function(vect);
    for (int i = 1; i < n; ++i)
    {
        temp_vect = dir_search_II(vector, direction, i * step, (i + 1) * step);
        temp = function(temp_vect);
        if (temp < value)
        {
            value = temp;
            vect = temp_vect;
        }
    }

    return(vect);
}

void PRCG::optimize()
{
    double alpha = 0;
    Vector a = rect.get_a();
    Vector b = rect.get_b();

	Vector x_current(initial);
	Vector x_previous(dimension);
    if (x_current == a) x_previous = b;
	else x_previous = a;

    Vector grad_current(function.gradient(x_current, EPS));
    Vector direction = -grad_current;
    Vector grad_previous(dimension);

	while (!(stopCriterion.if_stop(x_current, x_previous)))
	{
        xPath.push_back(x_current[0]);
        yPath.push_back(x_current[1]);

        alpha = rect.how_far(x_current, direction);

        x_previous = x_current;
        x_current = dir_search_I(x_current, direction, alpha);

        grad_previous = grad_current;
        grad_current = function.gradient(x_current, EPS);

        alpha = (grad_current * (grad_current - grad_previous)) / (grad_previous * grad_previous);
        direction = -grad_current + alpha * direction;

        ++total_iter;
    }
}
