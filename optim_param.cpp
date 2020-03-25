#include "optim_param.h"


Optim_param::Optim_param()
{
    f = new Trigonometric;
    a[0] = dom_x1;
    a[1] = dom_y1;
    b[0] = dom_x2;
    b[1] = dom_y2;
    rect = new Rect(a, b);
    initial[0] = x0;
    initial[1] = y0;
    sc = new by_difference(*f, num_iter, eps);
    m = new PRCG(2, *f, *rect, initial, *sc);
}

Optim_param::~Optim_param()
{
    delete f;
    delete rect;
    delete sc;
    delete m;
}

void Optim_param::change_func()
{
    delete f;
    switch(func_num)
    {
    case 0:
        f = new Exponential;
        break;
    case 1:
        f = new Trigonometric;
        break;
    case 2:
        f = new Rosenbrock;
        break;
    case 3:
        f = new Quadratic;
        break;
    }
}

void Optim_param::change_rect()
{
    delete rect;
    a[0] = dom_x1;
    a[1] = dom_y1;
    b[0] = dom_x2;
    b[1] = dom_y2;
    rect = new Rect(a, b);
}

void Optim_param::change_init()
{
    initial[0] = x0;
    initial[1] = y0;
}

void Optim_param::change_sc()
{
    delete sc;
    switch(sc_num)
    {
    case 0:
        sc = new by_difference(*f, num_iter, eps);
        break;
    case 1:
        sc = new by_gradient(*f, num_iter, eps);
        break;
    }
}

void Optim_param::change_method()
{
    delete m;
    switch(method_num)
    {
    case 0:
        m = new PRCG(2, *f, *rect, initial, *sc);
        break;
    case 1:
        m = new RSS(2, *f, *rect, initial, *sc, p, coef);
        break;
    }
}
