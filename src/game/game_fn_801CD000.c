typedef unsigned char u8;

typedef struct Group {
    u8 bytes[0xBC];
} Group;

extern Group dspStudio[];
extern int salAddStudioInput(Group* group, u8* source);

void hwAddInput(u8 index, u8* source)
{
    salAddStudioInput(&dspStudio[index], source);
}
