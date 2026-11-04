typedef unsigned short u16;
typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

/* 0x28-byte output of fn_8011F6A4, including its enabled byte at 0x24. */
typedef struct SearchResult {
    int second, first;
    Vec3 position;
    Vec3 direction;
    float value;
    u8 enabled;
} SearchResult;

/* Three target positions stored at lbl_803254A0. */
typedef struct VectorTable {
    Vec3 first;
    Vec3 second;
    Vec3 third;
} VectorTable;

typedef struct ActorFlags {
    unsigned char bit7 : 1;
    unsigned char bit6 : 1;
    unsigned char bit5 : 1;
    unsigned char bit4 : 1;
    unsigned char bit3 : 1;
    unsigned char bit2 : 1;
    unsigned char bit1 : 1;
    unsigned char bit0 : 1;
} ActorFlags;

typedef struct ActorState {
    char pad_000[0x64];
    void *resource;
    char pad_068[0x1FC];
    void *effect;
} ActorState;

extern int fn_80200C10(void *);
extern void* fn_80201B3C();
extern int fn_80201B54();
extern int fn_80200C20(void *);
extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern void* fn_80201B94();
extern void fn_8011F114();
extern int fn_80201B44();
extern void fn_80201DD8(int, int);
extern void fn_800359A0(void *, int);
extern void fn_800A3104(ActorState *, int);
extern void fn_800A3AC4(ActorState *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern int fn_800CC4DC(void *);
extern int fn_800A3588(ActorState *, void *, void *, void *, int);
extern int fn_800D39D0(ActorState *, void *, void *, int);
extern int fn_801AC9F4(u16, u8, Vec3 *, u8);
extern int fn_8013017C(void *);
extern int fn_801305D4(void *);
extern void fn_801301B0(void *, int, int);
extern void fn_80201E78(void *, void *);
extern void fn_800A3894(ActorState *, float *, void *);
extern void fn_800A2598(ActorState *);
extern void fn_800A3274(ActorState *, void *, int);
extern unsigned long long fn_8020123C(int, int, int, int);
extern int fn_80200C28(void *);
extern void *fn_80200C38(void *);
extern void fn_801A7228(int);
extern void fn_800A2D1C(ActorState *);
extern void fn_801557C4(void *, int);
extern void fn_800CD094(void *, void *, int);
extern void *fn_800A2018(ActorState *, u16);
extern void fn_800A2B8C(void *, void *);
extern void fn_800D38CC(ActorState *, float *);
extern void fn_800A2E00(ActorState *, int, int);
extern int fn_800A3A10(ActorState *, void *, int);
extern unsigned int fn_801A74C0(int);
extern unsigned int fn_801A7590(int);
extern void fn_800A4798(void *, int);
extern void fn_801A7588(int, unsigned int);
extern void fn_800A4634(ActorState *, void *);
extern int fn_800654F8(int);
extern unsigned int fn_801A7570(int);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_800A383C(ActorState *);
extern void fn_800A40C4(void *, ActorState *, void *, int);
extern int fn_801A7498(int);
extern void *fn_80201814(int);
extern float lbl_8064F354;
extern void fn_800A2430(ActorState *, int, void *, int *);
extern void fn_80064B38(void *, void *, int *);
extern void fn_800D3148();
extern void fn_800A3D90(void *, void *, void *, int *);
extern void fn_8012B324(void *);
extern void fn_80201D34(void *, int);
extern void fn_80201D1C(void *, int);
extern void fn_801E8328(int, void *);
extern void fn_800A3C2C(ActorState *, int);
extern void fn_800A2384(ActorState *, int, int);
extern void fn_800A2414(ActorState *, void *);
extern void fn_800A2F0C(ActorState *, int);
extern void fn_800A3AF8(void *);
extern void fn_800A1DA0(ActorState *, int);
extern void fn_800A2F7C(ActorState *);
extern int fn_800A2798(void *, void *, void *, int);
extern int fn_800460EC(void);
extern int fn_800A3180(void *, float *);
extern void fn_800A270C(void *, void *, int);
extern int fn_800A24A4(void *, void *, ActorState *, void *);
extern int fn_800D3410(void *, void *, void *);
extern void fn_800A25D8(void *, void *);
extern void fn_800A357C(ActorState *);
extern void fn_800A1AE0(void *, int);
extern int fn_80038308(void *, int, short *);
extern void fn_800A4428(void *, int);
extern int fn_800A2A80(void *, void *, void *, void *, void *, void *);
extern void fn_8012B344(void *);
extern void fn_800A30F4(ActorState *, int);
extern int fn_800D0AA8(void *, int);
extern void fn_800A3C4C(void *, void *, int, int);
extern void fn_800A4978(void *, void *, void *);
extern void fn_800A30B8(ActorState *, int);
extern int fn_800A306C(ActorState *);
extern void *fn_801294DC(void *, int, int, int);
extern int fn_800A44D4(ActorState *);
extern int fn_800A200C(ActorState *);
extern int fn_800A3074(int);
extern void fn_800A397C(ActorState *, void *, void *);
extern char lbl_80248A60[0x84];
extern char lbl_8064B738[7];
extern char lbl_8064B740[8];
extern char lbl_8064B748[4];
extern float lbl_8064F358;
extern void fn_8011FA8C(void *, int, int);
extern void fn_800CC860(void *, int, int);
extern void fn_800BE8D4(int);
extern void fn_800CA2C8(void *);
extern void fn_80204FDC(void *);
extern void fn_8012C62C(void *, int, void *, void *, void *, int);
extern void fn_802006D4(int, int, int, int, int);
extern void fn_802010C8(int, void *, int, float);
extern int fn_800D0A04(void *);
extern void fn_800A2688(void *, void *);
extern void fn_800D078C(void *, void *);
extern int fn_80128EAC(void *);
extern int fn_800A2B80(ActorState *);
extern void fn_800A43E8(ActorState *, int);
extern void fn_800D00EC(void *, void *, int);
extern int fn_801291CC(void *);
extern void fn_80129190(void *, int);
extern int fn_800CFE88(void *);
extern int fn_800D0328(void *, void *);
extern unsigned int lbl_8064F34C;
extern unsigned int lbl_8064F350;
extern unsigned int lbl_80651AA8[2];
extern float lbl_8064F35C;
extern float lbl_8064F360;
extern void *fn_800A1CD0(void *);
extern void fn_802045AC(void *, Vec3 *);
extern int fn_8011F6A4(void *, int, int, int, SearchResult *, int);
extern int fn_80179064(int, int, int, int);
extern int fn_80178E94(void *, void *);
extern void *fn_80135D80(Vec3 *, Vec3 *, Vec3 *, Vec3 *, void *,
                          float *, int, int, float);
extern void fn_800D34B8(void *, Vec3 *, Vec3 *, Vec3 *);
extern int fn_8012A1BC(void *, int);
extern int fn_8012A1FC(void *, int);
extern int fn_80128F40(void *);
extern void fn_80129FD0(void *, int, int);
extern void fn_801287C4(void *, void *, void *, int);
extern int fn_800D3598(void *, void *);
extern int fn_800D3620(void *, void *);
extern int fn_80204810(void *, int);
extern void fn_80128C44(void *, void *, unsigned int);
extern void fn_80128C28(void *, void *, unsigned int);
extern Vec3 lbl_803254A0[3];
extern float lbl_8064F364;
extern float lbl_8064F368;
extern void fn_800CFE30(ActorState *, void *);
extern void fn_800A2DC8(ActorState *);
extern int fn_8011FE54(void *);
extern void *fn_8012965C(void *, int, int, int);
extern int fn_800A1A84(void *, void *);
extern void fn_802020B4(void *, int);
extern void fn_80045A24(int, int);
extern void *fn_80128E30(void *);
extern void fn_8012880C(void *, void *, int);
extern void fn_800A2ED8(ActorState *, int);
extern void fn_801A9DCC(int, int, int);
extern int fn_800A2060(ActorState *);
extern int fn_800A20C0(ActorState *);
extern void fn_80008B38(void *, int, int);
extern void fn_80008C8C(void);
extern void fn_80008CA0(void);
extern char lbl_8064B728[8];
extern int lbl_8064D5A8;
extern int lbl_8064D180;

/* Actor event dispatcher. */
int fn_800D0B74(void *object, int alternate, void *event, int *value)
{
    int kind;
    char *data;
    VectorTable *vectors;
    void *actor;
    ActorState *state;
    int mode;
    void *source;
    void *resource;
    int object_id;
    int active;
    int event_value;
    int source_id;
    void *actor_8c;
    float position[3];
    Vec3 copied_position, sound_position, target_position;
    Vec3 point2, point3, point28, point29;

    vectors = (VectorTable *)lbl_803254A0;
    data = lbl_80248A60;
    kind = fn_80200C10(event);
    source = fn_80201B3C();
    source_id = source != 0 ? fn_80201B54(source) : -1;
    event_value = fn_80200C20(event);
    resource = fn_80201BC8(object);
    actor = fn_80201B8C(object);
    actor_8c = *(void **)((u8 *)actor + 0x8C);
    state = *(ActorState **)((u8 *)actor + 0x64);
    mode = (int)fn_80201B94(object);
    object_id = fn_80201B54(object);

    fn_8011F114(position, resource);
    active = fn_80201B44();
    fn_80201DD8(mode, active);

    if (kind == 3) {
        u16 actor_kind = *(u16 *)((u8 *)state + 0x86);
        int special = actor_kind != 2;
        int handled;
        Vec3 source_position;

        fn_800CC4DC(object);
        handled = fn_800A3588(state, object, (u8 *)state + 0x88, source,
                              special);
        handled |= fn_800D39D0(state, object, source, 1);
        if (handled != 0) {
            fn_801AC9F4(**(u16 **)((u8 *)state + 0x264), 0x64, (Vec3 *)position, 2);
        }
        ((void (**)(void *))*(void **)state)[4](object);
        if ((fn_8013017C(resource) & 0x40) != 0 &&
            fn_801305D4(resource) == 0) {
            fn_801301B0(resource, 0x40, 0);
        }
        if ((lbl_8064D5A8 & 0xF) == 0) {
            fn_80201E78(&source_position, source);
            copied_position = source_position;
            fn_800A3894(state, position, &copied_position);
        }
    }

    if (alternate == 0) {
        if (kind == 1) {
            void (**callbacks)(ActorState *, void *);
            fn_800359A0(object, 0);
            fn_80201DD8(mode, 0);
            fn_800A3104(state, 0);
            fn_800A3AC4(state);
            callbacks = *(void (***)(ActorState *, void *))state;
            callbacks[0](state, object);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }

        if (kind == 8) {
            fn_800A2598(state);
            fn_800A3274(state, object, 3);
            ((void (**)(ActorState *, void *, void *))*(void **)state)[8](
                state, object, event);
            fn_8020123C(0xFC, object_id, source_id, 0);
            fn_800A2D1C(state);
            fn_801557C4(*(void **)((u8 *)state + 0xC4), 1);
            fn_801557C4(*(void **)((u8 *)state + 0xC8), 1);
            *(void **)((u8 *)state + 0xC4) = 0;
            *(void **)((u8 *)state + 0xC8) = 0;
            fn_800CD094(object, event, 0xB4);
            return 1;
        }

        if (kind == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event), (int)fn_80200C38(event));
            fn_801A7228((int)fn_80200C38(event));
            return 1;
        }

        if (kind == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event), (int)fn_80200C38(event));
            fn_801A7228((int)fn_80200C38(event));
            return 1;
        }

        if (kind == 0x3E) {
            if (*(u8 *)((u8 *)state + 0x287) == 0) {
                *(u8 *)((u8 *)state + 0x287) = 1;
                fn_800A2B8C(object,
                             fn_800A2018(state, *(u16 *)((u8 *)state + 0x86)));
                fn_800D38CC(state, position);
                fn_800A2E00(state, object_id, 0x319);
            } else if (((ActorFlags *)((u8 *)state + 0x2A2))->bit7 == 0 &&
                       lbl_8064D180 == 0x53) {
                *(u16 *)((u8 *)state + 0x284) = 0xD2;
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }

        if (kind == 0x0B) {
            int result = 0;
            int event_arg2 = (int)fn_80200C38(event);
            if (fn_800A3A10(state, (u8 *)actor_8c + 0xEA, event_arg2) != 0) {
                if (((fn_801A74C0(event_arg2) >> 16) & 1) != 0 &&
                    (fn_801A7590(event_arg2) & 0x8000) != 0) {
                    fn_800A4798(object, event_arg2);
                    fn_801A7588(event_arg2,
                        1U << *(unsigned int *)((u8 *)state + 0x198));
                }
                fn_800A4634(state, resource);
                result = fn_800654F8(event_arg2);
                fn_8020123C(0x97, object_id, object_id,
                             *(u16 *)((u8 *)state->effect + 0x10));
            } else {
                ++*(u16 *)((u8 *)state + 0x29C);
                if ((fn_801A7570(event_arg2) & 0x10018) != 0) {
                    if (*(u16 *)((u8 *)state + 0x29C) == 1 ||
                        ((ActorFlags *)((u8 *)state + 0x2A2))->bit4 != 0) {
                        fn_8020104C(0x97, object_id, object_id, 0x2B5,
                                     lbl_8064F354);
                        fn_80201D2C(object, 0x7E);
                        fn_80201D14(object, 1);
                    } else {
                        fn_800A383C(state);
                        fn_8020104C(0x97, object_id, object_id, 0x2B5,
                                     lbl_8064F354);
                        fn_800A40C4(resource, state,
                                     *(void **)((u8 *)actor + 0x94), event_arg2);
                    }
                } else {
                    int linked = fn_801A7498(event_arg2);
                    if (linked != 0 && fn_80201BC8(fn_80201814(linked)) != 0) {
                        fn_80201DD8(mode, linked);
                    }
                }
            }
            if (value != 0) {
                *value = result;
            }
            return 1;
        }

        if (kind == 0xDC) {
            fn_800A2430(state, 0x0F, event, value);
            return 1;
        }

        if (kind == 0x27) {
            fn_80064B38(object, event, value);
            return 1;
        }

        if (kind == 0x3D) {
            fn_800D3148(state, object, event);
            return 1;
        }

        if (kind == 0x97) {
            u16 sound = (u16)(int)fn_80200C38(event);
            u8 volume = 0x64;
            sound_position = *(Vec3 *)position;
            switch (sound) {
            case 0x13A:
            case 0x2B5:
                sound = 0x2B5;
                fn_80201E78(&sound_position, source);
                /* fall through */
            case 0x243:
                volume = 0x7F;
                break;
            case 0x242:
            case 0x2C4:
                volume = 0x64;
                fn_80201E78(&sound_position, source);
                break;
            }
            fn_801AC9F4(sound, volume, &sound_position, 2);
            return 1;
        }

        if (kind == 0x20) {
            if (value != 0) {
                *value = 0;
            }
            return 1;
        }

        if (kind == 0x6B) {
            if (value != 0) {
                *value = 0;
            }
            return 1;
        }

        if (kind == 0x3B) {
            if (value != 0) {
                *value = 1;
            }
            return 1;
        }

        if (kind == 0x82) {
            if (value != 0) {
                *value = 0;
            }
            return 1;
        }

        if (kind == 0xE6) {
            fn_800A3D90(object, resource, event, value);
            return 1;
        }

        if (kind == 0x35) {
            fn_800A3D90(object, resource, event, value);
            return 1;
        }

        if (kind == 0x39) {
            fn_8012B324(resource);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            fn_801E8328(2, object);
            return 1;
        }

        if (kind == 0x91) {
            fn_800A3C2C(state, event_value);
            return 1;
        }

        if (kind == 0xF6) {
            fn_800A2384(state, event_value, (int)fn_80200C38(event));
            return 1;
        }

        if (kind == 0xF8) {
            fn_800A2414(state, event);
            return 1;
        }

        if (kind == 0xFA) {
            (int)fn_80200C38(event);
            ((ActorFlags *)((u8 *)state + 0x2A2))->bit6 = 0;
            fn_800A2F0C(state, 1);
            return 1;
        }

        if (kind == 0x37) {
            return 1;
        }

        if (kind == 0x32) {
            return 1;
        }

        if (kind == 0x1E) {
            return 1;
        }

    } else if (alternate == 1) {
        if (kind == 1) {
            return 1;
        }
        if (kind == 2) {
            return 1;
        }
        if (kind == 3) {
            if (((ActorFlags *)((u8 *)state + 0x2A2))->bit1 != 0) {
                ((ActorFlags *)((u8 *)state + 0x2A2))->bit1 = 0;
                fn_800A3AF8(object);
            }
            fn_800A1DA0(state, 0xE5);
            if (active != 0 && *(short *)((u8 *)state + 0x284) == 0) {
                int handled = 0;
                if (*(u16 *)((u8 *)state + 0x86) == 2) {
                    if (*(signed char *)((u8 *)state + 0x283) <= 0) {
                        fn_800A2F7C(state);
                    }
                    handled = fn_800A2798(object, resource, event, 0);
                    if (handled != 0) {
                        fn_80201D2C(object, 0x71);
                        fn_80201D14(object, 1);
                    }
                } else if (fn_800460EC() == 0 &&
                           fn_800A3180(object, position) != 0) {
                    int special = *(u16 *)((u8 *)state + 0x86) == 2;
                    if (special == 0) {
                        fn_800A270C(object, resource, 0);
                    }
                    handled = fn_800A2798(object, resource, event, special);
                    if (handled != 0) {
                        fn_80201D2C(object, 6);
                        fn_80201D14(object, 1);
                    }
                } else if (*(u16 *)((u8 *)state + 0x86) == 0) {
                    handled = fn_800A24A4(object, resource, state, event);
                } else if (*(u16 *)((u8 *)state + 0x86) == 1) {
                    handled = fn_800D3410(object, resource, event);
                    if (handled != 0) {
                        fn_80201D2C(object, 0x70);
                        fn_80201D14(object, 1);
                    }
                }
                if (handled == 0) {
                    fn_800A25D8(object, resource);
                }
            }
            if ((lbl_8064D5A8 & 7) == 0) {
                fn_80201DD8(mode, fn_80201B44());
            }
            return 1;
        }
    } else if (alternate == 0x61) {
        if (kind == 1) {
            return 1;
        }
        if (kind == 3) {
            fn_800A25D8(object, resource);
            return 1;
        }
        if (kind == 7) {
            fn_800A270C(object, resource, 0);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 0x0C) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 2) {
            fn_800A357C(state);
            return 1;
        }
    } else if (alternate == 6) {
        if (kind == 3) {
            fn_800A1DA0(state, 0xBF);
            if (*(u8 *)((u8 *)state + 0x280) != 0 &&
                (lbl_8064D5A8 & 3) == 0) {
                fn_800A25D8(object, resource);
            }
            return 1;
        }
        if (kind == 0x0C) {
            fn_800A1AE0((u8 *)state + 0x274, 0);
            ((void (**)(ActorState *, void *, void *))*(void **)state)[6](
                state, object, event);
            if (*(u16 *)((u8 *)state + 0x86) == 2) {
                short channel;
                fn_80038308(object, 0, &channel);
                fn_800A4428(object, channel);
            }
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 7) {
            fn_800A1AE0((u8 *)state + 0x274, 0);
            fn_800A270C(object, resource, 0);
            ((void (**)(ActorState *, void *, void *))*(void **)state)[7](
                state, object, event);
            if (fn_800A2A80(object, data + 0x38, lbl_8064B738,
                            data + 0x4C, lbl_8064B740,
                            data + 0x58) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (kind == 0x0D) {
            fn_800A1AE0((u8 *)state + 0x274, 0);
            fn_800A270C(object, resource, 0);
            ((void (**)(ActorState *, void *, void *))*(void **)state)[5](
                state, object, event);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            fn_8012B344(resource);
            return 1;
        }
        if (kind == 2) {
            fn_800A3AC4(state);
            return 1;
        }
    } else if (alternate == 0x71) {
        if (kind == 1) {
            fn_800A30F4(state, 1);
            return 1;
        }
        if (kind == 2) {
            return 1;
        }
        if (kind == 3) {
            fn_800A1DA0(state, 0xBF);
            if (*(short *)((u8 *)state + 0x284) > 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            } else if (*(u8 *)((u8 *)state + 0x280) != 0 &&
                       (lbl_8064D5A8 & 7) == 0) {
                fn_800A25D8(object, resource);
            }
            return 1;
        }
        if (kind == 0x0C) {
            --*(u8 *)((u8 *)state + 0x283);
            if (*(signed char *)((u8 *)state + 0x283) > 0) {
                if (fn_800A2798(object, resource, event, 0) == 0) {
                    fn_80201D2C(object, 1);
                    fn_80201D14(object, 1);
                }
            } else if (fn_800D0AA8(object, 0) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (kind == 7) {
            if (fn_800A2A80(object, data + 0x38, lbl_8064B748,
                            data + 0x4C, lbl_8064B740,
                            data + 0x58) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
    } else if (alternate == 7) {
        if (kind == 1) {
            if (*(u16 *)((u8 *)state + 0x86) == 2) {
                fn_800A2598(state);
            }
            fn_800A3104(state, 0);
            fn_800A3C4C(resource, actor, 0, 0);
            return 1;
        }
        if (kind == 0x36) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 7) {
            fn_800A270C(object, resource, 0);
            if (fn_800A2A80(object, data + 0x38, lbl_8064B748,
                            data + 0x4C, lbl_8064B740,
                            data + 0x58) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (kind == 2) {
            ((ActorFlags *)((u8 *)state + 0x2A2))->bit1 = 1;
            fn_800A4978(object, resource, actor);
            if (fn_800A2A80(object, data + 0x38, lbl_8064B748,
                            data + 0x4C, lbl_8064B740,
                            data + 0x58) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            *(int *)((u8 *)state + 0x190) = -1;
            return 1;
        }
    } else if (alternate == 0x70) {
        if (kind == 1) {
            fn_800A30B8(state, 1);
            return 1;
        }
        if (kind == 2) {
            return 1;
        }
        if (kind == 3) {
            fn_800A1DA0(state, 0xE5);
            if (*(signed char *)((u8 *)state + 0x282) == 0) {
                if (fn_800A306C(state) != 0) {
                    fn_801294DC(resource, 0x93, 0x21, 2);
                    fn_8020104C(0xD3, object_id, object_id, 0, lbl_8064F358);
                    fn_80201D2C(object, 0x6E);
                    fn_80201D14(object, 1);
                } else {
                    fn_80201D2C(object, 0x6F);
                    fn_80201D14(object, 1);
                }
            } else if (fn_800A44D4(state) == 0 && fn_800A200C(state) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            } else if (fn_800A200C(state) == 0 && fn_800A3074(active) == 0x32) {
                fn_80201D2C(object, 0x6F);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (kind == 0x78) {
            int target_id = *(int *)((u8 *)(int)fn_80200C38(event) + 0x20);
            ((void (**)(ActorState *, void *, void *))*(void **)state)[9](
                state, object, event);
            fn_800A397C(state, object, resource);
            fn_8020123C(0xD5, object_id, target_id, object_id);
            return 1;
        }
        if (kind == 7) {
            if (fn_800A2A80(object, data + 0x38, lbl_8064B748,
                            data + 0x4C, lbl_8064B740,
                            data + 0x58) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
    } else if (alternate == 8) {
        if (kind == 1) {
            if (resource != 0) {
                fn_8011FA8C(resource, 0xC0, 0);
            }
            fn_800CC860(object, 1, 0);
            fn_800BE8D4(object_id);
            fn_800CA2C8(object);
            fn_80204FDC(object);
            return 1;
        }
        if (kind == 0x11) {
            unsigned int color1 = lbl_80651AA8[0];
            unsigned int color2 = lbl_8064F350;
            unsigned int color3 = lbl_8064F34C;
            fn_8012C62C(resource, 0x0F, &color3, &color2, &color1, 4);
            fn_80201D34(object, 0x15);
            fn_80201D1C(object, 1);
            return 1;
        }
        if (kind == 2) {
            fn_802006D4(object_id, object_id, 8, 0x11, 0);
            return 1;
        }
        if (kind == 0xEF) {
            if (value != 0) {
                *value = 1;
            }
            return 1;
        }
        if (kind == 0x3B) {
            if (value != 0) {
                *value = 0;
            }
            return 1;
        }
        if (kind == 0x35) { return 1; }
        if (kind == 8) { return 1; }
        if (kind == 0x0B) { return 1; }
        if (kind == 0x27) { return 1; }
        if (kind == 0x37) { return 1; }
        if (kind == 0x1E) { return 1; }
        if (kind == 0x32) { return 1; }
    } else if (alternate == 0x73) {
        if (kind == 1) {
            fn_802010C8(6, object, 0, lbl_8064F35C);
            return 1;
        }
        if (kind == 2) {
            fn_8012B344(resource);
            return 1;
        }
        if (kind == 3) {
            fn_800A1DA0(state, 0xE5);
            return 1;
        }
        if (kind == 6) {
            if (fn_800D0A04(object) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (kind == 7) {
            if (fn_800A2A80(object, data + 0x38, lbl_8064B748,
                            data + 0x4C, lbl_8064B740,
                            data + 0x58) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
    } else if (alternate == 0x78) {
        if (kind == 1) {
            fn_800A3104(state, 1);
            fn_800A3AC4(state);
            fn_800A2688(resource, object);
            fn_802010C8(0xD4, object, 0, lbl_8064F360);
            return 1;
        }
        if (kind == 3) {
            fn_800A1DA0(state, 0xE5);
            return 1;
        }
        if (kind == 0xD4) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 2) {
            fn_800A270C(object, resource, 0);
            fn_800A3104(state, 0);
            fn_8012B344(resource);
            return 1;
        }
        if (kind == 7) {
            if (fn_800A2A80(object, data + 0x38, lbl_8064B748,
                            data + 0x4C, lbl_8064B740,
                            data + 0x58) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
    } else if (alternate == 0x56) {
        if (kind == 1) {
            fn_800A3104(state, 1);
            fn_800A3AC4(state);
            fn_800A2688(resource, object);
            fn_800D078C(resource, object);
            fn_8020104C(0xD4, object_id, object_id, 0,
                         (float)*(u16 *)((u8 *)state + 0x260));
            return 1;
        }
        if (kind == 3) {
            fn_800A1DA0(state, 0xE5);
            return 1;
        }
        if (kind == 0xD4) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 2) {
            fn_800A270C(object, resource, 0);
            fn_800A3104(state, 0);
            return 1;
        }
        if (kind == 0x78) {
            *(int *)((u8 *)state + 0x68) = 0;
            return 1;
        }
        if (kind == 7) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
    } else if (alternate == 0x6E) {
        if (kind == 1) { return 1; }
        if (kind == 2) {
            fn_800A3104(state, 0);
            fn_800A270C(object, resource, 0);
            return 1;
        }
        if (kind == 0xD3) {
            fn_800A2688(resource, object);
            fn_8020104C(0xD4, object_id, object_id, 0,
                         (float)*(u16 *)((u8 *)state + 0x260));
            return 1;
        }
        if (kind == 0xD4) {
            int animation = fn_80128EAC(resource);
            if (animation == 0x44 || animation == 0x93) {
                fn_8012B344(resource);
            }
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 3) {
            fn_800A25D8(object, resource);
            fn_800A1DA0(state, 0xE5);
            return 1;
        }
    } else if (alternate == 0x6F) {
        if (kind == 1) {
            fn_800A270C(object, resource, 0);
            return 1;
        }
        if (kind == 2) {
            fn_800A3104(state, 0);
            return 1;
        }
        if (kind == 3) {
            fn_800A1DA0(state, 0xE5);
            if (fn_800A2B80(state) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            } else if (fn_800460EC() == 0 &&
                       fn_800A3180(object, position) != 0 &&
                       *(short *)((u8 *)state + 0x284) == 0) {
                fn_800A2798(object, resource, event, 0);
            }
            return 1;
        }
    } else if (alternate == 0x77) {
        if (kind == 1) {
            if (fn_800A2B80(state) > 0) {
                fn_800A43E8(state, object_id);
            }
            *(u8 *)((u8 *)state + 0x286) = 0;
            fn_800A1DA0(state, 0xFF);
            return 1;
        }
        if (kind == 0x4C) {
            fn_800D00EC(object, resource, 1);
            return 1;
        }
        if (kind == 0x4D) {
            fn_800D00EC(object, resource, 2);
            return 1;
        }
        if (kind == 7) {
            if ((u16)fn_801291CC(resource) != 5) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (kind == 0x0C) {
            fn_800D00EC(object, resource, 3);
            return 1;
        }
        if (kind == 3) {
            fn_800A25D8(object, resource);
            fn_800A1DA0(state, 0xE5);
            if (fn_80128EAC(resource) == 0x0F && fn_800A2B80(state) == 0) {
                fn_80129190(resource, 5);
                if (fn_800460EC() == 0 &&
                    fn_800A3180(object, position) != 0 &&
                    *(short *)((u8 *)state + 0x284) == 0) {
                    fn_8012B344(resource);
                    if (fn_800A2798(object, resource, event, 0) != 0) {
                        fn_80201D2C(object, 6);
                        fn_80201D14(object, 1);
                    }
                } else {
                    int handled = 0;
                    if (fn_800CFE88(object) == 0) {
                        handled = fn_800D0328(object, resource);
                    }
                    if (handled == 0) {
                        fn_80201D2C(object, 1);
                        fn_80201D14(object, 1);
                    }
                }
            }
            return 1;
        }
    } else if (alternate == 0x44) {
        if (kind == 1) {
            fn_800A1DA0(state, 0xFF);
            return 1;
        }
        if (kind == 2) { return 1; }
        if (kind == 3) {
            SearchResult point;
            float collision[9];
            void *target;
            if (*(u8 *)((u8 *)state + 0x280) != 0) {
                fn_800A25D8(object, resource);
            }
            target = fn_800A1CD0(object);
            if (target != 0 && (*(u16 *)((u8 *)state + 0x84) & 0x80) == 0) {
                int separation, point_distance, target_distance;
                fn_802045AC(object, &target_position);
                fn_8011F6A4(resource, 3, 0, -1, &point, 1);
                point3 = point.position;
                separation = fn_80179064((int)point3.x, (int)point3.y,
                                          (int)target_position.x,
                                          (int)target_position.y);
                point_distance = fn_80178E94(position, &point3);
                target_distance = fn_80178E94(position, &target_position);
                if (separation < 0x1F4) {
                    fn_8011F6A4(resource, 2, 0, -1, &point, 1);
                    point2 = point.position;
                    fn_8011F6A4(resource, 0x1C, 0, -1, &point, 1);
                    point28 = point.position;
                    fn_8011F6A4(resource, 0x1D, 0, -1, &point, 1);
                    point29 = point.position;
                    if (fn_80135D80(&point2, &point3, &point28, &point29,
                                    target, collision, 1, 1, lbl_8064F364) != 0) {
                        *(u16 *)((u8 *)state + 0x84) |= 0x80;
                        fn_8020123C(0x9E, object_id, active, 0);
                        fn_800D34B8(target, &point3, &point29, &vectors->first);
                        fn_8020123C(0x9D, object_id, active, (int)&vectors->first);
                        fn_8020123C(0x0C, object_id, object_id, (int)&vectors->first);
                        fn_8020123C(0x97, object_id, object_id, 0x2C4);
                    }
                } else if (point_distance - target_distance > 0x12C) {
                    fn_8020123C(0x0C, object_id, object_id, (int)&vectors->first);
                }
            } else {
                fn_8011F6A4(resource, 3, 0, -1, &point, 1);
                point3 = point.position;
                fn_8011F6A4(resource, 0x1D, 0, -1, &point, 1);
                point29 = point.position;
                fn_800D34B8(target, &point3, &point29, &vectors->first);
                fn_8020123C(0x9D, object_id, active, (int)&vectors->first);
            }
            return 1;
        }
        if (kind == 0x0C) {
            int transitioning = 0;
            int frame;
            float remaining;
            void *animation;
            fn_800A1AE0((u8 *)state + 0x274, 0);
            if (fn_80128EAC(resource) == 0x6F) {
                int end = fn_8012A1BC(resource, 0x6F);
                fn_8012A1FC(resource, 0x6F);
                frame = fn_80128F40(resource) >> 17;
                transitioning = 1;
                remaining = lbl_8064F368 - (float)(frame - 0x42) /
                                             (float)(end - 0x42);
            }
            if ((*(u16 *)((u8 *)state + 0x84) & 0x80) != 0) {
                animation = fn_801294DC(resource, 0x70, 0x24, 6);
                if (animation != 0) {
                    int start = fn_8012A1FC(resource, 0x70);
                    fn_8012A1BC(resource, 0x70);
                    if (transitioning != 0) {
                        fn_80129FD0(resource,
                            (int)(remaining * (float)(0x11E - start) +
                                  (float)start) << 17, 1);
                    }
                    fn_801287C4(animation, (void *)fn_800D3598, object, 0x118);
                    fn_801287C4(animation, (void *)fn_800D3620, object,
                                 fn_8012A1BC(resource, 0x70) - 2);
                    fn_80128C44(animation, (void *)fn_80204810,
                                 ((unsigned int)object_id << 8) | 7);
                    fn_80128C28(animation, (void *)fn_80204810,
                                 ((unsigned int)object_id << 8) | 0x0C);
                    fn_80201D2C(object, 0x45);
                    fn_80201D14(object, 1);
                } else {
                    fn_8020123C(0x9F, object_id, active, 0);
                    fn_80201D2C(object, 1);
                    fn_80201D14(object, 1);
                }
            } else {
                animation = fn_801294DC(resource, 0x71, 0x24, 6);
                if (animation != 0) {
                    if (transitioning != 0) {
                        int next_frame;
                        fn_8012A1FC(resource, 0x71);
                        fn_8012A1BC(resource, 0x71);
                        next_frame = 0x13;
                        if (frame - 0x41 >= 0) {
                            next_frame = 0x12;
                        }
                        fn_80129FD0(resource, next_frame << 17, 1);
                    }
                    fn_80128C44(animation, (void *)fn_80204810,
                                 ((unsigned int)object_id << 8) | 7);
                    fn_80128C28(animation, (void *)fn_80204810,
                                 ((unsigned int)object_id << 8) | 0x0C);
                    fn_80201D2C(object, 0x46);
                    fn_80201D14(object, 1);
                } else {
                    fn_80201D2C(object, 1);
                    fn_80201D14(object, 1);
                }
            }
            return 1;
        }
        if (kind == 0x0D) {
            fn_800A270C(object, resource, 0);
            fn_8020123C(0x9F, object_id, active, 0);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            fn_8012B344(resource);
            return 1;
        }
    } else if (alternate == 0x45) {
        if (kind == 3) {
            void *target;
            SearchResult point3, point29;
            fn_800A1DA0(state, 0xE5);
            target = fn_800A1CD0(object);
            if (target != 0) {
                fn_8011F6A4(resource, 3, 0, -1, &point3, 1);
                fn_8011F6A4(resource, 0x1D, 0, -1, &point29, 1);
                fn_800D34B8(target, &point3.position, &point29.position,
                             &vectors->second);
            }
            fn_8020123C(0x9D, object_id, active, (int)&vectors->second);
            return 1;
        }
        if (kind == 0x9F) {
            fn_8012B344(resource);
            return 1;
        }
        if (kind == 0x0C) {
            void *target = fn_800A1CD0(object);
            SearchResult point3, point29;
            if (target != 0) {
                fn_8011F6A4(resource, 3, 0, -1, &point3, 1);
                fn_8011F6A4(resource, 0x1D, 0, -1, &point29, 1);
                fn_800D34B8(target, &point3.position, &point29.position,
                             &vectors->third);
                fn_8020123C(0x9D, object_id, active, (int)&vectors->third);
            }
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 7) {
            fn_800A270C(object, resource, 0);
            if (fn_800A2A80(object, data + 0x70, lbl_8064B738,
                            data + 0x4C, lbl_8064B740,
                            data + 0x58) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (kind == 0x0D) {
            fn_800A270C(object, resource, 0);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            fn_8012B344(resource);
            return 1;
        }
        if (kind == 2) { return 1; }
    } else if (alternate == 0x46) {
        if (kind == 1) {
            fn_800A1DA0(state, 0xF2);
            return 1;
        }
        if (kind == 0x0C) {
            fn_800A1AE0((u8 *)state + 0x274, 0);
            if (fn_800D0AA8(object, 1) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (kind == 7) {
            fn_800A1AE0((u8 *)state + 0x274, 0);
            fn_800A270C(object, resource, 0);
            if (fn_800A2A80(object, data + 0x38, lbl_8064B738,
                            data + 0x4C, lbl_8064B740,
                            data + 0x58) == 0 &&
                fn_800D0AA8(object, 1) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (kind == 0x0D) {
            fn_800A1AE0((u8 *)state + 0x274, 0);
            fn_800A270C(object, resource, 0);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            fn_8012B344(resource);
            return 1;
        }
    } else if (alternate == 0x7E) {
        if (kind == 1) {
            void *animation;
            ((ActorFlags *)((u8 *)state + 0x2A2))->bit4 = 0;
            ((ActorFlags *)((u8 *)state + 0x2A2))->bit3 = 0;
            *(int *)((u8 *)state + 0x298) = 0;
            fn_800A270C(object, resource, 0);
            fn_800CFE30(state, object);
            fn_800A2DC8(state);
            animation = fn_8012965C(resource, fn_8011FE54(resource), 0x21, 1);
            if (animation != 0) {
                fn_801287C4(animation, (void *)fn_800A1A84, state, 0x23);
                fn_802020B4(object, 0);
                fn_80045A24(1, 0);
            } else {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (kind == 2) {
            void *animation = fn_80128E30(resource);
            if (animation != 0) {
                fn_8012880C(animation, 0, 0);
            }
            ((ActorFlags *)((u8 *)state + 0x2A2))->bit3 = 0;
            fn_800A2ED8(state, 1);
            fn_80045A24(0, 0);
            fn_802020B4(object, 1);
            fn_801A9DCC(0, 0x64, 0x1E);
            return 1;
        }
        if (kind == 3) {
            if (((ActorFlags *)((u8 *)state + 0x2A2))->bit3 != 0) {
                int selection = fn_800A2060(state);
                switch (fn_800A20C0(state)) {
                case 2:
                    if (*(unsigned int *)((u8 *)state + 0x298) == 0) {
                        switch (selection) {
                        case 0:
                            fn_80008B38(lbl_8064B728, 0, 1);
                            fn_80008C8C();
                            break;
                        case 1:
                        default:
                            fn_80008B38(data + 0x20, 0, 3);
                            fn_80008C8C();
                            break;
                        }
                        *(unsigned int *)((u8 *)state + 0x298) = 1;
                    }
                    break;
                case 0:
                    fn_80008CA0();
                    fn_80201D2C(object, 1);
                    fn_80201D14(object, 1);
                    break;
                case 1:
                    break;
                }
            }
            return 1;
        }
    } else {
        return 0;
    }

    return 0;
}
