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
