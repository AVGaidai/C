/** \file */
/*
 * Nested ternary search minimum/maximum of function by gold ratio.
 * BY GAIDAI ANATOLY
 * 2017
 */
#include <stdio.h>
#include <stdlib.h>     /* atof(); */

#include <math.h>

#define GR 1.618

#define FUNC x * x + y * y + 6 * y - 4 * x



/**
 * \brief The function under study.
 *
 * \param x is value of first variable.
 * \param y is value of second variable.
 *
 * \return value of function in the point (x; y).
 */
double f(double x, double y)
{
    return FUNC;
}


/**
 * \brief The ternary search minimum of the function.
 *
 * \param f is function under study.
 * \param left is left border of the function definition area.
 * \param right is right border of the function definition area.
 * \param eps is accuracy of calculations.
 * \param var is number of variable.
 *
 * \return the point at which the function reaches minimum.
 */
double Ternary_Search_Min(double (*f)(double, double),
                          double left, double right, double eps, int var)
{
    double a, b;
    
    if (right - left < eps) {
        return (left + right) / 2;
    }
    a = right - (right - left) / GR;
    b = left + (right - left) / GR;

    /* If (var % 2) == 0, then y = 1, else x = 1 */
    if ((var % 2) == 0) {
        if (f(a, 1) < f(b, 1)) {
            return Ternary_Search_Min(f, left, b, eps, var);
        } else {
            return Ternary_Search_Min(f, a, right, eps, var);
        }
    } else {
        if (f(1, a) < f(1, b)) {
            return Ternary_Search_Min(f, left, b, eps, var);
        } else {
            return Ternary_Search_Min(f, a, right, eps, var);
        }
    }
}


/**
 * \brief The ternary search maximum of the function.
 *
 * \param f is function under study.
 * \param left is left border of the function definition area.
 * \param right is right border of the function definition area.
 * \param eps is accuracy of calculations.
 * \param var is number of variable.
 *
 * \return the point at which the function reaches maximum.
 */
double Ternary_Search_Max(double (*f)(double, double),
                          double left, double right, double eps, int var)
{
    double a, b;
    
    if (right - left < eps) {
        return (left + right) / 2;
    }
    a = right - (right - left) / GR;
    b = left + (right - left) / GR;

    /* If (var % 2) == 0, then y = 1, else x = 1 */
    if ((var % 2) == 0) {
        if (f(a, 1) > f(b, 1)) {
            return Ternary_Search_Max(f, left, b, eps, var);
        } else {
            return Ternary_Search_Max(f, a, right, eps, var);
        }
    } else {
        if (f(1, a) > f(1, b)) {
            return Ternary_Search_Max(f, left, b, eps, var);
        } else {
            return Ternary_Search_Max(f, a, right, eps, var);
        }
    }
}


/**
 * \brief The nested ternary search minimum of the function.
 *
 * \param f is function under study.
 * \param left_x is left border of the function definition area
 *               for first variable.
 * \param right_x is right border of the function definition area
 *                for first variable.
 * \param left_y is left border of the function definition area
 *               for second variable.
 * \param right_y is right border of the function definition area
 *                for second variable.
 * \param eps is accuracy of calculations.
 * \param x is first variable.
 * \param y is second variable.
 *
 * \return no value.
 */
void Nested_Ternary_Search_Min(double (*f)(double, double),
                               double left_x, double right_x,
                               double left_y, double right_y,
                               double eps, double *x, double *y)
{
    /* Ternary search minimum function value for y = 1 */
    *x = Ternary_Search_Min(f, left_x, right_x, eps, 0);
    /* Ternary search minimum fucntion value for x = 1 */
    *y = Ternary_Search_Min(f, left_y, right_y, eps, 1);
}


/**
 * \brief The nested ternary search maximum of the function.
 *
 * \param f is function under study.
 * \param left_x is left border of the function definition area
 *               for first variable.
 * \param right_x is right border of the function definition area
 *                for first variable.
 * \param left_y is left border of the function definition area
 *               for second variable.
 * \param right_y is right border of the function definition area
 *                for second variable.
 * \param eps is accuracy of calculations.
 * \param x is first variable.
 * \param y is second variable.
 *
 * \return no value.
 */
void Nested_Ternary_Search_Max(double (*f)(double, double),
                               double left_x, double right_x,
                               double left_y, double right_y,
                               double eps, double *x, double *y)
{
    /* Ternary search maximum function value for y = 1 */
    *x = Ternary_Search_Max(f, left_x, right_x, eps, 0);
    /* Ternary search maximum function value for x = 1 */
    *y = Ternary_Search_Max(f, left_y, right_y, eps, 1);
}


/**
 * \brief Main function.
 *
 * \param arg_1 is left border of the function definition area
 *              for first variable.
 * \param arg_2 is right border of the function definition area
 *              for first variable.
 * \param arg_3 is left border of the function definition area
 *              for second variable.
 * \param arg_4 is right border of the function definition area
 *              for second variable.
 * \param arg_5 is accuracy of calculations.
 *
 * \return zero if success, else 1.
 */
int main(int argc, char *argv[])
{
    double left_x, right_x, left_y, right_y, x, y, eps;

    eps = 0.001;     /* Default accuracy */

    if (argc < 5) {
        printf("Too few argements!\n");
        return 1;
    } else {
        left_x = atof(argv[1]);
        right_x = atof(argv[2]);
        left_y = atof(argv[3]);
        right_y = atof(argv[4]);
    }

    if (argc == 6) {
        eps = atof(argv[5]);
    }

    /* Nested ternary search minimum of function */
    Nested_Ternary_Search_Min(&f, left_x, right_x,
                              left_y, right_y, eps, &x, &y);
    printf("min: x=%f [%f; %f]\n"
           "     y=%f [%f; %f]\n", x, left_x, right_x, y, left_y, right_y);

    /* Nested ternary search maximum of function */
    Nested_Ternary_Search_Max(&f, left_x, right_x,
                              left_y, right_y, eps, &x, &y);
    printf("max: x=%f [%f; %f]\n"
           "     y=%f [%f; %f]\n", x, left_x, right_x, y, left_y, right_y);

    return 0;
    
}
