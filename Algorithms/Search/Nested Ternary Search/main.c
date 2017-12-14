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

#define FUNC pow(x - 0.2, 2.0) + pow(x - y * y, 2.0)

int cnt = 0;

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
    ++cnt;
    return FUNC;
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
 * \param x is first variable.
 * \param y is second variable.
 * \param eps is accuracy of calculations.
 *
 * \return no value.
 */
void Nested_Ternary_Search_Min(double (*f)(double, double),
                                 double left_x, double right_x,
                                 double left_y, double right_y,
                                 double *x, double *y, double eps)
{
    double ax, bx, ay, by, f1a, f1b, f2a, f2b, y1, y2, left, right;

    ax = right_x - (right_x - left_x) / GR;
    bx = left_x + (right_x - left_x) / GR;

    left = left_y;
    right = right_y;
    
    while (right_x - left_x > eps) {
        ay = right_y - (right_y - left_y) / GR;
        by = left_y + (right_y - left_y) / GR;
        f2a = f(ax, ay);
        f2b = f(ax, by);
        
        while (right_y - left_y > eps) {
            if (f2a < f2b) {
                right_y = by;
                by = ay;
                f2b = f2a;
                ay = right_y - (right_y - left_y) / GR;
                f2a = f(ax, ay);
            } else {
                left_y = ay;
                ay = by;
                f2a = f2b;
                by = left_y + (right_y - left_y) / GR;
                f2b = f(ax, by);
            }
        }
        y1 = (left_y + right_y) / 2;

        left_y = left;
        right_y = right;
        ay = right_y - (right_y - left_y) / GR;
        by = left_y + (right_y - left_y) / GR;
        f2a = f(bx, ay);
        f2b = f(bx, by);
        
        while (right_y - left_y > eps) {
            if (f2a < f2b) {
                right_y = by;
                by = ay;
                f2b = f2a;
                ay = right_y - (right_y - left_y) / GR;
                f2a = f(bx, ay);
            } else {
                left_y = ay;
                ay = by;
                f2a = f2b;
                by = left_y + (right_y - left_y) / GR;
                f2b = f(bx, by);
            }
        }
        y2 = (left_y + right_y) / 2;

        f1a = f(ax, y1);
        f1b = f(bx, y2);
        
        if (f1a < f1b) {
            right_x = bx;
            bx = ax;
            f1b = f1a;
            ax = right_x - (right_x - left_x) / GR;
            f1a = f(ax, y1);
            *y = y1;
        } else {
            left_x = ax;
            ax = bx;
            f1a = f1b;
            bx = left_x + (right_x - left_x) / GR;
            f1b = f(bx, y2);
            *y = y2;
        }
    }
    *x = (left_x + right_x) / 2;
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
 * \param x is first variable.
 * \param y is second variable.
 * \param eps is accuracy of calculations.
 *
 * \return no value.
 */
void Nested_Ternary_Search_Max(double (*f)(double, double),
                                 double left_x, double right_x,
                                 double left_y, double right_y,
                                 double *x, double *y, double eps)
{
    double ax, bx, ay, by, f1a, f1b, f2a, f2b, y1, y2, left, right;

    ax = right_x - (right_x - left_x) / GR;
    bx = left_x + (right_x - left_x) / GR;

    left = left_y;
    right = right_y;
    
    while (right_x - left_x > eps) {
        ay = right_y - (right_y - left_y) / GR;
        by = left_y + (right_y - left_y) / GR;
        f2a = f(ax, ay);
        f2b = f(ax, by);
        
        while (right_y - left_y > eps) {
            if (f2a > f2b) {
                right_y = by;
                by = ay;
                f2b = f2a;
                ay = right_y - (right_y - left_y) / GR;
                f2a = f(ax, ay);
            } else {
                left_y = ay;
                ay = by;
                f2a = f2b;
                by = left_y + (right_y - left_y) / GR;
                f2b = f(ax, by);
            }
        }
        y1 = (left_y + right_y) / 2;

        left_y = left;
        right_y = right;
        ay = right_y - (right_y - left_y) / GR;
        by = left_y + (right_y - left_y) / GR;
        f2a = f(bx, ay);
        f2b = f(bx, by);
        
        while (right_y - left_y > eps) {
            if (f2a > f2b) {
                right_y = by;
                by = ay;
                f2b = f2a;
                ay = right_y - (right_y - left_y) / GR;
                f2a = f(bx, ay);
            } else {
                left_y = ay;
                ay = by;
                f2a = f2b;
                by = left_y + (right_y - left_y) / GR;
                f2b = f(bx, by);
            }
        }
        y2 = (left_y + right_y) / 2;

        f1a = f(ax, y1);
        f1b = f(bx, y2);
        
        if (f1a > f1b) {
            right_x = bx;
            bx = ax;
            f1b = f1a;
            ax = right_x - (right_x - left_x) / GR;
            f1a = f(ax, y1);
            *y = y1;
        } else {
            left_x = ax;
            ax = bx;
            f1a = f1b;
            bx = left_x + (right_x - left_x) / GR;
            f1b = f(bx, y2);
            *y = y2;
        }
    }
    *x = (left_x + right_x) / 2;
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
                              left_y, right_y, &x, &y, eps);
    printf("min: x=%f [%f; %f]\n"
           "     y=%f [%f; %f]\n", x, left_x, right_x, y, left_y, right_y);

    /* Nested ternary search maximum of function */
    Nested_Ternary_Search_Max(&f, left_x, right_x,
                              left_y, right_y, &x, &y, eps);
    printf("max: x=%f [%f; %f]\n"
           "     y=%f [%f; %f]\n", x, left_x, right_x, y, left_y, right_y);

    printf("%d\n", cnt);
    return 0;
    
}
