typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 fn_8005099C(void);
extern u16 fn_80050B08(s32, s32, s32, u8*, s32, s32, s32);
extern int fn_801ACACC(u16, u8, u32, u32);

#pragma opt_propagation off
int fn_801ACB0C(u32 arg, u32 object_id)
{
    u32 object;
    s32 owner;
    u16 id;
    object = object_id;
    owner = fn_8005099C();
    id = fn_80050B08(owner, 0, 0x44, 0, 0, 0, 0);

    if (id != 0xFFFF) {
        fn_801ACACC(id, 100, object, 30);
        id = fn_80050B08(owner, 0, 0x44, 0, 0, 0, 0);
        fn_801ACACC(id, 80, object, 45);
        id = fn_80050B08(owner, 0, 0x44, 0, 0, 0, 0);
        fn_801ACACC(id, 75, object, 50);
        id = fn_80050B08(owner, 0, 0x44, 0, 0, 0, 0);
        fn_801ACACC(id, 50, object, 60);
    }
    return 1;
}
#pragma opt_propagation reset
