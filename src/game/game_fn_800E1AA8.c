typedef struct Color { unsigned char r, g, b, a; } Color;

typedef struct ObjectState {
    unsigned char pad_000[0x78];
    void **resource_ref;
} ObjectState;

extern Color lbl_8064F628;
extern const Color lbl_8064F62C;
extern const Color lbl_80651B28;
extern int fn_80201B54();
extern void *fn_80201B8C();
extern void *fn_80201890(void *);
extern void* fn_8012C62C(void *, int, Color *, Color *, Color *, int);

void fn_800E1AA8(void *object)
{
    Color source = lbl_8064F628;
    Color first;
    Color second;
    Color third;
    Color composed;
    void *resource;

    fn_80201B54(object);
    resource = fn_80201890(*((ObjectState *)fn_80201B8C(object))->resource_ref);
    composed = lbl_80651B28;
    composed.r = source.r;
    composed.g = source.g;
    composed.b = source.b;
    third = composed;
    second = lbl_8064F62C;
    first = source;
    fn_8012C62C(resource, 15, &first, &second, &third, 6);
}
