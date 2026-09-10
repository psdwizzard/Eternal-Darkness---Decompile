void fn_801208CC(float* out, const float* a, const float* b)
{
    float dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];

    out[0] = dot - b[0] * a[0];
    out[1] = -(b[0] * a[1]);
    out[2] = -(b[0] * a[2]);
    out[3] = -(b[0] * a[3]);
    out[4] = -(b[1] * a[0]);
    out[5] = dot - b[1] * a[1];
    out[6] = -(b[1] * a[2]);
    out[7] = -(b[1] * a[3]);
    out[8] = -(b[2] * a[0]);
    out[9] = -(b[2] * a[1]);
    out[10] = dot - b[2] * a[2];
    out[11] = -(b[2] * a[3]);
}
