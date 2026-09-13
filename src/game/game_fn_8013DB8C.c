extern float lbl_80650350;
extern float lbl_80650358;

#pragma opt_loop_invariants off
int fn_8013DB8C(const short* minimum, const short* maximum,
                const float* origin, const float* delta,
                float* result, float* amount)
{
    signed char state[3];
    float time[3];
    float candidate[3];
    int inside = 1;
    int axis;
    int selected;

    for (axis = 0; axis < 3; axis++) {
        if (origin[axis] < minimum[axis]) {
            state[axis] = 1;
            candidate[axis] = minimum[axis];
            inside = 0;
        } else if (origin[axis] > maximum[axis]) {
            state[axis] = 0;
            candidate[axis] = maximum[axis];
            inside = 0;
        } else {
            state[axis] = 2;
        }
    }

    if (inside) {
        *amount = lbl_80650350;
        return 1;
    }

    for (axis = 0; axis < 3; axis++) {
        if (state[axis] != 2 && delta[axis] != lbl_80650350) {
            time[axis] = (candidate[axis] - origin[axis]) / delta[axis];
        } else {
            time[axis] = lbl_80650358;
        }
    }

    selected = 0;
    for (axis = 1; axis < 3; axis++) {
        if (time[selected] < time[axis]) {
            selected = axis;
        }
    }
    if (time[selected] < lbl_80650350) {
        return 0;
    }

    for (axis = 0; axis < 3; axis++) {
        if (selected != axis) {
            result[axis] = origin[axis] + time[selected] * delta[axis];
            if (result[axis] < minimum[axis] || result[axis] > maximum[axis]) {
                return 0;
            }
        } else {
            result[axis] = candidate[axis];
        }
    }
    *amount = time[selected];
    return 1;
}

#pragma opt_loop_invariants reset
