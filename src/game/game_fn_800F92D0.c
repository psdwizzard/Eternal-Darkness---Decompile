typedef struct FileRecord {
    int handle;
    struct {
        unsigned short open_mode : 2;
        unsigned short io_mode : 3;
        unsigned short buffer_mode : 2;
        unsigned short file_kind : 3;
        unsigned short orientation : 2;
        unsigned short binary_io : 1;
        unsigned short reserved : 3;
    } mode;
    unsigned short reserved06;
    struct {
        unsigned char io_state : 3;
        unsigned char reserved : 5;
    } state;
    unsigned char eof;
    unsigned char error;
    unsigned char reserved0B[0xD];
    unsigned int position;
    unsigned char *buffer;
    unsigned int buffer_size;
    unsigned char *buffer_ptr;
    unsigned int buffer_space;
    unsigned int alignment_mask;
    char reserved30[4];
    unsigned int buffer_position;
    int (*position_fn)(int, long *, int, void *);
    char reserved3C[4];
    int (*write)(int, unsigned char *, unsigned int *, void *);
    char reserved44[4];
    void *ref;
} FileRecord;

enum { DISK_FILE = 1, CONSOLE_FILE = 2 };
enum { READ_WRITE = 3 };
enum { NEUTRAL = 0, WRITING = 1, READING = 2, REREADING = 3 };
enum { SEEK_CUR = 1, SEEK_END = 2 };
#define EFPOS 40

extern int lbl_8064CC50; /* errno */

int __flush_buffer(FileRecord *, unsigned int *);

/* MSL ftell, inlined into fseek */
static inline unsigned int file_tell(FileRecord *file)
{
    unsigned int pos;
    unsigned int state;

    if ((file->mode.file_kind != DISK_FILE &&
         file->mode.file_kind != CONSOLE_FILE) || file->error) {
        lbl_8064CC50 = EFPOS;
        return -1;
    }
    state = file->state.io_state;
    if (state == NEUTRAL) {
        return file->position;
    }
    pos = file->buffer_position + (file->buffer_ptr - file->buffer);
    if (state >= REREADING) {
        pos -= state - READING;
    }
    return pos;
}

int fn_800F92D0(void *stream, long offset, int origin)
{
    FileRecord *file = stream;
    int (*position_fn)(int, long *, int, void *);

    if (file->mode.file_kind != DISK_FILE || file->error) {
        lbl_8064CC50 = EFPOS;
        return -1;
    }

    if (file->state.io_state == WRITING) {
        if (__flush_buffer(file, 0)) {
            file->error = 1;
            file->buffer_space = 0;
            lbl_8064CC50 = EFPOS;
            return -1;
        }
    }

    if (origin == SEEK_CUR) {
        origin = 0;
        offset += file_tell(file);
    }

    if (origin != SEEK_END && file->mode.io_mode != READ_WRITE &&
        (file->state.io_state == READING ||
         file->state.io_state == REREADING)) {
        if ((unsigned long)offset >= file->position ||
            (unsigned long)offset < file->buffer_position) {
            file->state.io_state = NEUTRAL;
        } else {
            file->buffer_ptr =
                file->buffer + (offset - file->buffer_position);
            file->buffer_space = file->position - offset;
            file->state.io_state = READING;
        }
    } else {
        file->state.io_state = NEUTRAL;
    }

    if (file->state.io_state == NEUTRAL) {
        position_fn = file->position_fn;
        if (position_fn != 0 &&
            position_fn(file->handle, &offset, origin, file->ref)) {
            file->error = 1;
            file->buffer_space = 0;
            lbl_8064CC50 = EFPOS;
            return -1;
        }
        file->eof = 0;
        file->position = offset;
        file->buffer_space = 0;
    }

    return 0;
}
