extern void* fn_80201BC8(void* object);
extern void fn_8011F114(void* destination, void* source);

void fn_80201E78(void* destination, void* object)
{
    void* source = fn_80201BC8(object);
    fn_8011F114(destination, source);
}
