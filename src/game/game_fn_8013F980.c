#pragma use_lmw_stmw on

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Input { Vec3 first; Vec3 second; float value; } Input;
typedef struct Shape { unsigned char pad00[0x14]; Vec3 axis; float value; unsigned char pad24[0x14]; } Shape;
typedef struct Node {
    unsigned char count;
    unsigned char pad01[3];
    unsigned short* indices;
    short first;
    short second;
} Node;
typedef struct Collection {
    unsigned char pad00[0xC];
    void* context;
    unsigned char pad10[0x30];
    Node* nodes;
    unsigned char pad44[4];
    Shape* shapes;
} Collection;
typedef struct Iterator { unsigned int words[3]; } Iterator;

extern float lbl_806503D8;
extern void fn_801E8E54(Iterator*, int, unsigned int*);
extern void fn_801E8E68(Iterator*, int);
extern int fn_801E8E94(Iterator*);
extern int fn_8013C7BC(const Vec3*, const Vec3*, const Vec3*, float, float);
extern int fn_8013E284(const void*, const Shape*, const void*, Result*);
extern float fn_80211D4C(const Vec3*, const void*);
extern void fn_80140AEC(Shape*, Collection*);

Shape* fn_8013F980(Collection* collection, const Input* value, Result* out)
{
    Iterator second_set, first_set;
    Result candidate;
    unsigned int second_words[60], first_words[60];
    unsigned int offset;
    Vec3* candidate_point;
    Shape* shapes = collection->shapes;
    Shape* result = 0;

    fn_801E8E54(&first_set, 60, first_words);
    fn_801E8E54(&second_set, 60, second_words);
    fn_801E8E68(&first_set, 0);
    fn_801E8E68(&second_set, 0);
    candidate_point = &candidate.point;
    while (first_set.words[1] != 0) {
        int node_index = fn_801E8E94(&first_set);
        int state = fn_801E8E94(&second_set);
        if (state == 0 || (state == 1 && result == 0)) {
            if (node_index != -1) {
                Node* node = &collection->nodes[node_index];
                Shape* shape = &shapes[node->indices[0]];
                int side = fn_8013C7BC(&value->first,
                                       &value->second,
                                       &shape->axis,
                                       value->value, shape->value);
                if (side == 2) {
                    float best = lbl_806503D8;
                    int i;
                    int count = node->count;
                    for (i = 0, offset = 0; i < count; offset += 2, i++) {
                        shape = &shapes[*(unsigned short*)((unsigned char*)node->indices + offset)];
                        if (fn_8013E284(value, shape, collection->context, &candidate)) {
                            float distance = fn_80211D4C(candidate_point, value);
                            if (distance < best) {
                                best = distance;
                                result = shape;
                                *out = candidate;
                                fn_80140AEC(shape, collection);
                            }
                        }
                    }
                    if (result == 0) {
                        fn_801E8E68(&first_set, node->second);
                        fn_801E8E68(&second_set, 1);
                    }
                    fn_801E8E68(&first_set, node->first);
                    fn_801E8E68(&second_set, 0);
                } else if (side == 3) {
                    fn_801E8E68(&first_set, node->first);
                    fn_801E8E68(&second_set, 1);
                    fn_801E8E68(&first_set, node->second);
                    fn_801E8E68(&second_set, 0);
                } else if (side == 0) {
                    fn_801E8E68(&first_set, node->second);
                    fn_801E8E68(&second_set, 0);
                } else {
                    fn_801E8E68(&first_set, node->first);
                    fn_801E8E68(&second_set, 0);
                }
            }
        }
    }
    return result;
}
