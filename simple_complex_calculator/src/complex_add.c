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
