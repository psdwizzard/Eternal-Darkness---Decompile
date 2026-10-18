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
enum { NEUTRAL = 0, READING = 2, REREADING = 3 };
#define EFPOS 40

extern int errno; /* errno */

/* MSL ftell: report the logical position, including buffered I/O. */
unsigned int ftell(FileRecord *file)
{
    unsigned int pos;
    unsigned int state;

    if ((file->mode.file_kind != DISK_FILE &&
         file->mode.file_kind != CONSOLE_FILE) || file->error) {
        errno = EFPOS;
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
