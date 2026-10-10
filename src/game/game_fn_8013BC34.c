typedef float Matrix[3][4];
typedef struct Color {
    unsigned char r, g, b, a;
} Color;

typedef struct Vertex {
    unsigned int flags;
    short position[3];
    short unknown0A;
} Vertex;

typedef struct Geometry {
    short position[3];
    unsigned char unknown06[0x62];
    unsigned short count;
    unsigned short unknown6A;
    Vertex* vertices;
    unsigned char unknown70[8];
} Geometry;

extern void* fn_8011F9E4(void*, int);
extern void* fn_8011FA4C(void*, int);
extern int fn_8011F958(void*, void*);
extern void* fn_8011F130(void*);
extern void* fn_8011FE34(void*);
extern void fn_80179DB0(float*, short*);
extern void fn_802114E0(Matrix, void*);
extern void fn_80211710(Matrix, float*, float*);
extern void fn_80211A48(void*, float*, float*);
extern void fn_801ECC4C(void);
extern void fn_801ED468(int);
extern void fn_801EDA7C(void*, void*, int, int);
extern void fn_801ECF50(int);
extern int fn_8013BAAC(void*, void*, float);
extern void fn_801ECD74(Color*);
extern void fn_80226AB4(int, int, int);
extern void fn_8013C054(float, float, float);
extern void fn_8013C050(void);
extern char lbl_802FC53C[];
extern Color lbl_802FC5BC[];
extern float lbl_80650308;

void fn_8013BC34(void* target, void* object)
{
    Matrix rotation;
    float start[3];
    float end[3];
    Geometry* first;
    Geometry* second;
    int index;

    first = fn_8011F9E4(object, 0);
    second = fn_8011FA4C(object, 0);
    index = fn_8011F958(object, target);
    if (index != -1) {
        void* translation;
        void* angles;
        Geometry* b;

        translation = fn_8011F130(object);
        angles = fn_8011FE34(object);
        b = second + index;
        first += index;
        fn_80179DB0(start, first->position);
        fn_80179DB0(end, b->position);
        fn_802114E0(rotation, angles);
        fn_80211710(rotation, start, start);
        fn_80211710(rotation, end, end);
        fn_80211A48(translation, start, start);
        fn_80211A48(translation, end, end);
        fn_801ECC4C();
        fn_801ED468(0x1B);
        fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
        fn_801ECF50(4);
        if (fn_8013BAAC(target, object, lbl_80650308)) {
            Color color = lbl_802FC5BC[5];
            fn_801ECD74(&color);
        } else {
            Color color = lbl_802FC5BC[8];
            fn_801ECD74(&color);
        }
        for (index = 0; index < first->count; index++) {
            fn_80179DB0(start, first->vertices[index].position);
            fn_80179DB0(end, b->vertices[index].position);
            fn_80211710(rotation, start, start);
            fn_80211710(rotation, end, end);
            fn_80211A48(translation, start, start);
            fn_80211A48(translation, end, end);
            fn_80226AB4(0xA8, 3, 2);
            fn_8013C054(start[0], start[1], start[2]);
            fn_8013C054(end[0], end[1], end[2]);
            fn_8013C050();
        }
    }
}
