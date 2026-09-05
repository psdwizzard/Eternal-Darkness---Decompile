typedef struct Output {
    unsigned int first;
    unsigned int second;
    float time;
} Output;

typedef struct Source {
    unsigned int pad0;
    unsigned int first;
    unsigned int pad8;
    unsigned int second;
} Source;

typedef struct Owner {
    unsigned char pad[0x28];
    Source *source;
} Owner;

extern void *memcpy(void *, const void *, unsigned int);
extern int fn_80201B54(void *);
extern float fn_80200534(int, int, int);
extern int fn_80117E58(void);
extern float fn_80200BDC(void);
extern Owner *fn_80201B8C(void *);

unsigned short fn_800BB5C4(void *output, void *object)
{
    Output result;
    float time;

    time = fn_80200534(fn_80201B54(object), -1, 0x39);
    time += fn_80200BDC() - fn_80117E58();
    if (time >= 0.0f) {
        Source *source = fn_80201B8C(object)->source;
        result.second = source->second;
        result.first = source->first;
    }
    result.time = time;
    memcpy(output, &result, sizeof(result));
    return sizeof(result);
}
