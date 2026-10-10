typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef struct Object { u8 b[0x1000]; } Object;

extern int lbl_8064D18C;
extern int lbl_8064C270;
extern void* fn_80201814(u32);
extern int fn_80201B64(void*);
extern void fn_8020123C(int, u32, u32, int);
extern u8* fn_80201B8C(void*);
extern int fn_80201EB8(void*);
extern int fn_800A1060(void);
extern u8 fn_801911D0(void*); extern void fn_801911D8(void*,void*);
extern void fn_801911F4(void*,u8); extern u8* fn_801911C8(void*);
extern u8 fn_80180130(void*); extern int fn_80180138(void*,u8);
extern u8 fn_801911B0(void*,int); extern void fn_8019120C(void*,int);
extern s16* fn_8017FDA8(void*,int); extern s16* fn_8017FDE4(void*);
extern u8 fn_8017FDFC(void*); extern void fn_80149B60(void*,void*,int,int,int);
extern float fn_80048C2C(float); extern float fn_80048C50(float);
extern u8 fn_800FBFB0(void); extern void fn_801850FC(void*,void*);
extern void fn_80185108(void*); extern void fn_801851A0(void*,void*);
extern void fn_801D0E78(void*);

void fn_801DB140(void* self)
{
    void* actor;
    Object* o;
    void* state;
    s16* dest;
    int special;
    int changed;
    u8* table;
    u8 n;
    int count;
    u8* mask;
    s16* source;
    float angle;
    u8 f;
    void* child;
    int i;

    o = self;
    child = *(void**)(o->b + 0x18C);
    state = 0;
    if (child) {
        state = *(void**)((u8*)child + 0x88);
    }
    actor = fn_80201814(*(u32*)(o->b + 0xC));
    if (!actor || (fn_80201B64(actor) == 8 && !fn_800A1060())) {
        fn_8020123C(0x39, *(u32*)(o->b + 0xBC), *(u32*)(o->b + 0xBC), 0);
    }

    if (!(o->b[0xC4] & 1)) {
        if (state) {
            f = fn_801911D0(state);
            child = *(void**)(o->b + 0xC8);
            if (child) {
                f |= 4;
                fn_801911D8(state, child);
            } else {
                f &= ~1;
            }
            fn_801911F4(state, f);
        }
        fn_801D0E78(o);
        return;
    }

    special = fn_80201EB8(actor) == lbl_8064D18C;
    changed = 0;
    if (state && actor && o->b[0xC6]) {
        u8* info = fn_80201B8C(actor);
        if (info && *(void**)(info + 0x8C)) {
            child = fn_80201814(*(u32*)(*(u8**)(info + 0x8C) + 0x24));
            if (child) {
                info = fn_80201B8C(child);
                if (info && *(void**)(info + 0x24)) {
                    fn_801911D8(state, *(u8**)(info + 0x24) + 0xC8);
                }
            }
        }
        mask = fn_801911C8(state);
        for (i = (u8)fn_80180130(state) - 1, count = 0; i >= 0 && count < o->b[0xC6]; i--) {
            if (fn_80180138(state, i) && !fn_801911B0(state, i)) {
                fn_8019120C(state, i);
                *mask |= 1 << i;
                count++;
            }
        }
        o->b[0xC6] = 0;
    }

    if (o->b[0xC4] & 4) {
        if (o->b[0xC5]) {
            o->b[0xC5]--;
            changed = 1;
        } else {
            if (state) {
                f = fn_801911D0(state);
                fn_801911F4(state, f | 0x40);
                table = *(u8**)(o->b + 0x250);
                if (o->b[0xC4] & 0x30) {
                    fn_80149B60(actor, source = fn_8017FDE4(state), 0, 0, 0);
                    n = table[0];
                    for (i = 0; i < n; i++) {
                        if (!fn_801911B0(state, i)) {
                            dest = fn_8017FDA8(state, i);
                            angle = 360.0f * (float)i / (float)n;
                            dest[0] = (float)source[0] + 127.0f * fn_80048C2C(angle);
                            dest[1] = (float)source[1] + 127.0f * fn_80048C50(angle);
                            dest[2] = source[2] + 127 - fn_800FBFB0();
                        }
                    }
                }
                n = table[0];
                for (i = 0; i < n; i++) {
                    if (!fn_801911B0(state, i)) {
                        fn_801850FC(((void**)(table + 0x88))[i], &lbl_8064C270);
                        fn_80185108(((void**)(table + 0x88))[i]);
                        fn_801851A0(((void**)(table + 0x88))[i], fn_8017FDA8(state, i));
                    }
                }
            }
            if (!(o->b[0xC4] & 0x10)) {
                o->b[0xC4] &= ~4;
                o->b[0xC5] = 40;
            }
        }
    } else if (o->b[0xC4] & 2) {
        if (state) {
            f = fn_801911D0(state);
            fn_801911F4(state, f | 0x20);
        }
        o->b[0xC4] &= ~2;
    }

    if ((special && *(int*)(o->b + 0xC0) != lbl_8064D18C) || (o->b[0xFF0] & 2)) {
        if (state && !(o->b[0xC4] & 0x30)) {
            table = *(u8**)(o->b + 0x250);
            fn_80149B60(actor, source = fn_8017FDE4(state), 0, 0, 0);
            n = table[0];
            for (i = 0; i < n; i++) {
                if (!fn_801911B0(state, i)) {
                    dest = fn_8017FDA8(state, i);
                    angle = 360.0f * (float)i / (float)n;
                    dest[0] = (float)source[0] + 127.0f * fn_80048C2C(angle);
                    dest[1] = (float)source[1] + 127.0f * fn_80048C50(angle);
                    dest[2] = source[2] + 127 - fn_800FBFB0();
                }
            }
            if (!changed && fn_8017FDFC(state)) {
                for (i = 0; i < n; i++) {
                    if (!fn_801911B0(state, i)) {
                        dest = fn_8017FDA8(state, i);
                        fn_801850FC(((void**)(table + 0x88))[i], &lbl_8064C270);
                        fn_80185108(((void**)(table + 0x88))[i]);
                        fn_801851A0(((void**)(table + 0x88))[i], dest);
                    }
                }
            }
        }
        *(int*)(o->b + 0xC0) = lbl_8064D18C;
        o->b[0xFF0] &= ~2;
    }

    if (o->b[0xC4] & 0x10) {
        o->b[0xC4] |= 0x20;
    } else {
        o->b[0xC4] &= ~0x20;
    }
    o->b[0xC4] &= ~0x10;
}
