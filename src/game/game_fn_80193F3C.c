typedef unsigned char u8;
typedef signed short s16;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

void fn_80193F3C(u8 column, int row, Vec3s* center, Vec3s* output,
                 float x_offset, float y_offset, s16 scale, u8 x_scale,
                 u8 y_scale)
{
    int displacement;
    Vec3s* point;
    float factor;
    float x0;
    float y0;
    float x1;
    float y1;
    s16 center_x;
    s16 center_y;

    center_x = center->x;
    center_y = center->y;
    if (scale > 0) {
        if (scale > 210) {
            factor = 2100.0f / (float)(scale - 100);
        } else {
            factor = 10.0f;
        }
        x_offset *= factor;
        y_offset *= factor;
    }

    y0 = (float)x_scale * y_offset;
    x0 = (float)x_scale * x_offset;

    displacement = (((int)column - 4 - row) * 4 - 1);
    point = output;
    point[0].x = (s16)((float)center_x + x0);
    point[0].y = (s16)((float)center_y + y0);
    point[0].z = center->z;
    x1 = (float)y_scale * x_offset;
    y1 = (float)y_scale * y_offset;
    point[1].x = (s16)((float)center_x + x1);
    point[1].y = (s16)((float)center_y + y1);
    point[1].z = center->z;

    point = output + 1;
    point += displacement;
    point[0].x = (s16)((float)center_x - x0);
    point[0].y = (s16)((float)center_y - y0);
    point[0].z = center->z;
    point[1].x = (s16)((float)center_x - x1);
    point[1].y = (s16)((float)center_y - y1);
    point[1].z = center->z;

    point++;
    point += row * 4 + 5;
    point[0].x = (s16)((float)center_x - x0);
    point[0].y = (s16)((float)center_y + y1);
    point[0].z = center->z;
    point[1].x = center_x;
    point[1].y = center_y;
    point[1].z = center->z;

    point++;
    point += displacement;
    point[0].x = (s16)((float)center_x - x1);
    point[0].y = (s16)((float)center_y - y1);
    point[0].z = center->z;
    point[1].x = center_x;
    point[1].y = center_y;
    point[1].z = center->z;
}
