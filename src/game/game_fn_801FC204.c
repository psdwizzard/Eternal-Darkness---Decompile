typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct SVec3 {
    short x;
    short y;
    short z;
} SVec3;

extern const float lbl_806514F0;
extern const float lbl_80651500;
extern const float lbl_80651504;
extern const float lbl_80651508;
extern const float lbl_8065150C;
extern const float lbl_80651510;
extern const float lbl_80651514;
extern const float lbl_80651518;
extern const float lbl_8065151C;

extern void fn_801794A0(Vec3*, Vec3*, Vec3*);
extern void fn_80179A18(Vec3*);

void fn_801FC204(unsigned int type, int scale, SVec3* origin, SVec3* input,
                 SVec3* output, int relative)
{
    Vec3 direction;
    Vec3 a;
    Vec3 b;

    switch (type) {
    case 0:
        direction.x = -input->y;
        direction.y = input->x;
        direction.z = lbl_806514F0;
        if (direction.x == lbl_806514F0 && direction.y == lbl_806514F0) {
            direction.x = lbl_80651500;
        } else {
            fn_80179A18(&direction);
        }
        break;
    case 1:
        if (input->x == 0 && input->y == 0) {
            direction.x = lbl_806514F0;
            direction.y = lbl_80651500;
            direction.z = lbl_806514F0;
        } else {
            a.x = -input->y;
            a.y = input->x;
            a.z = lbl_806514F0;
            b.x = input->x;
            b.y = input->y;
            b.z = input->z;
            fn_801794A0(&a, &b, &direction);
        }
        break;
    case 2:
        direction.x = input->y;
        direction.y = -input->x;
        direction.z = lbl_806514F0;
        if (direction.x == lbl_806514F0 && direction.y == lbl_806514F0) {
            direction.x = lbl_80651504;
        } else {
            fn_80179A18(&direction);
        }
        break;
    case 3:
        if (input->x == 0 && input->y == 0) {
            direction.x = lbl_806514F0;
            direction.y = lbl_80651504;
            direction.z = lbl_806514F0;
        } else {
            a.x = input->x;
            a.y = input->y;
            a.z = input->z;
            b.x = -input->y;
            b.y = input->x;
            b.z = lbl_806514F0;
            fn_801794A0(&a, &b, &direction);
        }
        break;
    case 4:
        if (input->x == 0 && input->y == 0) {
            direction.x = lbl_80651508;
            direction.y = lbl_80651508;
            direction.z = lbl_806514F0;
        } else {
            a.x = -input->y;
            a.y = input->x;
            a.z = lbl_806514F0;
            b.x = input->x;
            b.y = input->y;
            b.z = input->z;
            fn_801794A0(&a, &b, &direction);
            fn_80179A18(&a);
            direction.x += a.x;
            direction.y += a.y;
            direction.z += a.z;
            fn_80179A18(&direction);
        }
        break;
    case 5:
        if (input->x == 0 && input->y == 0) {
            direction.x = lbl_8065150C;
            direction.y = lbl_80651508;
            direction.z = lbl_806514F0;
        } else {
            a.x = -input->y;
            a.y = input->x;
            a.z = lbl_806514F0;
            b.x = input->x;
            b.y = input->y;
            b.z = input->z;
            fn_801794A0(&a, &b, &direction);
            a.x = input->y;
            a.y = -input->x;
            a.z = lbl_806514F0;
            fn_80179A18(&a);
            direction.x += a.x;
            direction.y += a.y;
            direction.z += a.z;
            fn_80179A18(&direction);
        }
        break;
    case 6:
        if (input->x == 0 && input->y == 0) {
            direction.x = lbl_8065150C;
            direction.y = lbl_8065150C;
            direction.z = lbl_806514F0;
        } else {
            a.x = input->x;
            a.y = input->y;
            a.z = input->z;
            b.x = -input->y;
            b.y = input->x;
            b.z = lbl_806514F0;
            fn_801794A0(&a, &b, &direction);
            a.x = input->y;
            a.y = -input->x;
            a.z = lbl_806514F0;
            fn_80179A18(&a);
            direction.x += a.x;
            direction.y += a.y;
            direction.z += a.z;
            fn_80179A18(&direction);
        }
        break;
    case 7:
        if (input->x == 0 && input->y == 0) {
            direction.x = lbl_80651508;
            direction.y = lbl_8065150C;
            direction.z = lbl_806514F0;
        } else {
            a.x = input->x;
            a.y = input->y;
            a.z = input->z;
            b.x = -input->y;
            b.y = input->x;
            b.z = lbl_806514F0;
            fn_801794A0(&a, &b, &direction);
            a.x = -input->y;
            a.y = input->x;
            a.z = lbl_806514F0;
            fn_80179A18(&a);
            direction.x += a.x;
            direction.y += a.y;
            direction.z += a.z;
            fn_80179A18(&direction);
        }
        break;
    case 8:
        if (input->x == 0 && input->y == 0) { direction.x = lbl_80651510; direction.y = lbl_80651514; direction.z = lbl_806514F0; }
        break;
    case 9:
        if (input->x == 0 && input->y == 0) { direction.x = lbl_80651514; direction.y = lbl_80651510; direction.z = lbl_806514F0; }
        break;
    case 10:
        if (input->x == 0 && input->y == 0) { direction.x = lbl_80651518; direction.y = lbl_80651510; direction.z = lbl_806514F0; }
        break;
    case 11:
        if (input->x == 0 && input->y == 0) { direction.x = lbl_8065151C; direction.y = lbl_80651514; direction.z = lbl_806514F0; }
        break;
    case 12:
        if (input->x == 0 && input->y == 0) { direction.x = lbl_8065151C; direction.y = lbl_80651518; direction.z = lbl_806514F0; }
        break;
    case 13:
        if (input->x == 0 && input->y == 0) { direction.x = lbl_80651518; direction.y = lbl_8065151C; direction.z = lbl_806514F0; }
        break;
    case 14:
        if (input->x == 0 && input->y == 0) { direction.x = lbl_80651514; direction.y = lbl_8065151C; direction.z = lbl_806514F0; }
        break;
    case 15:
        if (input->x == 0 && input->y == 0) { direction.x = lbl_80651510; direction.y = lbl_80651518; direction.z = lbl_806514F0; }
        break;
    }

    output->x = origin->x + scale * direction.x;
    output->y = origin->y + scale * direction.y;
    output->z = origin->z + scale * direction.z;
    if (relative) {
        output->x += input->x;
        output->y += input->y;
        output->z += input->z;
    }
}
