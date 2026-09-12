#pragma use_lmw_stmw on

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Entry80204318 {
    char pad00[4];
    struct Entry80204318 *next;
    char pad08[8];
    int identifier;
    char pad14[0x20];
    void *transform;
} Entry80204318;

typedef struct Manager80204318 {
    char pad00[4];
    Entry80204318 *head;
} Manager80204318;

extern Manager80204318 *fn_802014AC(void);
extern int fn_80201B54(void *object);
extern void *fn_80201BC8(void *object);
extern int fn_80201EB8(void *object);
extern void fn_8011F114(Vec3 *position, void *transform);
extern u32 fn_80178E94(Vec3 *first, Vec3 *second);
extern u64 fn_8020123C(int type, int source, int target, int value);

Entry80204318 *fn_80204318(void *object, int value)
{
    Manager80204318 *manager;
    Entry80204318 *current;
    Entry80204318 *best;
    Vec3 source_position;
    Vec3 candidate_position;
    void *transform;
    int source;
    int environment;
    int candidate_environment;
    int best_distance;
    int distance;

    manager = fn_802014AC();
    best_distance = 0xFFFFFF;
    best = 0;
    transform = fn_80201BC8(object);
    fn_8011F114(&source_position, transform);
    source = fn_80201B54(object);
    current = manager->head;

    while (current != 0) {
        if ((u32)(fn_8020123C(0x3B, source, current->identifier, value) &
                  0xFFFFFFFFULL) != 0 &&
            current->identifier != source && current->transform != 0) {
            environment = fn_80201EB8(object);
            candidate_environment = fn_80201EB8(current);
            if (candidate_environment == environment) {
                fn_8011F114(&candidate_position, current->transform);
                distance = fn_80178E94(&source_position, &candidate_position);
                if (distance < best_distance) {
                    best_distance = distance;
                    best = current;
                }
            }
        }
        current = current->next;
    }

    return best;
}
