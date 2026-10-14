/* __CARDCompareFileName: compare a CARD directory name with a C string. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef int BOOL;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 reserved06[2];
    u8 fileName[32];
    u8 reserved28[0xE];
    u16 startBlock;
    u16 length;
    u8 reserved3A[6];
} CARDDir;

BOOL fn_80221430(CARDDir *ent, const char *fileName)
{
    char *entName;
    char c1;
    char c2;
    int n;

    entName = (char *)ent->fileName;
    n = 32;
    while (0 <= --n) {
        if ((c1 = *entName++) != (c2 = *fileName++)) {
            return 0;
        } else if (c2 == '\0') {
            return 1;
        }
    }

    if (*fileName == '\0') {
        return 1;
    }

    return 0;
}

