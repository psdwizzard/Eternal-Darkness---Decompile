typedef struct Message {
    unsigned int first;
    unsigned int second;
    float time;
    unsigned char byte;
    unsigned char pad[3];
} Message;

typedef struct Source {
    unsigned char pad[4];
    unsigned int first;
    unsigned int second;
    unsigned char padC[6];
    unsigned char byte;
} Source;

typedef struct Owner {
    unsigned char pad[0x30];
    Source *source;
} Owner;

extern void *memcpy(void *, const void *, unsigned int);
extern int fn_80201B54(void *);
extern float fn_80200534(int, int, int);
extern int fn_80117E58(void);
extern float fn_80200BDC(void);
extern Owner *fn_80201B8C(void *);
extern const float lbl_8064F010;
extern const double lbl_8064F020;

unsigned short fn_800BB9A4(void *output, void *object)
{
    Message result;
    float time;

    time = fn_80200534(fn_80201B54(object), -1, 0x39);
    time += fn_80200BDC() - fn_80117E58();
    if (time > lbl_8064F010) {
        Source *source = fn_80201B8C(object)->source;
        result.first = source->first;
        result.second = source->second;
        result.byte = source->byte;
    }
    result.time = time;
    memcpy(output, &result, sizeof(result));
    return sizeof(result);
}
