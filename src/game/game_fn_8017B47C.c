typedef unsigned char u8;

extern int CARDProbeEx(int, int*, int*);

int fn_8017B47C(int value, int* primary_value, int* primary_level)
{
    u8 attempt = 0;
    int result;

    while (attempt < 100) {
        result = CARDProbeEx(value, primary_value, primary_level);
        if (result == 0) {
            break;
        }
        attempt++;
    }

    return result;
}
