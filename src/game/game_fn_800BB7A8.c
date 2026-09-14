typedef struct Vector {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} Vector;

typedef struct Message {
    unsigned int first;
    unsigned int second;
    float time;
    unsigned char padC[4];
    Vector vector;
    unsigned char byte;
    unsigned char pad1D[3];
} Message;

typedef struct Source {
    unsigned char byte;
    unsigned char pad1[0xB];
    unsigned int first;
    unsigned int second;
    signed short value;
    unsigned char pad16[0xE];
    Vector vector;
} Source;

typedef struct Owner {
    unsigned char pad[0x2C];
    Source *source;
} Owner;

extern void *memcpy(void *, const void *, unsigned int);
extern int fn_80201B54();
extern float fn_80200534(void *, int, int);
extern int fn_80117E58(void);
extern float fn_80200BDC(void);
extern void *fn_80201B8C();
extern float lbl_8064F010;
extern double lbl_8064F020;

unsigned short fn_800BB7A8(void *output, void *object)
{
    Message result;
    float time;

    time = fn_80200534(((void *)fn_80201B54(object)), -1, 0x39);
    time += fn_80200BDC() - fn_80117E58();
    if (time >= lbl_8064F010) {
        Source *source = ((Owner *)fn_80201B8C(object))->source;
        result.first = source->first;
        result.second = source->second;
        *(signed short *)&result.padC[0] = source->value;
        result.vector = source->vector;
        result.byte = source->byte;
    }
    result.time = time;
    memcpy(output, &result, sizeof(result));
    return sizeof(result);
}
