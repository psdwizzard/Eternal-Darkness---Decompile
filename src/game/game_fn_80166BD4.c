unsigned long hash_s(const char* string, unsigned long length)
{
    unsigned long hash = length;
    unsigned long step = (length >> 5) | 1;

    for (; length >= step; length -= step) {
        hash ^= (hash << 5) + (hash >> 2) + (unsigned char)*string++;
    }
    return hash;
}
