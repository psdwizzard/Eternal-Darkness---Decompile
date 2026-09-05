typedef unsigned char u8;

typedef struct Group {
    u8 bytes[0xBC];
} Group;

extern Group lbl_80628CB0[];
extern int fn_801C773C(Group* group, u8* source);

void fn_801CD000(u8 index, u8* source)
{
    fn_801C773C(&lbl_80628CB0[index], source);
}
