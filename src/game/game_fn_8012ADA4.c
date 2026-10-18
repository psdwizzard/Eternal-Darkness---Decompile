typedef unsigned char u8;

typedef struct Vec8012ADA4 {
    float x;
    float y;
    float z;
} Vec8012ADA4;

#define FN_80128E30_RETURN u8*
#define FN_80128E30_PARAMETERS void*
extern FN_80128E30_RETURN fn_80128E30(FN_80128E30_PARAMETERS);
extern void fn_801231D8(Vec8012ADA4*, void*, void*);
extern float fn_8012CB60(void*, int, int);
extern void PSVECScale(Vec8012ADA4*, Vec8012ADA4*, float);
extern void PSVECAdd(void*, Vec8012ADA4*, Vec8012ADA4*);
extern void fn_8012B690(void*, Vec8012ADA4*, Vec8012ADA4*);
extern float lbl_806501B0;

void fn_8012ADA4(void* owner, Vec8012ADA4* output)
{
    u8* state;
    Vec8012ADA4 value;
    float scale;

    state = fn_80128E30(owner);
    if ((*(unsigned int*)(state + 0xF4) & 0x800) != 0) {
        value = *(Vec8012ADA4*)(state + 0xE4);
    } else {
        fn_801231D8(&value, owner, *(void**)(state + 0xC8));
        scale = fn_8012CB60(owner, 15, 2);
        if (lbl_806501B0 != scale) {
            PSVECScale(&value, &value, scale);
        }
    }
    if ((*(unsigned int*)(state + 0xF4) & 0x1000) != 0) {
        PSVECAdd(owner, &value, output);
    } else {
        fn_8012B690(owner, &value, output);
    }
}
