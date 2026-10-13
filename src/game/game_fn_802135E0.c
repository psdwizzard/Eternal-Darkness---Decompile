typedef unsigned int u32;
typedef int BOOL;

#define TRUE 1
#define FALSE 0

typedef struct FSTEntry {
    u32 isDirAndStringOff;
    u32 parentOrPosition;
    u32 nextEntryOrLength;
} FSTEntry;

extern FSTEntry *FstStart_8064D9E4;
extern u32 lbl_8064D9F0; /* currentDirectory */

u32 fn_80213480(u32 entry, char *path, u32 maxLength);

#define entryIsDir(i) (((FstStart_8064D9E4[i].isDirAndStringOff & 0xff000000) == 0) ? FALSE : TRUE)

/* DVDConvertEntrynumToPath */
static inline BOOL convertEntrynumToPath(u32 entry, char *path, u32 maxlen)
{
    u32 loc;

    loc = fn_80213480(entry, path, maxlen);
    if (loc == maxlen) {
        path[maxlen - 1] = '\0';
        return FALSE;
    }

    if (entryIsDir(entry)) {
        if (loc == maxlen - 1) {
            path[loc] = '\0';
            return FALSE;
        }
        path[loc++] = '/';
    }

    path[loc] = '\0';
    return TRUE;
}

/* DVDGetCurrentDir */
BOOL fn_802135E0(char *path, u32 maxlen)
{
    return convertEntrynumToPath(lbl_8064D9F0, path, maxlen);
}
