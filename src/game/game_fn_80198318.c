typedef signed short s16;
typedef unsigned char u8;

void fn_80198318(u8* entries, int start, u8 count, s16* vertices,
                 int vertex_index, int shift)
{
    s16* vertex;
    u8* entry = entries + start * 0x38;
    vertex = vertices + vertex_index * 3;

    for (; start < count; start++) {
        vertex[3] = vertex[0] + (*(s16*)(entry + 0x10) << shift);
        vertex[4] = vertex[1] + (*(s16*)(entry + 0x12) << shift);
        vertex[5] = vertex[2] + (*(s16*)(entry + 0x14) << shift);
        entry += 0x38;
        vertex += 6;
    }
}
