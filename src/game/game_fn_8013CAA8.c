typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec3s { short x, y, z; } Vec3s;

extern int fn_8013C9C4(const Vec3s* value, const Vec3* point, int axis);
extern void fn_8013C964(const Vec3s* value, int* first, int* second, int axis);

int fn_8013CAA8(register const Vec3* point_arg, register int count_arg,
                register const Vec3s* vertices, register int axis_arg, register int stride_arg)
{
    int previous_first, previous_second;
    int current_first, current_second;
    int i;
    int quadrant;
    int winding;
    register int stride;
    register int axis;
    register int count;
    register const Vec3* point;
    const Vec3s* current;
    int byte_stride;
    int previous_quadrant;
    const Vec3s* previous;
    register const Vec3s* start;
    register int closing_offset;

    /* ASM: mr, subf, and mulli retain separate loop arguments and the
     * closing-edge byte offset. C copy propagation changes the saved
     * argument registers and schedules this initialization differently. */
    asm {
        mr count, count_arg
        mr stride, stride_arg
        mr point, point_arg
        subf closing_offset, stride, count
        mr start, vertices
        mulli closing_offset, closing_offset, 6
        mr axis, axis_arg
    }
    previous = (const Vec3s*)((const char*)start + closing_offset);
    winding = 0;
    previous_quadrant = fn_8013C9C4(previous, point, axis);
    byte_stride = stride * sizeof(Vec3s);
    current = start;

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
                    register int previous_product;
                    register int first_delta;
                    register int current_product;
                    register int previous_second_value;
                    register int current_second_value;
                    register int edge_product;
                    /* Read each projected coordinate once, in retail order.
                     * The product scratch variables initially hold first
                     * coordinates and are overwritten by the arithmetic. */
                    current_second_value = *(volatile int*)&current_second;
                    previous_second_value = *(volatile int*)&previous_second;
                    current_product = *(volatile int*)&previous_first;
                    previous_product = *(volatile int*)&current_first;
                    /* ASM: subf, mullw, and add preserve the two directed
                     * deltas and the product order. MWCC's C scheduler changes
                     * the registers and reorders these independent products. */
                    asm {
                        subf edge_product, current_second_value, previous_second_value
                        subf first_delta, current_product, previous_product
                        subf current_product, previous_product, current_product
                        mullw previous_product, previous_second_value, current_product
                        mullw edge_product, edge_product, first_delta
                        mullw current_product, current_product, current_second_value
                        add edge_product, edge_product, previous_product
                    }
                    if (edge_product > current_product) {
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
