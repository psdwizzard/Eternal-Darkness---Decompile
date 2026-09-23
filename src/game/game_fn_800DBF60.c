typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;

extern void* fn_80201C24();
extern int fn_80201B54();
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a,b,c,d,e) fn_8020104C((a),(void*)(c),(void*)(d),(int)(e),(b))
extern void *fn_80201814();
extern void *fn_80155DB4(void *);
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS void *, void *
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern void *fn_80157924(void *);
extern void fn_80199130(void *, int);
extern void fn_80199138(void *, void *);
extern void fn_8007C17C(void *);
extern void *fn_80201890(int);
extern void fn_80120B4C(void *);
extern int fn_80157AB8(void *);
extern void fn_80147E88(void *);
extern void *fn_80149E04(void);
extern void fn_80153464(void *, void *);
extern int fn_80201AE4(void);
extern void fn_8019917C(void *);
extern int fn_801D3A24(u8, int);
extern unsigned int fn_80148300(void *, void *, void *);
extern void fn_80157930(void *, int);
extern void fn_80149EB8(void *);
extern int fn_8006749C(u8);
extern void fn_80120AD0(void *, int, s16, u16, float, float);
extern void *fn_8011F130(void *);
extern void fn_800DC3A0(void *, int, void *, u8, int, int);
extern int fn_801E855C(int, void *, int);
extern int fn_801E8328();
extern float lbl_8064F460;
extern float lbl_8064F464;
extern u8 lbl_80325B80[];

void fn_800DBF60(int owner, void *context, int level, void *effect, float amount)
{
    int effect_kind;
    void *state = fn_80201C24(context);
    int kind = fn_80201B54(context);

    if (amount > lbl_8064F464) {
        fn_8020104C(0x4b, amount, kind, kind, (int)effect);
    }

    {
        void *source = fn_80201814(owner);
        if (source != 0) {
            u8 position[16];
            u8 object_kind;
            void *node;
            void *action;
            void *link;
            void *object;

            action = fn_80155DB4(context);
            fn_80201E78(position, source);
            link = fn_80157924(state);
            if (link != 0) {
                fn_80199130(link, 1);
                fn_80199138(link, position);
                if (effect != 0) {
                    fn_8007C17C(effect);
                }
            }

            object = fn_80201890(kind);
            fn_80120B4C(object);
            object_kind = fn_80157AB8(state);
            fn_80147E88(lbl_80325B80);
            /* Preserve the kind before reusing its 32-bit work slot for a packet base. */
            effect_kind = kind;
            *(int *)(lbl_80325B80 + 0xa8) = kind;
            node = fn_80149E04();
            if (node != 0) {
                fn_80153464(lbl_80325B80, node);
                if (owner == fn_80201AE4()) {
                    lbl_80325B80[0xbc] |= 0x10;
                }
                {
                    kind = (int)lbl_80325B80;
                    fn_8019917C((void *)kind);
                    {
                        u8 *packet = lbl_80325B80;
                        packet[0] = 0x18;
                        *(u16 *)(packet + 4) = fn_801D3A24(object_kind, 0x31);
                        packet[1] = 3;
                        *(s8 *)(packet + 3) = -10;
                        if (amount > lbl_8064F464) {
                            *(u16 *)((u8 *)kind + 6) = (int)amount;
                        } else {
                            *(int *)(packet + 0x1c) = 1;
                        }
                        packet[0x15] = (u8)((u8)level * 2 - 1);
                        switch ((u8)level) {
                        case 2: packet[0x14] = 0x38; break;
                        case 3: packet[0x14] = 0x48; break;
                        case 4: packet[0x14] = 0x40; break;
                        }
                        packet[0x17] = 0xf0;
                        packet[0x18] = 0x78;
                        if (fn_80148300(action, lbl_80325B80, node) != 0) {
                            fn_80157930(state, *(int *)((u8 *)node + 0x88));
                        } else {
                            fn_80149EB8(node);
                        }
                    }
                }
            }

            {
                u16 flags = (u16)fn_8006749C(object_kind);
                u16 duration = 20 * (5 - (u8)level);
                flags |= 0x202;
                fn_80120AD0(object, 0, duration, flags, lbl_8064F460,
                             lbl_8064F460);
            }
            if (effect != 0) {
                fn_800DC3A0(effect, effect_kind, fn_8011F130(object), object_kind, level,
                            (int)amount);
                if (fn_801E855C(0x14, effect, 0) == 0) {
                    fn_801E8328(0x14, effect);
                }
            }
        }
    }
}
