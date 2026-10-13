/* fn_80235B10: libvorbis _book_maptype1_quantvals. Returns the largest
 * integer vals with vals^dim <= entries, starting from floor(pow(entries, 1/dim)). */

extern double fn_801023A0(double x, double y); /* pow */
extern double fn_80101A5C(double x);           /* floor */

typedef struct StaticCodebook {
    long dim;
    long entries;
} StaticCodebook;

long fn_80235B10(StaticCodebook* b) {
    float exponent;
    long vals;
    long dim;
    long entries;
    int i;
    long acc;
    long acc1;

    exponent = 1.0f / (float)b->dim;
    vals = fn_80101A5C(fn_801023A0((float)b->entries, exponent));
    dim = b->dim;
    entries = b->entries;
    for (;;) {
        i = 0;
        acc = 1;
        acc1 = 1;
        while (i < dim) {
            acc *= vals;
            acc1 *= vals + 1;
            i++;
        }
        if (acc <= entries && acc1 > entries) {
            break;
        }
        if (acc > entries) {
            vals--;
        } else {
            vals++;
        }
    }
    return vals;
}
