typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int lbl_8064CB7C;
extern float lbl_8064F1B0;

extern void *fn_801A7778(void *event);
extern void *fn_8020499C(void *state);
/* These forwarding accessors return the values left by their callees. */
extern u32 fn_801A78EC(void *event);
extern u32 fn_801A7910(void *event);
extern u8 fn_801A7934(void *event);
extern void *fn_800BF0C0(void *context, void *event);
extern void fn_800E87E0(void *, int, int, int, int, int, float);
extern u16 fn_80157994(void *state);
extern int fn_80201B54(void *object);
extern u32 fn_801A7498(void *event);
extern void fn_800CC140(int owner_id, int object_id, int unused, int mask, int flags);
extern void *fn_80201814(int id);
extern int fn_80204EC8(void *object, void *target);
extern int fn_801E8328(u32 kind, u32 object);
extern void *fn_8004918C(void);
extern void fn_8004948C(void *object, void *destination, int mode);
extern void fn_801A7864(void *event);

int fn_800C328C(void *context, void *event)
{
    void *event_object;
    void *object;
    u8 type;
    void *owner;
    void *state;
    u32 flags;
    int result;
    int object_id;
    int first;
    int owner_id;
    int blocked;
    u32 flags2;
    void *destination;
    int second;

    /* Preserve the event pointer through the original 32-bit conversion. */
    event_object = (void *)(u32)event;
    result = 1;
    blocked = 0;
    state = fn_801A7778(event_object);
    object = fn_8020499C(state);
    flags = fn_801A78EC(event_object);
    flags2 = fn_801A7910(event_object);
    first = ((flags & 0x40) != 0 || (flags2 & 0x400) != 0);
    type = fn_801A7934(event_object);
    second = (type != 0 || (flags2 & 0x100) != 0);

    if (second && first) {
        blocked = 1;
    }
    if (!blocked && lbl_8064CB7C == 0) {
        fn_800BF0C0(context, event_object);
    }
    fn_800E87E0(event_object, 1, 1, -1, -1, -1, lbl_8064F1B0);
    if (!blocked && lbl_8064CB7C == 0) {
        result = fn_80157994(state);
        if (result == 0) {
            object_id = fn_80201B54(object);
            owner_id = fn_801A7498(event_object);

            fn_800CC140(owner_id, object_id, 0, 0, 0);
            owner = fn_80201814(owner_id);
            fn_80204EC8(owner, object);
            fn_801E8328(2, (u32)object);
            destination = fn_8004918C();
            fn_8004948C(owner, destination, 0);
            fn_801A7864(destination);
        }
    }
    return result;
}
