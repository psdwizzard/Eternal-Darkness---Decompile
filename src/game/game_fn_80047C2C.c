typedef struct Object Object;

extern int fn_8011EB1C(Object *object);

int fn_80047C2C(Object *object)
{
    int result = 0;

    if (object != 0 && fn_8011EB1C(object) == 4) {
        result = 1;
    }
    return result;
}
