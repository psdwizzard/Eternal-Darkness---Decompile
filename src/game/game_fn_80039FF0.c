typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

extern u16 fn_8012A244(u8* owner);
extern void fn_80152838(Vec3f* position, Vec3f* target, u8 mode);
extern const float lbl_8064E248;

void fn_80039FF0(u8* owner, Vec3f* position)
{
    int emit = 0;
    Vec3f target;

    if (owner != 0) {
        switch (fn_8012A244(owner)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            emit = 1;
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 16:
        case 17:
        case 18:
        case 19:
            break;
        }
    } else {
        emit = 1;
    }

    if (emit) {
        target = *position;
        target.z += lbl_8064E248;
        fn_80152838(position, &target, 4);
    }
}
