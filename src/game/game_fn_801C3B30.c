typedef unsigned char u8;
typedef unsigned short u16;

extern void InsertData(u16, void*, u8, void*);

void ScanIDList(u16* ids, void* archive, u8 type, void* direct)
{
    while (*ids != 0xFFFF) {
        if (*ids & 0x8000) {
            u16 id = *ids & 0x3FFF;
            while (id <= ids[1]) {
                InsertData(id, archive, type, direct);
                id++;
            }
            ids += 2;
        } else {
            InsertData(*ids++, archive, type, direct);
        }
    }
}
