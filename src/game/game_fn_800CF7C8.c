typedef unsigned char u8;

typedef struct InstanceList {
    u8 count;
    u8 padding[0x87];
    void *instances[16];
} InstanceList;

extern void *fn_80156930(void *object);
extern void *fn_80156938(void *object);
extern void *fn_8017FD98(void *instance);
extern void fn_8017FF24(void *instance, u8 clear, u8 set);
extern void fn_80148730(void *object);
extern void fn_80148254(void *object);
extern void fn_80193AB8(u8 *object);
extern void fn_801939DC(u8 *object);

/* The body matches retail; the current compiler settings emit register
 * save/restore helpers in place of the retail stmw/lmw pair. */
int fn_800CF7C8(void *unused, void *object, void *context)
{
    void *handler = fn_80156930(object);

    if (handler == (void *)fn_80148730) {
        InstanceList *list = fn_80156938(object);
        if (list != 0) {
            int i;
            for (i = 0; i < list->count; i++) {
                void *instance = list->instances[i];
                void *draw = fn_8017FD98(instance);
                if (draw == (void *)fn_80193AB8 || draw == (void *)fn_801939DC) {
                    fn_8017FF24(instance, 8, 0);
                }
            }
        }
    } else if (handler == (void *)fn_80148254) {
        void *instance = fn_80156938(object);
        if (instance != 0) {
            void *draw = fn_8017FD98(instance);
            if (draw == (void *)fn_80193AB8 || draw == (void *)fn_801939DC) {
                fn_8017FF24(instance, 8, 0);
            }
        }
    }
    return 0;
}
