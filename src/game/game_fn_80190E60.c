typedef unsigned char u8;
typedef unsigned short u16;

extern int rand(void);
extern void fn_80179904(void*, int);
extern void* fn_80190D7C(void*, void*, void*);

void* fn_80190E60(void* arg0, u16* position, u8* config)
{
    position[0] = 0x10 - (rand() & 0x1F);
    position[1] = 0x10 - (rand() & 0x1F);
    position[2] = 0x10 - (rand() & 0xF);
    fn_80179904(position, config[0x18]);
    return fn_80190D7C(arg0, position, config);
}
