typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec {
    float x;
    float y;
    float z;
} Vec;

typedef struct SearchResult {
    u8 header[8];
    Vec position;
    Vec direction;
    u8 tail[0x4];
} SearchResult;

typedef struct Segment {
    Vec start;
    Vec end;
} Segment;

typedef struct ModeState {
    u8 pad[8];
    int mode;
} ModeState;

extern ModeState lbl_803003C8;
extern float lbl_8064B480;
extern float lbl_8064B484;

extern void *fn_8004910C(void *);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern int fn_801A7498(void *);
extern void fn_801A75C0(Vec *, void *, int, Vec *);
extern void fn_801A7610(void *, Segment);
extern void fn_801A7688(void *, int, Vec *);
extern void *fn_80201814(int);
extern int fn_80201B44(void);
extern void *fn_80201BC8(void *);
extern void fn_80211A48(Vec *, Vec *, Vec *);
extern void fn_80211A6C(Vec *, Vec *, Vec *);
extern void fn_80211A90(Vec *, Vec *, float);

void fn_8003BB04(void *object, int index) {
    SearchResult result;
    Segment segment;
    Vec start;
    Vec end;
    Vec scaled;
    Vec offset;
    Vec out0;
    Vec out1;
    void *model;
    int id;
    void *found;
    void *transform;
    void *target;
    int depth;

    id = fn_801A7498(object);
    model = fn_80201814(id);
    found = fn_8004910C(object);
    if (found != 0) {
        target = fn_80201BC8(found);
        if (fn_8011F6A4(target, 2, 15, -1, &result, 1) != -1) {
            fn_80211A90(&result.direction, &scaled, lbl_8064B480);
            fn_80211A48(&result.position, &scaled, &start);
        }
        if (fn_8011F6A4(target, 3, 15, -1, &result, 1) != -1) {
            fn_80211A90(&result.direction, &scaled, lbl_8064B484);
            fn_80211A48(&result.position, &scaled, &end);
        }
    } else {
        depth = 3;
        if (id == fn_80201B44() && (lbl_803003C8.mode == 5 || lbl_803003C8.mode == 8)) {
            depth = 2;
        }
        transform = fn_80201BC8(model);
        if (fn_8011F6A4(transform, 2, depth, -1, &result, 1) != -1) {
            fn_80211A90(&result.direction, &scaled, lbl_8064B480);
            fn_80211A48(&result.position, &scaled, &start);
        }
        if (fn_8011F6A4(transform, 3, depth, -1, &result, 1) != -1) {
            fn_80211A90(&result.direction, &scaled, lbl_8064B484);
            fn_80211A48(&result.position, &scaled, &end);
        }
    }
    fn_801A75C0(&out0, object, index, &start);
    fn_801A75C0(&out1, object, index + 1, &end);
    if (index == 2) {
        segment.start = end;
        fn_801A7688(object, 1, &offset);
        fn_80211A6C(&end, &offset, &segment.end);
        fn_801A7610(object, segment);
    }
}
