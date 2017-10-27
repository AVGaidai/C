/** \file */
/*
 * Ternary search minimum/maximum of function by gold ratio.
 * BY GAIDAI ANATOLY
 * 2017
 */
#include <stdio.h>
#include <stdlib.h>     /* atof(); */

#include <math.h>

#define GR 1.618

#define FUNC sin(x)



/**
 * \brief The function under study.
 *
 * \param x is value of variable.
 *
 * \return value of function in the point x.
 */
double f(double x)
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
 *
 * \return the point at which the function reaches minimum.
 */
double Ternary_Search_Min(double (*f)(double),
                          double left, double right, double eps)
{
    double a, b;
    
    if (right - left < eps) {
        return (left + right) / 2;
    }
    a = right - (right - left) / GR;
    b = left + (right - left) / GR;

    if (f(a) < f(b)) {
        return Ternary_Search_Min(f, left, b, eps);
    } else {
        return Ternary_Search_Min(f, a, right, eps);
    }
}



/**
 * \brief The ternary search maximum of the function.
 *
 * \param f is function under study.
 * \param left is left border of the function definition area.
 * \param right is right border of the function definition area.
 * \param eps is accuracy of calculations.
 *
 * \return the point at which the function reaches maximum.
 */
double Ternary_Search_Max(double (*f)(double),
                          double left, double right, double eps)
{
    double a, b;
    
    if (right - left < eps) {
        return (left + right) / 2;
    }
    a = right - (right - left) / GR;
    b = left + (right - left) / GR;

    if (f(a) > f(b)) {
        return Ternary_Search_Max(f, left, b, eps);
    } else {
        return Ternary_Search_Max(f, a, right, eps);
    }
}



/**
 * \brief Main function.
 *
 * \param arg_1 is left border of the function definition area.
 * \param arg_2 is right border of the function definition area.
 * \param arg_3 is accuracy of calculations.
 *
 * \return zero if success.
 */
int main(int argc, char *argv[])
{
    double left, right, eps;

    eps = 0.001;     /* Default accuracy */

    if (argc < 3) {
        printf("Too few argements!\n");
        return 1;
    } else {
        left = atof(argv[1]);
        right = atof(argv[2]);
    }

    if (argc == 4) {
        eps = atof(argv[3]);
    }
    
    printf("min[%f, %f]: %f\n",
           left, right, Ternary_Search_Min(&f, left, right, eps));

    printf("max[%f, %f]: %f\n",
           left, right, Ternary_Search_Max(&f, left, right, eps));
    
    return 0;
    
}
