typedef struct Object Object;

extern int fn_8011EB1C(Object *object);

int fn_80047C70(Object *object)
{
    int result = 0;

    if (object != 0 && fn_8011EB1C(object) == 2) {
        result = 1;
    }
    return result;
}
