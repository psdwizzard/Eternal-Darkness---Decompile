typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Sizing {
    unsigned char pad[0x1E];
    unsigned short kind;
    unsigned char pad20[0x86];
    unsigned short use_first;
} Sizing;

typedef struct Runtime {
    unsigned char pad[0x3C];
    Sizing* sizing;
    unsigned char pad40[0x208];
    int mode;
    unsigned char pad24C[8];
    int flags;
    unsigned char pad258[0x54];
    float scale;
    unsigned char pad2B0[0x20];
    unsigned short draw_flags;
} Runtime;

typedef struct Item {
    float value;
    int kind;
    int offset;
    float depth;
    int key;
    int use_first;
    float scale;
    Runtime* runtime;
    void* handle;
} Item;

extern Item lbl_804EF960[];
extern Vec3 lbl_8063D378;
extern Vec3 lbl_8063D400;
extern float lbl_8064B9D8;
extern float lbl_8064B9DC;
extern int lbl_8064CEF0;
extern float lbl_8064CEF4;
extern int lbl_8064CEF8;
extern int lbl_8064CF00;
extern float lbl_8064CF04;
extern float lbl_8064CF08;
extern int lbl_8064CF0C;
extern int lbl_8064D18C;
extern int lbl_8064D5A8;
extern float lbl_80650110; /* 0.0f */
extern float lbl_80650114; /* 1.0f */
extern float lbl_80650120; /* 600.0f */
extern float lbl_80650130; /* 14.0f */
extern float lbl_80650134; /* 300.0f */
extern double lbl_80650140; /* 0.05 */
extern float lbl_80650148; /* 2.0f */
extern float lbl_8065014C; /* 15.5f */
extern float lbl_80650150; /* 14.5f */
extern float lbl_80650154; /* 500.0f */
extern float lbl_80650158; /* 2500.0f */
extern double lbl_80650160; /* 15.0 */
extern double lbl_80650168; /* 12.0 */
extern float lbl_80650170; /* 0.1f */

extern int fn_8012356C(const Item* first, const Item* second);
extern void qsort(void* base, int count, int size, int (*compare)(const Item*, const Item*));
extern int fn_8011EB04(Runtime* runtime);
extern void fn_8011F114(Vec3* out, Runtime* runtime);
extern unsigned int fn_8011FAEC(Runtime* runtime);
extern unsigned int fn_8011FAF4(Runtime* runtime);
extern void fn_801235E4(Item* items, int count, int* total_offsets, int* total_sizes);
extern float fn_80123708(Runtime* runtime, int alternate);
extern int fn_801261E8(Runtime* runtime);
extern void* fn_80155DB4(void* handle);
extern void* fn_80156930(void);
extern int fn_8015E4E8(void);
extern void fn_801EF374(int level);
extern int fn_801EF37C(void);
extern void fn_8020123C(int id, int a, int b, int c);
extern int fn_80201B4C(void* handle);
extern int fn_80201B54(void* handle);
extern void* fn_80201B9C(void);
extern void* fn_80201BC0(void* handle);
extern Runtime* fn_80201BC8(void* handle);
extern void PSVECSubtract(const Vec3* a, const Vec3* b, Vec3* out);
extern float PSVECMag(const Vec3* v);
extern float PSVECDotProduct(const Vec3* a, const Vec3* b);

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void fn_801237F0(int force)
{
    int total_sizes;
    int total_offsets;
    Vec3 dir;
    Vec3 pos;
    Vec3 tmp;
    float fade_a;
    float fade_b;
    float scale;
    float len;
    float dist;
    float near_scale;
    float target;
    float falloff;
    float max_scale;
    float min_scale;
    float fade;
    int count;
    int enabled;
    int far_count;
    int key;
    void* handle;
    Runtime* runtime;
    unsigned int status;
    int i;
    int seen;
    int best;
    int best_index;
    int done;
    int tries;

    handle = fn_80201B9C();
    total_sizes = 0;
    fade_a = lbl_8064CF08;
    total_offsets = 0;
    fade_b = lbl_8064CF04;
    enabled = lbl_8064CEF8;
    count = 0;
    far_count = 0;
    tries = 8;

    PSVECSubtract(&lbl_8063D400, &lbl_8063D378, &dir);
    len = PSVECMag(&dir);
    if (fn_8015E4E8() != 0) {
        fade_b = fade_a = lbl_80650130;
    }
    if (lbl_80650110 == len) {
        return;
    }

    dir.x /= len;
    dir.y /= len;
    dir.z /= len;
    len = -PSVECDotProduct(&dir, &lbl_8063D378);

    while (handle != 0) {
        runtime = fn_80201BC8(handle);
        if (runtime != 0 && fn_80201B4C(handle) != 4) {
            status = fn_8011FAEC(runtime);
            if (fn_80155DB4(handle) != 0 &&
                (fn_80156930() != 0 || ((status & 0x8000) && (status & 0x08000000)))) {
                key = fn_8011EB04(runtime);
                fn_8011F114(&tmp, runtime);
                pos = tmp;
                scale = lbl_8064B9D8;
                if (runtime->sizing != 0) {
                    near_scale = fn_80123708(runtime, 0);
                    dist = -PSVECDotProduct(&pos, &dir) - lbl_80650134;
                    if (dist > len && (status & 0x8000) == 0 && runtime->mode <= 2) {
                        scale = near_scale;
                    } else {
                        far_count++;
                    }
                    PSVECSubtract(&pos, &lbl_8063D378, &pos);
                    lbl_804EF960[count].key = key;
                    lbl_804EF960[count].kind = runtime->sizing->kind;
                    lbl_804EF960[count].value = PSVECMag(&pos);
                    lbl_804EF960[count].depth = dist - len;
                    lbl_804EF960[count].runtime = runtime;
                    lbl_804EF960[count].scale = scale;
                    lbl_804EF960[count].handle = handle;
                    if (lbl_804EF960[count].value < lbl_80650120 && scale != near_scale) {
                        lbl_804EF960[count].use_first = runtime->sizing->use_first & 1;
                    } else {
                        lbl_804EF960[count].use_first = 0;
                    }
                    if ((lbl_8064D18C == 0x91 || lbl_8064D18C == 0x137 || lbl_8064D18C == 0x14E) &&
                        runtime->mode == 3) {
                        lbl_804EF960[count].use_first = runtime->sizing->use_first & 1;
                    }
                    if (fn_8011FAF4(runtime) & 0x1000) {
                        lbl_804EF960[count].use_first = runtime->sizing->use_first & 1;
                    }
                    count++;
                }
            }
        }
        handle = fn_80201BC0(handle);
    }

    qsort(lbl_804EF960, count, sizeof(Item), fn_8012356C);
    fn_801235E4(lbl_804EF960, count, &total_offsets, &total_sizes);

    /* Literal constants here: retail reloads 15.0f for the divide instead of
     * reusing the compare's load, which only happens for literals. */
    if (fade_a > 15.0f || fade_b > 15.0f) {
        fade = (fade_a > fade_b) ? fade_a : fade_b;
        if (fade < 20.0f) {
            lbl_8064CEF8 = 1;
            lbl_8064CEF4 += fade / 15.0f - lbl_80650114;
            if (lbl_8064CEF4 > lbl_80650114) {
                lbl_8064CEF4 = lbl_80650114;
            }
        }
    }
    if (fade_a < lbl_80650130 && fade_b < lbl_80650130) {
        if (lbl_8064CEF4 > lbl_80650110) {
            if (lbl_8064B9DC >= lbl_80650114) {
                lbl_8064CEF4 = lbl_8064CEF4 - lbl_80650140;
            }
        } else {
            lbl_8064CEF4 = lbl_80650110;
            enabled = 0;
            lbl_8064B9DC = lbl_80650114;
            lbl_8064CEF8 = 0;
        }
    }

    if (total_sizes >= 40000 || total_offsets >= 650016) {
        for (i = 0; i < count; i++) {
            lbl_804EF960[i].use_first = 0;
        }
    }

    fade_b = lbl_80650148 * lbl_8064CEF4;
    if (enabled != 0) {
        int level;
        seen = 0;
        level = fn_801EF37C();
        if (fade_a > lbl_8065014C) {
            level = level - 1;
            fn_801EF374(level > 0 ? level : 0);
        } else if (fade_a < lbl_80650150) {
            level = level + 1;
            fn_801EF374(level >= 7 ? 7 : level);
        }

        target = lbl_80650114;
        for (i = 0; i < count; i++) {
            scale = fn_80123708(lbl_804EF960[i].runtime, 0);
            if (fn_80201B4C(lbl_804EF960[i].handle) == 3) {
                lbl_804EF960[i].scale = scale;
            } else if (lbl_804EF960[i].runtime->mode <= 2) {
                dist = lbl_804EF960[i].value - lbl_80650154;
                if (dist < lbl_80650110) {
                    if (scale != lbl_804EF960[i].scale) {
                        lbl_804EF960[i].scale = lbl_80650114;
                    }
                    seen++;
                } else {
                    lbl_804EF960[i].scale = MAX(scale, lbl_804EF960[i].scale * (lbl_80650114 - (fade_b * (float)seen) / (float)far_count));
                    if (lbl_8064D18C != 0x27 && dist > lbl_80650158) {
                        lbl_804EF960[i].scale = scale;
                    }
                    seen++;
                }
            } else {
                lbl_804EF960[i].scale = lbl_80650114;
            }
            if (lbl_804EF960[i].scale > target) {
                lbl_804EF960[i].scale = target;
            } else if (lbl_804EF960[i].scale < scale) {
                lbl_804EF960[i].scale = scale;
            }
        }
    }

    fn_801235E4(lbl_804EF960, count, &total_offsets, &total_sizes);
    while (total_sizes >= 40000 || total_offsets >= 650016) {
        done = 0;
        if (force != 0) {
            scale = lbl_80650110;
            best = -1;
            best_index = 0;
            for (i = 0; i < count; i++) {
                if (scale != lbl_804EF960[i].scale && fn_80201B4C(lbl_804EF960[i].handle) == 3) {
                    int age = lbl_8064D5A8 - fn_801261E8(lbl_804EF960[i].runtime);
                    if (best < age) {
                        best = age;
                        best_index = i;
                    }
                }
            }
            if (best != -1) {
                lbl_804EF960[best_index].scale = lbl_80650110;
                fn_8020123C(0x39, 0, fn_80201B54(lbl_804EF960[best_index].handle), 0);
                done = 1;
                tries++;
            }
        }
        if (done == 0) {
            for (i = count - 2; i >= 0; i--) {
                near_scale = fn_80123708(lbl_804EF960[i].runtime, 0);
                if (lbl_804EF960[i].scale > near_scale) {
                    lbl_804EF960[i].scale = near_scale;
                    break;
                }
            }
        }
        fn_801235E4(lbl_804EF960, count, &total_offsets, &total_sizes);
        if (--tries <= 0) {
            break;
        }
    }

    while (total_sizes >= 40000 || total_offsets >= 650016) {
        count--;
        fn_801235E4(lbl_804EF960, count, &total_offsets, &total_sizes);
    }

    if (fade_a > lbl_80650160) {
        lbl_8064CF0C = 0;
    } else if (fade_a < lbl_80650168) {
        lbl_8064CF0C = 1;
    }

    min_scale = lbl_80650110;
    max_scale = lbl_80650114;
    for (i = 0; i < count; i++) {
        if (lbl_8064CF0C != 0) {
            lbl_804EF960[i].runtime->draw_flags |= 0x100;
        } else {
            lbl_804EF960[i].runtime->draw_flags &= ~0x100;
        }
        if (lbl_804EF960[i].scale < min_scale) {
            lbl_804EF960[i].scale = lbl_80650170;
        }
        if (lbl_804EF960[i].scale > max_scale) {
            lbl_804EF960[i].scale = max_scale;
        }
        lbl_804EF960[i].runtime->scale = lbl_804EF960[i].scale;
        if (min_scale != lbl_804EF960[i].scale) {
            lbl_804EF960[i].runtime->flags |= 0x80000;
        }
        if (lbl_804EF960[i].use_first != 0) {
            lbl_804EF960[i].runtime->flags |= 0x400000;
        } else {
            lbl_804EF960[i].runtime->flags &= ~0x400000;
        }
    }

    lbl_8064CEF0 = total_offsets;
    lbl_8064CF00 = total_sizes;
}
