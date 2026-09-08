typedef struct RangeControl {
    int minimum;
    int maximum;
    int window;
    int value;
    int start;
    int step;
    unsigned int flags;
    int (*accept)(int);
    void (*changed)(void);
} RangeControl;

void fn_801E8B6C(RangeControl* control, short amount)
{
    int old = control->value;

    if (control->accept != 0) {
        int increment = amount;
        int candidate = old + increment;
        while (candidate >= control->minimum && candidate <= control->maximum) {
            if (control->accept(candidate) != 0) {
                control->value = candidate;
                break;
            }
            candidate += amount != 0 ? increment : 1;
        }
    } else {
        control->value = old + amount;
    }

    if (control->value < control->minimum) {
        if (control->flags & 1) {
            control->value = control->maximum - (control->minimum - control->value - 1);
        } else {
            control->value = control->minimum;
        }
    } else if (control->value > control->maximum) {
        if (control->flags & 1) {
            int wrapped = control->value - control->maximum + control->minimum;
            control->value = wrapped - 1;
        } else {
            control->value = control->maximum;
        }
    }

    while (control->value < control->start) {
        control->start -= control->step;
    }
    while (control->value >= control->start + control->window) {
        control->start += control->step;
    }

    if (control->flags & 2) {
        if (control->start < control->minimum) {
            control->start = control->minimum;
        } else if (control->start > control->maximum) {
            control->start = control->maximum;
        }
    }

    if (control->changed != 0 && amount != 0 && old != control->value) {
        control->changed();
    }
}
