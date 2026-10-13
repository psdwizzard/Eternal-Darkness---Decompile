/* fn_80234110: one radix-2 decimation-in-frequency butterfly stage over
 * 8 complex values (interleaved re/im), followed by the two half-size
 * transforms done by fn_80234248. */

extern float lbl_80651844;

void fn_80234248(float* data);

void fn_80234110(float* p) {
    float re;
    float im;
    float a;
    float b;
    float r = lbl_80651844;

    a = p[0];
    b = p[8];
    re = a - b;
    im = p[1] - p[9];
    p[8] = b + a;
    p[9] = p[9] + p[1];
    p[0] = r * (im + re);
    p[1] = r * (im - re);

    a = p[10];
    b = p[2];
    re = a - b;
    im = p[3] - p[11];
    p[10] = a + b;
    p[11] = p[11] + p[3];
    p[2] = im;
    p[3] = re;

    a = p[12];
    b = p[4];
    re = a - b;
    im = p[13] - p[5];
    p[12] = a + b;
    p[13] = p[13] + p[5];
    p[4] = r * (re - im);
    p[5] = r * (re + im);

    a = p[14];
    b = p[6];
    re = a - b;
    im = p[15] - p[7];
    p[14] = a + b;
    p[15] = p[15] + p[7];
    p[6] = re;
    p[7] = im;

    fn_80234248(p);
    fn_80234248(p + 8);
}
