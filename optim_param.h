#pragma once

#include "Vector.h"
#include "Rect.h"
#include "Function.h"
#include "StopCriterion.h"
#include "Method.h"


class Optim_param
{
public:
    int func_num = 0;
    double dom_x1 = -1;
    double dom_x2 = 1;
    double dom_y1 = -1;
    double dom_y2 = 1;
    double x0 = 0;
    double y0 = 0;
    int sc_num = 0;
    double eps = 1e-6;
    int method_num = 0;
    int num_iter = 1000;
    double p = 0.5;
    double coef = 0.25;

    Function * f;
    Vector a = Vector(2);
    Vector b = Vector(2);
    Rect * rect;
    Vector initial = Vector(2);
    StopCriterion * sc;
    Method * m;

    Optim_param();
    ~Optim_param();
    void change_func();
    void change_rect();
    void change_init();
    void change_sc();
    void change_method();
};
