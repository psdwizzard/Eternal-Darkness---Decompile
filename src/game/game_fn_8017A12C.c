extern float fn_80179F20(float angle);

#pragma opt_propagation off
void fn_8017A12C(float* out, float current, float target)
{
    float wrapped;
    float wrapped_magnitude;
    float difference_magnitude;
    float difference;

    target -= current;
    difference = fn_80179F20(target);

    if (difference > 0.0f) {
        wrapped = difference - 6.2831855f;
    } else {
        wrapped = 6.2831855f + difference;
    }

    wrapped_magnitude = wrapped < 0.0f ? -wrapped : wrapped;
    difference_magnitude = difference < 0.0f ? -difference : difference;
    *out = difference_magnitude < wrapped_magnitude ? difference : wrapped;
}
#pragma opt_propagation reset
