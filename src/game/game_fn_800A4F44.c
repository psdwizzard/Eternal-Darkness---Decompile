extern float PSVECSquareMag(void);

int fn_800A4F44(float value)
{
    float square = value * value;
    float sample = PSVECSquareMag();
    int result;

    if (sample < square) {
        result = -1;
    } else if (sample > square) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
