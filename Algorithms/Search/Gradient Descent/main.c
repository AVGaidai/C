#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FUNC pow(x1 - 0.2, 2.0) +  pow(x1 - x2 * x2, 2.0)

double foo(double x1, double x2)
{
    return FUNC;
}

int main(int argc, char *argv[])
{
    double x1, x2;
    double step = 1.0, eps = 0.001;
    double inc_x = 0.05, inc_f1, inc_f2;
    double S1, S2;

    int i = 0;

    
    if (argc >= 2) {
        step = atof(argv[1]);
    }

    if (argc >= 3) {
        inc_x = atof(argv[2]);
    }
    
    if (argc >= 4) {
        eps = atof(argv[3]);
    }

    printf("Please, input start coordinates:\n x1=");
    scanf("%lf", &x1);
    printf(" x2=");
    scanf("%lf", &x2);

    while (step > eps) {
        inc_f1 = foo(x1 + inc_x, x2) - foo(x1, x2);
        inc_f2 = foo(x1, x2 + inc_x) - foo(x1, x2);

        /* printf("inc: %f %f\n", inc_f1, inc_f2); */
        S1 = 0 - inc_f1 / sqrt(pow(inc_f1, 2.0) + pow(inc_f2, 2.0));
        S2 = 0 - inc_f2 / sqrt(pow(inc_f1, 2.0) + pow(inc_f2, 2.0));
    
        printf("%f %f %f %f %f\n", x1, x2, S1, S2, foo(x1, x2));

        if (inc_f1 < 0 || inc_f2 < 0) {
            step /= 2;
        }
        
        x1 = x1 + step * S1;
        x2 = x2 + step * S2;
    }
    
    return 0;
}
