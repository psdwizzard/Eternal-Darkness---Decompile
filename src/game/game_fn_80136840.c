typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec3s { short x, y, z; } Vec3s;
typedef struct Vec3i { int x, y, z; } Vec3i;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Quad {
    float unk0;
    Vec3i pos;
    unsigned short idx[4];
    unsigned char unk18;
} Quad;
typedef struct QuadInfo {
    short unk0;
    unsigned char unk2;
    float x, y, z;
    float dist;
    Vec3i pos;
    float unk20;
    unsigned char unk24;
    char pad25[3];
    short unk28;
    unsigned short *indices;
    unsigned char unk30;
    int unk34;
} QuadInfo;
typedef struct Surface {
    Vec3 point;
    float pad0C, pad10;
    Vec3 normal;
    float extent;
} Surface;

extern void fn_80136610(Quad*, QuadInfo*, Vec3s*);
extern int fn_8013F078(const Vec3*, const Surface*, const void*, Result*, float);
extern float fn_80211D4C(const Vec3*, const Vec3*);
extern float lbl_806502A0;

int fn_80136840(const Vec3* point, void* object, Result* out, float radius)
{
    QuadInfo surface;
    Result candidate;
    float best = lbl_806502A0;
    int found = 0;
    unsigned char i;

    for (i = 0; i < 6; i++) {
        fn_80136610((Quad*)((char*)object + 0x30 + i * 0x1C),
                    &surface, (Vec3s*)object);
        if (fn_8013F078(point, (const Surface*)&surface, object, &candidate, radius)) {
            float distance = fn_80211D4C(point, &candidate.point);
            if (distance < best) {
                best = distance;
                found = 1;
                *out = candidate;
            }
        }
    }
    return found;
}
