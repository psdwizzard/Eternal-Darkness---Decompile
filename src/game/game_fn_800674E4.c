typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;

extern s32 lbl_8064D18C;
extern s32 fn_80036D38();
extern int fn_80201B54();
extern void* fn_80201B94();
extern s32 fn_80200C20();
extern int fn_80200C38();
extern void *fn_80201B8C();
extern s32 fn_801A717C();
extern void fn_801A7470();
extern void fn_801A74A0();
extern void fn_801A74A8();
extern unsigned long long fn_8020123C();
extern void fn_801A7228();
extern void *fn_80201814();
extern void fn_800359A0();
extern s32 fn_800AD2B4();
extern s32 fn_8015C9F0();
extern void fn_8016B400();
extern void fn_80201DD8();

void fn_800674E4(s32 context, s32 event)
{
    s32 actor = fn_80036D38(context);
    s32 has_target;
    s32 owner_object;
    s32 owner;
    u32 flags;
    s32 event_id;
    s32 state;
    s32 mode;
    s32 effect;
    s32 result;

    owner = fn_80201B54(context);
    owner_object = (s32)fn_80201B94(context);
    event_id = fn_80200C20(event);
    has_target = fn_80200C38(event) != -1;
    state = (s32)fn_80201B8C(context);
    mode = *(u8 *)(state + 0x9F);
    switch (mode) {
        case 3:
        case 4:
            effect = fn_801A717C();
            fn_801A7470(effect, 0x10);
            fn_801A74A0(effect, owner);
            fn_801A74A8(effect, owner);
            fn_8020123C(0x35, owner, owner, effect);
            fn_801A7228(effect);
            fn_800359A0(context, fn_80201814(event_id));
            break;
    }
    if (has_target) {
        result = fn_800AD2B4();
        if (lbl_8064D18C == 0x29 && fn_8015C9F0() == 0)
            fn_8016B400(0x47E, owner, 0);
        flags = *(u32 *)actor;
        flags |= 0x00400000;
        *(u32 *)actor = flags;
        *(s32 *)(actor + 0xC0) = event_id;
        fn_80201DD8(owner_object, 0);
        if (result != 0 && event_id != result)
            fn_8020123C(0x90, owner, result, 0);
    }
}
