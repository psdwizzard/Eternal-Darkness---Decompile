typedef struct Shape Shape;
typedef struct Obstacle Obstacle;
typedef struct Result Result;

typedef struct CollisionEntry {
    unsigned int condition;
    unsigned char obstacle_index;
    unsigned char flags;
} CollisionEntry;

typedef struct CollisionWorld {
    unsigned char pad00[0x44];
    unsigned char* obstacles;
    unsigned char pad48[4];
    void* context;
} CollisionWorld;

extern void* lbl_8064C4E0;
extern void* lbl_8064C4E4;

extern int fn_801E79FC(void*, unsigned int);
extern int fn_8013E284(const Shape*, const Obstacle*, const void*, Result*);

int fn_801374D8(void* object, const Shape* shape, const CollisionEntry* entry,
                const CollisionWorld* world, Result* result)
{
    unsigned char flags;

    if (fn_801E79FC(lbl_8064C4E0, entry->condition) != 0) {
        flags = entry->flags;
        if (((flags & 2) == 0 || object != lbl_8064C4E4) &&
            ((flags & 1) == 0 || object == lbl_8064C4E4)) {
            return fn_8013E284(
                shape,
                (const Obstacle*)(world->obstacles +
                                  entry->obstacle_index * 0x38),
                world->context, result);
        }
    }
    return 0;
}
