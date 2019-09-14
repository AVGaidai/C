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
