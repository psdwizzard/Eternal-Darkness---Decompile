#pragma use_lmw_stmw on

extern void lua_error(void*, char*);
extern unsigned int luaO_power2(unsigned int);
extern void* luaM_realloc(void*, void*, unsigned int, char*, int);
extern char lbl_8064BB28;

void* luaM_growaux(void* allocator, void* block, unsigned int count,
                  unsigned int increment, unsigned int element_size,
                  char* file, unsigned int limit)
{
    unsigned int new_count = count + increment;

    if (count >= limit - increment) {
        lua_error(allocator, file);
    }
    if (count >= (new_count ^ count) ||
        (count != 0 && new_count < 4)) {
        return block;
    }
    return luaM_realloc(allocator, block,
                       element_size * luaO_power2(new_count),
                       &lbl_8064BB28, 0x7F);
}
