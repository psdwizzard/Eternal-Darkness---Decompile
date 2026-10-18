typedef struct Vec3 { float x, y, z; } Vec3;

extern float PSVECSquareDistance(const Vec3*, const Vec3*);
extern float PSVECDotProduct(const Vec3*, const Vec3*);

unsigned char fn_8013D618(const Vec3* first, const Vec3* second,
                          float radius, float threshold,
                          const Vec3* direction)
{
    if (PSVECSquareDistance(first, second) < radius * radius) {
        return PSVECDotProduct(first, direction) > threshold;
    }
    return 0;
}
