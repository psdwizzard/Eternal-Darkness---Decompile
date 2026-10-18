typedef unsigned char u8;

typedef struct Group {
    u8 bytes[0xBC];
} Group;

extern Group dspStudio[];
extern int salRemoveStudioInput(Group* group, u8* source);

void hwRemoveInput(u8 index, u8* source)
{
    salRemoveStudioInput(&dspStudio[index], source);
}
