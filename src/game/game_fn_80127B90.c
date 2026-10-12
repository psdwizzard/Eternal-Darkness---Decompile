typedef struct VertexData {
    char data[0xE];
    signed char active;
    char pad_F;
} VertexData;

typedef struct VertexAttribute {
    unsigned int words[4];
} VertexAttribute;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef struct RotationKey {
    unsigned int flags;
    VertexData value;
} RotationKey;

extern unsigned int fn_801285CC(const unsigned int* value);
extern void fn_8012811C(VertexData* input, VertexAttribute* output);
extern int fn_8017A750(const Vec4* left, const Vec4* right);
extern void fn_8017A71C(Vec4* value);
extern void fn_8017A7D4(const Vec4* left, const Vec4* right, float amount,
                       Vec4* output);
extern const float lbl_80650198;
extern const float lbl_8065019C;

void fn_80127B90(RotationKey* left, RotationKey* right, Vec4* output,
                 float amount) {
    Vec4 second;
    Vec4 first;
    int type;

    if ((int)fn_801285CC(&left->flags) == 3 && (int)fn_801285CC(&right->flags) == 3) {
        type = 3;
    } else if ((int)fn_801285CC(&left->flags) == 2 && (int)fn_801285CC(&right->flags) == 2) {
        type = 2;
    }

    if (amount <= lbl_80650198) {
        if (type != 3) {
            fn_8012811C(&left->value, (VertexAttribute*)output);
        }
    } else if (lbl_8065019C - amount <= lbl_80650198) {
        if (type != 3) {
            fn_8012811C(&right->value, (VertexAttribute*)output);
        }
    } else if (type != 3 && type == 2) {
        Vec4* firstPtr;
        fn_8012811C(&left->value, (VertexAttribute*)&first);
        fn_8012811C(&right->value, (VertexAttribute*)&second);
        firstPtr = &first;
        if (fn_8017A750(firstPtr, &second)) {
            fn_8017A71C(&second);
        }
        fn_8017A7D4(firstPtr, &second, amount, output);
    }
}
