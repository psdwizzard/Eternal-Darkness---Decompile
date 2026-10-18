int utf8_to_unicode(void* output, const char* input, unsigned long count);

int mbtowc(void* output, const char* input, unsigned long count)
{
    return utf8_to_unicode(output, input, count);
}
