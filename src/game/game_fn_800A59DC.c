/* State/event dispatch for a scripted character actor.
 * The common state (0) handles a long list of shared events; the other
 * states only react to a handful of events and swallow the rest.
 */
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;
#define NULL ((void*)0)

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Counter {
    u8 pad00[0x10A];
    s8 count;
} Counter;
typedef struct Effect {
    u8 pad00[0x86];
    s16 timer;
} Effect;
typedef struct Timers {
    u8 pad00[0x14E];
    s16 delay;
    s16 cooldown;
} Timers;
typedef struct Runtime {
    u8 pad00[0x4];
    Counter **counter;
    Effect *effect;
    u8 pad0C[0x80];
    Timers *timers;
    u8 pad90[0xE];
    u8 kind;
    u8 mode;
} Runtime;
/* Animation/sound names used when leaving the scripted states. */
typedef struct MessageTable {
    char idle_name[0x1C];
    char fade_name[0xC];
    char exit_name[0x18];
    char stand_name[0x14];
    char talk_name[0x1C];
    char talk_end_name[0x10];
} MessageTable;

extern s32 fn_80035FB8();
extern s32 fn_8003BF5C();
extern void fn_8003C320();
extern void fn_8003CD0C();
extern s32 fn_80048A60();
extern void fn_80048A68();
extern void fn_8005EA38();
extern void fn_8005EC6C();
extern void fn_8005FD84();
extern void fn_8005FF94();
extern void fn_80060904();
extern void fn_80062ED0();
extern void fn_80064B38();
extern s32 fn_800654F8();
extern void fn_80066754();
extern void fn_80066A0C();
extern void fn_80066AEC();
extern void fn_80067858();
extern void fn_80068290();
extern s32 fn_8006D4DC();
extern s32 fn_8008ABD4();
extern void fn_8008CBE8();
extern void fn_800A5390();
extern void fn_800A57D4();
extern s32 fn_800A5948();
extern s32 fn_800AD2B4();
extern void fn_800C030C(void*, void*, float);
extern void fn_800C16F4();
extern void fn_800C3D94();
extern void fn_800C63D8();
extern void fn_800C677C();
extern s32 fn_800CCAD0();
extern void fn_800CD094();
extern u8 rand();
extern void fn_8011E174();
extern void fn_8011F114();
extern void fn_801287C4();
extern void fn_80128C28();
extern void fn_80128C44();
extern u32 fn_80128E30();
extern s32 fn_80128EAC();
extern u8 fn_80128EE4();
extern void fn_80128F74();
extern s32 fn_801290D0();
extern s32 fn_801294DC();
extern s32 fn_8012A1BC();
extern void fn_8012AC74();
extern void fn_8012B344();
extern u32 fn_8015C910();
extern void fn_8016B400();
extern void fn_801A5910();
extern void fn_801A7228();
extern s32 fn_801A7530();
extern void fn_801A7538();
extern void fn_801E7974();
extern void fn_801E79A0();
extern s32 fn_801E79FC();
extern void fn_801E8328();
extern void fn_802006D4();
extern s32 fn_80200C10();
extern s32 fn_80200C20();
extern s32 fn_80200C28();
extern void* fn_80200C38();
extern void fn_8020104C(int, int, int, int, float);
extern void fn_8020123C();
extern void* fn_80201814();
extern s32 fn_80201B54();
extern void* fn_80201B8C();
extern void* fn_80201B94();
extern void* fn_80201BC8();
extern void* fn_80201C48();
extern void fn_80201D14();
extern void fn_80201D2C();
extern void fn_80201DD8();
extern s32 fn_80201EB8();
extern void fn_80204810();
extern MessageTable lbl_80245738;
extern char lbl_8064B640[4];
extern char lbl_8064B644[8];
extern char lbl_8064B64C[8];
extern char lbl_8064B654[8];
extern s32 lbl_8064B81C;
extern void* lbl_8064C4E0;
extern s32 lbl_8064C948;
extern s32 lbl_8064C94C;
extern s32 lbl_8064C950;
extern s32 lbl_8064D18C;
extern f32 lbl_8064EF04;
extern f32 lbl_8064EF08;
extern f32 lbl_8064EF0C;
extern f32 lbl_8064EF10;

int fn_800A59DC(void* object, int state, void* event, int* result)
{
    Vec3 position;
    MessageTable* messages = &lbl_80245738;
    Runtime* runtime;
    Timers* timers;
    void* context;
    void* actor;
    int object_id;
    int scene_id;
    int event_type;
    Counter* counter;
    int value;
    int arg;
    int enable;
    int sound;
    int item;
    void* sender;
    int visible;
    void* param;
    int flags;
    int handle;
    void* target;
    void* target_actor;
    float speed;

    event_type = fn_80200C10(event);
    actor = fn_80201BC8(object);
    context = fn_80201B94(object);
    object_id = fn_80201B54(object);
    runtime = (Runtime*)fn_80201B8C(object);
    timers = runtime->timers;
    fn_8011F114(&position, actor);
    scene_id = fn_80201EB8(object);
    if (fn_8015C910() != 0 && fn_800CCAD0(object, event, result) != 0) {
        return 1;
    }
    if (event_type == 3) {
        fn_80067858(object_id);
        timers->delay = timers->delay >= 1 ? timers->delay - 1 : 0;
        timers->cooldown = timers->cooldown >= 4 ? timers->cooldown - 1 : 0;
        if (runtime->effect != NULL) {
            runtime->effect->timer = runtime->effect->timer <= 1 ? 0 : runtime->effect->timer - 1;
        }
        if (runtime->counter != NULL) {
            counter = *runtime->counter;
            if (counter != NULL && counter->count != 0) {
                counter->count--;
            }
        }
        fn_800A57D4(&lbl_8064C950, runtime);
    }
    if (state == 0) {
        if (event_type == 1) {
            handle = fn_800AD2B4();
            lbl_8064C94C = 0;
            lbl_8064C950 = 300;
            if (handle != 0) {
                fn_8020123C(0x90, object_id, handle, 0);
            }
            lbl_8064C948 = fn_801E79FC(lbl_8064C4E0, 0x39A);
            if (fn_801E79FC(lbl_8064C4E0, 0x283) == 1 && lbl_8064D18C == 0x1B &&
                fn_800A5948(0xE98A39BB, object_id, actor) != 0) {
                fn_801E7974(lbl_8064C4E0, 0x39A);
            } else {
                fn_801E79A0(lbl_8064C4E0, 0x39A);
            }
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (event_type == 0x1F) {
            if (result != NULL) {
                *result = 1;
            }
            return 1;
        } else if (event_type == 0xEE) {
            if (result != NULL) {
                *result = -1;
            }
            return 1;
        } else if (event_type == 0xBB) {
            if ((param = fn_80200C38(event)) != NULL) {
                fn_801E7974(lbl_8064C4E0, param);
            }
            return 1;
        } else if (event_type == 0xBC) {
            if ((param = fn_80200C38(event)) != NULL) {
                fn_801E79A0(lbl_8064C4E0, param);
            }
            return 1;
        } else if (event_type == 0xBE) {
            enable = (int)fn_80200C38(event);
            if (enable != 0) {
                fn_8016B400(enable, object_id, 0);
            }
            return 1;
        } else if (event_type == 0x86) {
            fn_801A5910(fn_80200C38(event));
            return 1;
        } else if (event_type == 0x69) {
            fn_8005FF94(object, event, result);
            return 1;
        } else if (event_type == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        } else if (event_type == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        } else if (event_type == 0xB) {
            value = fn_800654F8(fn_80200C38(event));
            if (result != NULL) {
                *result = value;
            }
            return 1;
        } else if (event_type == 0x35) {
            fn_80066754(object, event, result);
            return 1;
        } else if (event_type == 0x20) {
            if (runtime->kind == 1 && runtime->mode == 3) {
                fn_80062ED0(object, actor, event, result);
            }
            return 1;
        } else if (event_type == 0x2B) {
            fn_800C3D94(object, event, result);
            return 1;
        } else if (event_type == 0x29) {
            arg = (int)fn_80200C38(event);
            fn_80201DD8(context, 0);
            fn_800C63D8();
            fn_800C16F4(object, arg, 1, 0);
            return 1;
        } else if (event_type == 0x2A) {
            param = fn_80200C38(event);
            if (fn_80048A60() == 0) {
                fn_80201DD8(context, 0);
                fn_80048A68(1);
                fn_800C63D8();
            }
            fn_800C16F4(object, param, 1, 1);
            return 1;
        } else if (event_type == 0x8) {
            if (runtime->mode == 6) {
                fn_8011E174(0x400, 0);
            }
            if (runtime->mode == 3) {
                fn_8003C320(object, event);
            } else {
                fn_800CD094(object, event, 0xB4);
            }
            return 1;
        } else if (event_type == 0x2D) {
            if (fn_80128EE4(actor) != 0x10) {
                fn_801294DC(actor, 0xF, 0x21, 1);
            }
            return 1;
        } else if (event_type == 0x2C) {
            speed = lbl_8064EF04;
            if (runtime->mode == 6) {
                speed = lbl_8064EF08;
            } else if (runtime->mode == 4) {
                speed = lbl_8064EF0C;
            }
            fn_800C030C(object, event, speed);
            return 1;
        } else if (event_type == 0x28) {
            if (runtime->mode == 3) {
                fn_8003CD0C(object, actor, event);
            } else if (runtime->mode == 4) {
                fn_80060904(object, actor, event);
            } else if (runtime->mode == 6) {
                target_actor = fn_80201C48(context);
                target = fn_80201814();
                if (target == NULL) {
                    target = object;
                    target_actor = (void*)object_id;
                }
                fn_8008CBE8(object, target_actor);
                if (fn_8008ABD4(object, target, event, 1) != 0) {
                    fn_8011E174(0x400, 1);
                    fn_8020104C(8, object_id, object_id, 0, lbl_8064EF10);
                }
            }
            return 1;
        } else if (event_type == 0xFA) {
            switch ((int)fn_80200C38(event)) {
            case 7:
                fn_800A5390(object, actor, runtime, event, 0, 1, 1);
                break;
            }
            return 1;
        } else if (event_type == 0x87) {
            if (fn_8006D4DC(0x17) == 0) {
                fn_800A5390(object, actor, runtime, event, 0, 1, 1);
            }
            return 1;
        } else if (event_type == 0x27) {
            param = fn_80200C38(event);
            flags = fn_801A7530();
            if (flags & 1) {
                fn_801A7538(param, 1);
                fn_80064B38(object, event, result);
                fn_801A7538(param, flags);
            }
            return 1;
        } else if (event_type == 0xEF) {
            value = 0;
            if (runtime->mode == 6) {
                value = 1;
            }
            if (result != NULL) {
                *result = value;
            }
            return 1;
        } else if (event_type == 0x3B) {
            sender = fn_80201814(fn_80200C20(event));
            if (runtime->mode == 6) {
                visible = 0;
                if (((int)fn_80200C38(event) & 5) || fn_8003BF5C(sender) != 0) {
                    visible = 1;
                }
                if (result != NULL) {
                    *result = visible;
                }
            } else if (result != NULL) {
                *result = lbl_8064B81C;
            }
            return 1;
        } else if (event_type == 0x65) {
            if (result != NULL) {
                *result = 1;
            }
            return 1;
        } else if (event_type == 0x82) {
            if (result != NULL) {
                *result = 1;
            }
            return 1;
        } else if (event_type == 0x37) {
            if (runtime->mode == 3) {
                fn_80066AEC(object, event);
            }
            return 1;
        } else if (event_type == 0x32) {
            if (runtime->mode == 3) {
                fn_80066A0C(object, event);
            }
            return 1;
        } else if (event_type == 0x3F) {
            if (runtime->mode == 3) {
                fn_80068290(object, event, result);
            }
            return 1;
        } else if (event_type == 0xB9) {
            if (result != NULL) {
                *result = 0;
            }
            return 1;
        } else if (event_type == 0xF1) {
            fn_8005EC6C(scene_id, object, actor, runtime, event);
            return 1;
        } else if (event_type == 0xDF) {
            fn_8005EA38(scene_id, object, event, &position);
            return 1;
        } else if (event_type == 0xEE) {
            if (result != NULL) {
                *result = -1;
            }
            return 1;
        } else if (event_type == 0xA5) {
            sound = (int)fn_80200C38(event);
            fn_800C677C(object, sound, 0);
            return 1;
        } else if (event_type == 0x9D) {
            item = (int)fn_80200C38(event);
            fn_8012AC74(actor, item, 3);
            return 1;
        }
    } else if (state == 1) {
        if (event_type == 1) {
            lbl_8064C94C = 0;
            return 1;
        } else if (event_type == 3) {
            if (++lbl_8064C94C > rand() + 900) {
                fn_801294DC(actor, 0x10, 0x20, 1);
                lbl_8064C94C = 0;
            }
            if (runtime->mode == 4) {
                fn_8005FD84(object_id, object, actor, runtime, runtime->effect);
            }
            return 1;
        }
    } else if (state == 7) {
        if (event_type == 3) {
            if (runtime->mode == 4) {
                fn_8005FD84(object_id, object, actor, runtime, runtime->effect);
            }
            return 1;
        } else if (event_type == 0x36) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (event_type == 7) {
            if (fn_80035FB8(object, messages->idle_name, lbl_8064B640,
                            messages->fade_name, lbl_8064B644, messages->exit_name) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (event_type == 0x29) {
            return 1;
        } else if (event_type == 0x2A) {
            return 1;
        } else if (event_type == 0x2B) {
            return 1;
        } else if (event_type == 0x2D) {
            return 1;
        } else if (event_type == 0x2C) {
            return 1;
        } else if (event_type == 0x28) {
            return 1;
        }
    } else if (state == 6) {
        if (event_type == 3) {
            if (runtime->mode == 4) {
                fn_8005FD84(object_id, object, actor, runtime, runtime->effect);
            }
            return 1;
        } else if (event_type == 0xC) {
            if (runtime->mode == 6) {
                fn_8020123C(8, object_id, object_id, 0);
            } else {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (event_type == 7) {
            if (fn_80035FB8(object, messages->stand_name, lbl_8064B64C,
                            messages->fade_name, lbl_8064B644, messages->exit_name) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (event_type == 0xD) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            fn_8012B344(actor);
            return 1;
        } else if (event_type == 0x29) {
            return 1;
        } else if (event_type == 0x2A) {
            return 1;
        } else if (event_type == 0x2B) {
            return 1;
        } else if (event_type == 0x2D) {
            return 1;
        } else if (event_type == 0x2C) {
            return 1;
        } else if (event_type == 0x2E) {
            return 1;
        } else if (event_type == 0x28) {
            return 1;
        }
    } else if (state == 0x21) {
        if (event_type == 3) {
            if (runtime->mode == 4) {
                fn_8005FD84(object_id, object, actor, runtime, runtime->effect);
            }
            return 1;
        } else if (event_type == 7) {
            if (fn_80035FB8(object, messages->talk_name, messages->talk_end_name,
                            messages->fade_name, lbl_8064B644, messages->exit_name) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (event_type == 0x19) {
            handle = fn_801294DC(actor, 0x2A, 0x20, 8);
            if (handle != 0) {
                fn_80128C44(handle, fn_80204810, (object_id << 8) | 7);
                fn_80128C28(handle, fn_80204810, (object_id << 8) | 0x38);
            }
            return 1;
        } else if (event_type == 0x38) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (event_type == 0xEE) {
            return 1;
        } else if (event_type == 0x1E) {
            return 1;
        } else if (event_type == 0x35) {
            return 1;
        } else if (event_type == 0x37) {
            return 1;
        } else if (event_type == 0x32) {
            return 1;
        } else if (event_type == 0x69) {
            return 1;
        }
    } else if (state == 0x20) {
        if (event_type == 3) {
            if (runtime->mode == 4) {
                fn_8005FD84(object_id, object, actor, runtime, runtime->effect);
            }
            return 1;
        } else if (event_type == 5) {
            value = fn_80128EAC(actor);
            flags = fn_801290D0(actor);
            if (fn_80128E30(actor) != 0 && value == 0x4D && (flags & 1)) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
                fn_80128F74(actor, flags & ~1);
            }
            return 1;
        } else if (event_type == 7) {
            fn_802006D4(object_id, object_id, 0x20, 5, 0);
            if (fn_80035FB8(object, messages->talk_name, lbl_8064B654,
                            messages->fade_name, lbl_8064B644, messages->exit_name) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
    } else if (state == 8) {
        if (event_type == 1) {
            value = fn_8012A1BC(actor, 0x18);
            fn_8011E174(0x40, 1);
            fn_801287C4(fn_80128E30(actor), fn_80204810, (object_id << 8) | 6, value - 1);
            return 1;
        } else if (event_type == 6) {
            fn_800A5390(object, actor, runtime, event, 1, 1, 1);
            return 1;
        } else if (event_type == 0xFA) {
            return 1;
        } else if (event_type == 0x20) {
            return 1;
        } else if (event_type == 0x6B) {
            return 1;
        } else if (event_type == 0x3F) {
            return 1;
        } else if (event_type == 0x1E) {
            return 1;
        } else if (event_type == 0x35) {
            return 1;
        } else if (event_type == 0x37) {
            return 1;
        } else if (event_type == 0x32) {
            return 1;
        } else if (event_type == 0x8) {
            return 1;
        } else if (event_type == 0xB) {
            return 1;
        } else if (event_type == 0x27) {
            return 1;
        } else if (event_type == 0x69) {
            return 1;
        } else if (event_type == 0x87) {
            return 1;
        } else if (event_type == 0x3B) {
            return 1;
        } else if (event_type == 2) {
            fn_801E8328(0x1E, 0x40);
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
