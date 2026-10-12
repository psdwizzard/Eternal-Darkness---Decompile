typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec3s { short x, y, z; } Vec3s;

extern int fn_8013C9C4(const Vec3s* value, const Vec3* point, int axis);
extern void fn_8013C964(const Vec3s* value, int* first, int* second, int axis);

int fn_8013CAA8(const Vec3* point, int count, const Vec3s* vertices,
                int axis, int stride)
{
    int previous_first, previous_second;
    int current_first, current_second;
    int i;
    int quadrant;
    int winding;
    const Vec3s* current;
    int byte_stride;
    int previous_quadrant;
    const Vec3s* previous;

    byte_stride = stride * sizeof(Vec3s);
    /* Start with the closing edge, then follow every stride-th vertex. */
    previous = vertices + (count - stride);
    winding = 0;
    previous_quadrant = fn_8013C9C4(previous, point, axis);
    current = vertices;

    for (i = 0; i < count; i += stride) {
        quadrant = fn_8013C9C4(current, point, axis);
        if (previous_quadrant != quadrant) {
            if (((previous_quadrant + 1) & 3) == quadrant) {
                winding++;
            } else if (((quadrant + 1) & 3) == previous_quadrant) {
                winding--;
            } else {
                fn_8013C964(previous, &previous_first, &previous_second, axis);
                fn_8013C964(current, &current_first, &current_second, axis);
                {
                    int second_delta = previous_second - current_second;
                    int first_delta = current_first - previous_first;
                    int reverse_first_delta = previous_first - current_first;
                    if (first_delta * second_delta
                            + reverse_first_delta * previous_second
                            > reverse_first_delta * current_second) {
                        winding += 2;
                    } else {
                        winding -= 2;
                    }
                }
            }
            previous_quadrant = quadrant;
        }
        previous = current;
        current = (const Vec3s*)((const char*)current + byte_stride);
    }
    return winding;
}
