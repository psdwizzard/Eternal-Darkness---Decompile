typedef unsigned char u8;
typedef unsigned short u16;

extern void* fn_8017FDE4(void*);
extern void fn_8017E1B0(void*, void*);
extern void fn_80186A80(void*, int);
extern void fn_80149E28(void*);

#pragma opt_propagation off
void fn_8015023C(u8* instance)
{
    u8* self = instance;
    u8* embedded;
    embedded = self + 8;

    if (*(void**)(self + 0xA4) != 0) {
        fn_8017E1B0(fn_8017FDE4(*(void**)(self + 0xA4)), embedded);
    }
    if (*(unsigned short*)(self + 0x132C) == embedded[7]) {
        if (*(void**)(embedded + 0x9C) != 0) {
            fn_80186A80(*(void**)(embedded + 0x9C), embedded[6]);
        }
    } else if (*(unsigned short*)(self + 0x132C) > 30) {
        fn_80149E28(self);
    }
}
#pragma opt_propagation reset
