typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Segment {
    Vec3 first;
    Vec3 second;
    Vec3 axis;
    float length;
} Segment;

typedef struct QueryResult {
    u32 header[2];
    Vec3 position;
    Vec3 direction;
    u32 tail[2];
} QueryResult;

typedef struct State {
    u32 flags;
    Vec3 position;
} State;

typedef struct Owner {
    State *state;
} Owner;

extern int lbl_8064CB60;
extern void *lbl_8064C718;
extern float lbl_8064F1F0;

extern void *fn_80201B8C(void *);
extern void *fn_8004918C(void);
extern void *fn_8004914C(void);
extern void *fn_801A7780(void *);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern void fn_80211AAC(const Vec3 *, Vec3 *);
extern void fn_80211A90(const Vec3 *, Vec3 *, float);
extern void fn_80211A48(const Vec3 *, const Vec3 *, Vec3 *);
extern void *fn_8012AB2C(void *);
extern void fn_8013F4D0(Segment *, const Vec3 *, const Vec3 *);
extern void *fn_80140258(void *, const Vec3 *, Vec3 *, int, void *);

void fn_800C6254(void *context, void *object)
{
    Segment segment;
    QueryResult query;
    Vec3 position;
    Vec3 direction;
    Owner *owner;
    void *data;
    void *model;
    void *collision;
    u32 flags;

    if (lbl_8064CB60 != 0 && context != 0 && object != 0) {
        owner = fn_80201B8C(context);
        if (owner != 0 && owner->state != 0) {
            data = fn_8004918C();
            model = fn_8004914C();
            flags = (u32)fn_801A7780(data);
            if (model != 0 && (flags & 0x90018)) {
                if (fn_8011F6A4(model, 4, -1, -1, &query, 1) != -1) {
                    position = query.position;
                    direction = query.direction;
                }
                fn_80211AAC(&direction, &direction);
                fn_80211A90(&direction, &direction, lbl_8064F1F0);
                fn_80211A48(&position, &direction, &position);
                collision = fn_8012AB2C(object);
                fn_8013F4D0(&segment, &query.position, &position);
                lbl_8064C718 = fn_80140258(collision, &segment.first,
                                          &owner->state->position, 3, 0);
                if (lbl_8064C718 == 0) {
                    owner->state->position = position;
                }
            }
        }
    }
}
