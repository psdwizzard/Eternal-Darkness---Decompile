typedef unsigned int u32;

extern void sndStreamARAMUpdate(u32 stid, u32 off1, u32 len1, u32 off2, u32 len2);

void fn_80237EAC(u32 streamId, u32 half) {
    sndStreamARAMUpdate(streamId, half << 13, 0x2000, 0, 0);
}
