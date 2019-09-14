#ifndef COMPLEX_NUM
#define COMPLEX_NUM

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
Complex_Num cn_add(Complex_Num, Complex_Num);

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
Complex_Num cn_sub(Complex_Num, Complex_Num);

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
Complex_Num cn_mul(Complex_Num, Complex_Num);

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
Complex_Num cn_div(Complex_Num, Complex_Num);

#endif
