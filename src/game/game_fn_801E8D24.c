typedef struct RangeControl {
    int minimum;
    int maximum;
    int window;
    int value;
    int start;
} RangeControl;

int fn_801E8D24(RangeControl* control)
{
    return control->value - control->start;
}
