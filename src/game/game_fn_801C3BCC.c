typedef unsigned char u8;
typedef unsigned short u16;

extern void InsertData(u16, void*, u8, void*);

void ScanIDListReverse(u16* ids, void* archive, u8 type, void* direct)
{
    short id;
    u16* cursor;

    if (*ids == 0xFFFF) {
        return;
    }

    cursor = ids;
    while (*cursor != 0xFFFF) {
        cursor++;
    }
    cursor--;

    while (cursor >= ids) {
        if (cursor != ids) {
            if (cursor[-1] & 0x8000) {
                id = *cursor;
                while (id >= (short)(cursor[-1] & 0x3FFF)) {
                    InsertData(id, archive, type, direct);
                    id--;
                }
                cursor -= 2;
            } else {
                InsertData(*cursor, archive, type, direct);
                cursor--;
            }
        } else {
            InsertData(*cursor, archive, type, direct);
            cursor--;
        }
    }
}
