extern void* fn_8011FE34(void*);
extern void fn_8017A284(void*, float*, float*);
extern const double lbl_806501C8;

float fn_8012B750(void* object)
{
    float value[4];
    float output;

    object = fn_8011FE34(object);
    fn_8017A284(object, &value[0], &value[1]);
    if (value[3] < lbl_806501C8) {
        output = -value[0];
    } else {
        output = value[0];
    }
    value[0] = output;
    return output;
}
