typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void fn_80211484(void*, float, float, float);

void fn_8012E42C(int* initialized, Vec3 value, void* matrix)
{
    if (*initialized == 0) {
        fn_80211484(matrix, value.x, value.y, value.z);
    } else {
        *(float*)((char*)matrix + 0xC) = value.x;
        *(float*)((char*)matrix + 0x1C) = value.y;
        *(float*)((char*)matrix + 0x2C) = value.z;
    }
    *initialized = 1;
}
