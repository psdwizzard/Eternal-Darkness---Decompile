/* Release tracked resources that are no longer referenced by an active region. */
typedef struct Entry {
    int value;
    void* object;
    int resource;
    void* callback;
    int state;
    int index;
    unsigned short flags;
    unsigned short pad;
} Entry;

typedef struct Region {
    unsigned char pad00[0x3A];
    short ids[4];
    unsigned char pad42[0x26];
    unsigned int flags;
    short side;
    short angle;
    unsigned char pad70[4];
} Region;

typedef struct RegionSet {
    unsigned char pad00[0xB0];
    unsigned short count;
    unsigned short padB2;
    Region* regions;
} RegionSet;

extern Entry lbl_80332428[];
extern const int lbl_80650058;
extern const int lbl_8065005C;
extern int (*lbl_8064CE9C)(void*, int);
extern void* fn_8015C28C(int);
extern void fn_8011DD8C(int, int);

void fn_8011DE18(void)
{
    RegionSet* set = fn_8015C28C(2);
    int indices[2];
    int* index = indices;
    Region* region;
    short first, second, third;
    int id;
    int count;
    int j;
    int found;
    int i;

    indices[0] = lbl_80650058;
    indices[1] = lbl_8065005C;

    for (i = 0; i < 2; i++, index++) {
        found = 0;
        if (lbl_80332428[*index].resource != -1) {
            id = lbl_8064CE9C(lbl_80332428[*index].callback, *index);
            region = set->regions;
            for (j = 0, count = set->count; j < count; j++, region++) {
                if (region->flags & 1) {
                    first = 0;
                    second = 0;
                    third = 0;
                    switch (region->side) {
                    case 2:
                        break;
                    case 0:
                        first = region->ids[0];
                        second = region->ids[1];
                        third = region->ids[2];
                        break;
                    case 1:
                        first = region->ids[1];
                        second = region->ids[2];
                        third = region->ids[3];
                        break;
                    }
                    if ((first != 0 && id == first) ||
                        (second != 0 && id == second) ||
                        (third != 0 && id == third)) {
                        found = 1;
                        break;
                    }
                }
            }
            if (!found) {
                fn_8011DD8C(*index, 1);
            }
        }
    }
}
