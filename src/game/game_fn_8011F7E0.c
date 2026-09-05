void fn_8011F7E0(void* object, int enabled)
{
    unsigned int current_flags;
    unsigned int* flags = (unsigned int*)((char*)object + 0x254);
    if (enabled) {
        *flags |= 0x400;
    } else {
        current_flags = *flags;
        *flags = current_flags & ~0x400;
    }
}
