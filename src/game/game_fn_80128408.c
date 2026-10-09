typedef unsigned char u8;

typedef struct Entry1238 {
    int state;
    u8 pad[0x1234];
} Entry1238;

extern Entry1238 lbl_8056FA80[];

int fn_80128408(void)
{
    int i;
    int count;

    count = 0;
    for (i = 0; i < 48; i++) {
        if (lbl_8056FA80[i].state == 0) {
            count++;
        }
    }
    return count;
}
