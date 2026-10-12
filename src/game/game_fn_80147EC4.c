typedef struct Vec3s {
    short x, y, z;
} Vec3s;

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

typedef struct Entry Entry;
struct Entry {
    unsigned char unknown00[4];
    short type;
    unsigned char unknown06[0x8A];
    void *(*create)(Vec3s *, Vec3s *, Entry *);
    void *instance;
    Vec3f position;
    Vec3s rotation;
    unsigned char flags;
};

typedef struct Item Item;
typedef struct Object Object;

extern int fn_80147E64(short);
/* These calls retain arguments passed by retail but unused by the callees. */
extern Item *fn_80156DA0();
extern void fn_80156914();
extern void fn_80156904(Object *, void *);
extern void fn_801568FC(Object *, void *);
extern void fn_801568C0(Object *, void *);
extern void fn_801568B8(Object *, void *);
extern void fn_8015690C(Object *, void *);
extern void fn_80156918(Object *, void *);
extern void fn_8017FF1C(void *, unsigned char);
extern void fn_8017FD34(void *);
extern int fn_801481BC(void *, void *, int);
extern void fn_80148254(void *);
extern void fn_80148294(void *);
extern void fn_80148130(void *, Vec3f *);

Item *fn_80147EC4(Entry *entry)
{
    Vec3s position;
    Item *item = 0;

    position.x = entry->position.x;
    position.y = entry->position.y;
    position.z = entry->position.z;
    if (entry->create != 0) {
        entry->instance = entry->create(&position, &entry->rotation, entry);
    }
    if (entry->instance != 0) {
        item = fn_80156DA0(fn_80147E64(entry->type), &entry->position);
        if (item != 0) {
            fn_80156904((Object *)item, 0);
            fn_801568FC((Object *)item, (void *)fn_801481BC);
            fn_801568C0((Object *)item, 0);
            fn_801568B8((Object *)item, (void *)fn_80148254);
            fn_8015690C((Object *)item, (void *)fn_80148294);
            fn_80156914(item, fn_80148130);
            fn_80156918((Object *)item, entry->instance);
            fn_8017FF1C(entry->instance, entry->flags);
        } else if (entry->instance != 0) {
            fn_8017FD34(entry->instance);
            entry->instance = 0;
        }
    }
    return item;
}
