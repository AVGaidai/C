#include <math.h>

/** 
 * The data type for representing a complex number
 * Re -- real part (OX);
 * Im -- image part (OY);
 */
typedef struct {

    double Re;
    double Im;

} Complex_Num;

/** 
 * Division function for complex numbers
 * 
 * \param {
 * A -- dividend: A = x1 + i*y1;
 * B -- divisor: B = x2 + i*y2;
 * }
 *
 * \return {
 * C -- quotient: C = A / B = (x1*x2 + y1*y2) / (x2^2 + y2^2) +
 *                            i*((y1*x2 - x1*y2) / (x2^2 + y2^2))
 * }
*/
Complex_Num cn_div(Complex_Num A, Complex_Num B)
{
    return (Complex_Num) {
        .Re = (A.Re * B.Re + A.Im * B.Im) / 
              (pow(B.Re, 2.0) + pow(B.Im, 2.0)),
        .Im = (A.Im * B.Re - A.Re * B.Im) /
              (pow(B.Re, 2.0) + pow(B.Im, 2.0))
    };
}

