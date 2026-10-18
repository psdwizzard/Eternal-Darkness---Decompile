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

extern void dataInsertMacro(u16, void*);
extern void dataRemoveMacro(u16);
extern void dataInsertKeymap(u16, void*);
extern void dataRemoveKeymap(u16);
extern void dataInsertLayer(u16, void*, u16);
extern void dataRemoveLayer(u16);
extern void dataInsertCurve(u16, void*);
extern void dataRemoveCurve(u16);
extern void dataAddSampleReference(u16);
extern void dataRemoveSampleReference(u16);

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

void InsertData(u16 id, void* data, u8 dataType, u32 remove)
{
    MEM_DATA* m;

    switch (dataType) {
    case 0:
        if (!remove) {
            if ((m = GetMacroAddr(id, data)) != 0) {
                dataInsertMacro(id, &m->data.cmd);
            } else {
                dataInsertMacro(id, 0);
            }
        } else {
            dataRemoveMacro(id);
        }
        break;
    case 2: {
        id |= 0x4000;
        if (!remove) {
            if ((m = GetKeymapAddr(id, data)) != 0) {
                dataInsertKeymap(id, &m->data.map);
            } else {
                dataInsertKeymap(id, 0);
            }
        } else {
            dataRemoveKeymap(id);
        }
        break;
    }
    case 3: {
        id |= 0x8000;
        if (!remove) {
            if ((m = GetLayerAddr(id, data)) != 0) {
                dataInsertLayer(id, &m->data.layer.entry, m->data.layer.num);
            } else {
                dataInsertLayer(id, 0, 0);
            }
        } else {
            dataRemoveLayer(id);
        }
        break;
    }
    case 4:
        if (!remove) {
            if ((m = GetCurveAddr(id, data)) != 0) {
                dataInsertCurve(id, &m->data.tab);
            } else {
                dataInsertCurve(id, 0);
            }
        } else {
            dataRemoveCurve(id);
        }
        break;
    case 1:
        if (!remove) {
            dataAddSampleReference(id);
        } else {
            dataRemoveSampleReference(id);
        }
        break;
    }
}
