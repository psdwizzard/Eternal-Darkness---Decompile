typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

void* fn_801CC370(void* key, void* base, int count, u32 stride, s32 (*cmp)(void*, void*))
{
    long low;
    long high;
    long mid;
    long result;
    void* entry;

    if (count != 0) {
        low = 1;
        high = count;
        do {
            if ((result = cmp(key, (entry = (u8*)base + stride * ((mid = (low + high) >> 1) - 1)))) == 0) {
                return entry;
            }
            if (result < 0) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } while (low <= high);
    }
    return 0;
}
