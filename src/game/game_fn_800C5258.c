typedef unsigned char u8;

typedef struct Owner {
    u8 pad[0x8C];
    void **data;
} Owner;

extern void *fn_801A7498(void *);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern unsigned long long fn_8020123C();

#pragma opt_propagation off
int fn_800C5258(void *unused, void *object)
{
    void *saved_object;
    void *value;
    Owner *owner;

    saved_object = object;
    value = fn_801A7498(saved_object);
    fn_80201814(value);
    owner = ((Owner *)fn_80201B8C());
    fn_8020123C(0x31, value, owner->data[7], saved_object);
    return 1;
}
#pragma opt_propagation reset
