/** \file */
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
 * Addition function for complex numbers
 * 
 * \param {
 * A -- first addend: A = x1 + i*y1;
 * B -- second addend: B = x2 + i*y2;
 * }
 *
 * \return {
 * C -- sum: C = A + B = (x1 + x2) + i*(y1 + y2)
 * }
 */
Complex_Num cn_add(Complex_Num A, Complex_Num B)
{
    return (Complex_Num) {
        .Re = A.Re + B.Re,
        .Im = A.Im + B.Im
    };
}

/** 
 * Subtraction function for complex numbers
 * 
 * \param {
 * A -- minuend: A = x1 + i*y1;
 * B -- subtrahend: B = x2 + i*y2;
 * }
 *
 * \return {
 * C -- difference: C = A - B = (x1 - x2) + i*(y1 - y2)
 * }
*/
Complex_Num cn_sub(Complex_Num A, Complex_Num B)
{
    return (Complex_Num) {
        .Re = A.Re - B.Re,
        .Im = A.Im - B.Im
    };
}


/** 
 * Multiplication function for complex numbers
 * 
 * \param {
 * A -- multiplicand: A = x1 + i*y1;
 * B -- multiplier: B = x2 + i*y2;
 * }
 *
 * \return {
 * C -- product: C = A * B = (x1*x2 - y1*y2) + i*(y1*x2 + x1*y2)
 * }
*/
Complex_Num cn_mul(Complex_Num A, Complex_Num B)
{
    return (Complex_Num) {
        .Re = A.Re * B.Re - A.Im * B.Im,
        .Im = A.Im * B.Re + A.Re * B.Im
    };
}


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

