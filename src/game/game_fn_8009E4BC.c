typedef unsigned char u8;
typedef signed short s16;

typedef struct Entry8009E4BC {
    u8 field_00;
    u8 pad01[0x2B];
} Entry8009E4BC;

typedef struct State8009E4BC {
    u8 pad00[0x18];
    u8 pad18[0x50];
    Entry8009E4BC entries[1];
} State8009E4BC;

typedef struct Context8009E4BC {
    u8 pad00[8];
    s16 counter;
} Context8009E4BC;

typedef struct Inner8009E4BC {
    u8 pad00[0x44];
    void* object;
} Inner8009E4BC;

typedef struct Global8009E4BC {
    u8 pad00[0x8C];
    Inner8009E4BC* inner;
} Global8009E4BC;

extern void *fn_8006ED3C();
extern void fn_801EFE84(int);
extern void fn_8006DEF8(State8009E4BC*, int, void*, void*, int);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a,b,c,d,e) fn_8020104C((int)(a),(void*)(b),(void*)(c),(int)(d),(float)(e))
extern void* fn_80036D38(void*);
extern void fn_802020B4(void*, int);
extern void fn_801A5C30(int);
extern const float lbl_8064EDC0;

int fn_8009E4BC(register State8009E4BC* state)
{
    register unsigned long state_r = (unsigned long)state;
    int index;
    Context8009E4BC* context;
    int result;
    int i;

    result = 0;
    context = fn_8006ED3C((State8009E4BC*)state_r, 0x16, &index);

    if (context != 0) {
        if (context->counter == 0) {
            fn_801EFE84(0);
        }
        context->counter++;
        if (context->counter >= 50) {
            for (i = 0; i < 3; i++) {
                ((State8009E4BC*)state_r)->entries[index].field_00 = i;
                fn_8006DEF8((State8009E4BC*)state_r, 0x16, 0, 0, 0);
            }
            {
                void* object = fn_80201814(*(void**)((u8*)state_r + 0x38));
                fn_8020104C(0x51, 0, ((Global8009E4BC*)fn_80201B8C())->inner->object, 0, lbl_8064EDC0);
                fn_802020B4(fn_80201814(*(void**)((u8*)fn_80036D38(object) + 0x44)), 0);
            }
            fn_801A5C30(0);
            result = 1;
        }
    }
    return result;
}
