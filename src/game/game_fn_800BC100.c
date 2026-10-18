typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;

typedef struct Result {
    Vec3 normal;
    Vec3 point;
} Result;

typedef struct Owner Owner;

typedef struct Marker {
    const short *position;
    unsigned char pad04[0x32];
    unsigned char id;
    unsigned char pad37;
} Marker;

typedef struct Candidate {
    Marker *marker;
    unsigned int distance;
    unsigned int other;
} Candidate;

extern void fn_800BCCC4(const short *source, Vec3 *result);
extern unsigned int rand(void);
extern void fn_8013F3C0(Shape *out, const Vec3 *first, const Vec3 *second, float radius);
extern void *fn_8015C2FC(int selector);
extern void *fn_8013FBE4(Owner *owner, const void *value, Result *out,
                        void *context, unsigned int flags);
extern unsigned int fn_80178E94(const float *a, const float *b);
extern void *memset(void *dest, int value, unsigned long size);

extern Marker *lbl_80320B98[50];
extern Marker *lbl_8064CA74;
extern const float lbl_8064F0C8;
extern const float lbl_8064F0CC;

Marker *fn_800BC100(const short *key, Vec3 *origin, int *outIndex, unsigned int flags,
                    int *minDist, int *maxDist, Vec3 *other)
{
    Vec3 pos;
    Result hit;
    Shape shape;
    Candidate slots[8];
    unsigned int dist;
    int visible;
    int count;
    Marker *found;
    unsigned int best;
    int collect;
    int i;

    best = (flags & 2) ? 0xFFFFFFFF : 0;
    collect = flags & 0x80;
    found = 0;
    if (collect) {
        memset(slots, 0, sizeof(slots));
        best = *minDist;
    }
    if (!(flags & 0x10) && outIndex != 0) {
        *outIndex = -1;
    }
    if (key == 0 && (flags & 1)) {
        return 0;
    }
    if ((flags & 8) && maxDist == 0 && minDist == 0) {
        Marker *marker = lbl_8064CA74;
        for (count = 0; marker->position != 0 && count < 500; count++) {
            marker++;
        }
        count = (int)rand() % count;
        if (outIndex != 0) {
            *outIndex = count;
        }
        return &lbl_8064CA74[count];
    }
    if ((flags & 8) && (maxDist != 0 || minDist != 0)) {
        int lo;
        int hi;
        int n;
        int total;

        lo = minDist != 0 ? *minDist : 0;
        hi = maxDist != 0 ? *maxDist : 128000;
        memset(lbl_80320B98, 0, sizeof(lbl_80320B98));
        n = 0;
        total = 0;
        for (; lbl_8064CA74[n].position != 0 && n < 500 && total < 50; n++) {
            int d;
            fn_800BCCC4(lbl_8064CA74[n].position, &pos);
            d = fn_80178E94(&origin->x, &pos.x);
            if (d <= hi && d >= lo) {
                lbl_80320B98[total] = &lbl_8064CA74[n];
                total++;
            }
        }
        if (total != 0) {
            n = (int)rand() % total;
            if (outIndex != 0) {
                *outIndex = lbl_80320B98[n]->id;
            }
            return lbl_80320B98[n];
        }
        return 0;
    }
    for (i = 0; lbl_8064CA74[i].position != 0 && i < 500; i++) {
        if (flags & 1) {
            if (key == lbl_8064CA74[i].position) {
                if (outIndex != 0) {
                    *outIndex = i;
                }
                return &lbl_8064CA74[i];
            }
        } else if (flags & 0x10) {
            if (*outIndex == lbl_8064CA74[i].id) {
                if (outIndex != 0) {
                    *outIndex = i;
                }
                return &lbl_8064CA74[i];
            }
        } else if (flags & 2) {
            fn_800BCCC4(lbl_8064CA74[i].position, &pos);
            dist = fn_80178E94(&pos.x, &origin->x);
            if (dist < best) {
                visible = 1;
                if (flags & 0x40) {
                    origin->z += lbl_8064F0C8;
                    pos.z += lbl_8064F0C8;
                    fn_8013F3C0(&shape, origin, &pos, lbl_8064F0CC);
                    if (fn_8013FBE4(fn_8015C2FC(2), &shape, &hit, 0, 8) != 0) {
                        visible = 0;
                    }
                    origin->z -= lbl_8064F0C8;
                    pos.z -= lbl_8064F0C8;
                }
                if (visible) {
                    if (collect) {
                        int j;
                        int empty = -1;
                        int replace = -1;
                        int slot;
                        for (j = 0; empty == -1 && j < 8; j++) {
                            if (slots[j].marker == 0) {
                                empty = j;
                            } else if (slots[j].distance > dist) {
                                replace = j;
                            }
                        }
                        slot = empty;
                        if (empty == -1) {
                            slot = replace;
                        }
                        if (slot != -1) {
                            slots[slot].marker = &lbl_8064CA74[i];
                            slots[slot].distance = dist;
                            slots[slot].other = fn_80178E94(&other->x, &pos.x);
                        }
                    } else {
                        if (outIndex != 0) {
                            *outIndex = i;
                        }
                        best = dist;
                        found = &lbl_8064CA74[i];
                    }
                }
            }
        } else if (flags & 4) {
            fn_800BCCC4(lbl_8064CA74[i].position, &pos);
            dist = fn_80178E94(&pos.x, &origin->x);
            if (dist > best) {
                visible = 1;
                if (flags & 0x40) {
                    origin->z += lbl_8064F0C8;
                    pos.z += lbl_8064F0C8;
                    fn_8013F3C0(&shape, origin, &pos, lbl_8064F0CC);
                    if (fn_8013FBE4(fn_8015C2FC(2), &shape, &hit, 0, 8) != 0) {
                        visible = 0;
                    }
                    origin->z -= lbl_8064F0C8;
                    pos.z -= lbl_8064F0C8;
                }
                if (visible) {
                    if (outIndex != 0) {
                        *outIndex = i;
                    }
                    best = dist;
                    found = &lbl_8064CA74[i];
                }
            }
        }
    }
    if (collect) {
        unsigned int min = 0xFFFFFFFF;
        int j;
        int pick = -1;
        for (j = 0; j < 8; j++) {
            if (slots[j].marker != 0 && slots[j].other < min) {
                pick = j;
                min = slots[j].other;
            }
        }
        if (pick != -1) {
            found = slots[pick].marker;
        }
    }
    return found;
}
