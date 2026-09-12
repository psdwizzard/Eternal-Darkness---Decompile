typedef unsigned char u8;
typedef unsigned short u16;

extern void *fn_80156938(void*);
extern void *fn_80201BC8(void*);
extern int fn_801990E8(void*);
extern int fn_8012FAB4(void*, int);
extern void* fn_80201C24(void*);
extern int fn_80157894(void);
extern void fn_80157B6C(void*, int);
extern void fn_80199154(void*, int);
extern void fn_80199164(void*, int);
extern u8 fn_801990E0(void*);
extern void fn_8019915C(void*, int);
extern void fn_80199174(void*, int);
extern int fn_801990F0(void*);
extern int fn_80199110(void*);
extern int fn_80199108(void*);
extern int fn_8017FEA4(void*);
extern u8 fn_80199118(void*);
extern int fn_80199100(void*);
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern void* fn_8017FDA8(void*, int);
extern void fn_801534D8(void*, float, short*);
extern void fn_8019916C(void*, int);
extern u8 fn_801990F8(void*);

void fn_801535D8(void* object, void* other)
{
    void* runtime;
    int count;
    void* other_owner = 0;
    void* other_state = 0;
    int active;
    int value;
    u16 masked_count;
    u8 bits;
    float fraction;

    runtime = *(void**)((u8*)fn_80156938(object) + 0x88);

    if (other != 0 && (other_state = fn_80156938(other)) != 0) {
        other_owner = fn_80201BC8(other_state);
    }
    if (fn_801990E8(runtime) == 0) {
      if (other_owner != 0) {
       if (fn_8012FAB4(other_owner, 15) == 0) {
    other_owner = fn_80201C24(other_state);
    if (fn_80157894() & 4) {
        value = 24;
        count = 7;
        fn_80157B6C(other_owner, 4);
        fn_80199154(runtime, 1);
        fn_80199164(runtime, 0);
        switch (fn_801990E0(runtime)) {
        case 0x38: value = 6; count = 3; break;
        case 0x48: value = 12; count = 3; break;
        case 0x40: value = 24; count = 1; break;
        }
        fn_8019915C(runtime, value);
        fn_80199174(runtime, count);
        active = 1;
    } else {
        active = fn_801990F0(runtime);
    }
    if (fn_80199110(runtime) == 0 && active == 0) {
        goto done;
    }
    if (fn_80199108(runtime) != 0) {
        goto done;
    }
    count = fn_8017FEA4(runtime);
    masked_count = (u16)count;
    bits = fn_80199118(runtime);
    if ((masked_count & bits) != 0) {
        goto done;
    }
    count = fn_80199100(runtime);
    fraction = (float)(fn_800FBFB0() & 15) / 15.0f;
    fn_801534D8(other_state, fraction,
                (short*)fn_8017FDA8(runtime, (u8)count));
    fn_8019916C(runtime, 1);
    if (active != 0 && (u8)count >= fn_801990F8(runtime) - 1) {
        value = 0;
        switch (fn_801990E0(runtime)) {
        case 0x38: value = 3; break;
        case 0x48: value = 5; break;
        case 0x40: value = 7; break;
        }
        fn_8019915C(runtime, value);
        fn_80199174(runtime, 7);
        fn_80199154(runtime, 0);
    }
       }
      }
    }
done:
    ;
}
