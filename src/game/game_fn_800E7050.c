typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct PathObject {
    void *object;
    s16 field4;
    u16 duration;
    u8 kind;
    u8 pad[0x33];
} PathObject;

typedef struct Entry {
    int id;
    s16 field4;
    u16 kind;
    u16 period;
    u16 countdown;
    PathObject *source;
} Entry;

extern Entry lbl_80325DB8[10];
extern void *fn_8015C5E4(int, u16 *);
extern void fn_800E7838(void);

void fn_800E7050(int owner, void *object)
{
    u16 count;
    PathObject *objects;
    PathObject *source;
    u8 slot;
    u16 index;

    objects = fn_8015C5E4(2, &count);
    if (objects != 0) {
        for (slot = 0; slot < 10; slot++) {
            if (lbl_80325DB8[slot].id == 0) {
                lbl_80325DB8[slot].id = owner;
                for (index = 0; index < count; index++) {
                    if (object == objects[index].object) {
                        break;
                    }
                }
                /* If no object matches, retail reads one past the objects array. */
                source = &objects[index];
                lbl_80325DB8[slot].field4 = source->field4;
                lbl_80325DB8[slot].kind = source->kind;
                lbl_80325DB8[slot].period = source->duration + 10;
                lbl_80325DB8[slot].source = source;
                lbl_80325DB8[slot].countdown = 0;
                fn_800E7838();
                break;
            }
        }
    }
}
