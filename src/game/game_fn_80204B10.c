typedef struct Link80204B10 Link80204B10;
typedef struct Object80204B10 Object80204B10;
typedef struct Group80204B10 Group80204B10;

struct Link80204B10 {
    void *value;
    Link80204B10 *next;
    int key;
};

struct Group80204B10 {
    void *field_0;
    Link80204B10 *volatile links;
};

struct Object80204B10 {
    void *field_0;
    Object80204B10 *next;
    unsigned char pad_08[8];
    int index;
    unsigned char pad_14[28];
    Group80204B10 *group;
};

extern Group80204B10 *fn_80204A8C(void);
extern void *fn_80201B9C(void);
extern unsigned int fn_80204A94(void *link, void *object);

Group80204B10 *fn_80204B10(void *object, int *index)
{
    Group80204B10 *group;
    Link80204B10 *links;
    Object80204B10 *current;

    group = fn_80204A8C();
    current = fn_80201B9C();
    links = group->links;

    if (fn_80204A94(links, object) != 0) {
        if (index != 0) {
            *index = -1;
        }
        return fn_80204A8C();
    }

    while (current != 0) {
        if (current->group != 0 &&
            fn_80204A94(current->group->links, object) != 0) {
            if (index != 0) {
                *index = current->index;
            }
            return current->group;
        }
        current = current->next;
    }

    if (index != 0) {
        *index = 0;
    }
    return 0;
}
