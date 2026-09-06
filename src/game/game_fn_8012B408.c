typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Entry8012B408 {
    u8 pad[6];
    u16 id;
} Entry8012B408;

typedef struct Output8012B408 {
    int id;
    Entry8012B408* entry;
    void* owner;
    u8 kind;
    u8 flags;
    u8 pad[2];
} Output8012B408;

typedef struct Owner8012B408 {
    u8 pad[0x14];
    u16 count;
    u8 pad2[2];
    Entry8012B408* entries;
} Owner8012B408;

void fn_8012B408(Owner8012B408* owner, Output8012B408* output)
{
    Entry8012B408* entry;
    int index;

    if (owner->count == 0) {
        return;
    }
    entry = owner->entries;
    for (index = 0; index < owner->count; index++, entry = (Entry8012B408*)((u8*)entry + 0x128), output++) {
        output->id = entry->id;
        output->entry = entry;
        output->owner = owner;
        output->kind = 8;
        output->flags = 0;

        switch (output->id) {
        case 142:
            output->kind = 0x19;
            break;
        case 48: case 49: case 50: case 51: case 52:
            output->flags = 0x40;
            output->kind = 0x14;
            break;
        case 11: case 12:
        case 69: case 70: case 71:
            output->kind = 1;
            break;
        case 0:
            output->flags = 0x40;
            break;
        case 1:
            output->flags = 1;
            output->kind = 0xC;
            break;
        case 2:
            output->flags = 2;
            output->kind = 0xC;
            break;
        case 3:
            output->flags = 8;
            output->kind = 0xC;
            break;
        case 4: case 5: case 6: case 7: case 8: case 9:
        case 65:
        case 108: case 109: case 110: case 111: case 112: case 113:
            output->flags = 0x20;
            output->kind = 6;
            break;
        case 15: case 16: case 17:
            output->flags = output->kind = 0x10;
            break;
        case 127:
            output->kind = 1;
            break;
        case 125:
            output->kind = 8;
            break;
        case 124:
            output->kind = 1;
            break;
        case 24:
            output->kind = 6;
            break;
        case 144:
            output->kind = 1;
            break;
        case 76:
            output->kind = 2;
            break;
        default:
            output->flags = 0;
            break;
        }
    }
}
