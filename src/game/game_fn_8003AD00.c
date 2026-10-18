typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Candidate {
    int id;
    unsigned int dist;
    int hit;
    int valid;
} Candidate;

extern int fn_8003B794(void *, Candidate *, int, void *);
extern int fn_8003B878(const void *, const void *);
extern int fn_80066D80(void *, int);
extern void qsort(void *, unsigned long, unsigned long, int (*)(const void *, const void *));
extern void *fn_8011F130(void *);
extern int fn_80135D80(Vec3 *, Vec3 *, Vec3 *, Vec3 *, void *, void *, unsigned char, unsigned char, float);
extern unsigned int fn_80178E94(void *, void *);
extern int fn_801A7490(void *);
extern unsigned int fn_801A7498(void *);
extern int fn_801A7578(void *);
extern int fn_801A7688(void *, int, Vec3 *);
extern int fn_801A7770(void *);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void *fn_80201814(int);
extern void *fn_80201890(int);
extern int fn_80201B54(void *);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
extern void *fn_80201BC8(void *);
extern int fn_80201EB8(void *);

/* debug triangle ring buffer: 20 triangles of 3 vertices */
extern Vec3 lbl_80301D3C[][3];
extern int lbl_8064C5E0;
extern int lbl_8064CB58;
extern float lbl_8064E240;

int fn_8003AD00(void *obj, void *target, void *area, int *outId, int *outBit) {
    int result;
    int count;
    void *areaGroup;
    void *cur;
    int areaObj;
    unsigned int maxDist;
    void *selfPos;
    int bit;
    int areaId;
    Vec3 v0;
    Vec3 v1;
    Vec3 v2;
    Vec3 v3;
    char hitBuf[0x24];
    Candidate list[11];
    Candidate *entry;
    int id;
    void *pos;
    int hit;
    int found;
    int i;
    void *data;

    result = 0;
    count = 0;
    cur = fn_80201B9C();
    areaObj = fn_801A7498(area);
    areaId = fn_801A7490(area);
    areaGroup = fn_80201814(areaObj);
    if (target != 0) {
        bit = fn_801A7770(area);
    }
    selfPos = fn_8011F130(fn_80201BC8(obj));
    maxDist = fn_801A7578(area) + 0x28;
    fn_801A7688(area, 0, &v0);
    fn_801A7688(area, 1, &v1);
    fn_801A7688(area, 2, &v2);
    fn_801A7688(area, 3, &v3);

    if (lbl_8064CB58 != 0) {
        lbl_80301D3C[lbl_8064C5E0][0] = v0;
        lbl_80301D3C[lbl_8064C5E0][1] = v1;
        lbl_80301D3C[lbl_8064C5E0][2] = v2;
        lbl_8064C5E0 = (lbl_8064C5E0 >= 20) ? 0 : lbl_8064C5E0 + 1;
        lbl_80301D3C[lbl_8064C5E0][0] = v2;
        lbl_80301D3C[lbl_8064C5E0][1] = v3;
        lbl_80301D3C[lbl_8064C5E0][2] = v1;
        lbl_8064C5E0 = (lbl_8064C5E0 >= 20) ? 0 : lbl_8064C5E0 + 1;
    }

    entry = list;
    while (cur != 0 && count < 11) {
        id = fn_80201B54(cur);
        if (cur != areaGroup && fn_80201EB8(cur) == fn_80201EB8(areaGroup) &&
            (target == cur || (unsigned int)(fn_8020123C(0x3B, areaObj, id, 0) & 0xFFFFFFFF) == 1)) {
            data = fn_80201BC8(cur);
            pos = fn_8011F130(data);
            if (fn_80178E94(selfPos, pos) < maxDist) {
                hit = fn_80135D80(&v0, &v1, &v2, &v3, data, hitBuf, 1, 1, lbl_8064E240);
                if (hit != 0) {
                    entry->id = id;
                    entry->dist = fn_80178E94(selfPos, pos);
                    count++;
                    entry->hit = hit;
                    entry->valid = 1;
                    entry++;
                }
            }
        }
        cur = fn_80201BC0(cur);
    }

    if (count > 0) {
        i = 0;
        found = 0;
        if (count > 1) {
            qsort(list, count, sizeof(Candidate), fn_8003B878);
        }
        if (list[0].id == areaId) {
            list[0].hit = 1 << bit;
        }
        data = fn_80201890(list[0].id);
        do {
            if ((list[0].hit & (1 << i)) && fn_80066D80(data, i) != 0) {
                found = 1;
                *outBit = i;
                *outId = list[0].id;
                break;
            }
            i++;
        } while (i <= 15);
        if (found) {
            result = fn_8003B794(obj, list, 1, area);
        }
    }
    return result;
}
