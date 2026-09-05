typedef unsigned short u16;

typedef struct Header {
    u16 magic;
    u16 version;
} Header;

#pragma opt_propagation off
int fn_80125D50(Header* header)
{
    int new_enough;
    int version;

    version = header->version;
    new_enough = 0;
    if (version >= 45) {
        new_enough = 1;
    }
    return new_enough && header->magic == 252;
}
#pragma opt_propagation reset
