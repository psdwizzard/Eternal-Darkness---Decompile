typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Matrix34 {
    float m[3][4];
} Matrix34;

typedef struct Geometry {
    short position[3];
    unsigned char unused[0x72];
} Geometry;

extern Geometry* fn_8011F9E4(void*, int);
extern Geometry* fn_8011FA4C(void*, int);
extern int fn_8011F958(void*, void*);
extern Vec3* fn_8011F130(void*);
extern void* fn_8011FE34(void*);
extern void fn_80179DB0(Vec3*, const short*);
extern void fn_802114E0(Matrix34*, void*);
extern void fn_80211710(Matrix34*, Vec3*, Vec3*);
extern void fn_80211A48(Vec3*, Vec3*, Vec3*);
extern void fn_80211A6C(Vec3*, Vec3*, Vec3*);
extern void fn_80211AAC(Vec3*, Vec3*);
extern float fn_80211B44(Vec3*, Vec3*);
extern void* fn_80201B9C(void);
extern void* fn_80201B3C(void);
extern void* fn_80201BC0(void*);
extern void* fn_80201BC8(void*);
extern int fn_80201EB8(void*);
extern int fn_80201B5C(void*);
extern int lbl_8064D18C;
extern float lbl_8065030C;
extern float lbl_80650310;
extern float lbl_80650314;

int fn_8013BE5C(void* target, void* object)
{
    Matrix34 transform;
    Vec3 start;
    Vec3 end;
    Vec3 direction;
    Geometry* first;
    Geometry* second;
    int index;
    Vec3* translation;
    void* rotation;
    void* node;
    void* current;
    float plane;

    first = fn_8011F9E4(object, 0);
    second = fn_8011FA4C(object, 0);
    index = fn_8011F958(object, target);
    if (index != -1) {
        translation = fn_8011F130(object);
        rotation = fn_8011FE34(object);
        node = fn_80201B9C();
        current = fn_80201B3C();
        fn_80179DB0(&start, first[index].position);
        fn_80179DB0(&end, second[index].position);
        fn_802114E0(&transform, rotation);
        fn_80211710(&transform, &start, &start);
        fn_80211710(&transform, &end, &end);
        fn_80211A48(translation, &start, &start);
        fn_80211A48(translation, &end, &end);
        fn_80211A6C(&end, &start, &direction);
        fn_80211AAC(&direction, &direction);
        plane = -fn_80211B44(&start, &direction);

        while (node != 0) {
            void* body;
            if (node != current && fn_80201EB8(node) == lbl_8064D18C &&
                (body = fn_80201BC8(node)) != 0) {
                Vec3* position = fn_8011F130(body);
                float distance = plane + fn_80211B44(position, &direction);
                float limit = lbl_8065030C;
                float magnitude;
                if (fn_80201B5C(node) == 5)
                    limit = lbl_80650310;
                if (distance < lbl_80650314)
                    magnitude = -distance;
                else
                    magnitude = distance;
                if (magnitude < limit)
                    return 1;
            }
            node = fn_80201BC0(node);
        }
        return 0;
    }
    return 1;
}
