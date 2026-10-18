typedef unsigned short u16;

extern u16 seqMIDIPriority[][16];

u16 seqGetMIDIPriority(unsigned char row, unsigned char column)
{
    return seqMIDIPriority[row][column];
}
