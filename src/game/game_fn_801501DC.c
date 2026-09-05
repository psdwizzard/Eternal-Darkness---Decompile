typedef unsigned char u8;
typedef unsigned short u16;

extern void* fn_8017FDE4(void*);
extern void fn_8017E1B0(void*, void*);
extern void fn_80149E28(void*);

#pragma opt_propagation off
void fn_801501DC(u8* instance)
{
    u8* self = instance;
    u8* embedded;
    embedded = self + 8;

    if (*(void**)(self + 0xA4) != 0) {
        fn_8017E1B0(fn_8017FDE4(*(void**)(self + 0xA4)), embedded);
    }
    if (*(u16*)(self + 0x132C) > 25) {
        fn_80149E28(self);
    }
}
#pragma opt_propagation reset
