/* fn_8021302C (0x8021302C, 756 bytes): DVDConvertPathToEntrynum (SDK dvdfs.c) */

typedef int s32;
typedef unsigned int u32;
typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef struct FSTEntry {
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
} FSTEntry;

extern int fn_800F8CF0(int); /* tolower */
extern void fn_8020C5D0(const char *, int, const char *, ...); /* OSPanic */

extern FSTEntry *FstStart_8064D9E4;
extern char *FstStringStart_8064D9E8;
extern u32 lbl_8064D9F0; /* currentDirectory */
extern u32 __DVDLongFileNameFlag;
extern const char lbl_8064C400[8]; /* "dvdfs.c" */
extern char lbl_802FE150[];

#define entryIsDir(i) (((FstStart_8064D9E4[i].isDirAndStringOff & 0xff000000) == 0) ? FALSE : TRUE)
#define stringOff(i) (FstStart_8064D9E4[i].isDirAndStringOff & ~0xff000000)
#define parentDir(i) (FstStart_8064D9E4[i].parentOrPosition)
#define nextDir(i) (FstStart_8064D9E4[i].nextEntryOrLength)

static inline BOOL isSame(const char *path, const char *string) {
    while (*string != '\0') {
        if (fn_800F8CF0(*path++) != fn_800F8CF0(*string++)) {
            return FALSE;
        }
    }
    if ((*path == '/') || (*path == '\0')) {
        return TRUE;
    }
    return FALSE;
}

s32 fn_8021302C(char *pathPtr) {
    const char *ptr;
    char *stringPtr;
    BOOL isDir;
    u32 length;
    u32 dirLookAt;
    u32 i;
    const char *origPathPtr = pathPtr;
    const char *extentionStart;
    BOOL illegal;
    BOOL extention;

    dirLookAt = lbl_8064D9F0;

    while (1) {
        if (*pathPtr == '\0') {
            return (s32)dirLookAt;
        } else if (*pathPtr == '/') {
            dirLookAt = 0;
            pathPtr++;
            continue;
        } else if (*pathPtr == '.') {
            if (*(pathPtr + 1) == '.') {
                if (*(pathPtr + 2) == '/') {
                    dirLookAt = parentDir(dirLookAt);
                    pathPtr += 3;
                    continue;
                } else if (*(pathPtr + 2) == '\0') {
                    return (s32)parentDir(dirLookAt);
                }
            } else if (*(pathPtr + 1) == '/') {
                pathPtr += 2;
                continue;
            } else if (*(pathPtr + 1) == '\0') {
                return (s32)dirLookAt;
            }
        }

        if (__DVDLongFileNameFlag == 0) {
            extention = FALSE;
            illegal = FALSE;

            for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++) {
                if (*ptr == '.') {
                    if ((ptr - pathPtr > 8) || (extention == TRUE)) {
                        illegal = TRUE;
                        break;
                    }
                    extention = TRUE;
                    extentionStart = ptr + 1;
                } else if (*ptr == ' ') {
                    illegal = TRUE;
                }
            }

            if ((extention == TRUE) && (ptr - extentionStart > 3)) {
                illegal = TRUE;
            }

            if (illegal) {
                fn_8020C5D0(lbl_8064C400, 376, lbl_802FE150, origPathPtr);
            }
        } else {
            for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++) {
            }
        }

        isDir = (*ptr == '\0') ? FALSE : TRUE;
        length = (u32)(ptr - pathPtr);

        ptr = pathPtr;

        for (i = dirLookAt + 1; i < nextDir(dirLookAt); i = entryIsDir(i) ? nextDir(i) : (i + 1)) {
            if ((entryIsDir(i) == FALSE) && (isDir == TRUE)) {
                continue;
            }

            stringPtr = FstStringStart_8064D9E8 + stringOff(i);

            if (isSame(ptr, stringPtr) == TRUE) {
                goto next_hier;
            }
        }

        return -1;

    next_hier:
        if (isDir == FALSE) {
            return (s32)i;
        }

        dirLookAt = i;
        pathPtr += length + 1;
    }
}
