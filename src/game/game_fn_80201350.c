extern void *fn_80201BC8(void *object);
extern unsigned int fn_8011FAEC(void *object);
extern unsigned int fn_8011FADC(void *object, unsigned int flags);

int fn_80201350(void *object, unsigned char enabled)
{
    void *resource;
    unsigned int flags;
    unsigned int updatedFlags;

    if (object != 0) {
        resource = fn_80201BC8(object);
    } else {
        resource = 0;
    }

    if (resource != 0) {
        flags = fn_8011FAEC(resource);
        updatedFlags = flags | 0xC0;
        if (enabled == 0) {
            updatedFlags = flags & ~0xC0;
        }
        return fn_8011FADC(resource, updatedFlags);
    }

    return -1;
}
