/* _book_maptype1_quantvals: libvorbis _book_maptype1_quantvals. Returns the largest
 * integer vals with vals^dim <= entries, starting from floor(pow(entries, 1/dim)). */

extern double pow(double x, double y); /* pow */
extern double floor(double x);           /* floor */

typedef struct StaticCodebook {
    long dim;
    long entries;
} StaticCodebook;

long _book_maptype1_quantvals(StaticCodebook* b) {
    float exponent;
    long vals;
    long dim;
    long entries;
    int i;
    long acc;
    long acc1;

    exponent = 1.0f / (float)b->dim;
    vals = floor(pow((float)b->entries, exponent));
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
