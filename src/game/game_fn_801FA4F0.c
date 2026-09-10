typedef unsigned short u16;
typedef unsigned long size_t;

extern int lbl_8064C3A4;
extern int lbl_8064C3A8;
extern int lbl_8064D7A4;
extern int lbl_8064D79C;
extern int lbl_8064D7A8;
extern int lbl_8064D7BC;
typedef struct Object {
    unsigned char bytes[0x88];
} Object;

typedef struct ObjectState {
    Object active[24];
    Object object24;
    Object object25;
    unsigned char tail[0x64];
    unsigned char padE34[0x6A8];
    unsigned char saved_tail[0x64];
    Object saved_active[24];
    Object saved_object24;
    Object saved_object25;
} ObjectState;

extern ObjectState lbl_8063C6B8;

extern void* memcpy(void*, const void*, size_t);

void fn_801FA4F0(u16 state, int token)
{
    ObjectState* data = &lbl_8063C6B8;

    if (state == 1) {
        if (lbl_8064C3A4 == 2 && lbl_8064D79C == 0) {
            memcpy(&lbl_8064D7A8, &lbl_8064D7BC, 4);
            memcpy(&lbl_8064D7A4, &lbl_8064C3A8, 4);
            memcpy(data->saved_tail, data->tail, 0x64);
            memcpy(&data->saved_active[0], &data->active[0], 0x660);
            memcpy(&data->saved_active[12], &data->active[12], 0x660);
            memcpy(&data->saved_object24, &data->object25, 0x88);
            memcpy(&data->saved_object25, &data->object24, 0x88);
            lbl_8064D79C = token;
            lbl_8064C3A4 = 1;
        }
    } else if (state == 2) {
        if (lbl_8064C3A4 == 1 && lbl_8064D79C == token) {
            memcpy(&lbl_8064D7BC, &lbl_8064D7A8, 4);
            memcpy(&lbl_8064C3A8, &lbl_8064D7A4, 4);
            memcpy(data->tail, data->saved_tail, 0x64);
            memcpy(&data->active[0], &data->saved_active[0], 0x660);
            memcpy(&data->active[12], &data->saved_active[12], 0x660);
            memcpy(&data->object25, &data->saved_object24, 0x88);
            memcpy(&data->object24, &data->saved_object25, 0x88);
            lbl_8064C3A4 = 2;
            lbl_8064D79C = 0;
        }
    }
}
