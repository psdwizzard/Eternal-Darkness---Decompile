/* fn_80233EB0: one radix-2 decimation-in-frequency butterfly stage over
 * 16 complex values (interleaved re/im), followed by the two half-size
 * transforms done by fn_80234110. */

extern float lbl_8065183C;
extern float lbl_80651840;
extern float lbl_80651844;

void fn_80234110(float* data);

void fn_80233EB0(float* p) {
    float re;
    float im;
    float a;
    float b;
    float c = lbl_8065183C;
    float s = lbl_80651840;
    float r = lbl_80651844;

    a = p[30];
    b = p[14];
    re = a - b;
    im = p[31] - p[15];
    p[30] = a + b;
    p[31] = p[31] + p[15];
    p[14] = re;
    p[15] = im;

    a = p[28];
    b = p[12];
    re = a - b;
    im = p[29] - p[13];
    p[28] = a + b;
    p[29] = p[29] + p[13];
    p[12] = c * re - s * im;
    p[13] = s * re + c * im;

    a = p[26];
    b = p[10];
    re = a - b;
    im = p[27] - p[11];
    p[26] = a + b;
    p[27] = p[27] + p[11];
    p[10] = r * (re - im);
    p[11] = r * (re + im);

    a = p[24];
    b = p[8];
    re = a - b;
    im = p[25] - p[9];
    p[24] = a + b;
    p[25] = p[25] + p[9];
    p[8] = s * re - c * im;
    p[9] = s * im + c * re;

    a = p[22];
    b = p[6];
    re = a - b;
    im = p[7] - p[23];
    p[22] = a + b;
    p[23] = p[23] + p[7];
    p[6] = im;
    p[7] = re;

    a = p[4];
    b = p[20];
    re = a - b;
    im = p[5] - p[21];
    p[20] = b + a;
    p[21] = p[21] + p[5];
    p[4] = c * im + s * re;
    p[5] = s * im - c * re;

    a = p[2];
    b = p[18];
    re = a - b;
    im = p[3] - p[19];
    p[18] = b + a;
    p[19] = p[19] + p[3];
    p[2] = r * (im + re);
    p[3] = r * (im - re);

    a = p[0];
    b = p[16];
    re = a - b;
    im = p[1] - p[17];
    p[16] = b + a;
    p[17] = p[17] + p[1];
    p[0] = s * im + c * re;
    p[1] = c * im - s * re;

    fn_80234110(p);
    fn_80234110(p + 16);
}
