typedef struct Message {
    unsigned int value;
    float time;
} Message;

typedef struct Source {
    unsigned char pad[4];
    unsigned int value;
} Source;

typedef struct Owner {
    unsigned char pad[0x34];
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

unsigned short fn_800BBAF0(void *output, void *object)
{
    Message result;
    float time;

    time = fn_80200534(fn_80201B54(object), -1, 0x39);
    time += fn_80200BDC() - fn_80117E58();
    if (time >= lbl_8064F010) {
        result.value = fn_80201B8C(object)->source->value;
    }
    result.time = time;
    memcpy(output, &result, sizeof(result));
    return sizeof(result);
}
