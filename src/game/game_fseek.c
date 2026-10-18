int _fseek(void* stream, long offset, int origin);

int fseek(void* stream, long offset, int origin)
{
    return _fseek(stream, offset, origin);
}
