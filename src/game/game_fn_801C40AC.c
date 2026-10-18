typedef unsigned char u8;
typedef unsigned short u16;

extern int seqPlaySong(u16, u16, void*, void*, u8, void*);

int sndSeqPlayEx(u16 resource_id, u16 record_id, void* arg2, void* arg3,
                void* arg4)
{
    return seqPlaySong(resource_id, record_id, arg2, arg3, 0, arg4);
}
