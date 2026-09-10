typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct MEM_DATA {
    volatile u32 nextOff;
    u16 id;
    u16 reserved;
    union {
        struct {
            u32 num;
            u8 entry[1];
        } layer;
        u8 map[1];
        u8 tab[1];
        u8 cmd[1];
    } data;
} MEM_DATA;

typedef struct POOL_DATA {
    u32 macroOff;
    u32 curveOff;
    u32 keymapOff;
    u32 layerOff;
} POOL_DATA;

extern void fn_801BC8F4(u16, void*);
extern void fn_801BCC04(u16);
extern void fn_801BB5D0(u16, void*);
extern void fn_801BB7C0(u16);
extern void fn_801BB944(u16, void*, u16);
extern void fn_801BBB8C(u16);
extern void fn_801BBD58(u16, void*);
extern void fn_801BBF50(u16);
extern void fn_801BC500(u16);
extern void fn_801BC5D8(u16);

static inline MEM_DATA* GetMacroAddr(u16 id, POOL_DATA* pool)
{
    MEM_DATA* m;
    if (pool == 0)
        return 0;
    m = (MEM_DATA*)((u8*)pool + pool->macroOff);
    while (m->nextOff != 0xFFFFFFFF) {
        if (m->id == id)
            return m;
        m = (MEM_DATA*)((u8*)m + m->nextOff);
    }
    return 0;
}

static inline MEM_DATA* GetCurveAddr(u16 id, POOL_DATA* pool)
{
    MEM_DATA* m;
    if (pool == 0)
        return 0;
    m = (MEM_DATA*)((u8*)pool + pool->curveOff);
    while (m->nextOff != 0xFFFFFFFF) {
        if (m->id == id)
            return m;
        m = (MEM_DATA*)((u8*)m + m->nextOff);
    }
    return 0;
}

static inline MEM_DATA* GetKeymapAddr(u16 id, POOL_DATA* pool)
{
    MEM_DATA* m;
    if (pool == 0)
        return 0;
    m = (MEM_DATA*)((u8*)pool + pool->keymapOff);
    while (m->nextOff != 0xFFFFFFFF) {
        if (m->id == id)
            return m;
        m = (MEM_DATA*)((u8*)m + m->nextOff);
    }
    return 0;
}

static inline MEM_DATA* GetLayerAddr(u16 id, POOL_DATA* pool)
{
    MEM_DATA* m;
    if (pool == 0)
        return 0;
    m = (MEM_DATA*)((u8*)pool + pool->layerOff);
    while (m->nextOff != 0xFFFFFFFF) {
        if (m->id == id)
            return m;
        m = (MEM_DATA*)((u8*)m + m->nextOff);
    }
    return 0;
}

void fn_801C38CC(u16 id, void* data, u8 dataType, u32 remove)
{
    MEM_DATA* m;

    switch (dataType) {
    case 0:
        if (!remove) {
            if ((m = GetMacroAddr(id, data)) != 0) {
                fn_801BC8F4(id, &m->data.cmd);
            } else {
                fn_801BC8F4(id, 0);
            }
        } else {
            fn_801BCC04(id);
        }
        break;
    case 2: {
        id |= 0x4000;
        if (!remove) {
            if ((m = GetKeymapAddr(id, data)) != 0) {
                fn_801BB5D0(id, &m->data.map);
            } else {
                fn_801BB5D0(id, 0);
            }
        } else {
            fn_801BB7C0(id);
        }
        break;
    }
    case 3: {
        id |= 0x8000;
        if (!remove) {
            if ((m = GetLayerAddr(id, data)) != 0) {
                fn_801BB944(id, &m->data.layer.entry, m->data.layer.num);
            } else {
                fn_801BB944(id, 0, 0);
            }
        } else {
            fn_801BBB8C(id);
        }
        break;
    }
    case 4:
        if (!remove) {
            if ((m = GetCurveAddr(id, data)) != 0) {
                fn_801BBD58(id, &m->data.tab);
            } else {
                fn_801BBD58(id, 0);
            }
        } else {
            fn_801BBF50(id);
        }
        break;
    case 1:
        if (!remove) {
            fn_801BC500(id);
        } else {
            fn_801BC5D8(id);
        }
        break;
    }
}
