typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Command {
    u8 value;
    u8 flags;
    u8 pad[2];
    u32 data;
} Command;

typedef struct CommandList {
    Command commands[4];
    u8 pad[2];
    u8 count;
} CommandList;

extern u32 inpTranslateExCtrl(u32);

void inpAddCtrl(CommandList* list, u32 value, u32 data, u8 flags, u32 direct)
{
    u32 index;

    if (flags == 0) {
        list->count = 0;
    }
    index = list->count;
    if (index < 4) {
        list->count = index + 1;
        if (direct == 0) {
            value = inpTranslateExCtrl(value);
        } else {
            flags |= 0x10;
        }
        list->commands[(u8)index].value = value;
        list->commands[(u8)index].flags = flags;
        list->commands[(u8)index].data = data;
    }
}
