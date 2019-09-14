#include <stdio.h>

#include "include/complex_num.h"

int main(void)
{
    Complex_Num A, B, C;

    printf("\E[H\E[2J");
    printf( "Enter the first complex number "
            "as a pair of numbers with a space:\n> " );
    scanf("%lf %lf", &A.Re, &A.Im);

    printf( "Enter the second complex number "
            "as a pair of numbers with a space:\n> " );
    scanf("%lf %lf", &B.Re, &B.Im);

    int act = 0;


    printf( "Select action:\n"
            "1) Addition\n"
            "2) Subtraction\n"
            "3) Multiplication\n"
            "4) Devision\n"
            "0) Nothing\n\n"      );
    do {
        printf("> ");
        scanf("%d", &act);
        switch (act) {
            case 1:
                printf("A + B = C\n");
                C = cn_add(A, B);
                break;
            case 2:
                printf("A - B = C\n");
                C = cn_sub(A, B);
                break;
            case 3:
                printf("A * B = C\n");
                C = cn_mul(A, B);
                break;
            case 4:
                printf("A / B = C\n");
                C = cn_div(A, B);
                break;
            case 0:
            default:
                break;
        }
    } while (act < 0 || act > 4);
    
    if (act) {
        printf("A = (%.2lf) + i*(%.2lf)\n", A.Re, A.Im);
        printf("B = (%.2lf) + i*(%.2lf)\n", B.Re, B.Im);
        printf("C = (%.2lf) + i*(%.2lf)\n", C.Re, C.Im);
    }
}
