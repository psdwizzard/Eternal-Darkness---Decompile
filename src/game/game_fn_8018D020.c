typedef signed short s16;

void fn_8018D020(s16* out, float x, float y, float z, float w, float t)
{
    out[0] = x;
    out[1] = y;
    out[2] = t;
    out[3] = z;
    out[4] = y;
    out[5] = t;
    out[6] = z;
    out[7] = w;
    out[8] = t;
    out[9] = x;
    out[10] = w;
    out[11] = t;
}
