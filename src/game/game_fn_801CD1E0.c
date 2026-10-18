typedef unsigned char u8;

extern void aramFreeStreamBuffer(u8 index);

void hwExitStream(u8 index)
{
    aramFreeStreamBuffer(index);
}
