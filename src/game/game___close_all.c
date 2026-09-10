typedef unsigned char u8;

typedef enum FileKind {
    FILE_KIND_CLOSED,
    FILE_KIND_DISK,
    FILE_KIND_CONSOLE,
    FILE_KIND_UNAVAILABLE
} FileKind;

typedef struct FileMode {
    unsigned int open_mode : 2;
    unsigned int io_mode : 3;
    unsigned int buffer_mode : 2;
    unsigned int file_kind : 3;
    unsigned int binary_io : 1;
} FileMode;

typedef struct FileRecord {
    char pad0[4];
    FileMode mode;
    char pad8[4];
    u8 allocated;
    char padD[0x3F];
    struct FileRecord *next;
} FileRecord;

extern FileRecord __files[];
extern void fn_800F91F0(FileRecord *);
extern void fn_800F68D0(FileRecord *);

void __close_all(void)
{
    FileRecord *file = __files;
    FileRecord *last;

    while (file != 0) {
        if (file->mode.file_kind != FILE_KIND_CLOSED) {
            fn_800F91F0(file);
        }

        last = file;
        file = file->next;
        if (last->allocated != 0) {
            fn_800F68D0(last);
        } else {
            last->mode.file_kind = FILE_KIND_UNAVAILABLE;
            if (file != 0 && file->allocated != 0) {
                last->next = 0;
            }
        }
    }
}
