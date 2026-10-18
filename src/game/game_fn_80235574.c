/* res0_unpack: Vorbis residue 0/1/2 header unpack (res0_unpack). */

typedef int s32;
typedef unsigned int u32;

typedef struct ResidueInfo {
    s32 begin;
    s32 end;
    s32 grouping;
    s32 partitions;
    s32 groupbook;
    s32 secondstages[64];
    s32 booklist[256];
    unsigned char rest[0x914 - 0x514];
} ResidueInfo;

typedef struct CodecSetup {
    unsigned char pad[0x1c];
    s32 books;
} CodecSetup;

typedef struct VorbisInfo {
    unsigned char pad[0x1c];
    CodecSetup *codec_setup;
} VorbisInfo;

extern s32 oggpack_read(void *opb, s32 bits);
extern void *fn_8022F780(s32 size);

static int icount(u32 v) {
    int ret = 0;
    while (v) {
        ret += v & 1;
        v >>= 1;
    }
    return ret;
}

ResidueInfo *res0_unpack(VorbisInfo *vi, void *opb) {
    int j;
    int acc = 0;
    ResidueInfo *info = fn_8022F780(sizeof(ResidueInfo));
    CodecSetup *ci = vi->codec_setup;

    info->begin = oggpack_read(opb, 24);
    info->end = oggpack_read(opb, 24);
    info->grouping = oggpack_read(opb, 24) + 1;
    info->partitions = oggpack_read(opb, 6) + 1;
    info->groupbook = oggpack_read(opb, 8);

    for (j = 0; j < info->partitions; j++) {
        int cascade = oggpack_read(opb, 3);
        if (oggpack_read(opb, 1)) {
            cascade |= oggpack_read(opb, 5) << 3;
        }
        info->secondstages[j] = cascade;
        acc += icount(cascade);
    }
    for (j = 0; j < acc; j++) {
        info->booklist[j] = oggpack_read(opb, 8);
    }

    if (info->groupbook >= ci->books) goto errout;
    for (j = 0; j < acc; j++) {
        if (info->booklist[j] >= ci->books) goto errout;
    }

    return info;
errout:
    return 0;
}
