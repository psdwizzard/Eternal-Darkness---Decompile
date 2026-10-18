typedef unsigned char u8;
typedef unsigned short u16;

extern int fn_80180430(u8*, u8);
extern void fn_80180518(u8*, u8, int);
extern int fn_80180454(u8*);
extern void fn_8017E1B0(u8*, u8*);
extern unsigned int rand(void);
extern void fn_8018E230(u8*, u8*, int, u8, u8, int);
extern u8 fn_8018E26C(u8*, u8*);
extern void* memcpy(void*, const void*, unsigned int);

int fn_8018322C(u8* self)
{
    int count;
    u8* entry;
    int i;

    entry = *(u8**)(self + 0x4C);
    count = self[1];
    for (i = 0; i < count; entry += 0x38, i++) {
        if (fn_80180430(self + 0x24, (u8)i) != 0) {
            entry[0x21] += self[0x8D];
            if (entry[0x21] > self[0x8E]) {
                entry[0x21] = self[0x8E];
            }
            fn_8017E1B0(entry + 0xA, entry + 0x10);
            if (entry[0] == 0) {
                self[0x8C] = rand() & 3;
                entry[0x21] = self[0x8F];
                memcpy(entry + 0xA, self + 0x10, 6);
                memcpy(entry + 0x10, self + 0x16, 6);
                fn_8018E230(entry, entry + 0x2B, 1, self[2], self[4], 0);
            } else if (fn_8018E26C(entry, entry + 0x2B) == 0 &&
                       *(u16*)(self + 0xA) >= *(u16*)(entry + 8)) {
                fn_80180518(self + 0x24, (u8)i, 0);
            }
        }
    }

    (*(u16*)(self + 0xA))++;
    if ((*(u16*)(self + 0xA) & 7) == 0 &&
        *(u16*)(self + 0xA) < *(u16*)(entry + 8)) {
        fn_80180518(self + 0x24, (u8)(*(u16*)(self + 0xA) >> 3), 1);
    }
    if (fn_80180454(self + 0x24) != 0) {
        *(u16*)(self + 0x22) = 8;
    }
    return 0;
}
