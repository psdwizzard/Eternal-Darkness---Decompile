typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;

typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct Int3 { s32 v[3]; } Int3;
typedef struct Int4 { s32 v[4]; } Int4;

typedef struct QueryResult {
    u8 pad00[8];
    Vec3 position;
    u8 pad14[0x14];
} QueryResult;

typedef struct TemporaryDescriptor {
    u8 data[0x28];
} TemporaryDescriptor;

typedef struct EffectSlot {
    u8 data[0xC4];
} EffectSlot;

typedef struct SoundTag {
    u32 head;
    u16 tail;
} SoundTag;

typedef struct Emitter {
    u8 pad00;
    u8 start;
    u8 pad02;
    s8 tint;
    u8 colour[2];
    u16 lifetime;
    u16 step;
    u8 pad0A[0xA];
    s8 divisor;
    u8 pad15[3];
    u8 flags;
    u8 mode;
    u8 pad1A[2];
    u16 alpha;
    u8 pad1E[0x5A];
    u8 shape[0x18];
    void (*update)(void);
    s32 next;
    Vec3 position;
    u8 tag[6];
    u8 kind;
    u8 padAB[5];
} Emitter;

typedef struct Trail {
    u8 pad00[0x2E];
    u16 flags;
} Trail;

typedef struct SpellState {
    s32 type;
    s32 phase;
    s32 caster_id;
    s32 target_id;
    s32 charge;
    s32 spell_id;
    s32 hit;
    Vec3 from;
    Vec3 to;
    Vec3 hit_pos[4];
    EffectSlot slots[4];
    Emitter emitter;
    Trail trail;
} SpellState;

typedef struct ActorData {
    u8 pad00[0x40];
    SpellState *spell;
} ActorData;

typedef struct SpellPool {
    u8 pad00[0x30];
    Vec3 offset;
    Int3 no_hits3;
    Vec3 rot130;
    Vec3 rot132;
    Vec3 rot134;
    Vec3 origin;
    Int4 no_hits4;
} SpellPool;

extern s32 lbl_8064D18C;
extern const SpellPool lbl_80238CD0;
extern const f32 lbl_8064E04C, lbl_8064E05C, lbl_8064E064, lbl_8064E070;
extern const f32 lbl_8064E114, lbl_8064E120, lbl_8064E138, lbl_8064E13C;
extern const f32 lbl_8064E140, lbl_8064E144, lbl_8064E148, lbl_8064E14C;
extern const f32 lbl_8064E150, lbl_8064E154, lbl_8064E158;
extern const u32 lbl_80651914;
extern const u16 lbl_80651918;

extern void *memcpy(void *, const void *, unsigned long);
extern void fn_80031544(void *, s32, s32);
extern void fn_80031694(Vec3 *, s32, s32);
extern void fn_800317AC(void *, s32);
extern void fn_80031948(Vec3 *, s32);
extern void fn_80031A00(u8, EffectSlot *, s32, Vec3 *, s32, s32, s32, u8, u8, s32, s32);
extern s32 fn_80031BE0(void *, s32, s32, Vec3 *, void *, Vec3 *);
extern void fn_80031C78(void *, s32);
extern void *fn_80031D24(Vec3 *, Vec3 *, s32, s32, s32, u8, u8, u8, u8, s32);
extern s32 fn_80035628(void *);
extern void fn_800359A0(void *, void *);
extern s32 fn_80066D04(void *, s32);
extern s32 fn_80071DD8(void);
extern void fn_800C43AC(Vec3 *, void *);
extern s32 fn_8011EB04(void *);
extern void fn_8011F114(Vec3 *, void *);
extern s32 fn_8011F598(void *, s32, s32, s32, QueryResult *, s32);
extern s32 fn_8011F6A4(void *, s32, s32, s32, QueryResult *, s32);
extern u32 fn_8011FAF4(void *);
extern void fn_80120AD0(f32, f32, void *, s32, s32, s32);
extern void fn_8012B690(void *, Vec3 *, Vec3 *);
extern void fn_8013F4D0(TemporaryDescriptor *, Vec3 *, Vec3 *);
extern u32 fn_8014317C(TemporaryDescriptor *, Vec3 *, void *, s32, s32);
extern void fn_8014CBC0(Trail *);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern void fn_801858E0(Emitter *);
extern void fn_80185AE8(void);
extern s32 fn_801A717C(void);
extern void fn_801A7228(s32);
extern void fn_801A7470(s32, s32);
extern void fn_801A74A0(s32, s32);
extern void fn_801A74A8(s32, s32);
extern void fn_801A74D8(s32, s32);
extern void fn_801A7518(s32, s32);
extern void fn_801A7538(s32, s32);
extern void fn_801A7588(s32, s32);
extern void fn_801A764C(s32, Vec3 *);
extern void fn_801A7668(s32, s32);
extern void fn_801A7670(s32, u8);
extern void fn_801AC9F4(s32, s32, Vec3 *, s32);
extern s16 fn_801CEB2C(s32);
extern s32 fn_801D1B10(s16, s32, s32, u8);
extern void fn_801D38BC(s32, void *, void *);
extern s32 fn_801D38E8(s32);
extern u32 fn_801D39E0(void);
extern void fn_801DD0A8(s32, void *, s32);
extern void fn_801E2B28(Trail *, Vec3 *, u32 *, s32, s32);
extern void fn_801E8328(s32, void *);
extern void fn_802006D4(s32, s32, s32, s32, s32);
extern s32 fn_80200C10(void *);
extern void *fn_80200C38(void *);
extern void fn_8020104C(s32, s32, s32, void *, f32);
extern u64 fn_8020123C(s32, s32, s32, s32);
extern void *fn_80201814(s32);
extern s32 fn_80201AE4(void);
extern s32 fn_80201B44(void);
extern s32 fn_80201B54(void *);
extern s32 fn_80201B5C(void *);
extern ActorData *fn_80201B8C(void *);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
extern void *fn_80201BC8(void *);
extern void fn_80201D14(void *, s32);
extern void fn_80201D1C(void *, s32);
extern void fn_80201D2C(void *, s32);
extern void fn_80201D34(void *, s32);
extern void fn_80201E78(Vec3 *, void *);
extern s32 fn_80201EB8(void *);
extern u8 fn_80202160(void *);
extern u8 fn_80204578(void *, Vec3 *);
extern void PSVECSubtract(Vec3 *, Vec3 *, Vec3 *);
extern f32 PSVECMag(Vec3 *);

s32 fn_8002FAE8(void *actor, s32 mode, void *message)
{
    QueryResult anchor_query;
    QueryResult query8;
    QueryResult query9;
    TemporaryDescriptor ray;
    Vec3 offset;
    Int3 hits3;
    Vec3 rot130;
    Vec3 rot132;
    Vec3 rot134;
    Vec3 hit;
    Vec3 ray_from;
    Vec3 ray_to;
    Vec3 delta;
    Vec3 lifted;
    Vec3 pos;
    Vec3 target_pos;
    Int4 hits4;
    Vec3 anchor;
    Vec3 model_pos;
    Vec3 origin;
    SoundTag tag;
    u32 trail_arg;
    const SpellPool *pool;
    s32 msg;
    SpellState *state;
    s32 self;
    s32 flag;

    pool = &lbl_80238CD0;
    msg = fn_80200C10(message);
    state = fn_80201B8C(actor)->spell;
    self = fn_80201B54(actor);
    flag = fn_80202160(actor);

    if (mode == 0) {
        if (msg == 1) {
            if (state->phase != lbl_8064D18C) {
                fn_8020123C(0x39, self, self, 0);
            } else {
                if (state->charge > 0) {
                    fn_8020104C(0x62, self, self, 0, state->charge);
                } else {
                    fn_8020123C(0x62, self, self, 0);
                }
                fn_80201D2C(actor, 1);
                fn_80201D14(actor, 1);
            }
            return 1;
        }
        if (msg == 0x62) {
            if (state->phase != lbl_8064D18C) {
                fn_8020123C(0x39, self, self, 0);
            } else {
                s32 object_id;
                void *objA;
                void *objB;
                void *model;
                s32 bits;
                u8 kind;
                u8 variant;

                offset = pool->offset;
                objA = fn_80201814(state->caster_id);
                objB = fn_80201814(state->target_id);
                if (objA != 0 && objB != 0) {
                    hits3 = pool->no_hits3;
                    fn_80201E78(&anchor, objB);
                    state->to = anchor;
                    model = fn_80201BC8(objA);
                    fn_80031544(objA, 0x13, 0);
                    if (fn_80201B5C(objB) != 6 && fn_80201B5C(objB) != 0x39) {
                        fn_800317AC(objA, state->type);
                    }
                    if (fn_80201B5C(objB) == 0x39) {
                        void *anchor_model = fn_80201BC8(objB);
                        if (anchor_model != 0 &&
                            fn_8011F6A4(anchor_model, 0, 1, -1, &anchor_query, 1) != -1) {
                            state->to = anchor_query.position;
                        }
                    }
                    if (state->type == 0) {
                        object_id = fn_80035628(objA);
                    } else {
                        object_id = fn_801D38E8(state->spell_id);
                    }
                    fn_8012B690(model, &offset, &state->from);
                    if (lbl_8064D18C != 0x61 || state->caster_id != fn_80201AE4()) {
                        hits3.v[0] = fn_80031BE0(objA, 0x13, 8, &state->from, model, &state->hit_pos[0]);
                        hits3.v[1] = fn_80031BE0(objA, 0x13, 9, &state->from, model, &state->hit_pos[1]);
                        hits3.v[2] = fn_80031BE0(objA, 0x13, 0, &state->from, model, &state->hit_pos[2]);
                    }
                    if (hits3.v[0] != 0 || hits3.v[1] != 0 || hits3.v[2] != 0) {
                        if (hits3.v[0] != 0) {
                            fn_80031A00(0, &state->slots[1], object_id, &state->hit_pos[0], state->caster_id, 0x13, 8, 10, 3, 0, flag);
                            fn_8020104C(0x92, self, self, &state->hit_pos[0], lbl_8064E13C);
                        }
                        if (hits3.v[1] != 0) {
                            fn_80031A00(0, &state->slots[2], object_id, &state->hit_pos[1], state->caster_id, 0x13, 9, 10, 3, 0, flag);
                            fn_8020104C(0x92, self, self, &state->hit_pos[1], lbl_8064E13C);
                        }
                        if (hits3.v[2] != 0) {
                            fn_80031A00(0, &state->slots[0], object_id, &state->hit_pos[2], state->caster_id, 0x13, 0, 10, 3, 0, flag);
                            fn_8020104C(0x92, self, self, &state->hit_pos[2], lbl_8064E13C);
                        }
                        fn_8020104C(0x39, self, self, 0, lbl_8064E120);
                    } else {
                        bits = fn_8011FAF4(model) & 0x200;
                        if (fn_80201B5C(objB) == 0x39) {
                            fn_80031A00(0, &state->slots[1], object_id, &state->from, fn_80201B54(objB), 0, 1, 10, 3, 1, flag);
                        } else {
                            kind = 0x14;
                            variant = 6;
                            if ((bits != 0 || fn_80066D04(objA, 8) != 0) &&
                                fn_8011F598(model, 0x13, 8, -1, &query8, 1) != -1) {
                                fn_80031A00(0, &state->slots[1], object_id, &state->from, state->caster_id, 0x13, 8, 10, 3, 0, flag);
                                kind = 10;
                                variant = 3;
                            }
                            if ((bits != 0 || fn_80066D04(objA, 9) != 0) &&
                                fn_8011F598(model, 0x13, 9, -1, &query9, 1) != -1) {
                                fn_80031A00(0, &state->slots[2], object_id, &state->from, state->caster_id, 0x13, 9, 10, 3, 0, flag);
                                kind = 10;
                                variant = 3;
                            }
                            if (bits != 0 || fn_80066D04(objA, 0) != 0) {
                                fn_80031A00(0, &state->slots[0], object_id, &state->from, state->caster_id, 0x13, 0, kind, variant, 0, flag);
                            }
                        }
                        fn_8020104C(99, self, self, 0, lbl_8064E140);
                        fn_8020104C(0x39, self, self, 0, lbl_8064E070);
                    }
                } else {
                    fn_8020104C(0x39, self, self, 0, lbl_8064E064);
                }
            }
            return 1;
        }
        if (msg == 0x3D) {
            fn_8020123C(0x39, self, self, 0);
            return 1;
        }
        if (msg == 0x39) {
            fn_801E8328(2, actor);
            fn_80201D34(actor, 0);
            fn_80201D1C(actor, 1);
            return 1;
        }
        if (msg == 0x92) {
            void *where = fn_80200C38(message);
            s32 object_id;
            if (state->type == 0) {
                object_id = fn_80035628(fn_80201814(state->caster_id));
            } else {
                object_id = fn_801D38E8(state->spell_id);
            }
            fn_80031C78(where, object_id);
            return 1;
        }
    } else if (mode == 1) {
        if (msg == 99) {
            if (state->phase != lbl_8064D18C) {
                fn_8020123C(0x39, self, self, 0);
            } else {
                void *objA;
                void *objB;
                void *model;
                s32 special;
                u8 level;

                objA = fn_80201814(state->caster_id);
                if (objA != 0) {
                    objB = fn_80201814(state->target_id);
                    if (objB != 0) {
                        special = 0;
                        if (fn_80201B5C(objB) == 0x58) {
                            objB = fn_80201BC8(objB);
                            if (objB != 0) {
                                switch (fn_8011EB04(objB)) {
                                case 0x130:
                                    rot130 = pool->rot130;
                                    fn_8012B690(objB, &rot130, &state->to);
                                    special = 1;
                                    break;
                                case 0x132:
                                    rot132 = pool->rot132;
                                    fn_8012B690(objB, &rot132, &state->to);
                                    special = 1;
                                    break;
                                case 0x134:
                                    rot134 = pool->rot134;
                                    fn_8012B690(objB, &rot134, &state->to);
                                    special = 1;
                                    break;
                                }
                            }
                        }
                        if (lbl_8064D18C != 0x61 || state->caster_id != fn_80201AE4()) {
                            model = fn_80201BC8(objA);
                            ray_from = state->from;
                            ray_from.z += lbl_8064E114;
                            ray_to = state->to;
                            ray_to.z += lbl_8064E114;
                            fn_8013F4D0(&ray, &ray_from, &ray_to);
                            if (fn_8014317C(&ray, &hit, model, 0, 0x20) != 0) {
                                state->to = hit;
                                state->to.z -= lbl_8064E114;
                                state->hit = 1;
                                if (lbl_8064D18C == 0x29) {
                                    state->to.z = lbl_8064E138;
                                }
                            }
                        }
                        if (special) {
                            level = 1;
                        } else {
                            f32 dist;
                            PSVECSubtract(&state->from, &state->to, &delta);
                            dist = PSVECMag(&delta);
                            if (dist < lbl_8064E144) {
                                level = 0;
                            } else if (dist < lbl_8064E148) {
                                level = 1;
                            } else {
                                level = 2;
                            }
                        }
                        fn_80031D24(&state->from, &state->to,
                                    state->type == 0 ? fn_80035628(objA) : fn_801D38E8(state->spell_id),
                                    1, 1, 2, 0x14, 6, level, flag);
                        fn_8020104C(100, self, self, 0, lbl_8064E13C * (level + 1) - lbl_8064E138);
                        fn_801AC9F4(0x4A, 100, &state->from, 3);
                    }
                }
            }
            return 1;
        }
        if (msg == 100) {
            if (state->phase != lbl_8064D18C) {
                fn_8020123C(0x39, self, self, 0);
            } else {
                s32 handle;
                void *iter;
                void *caster_obj;
                void *caster_model;
                s32 object_id;
                s32 caster;
                s32 room;
                Emitter *emitter;

                handle = fn_801A717C();
                iter = fn_80201B9C();
                tag.head = lbl_80651914;
                tag.tail = lbl_80651918;
                caster = state->caster_id;
                caster_obj = fn_80201814(caster);
                if (caster_obj != 0) {
                    caster_model = fn_80201BC8(caster_obj);
                    if (state->type == 0) {
                        object_id = fn_80035628(caster_obj);
                    } else {
                        object_id = fn_801D38E8(state->spell_id);
                    }
                    if (state->type == 0) {
                        trail_arg = fn_801D39E0();
                        fn_8014CBC0(&state->trail);
                        state->trail.flags |= 2;
                        fn_801E2B28(&state->trail, &state->to, &trail_arg, 0x20, 0x1E);
                    }
                    room = fn_80201EB8(caster_obj);
                    if (state->hit == 0) {
                        emitter = &state->emitter;
                        fn_801858E0(emitter);
                        emitter->start = 0x4B;
                        emitter->tint = -0x19;
                        fn_801D38BC(object_id, emitter->shape, emitter->colour);
                        emitter->divisor = 0xD;
                        emitter->alpha = emitter->start;
                        emitter->flags |= 2;
                        emitter->mode = 8;
                        emitter->step = (0x5F - emitter->start) / emitter->divisor;
                        emitter->lifetime = emitter->step + 10;
                        emitter->update = fn_80185AE8;
                        lifted = state->to;
                        lifted.z += lbl_8064E144;
                        emitter->position = lifted;
                        memcpy(emitter->tag, &tag, 6);
                        emitter->next = 0;
                        emitter->kind = 4;
                        if (flag != 0) {
                            emitter->kind |= 8;
                        }
                        fn_801E8328(0x10, emitter);
                    }
                    fn_801A74A0(handle, caster);
                    fn_801A7588(handle, 0x8000);
                    if (state->type == 0) {
                        s32 hit_any = 0;
                        if (state->hit == 0) {
                            for (; iter != 0; iter = fn_80201BC0(iter)) {
                                Vec3 *src;
                                void *model;
                                s32 iter_room;
                                s32 iter_id;
                                s32 q18, q1a, q19, q17;
                                s32 h0, h1, h2, h3;
                                u32 result;
                                s32 player;

                                model = fn_80201BC8(iter);
                                if (model != 0) {
                                    fn_8011F114(&model_pos, model);
                                    src = &model_pos;
                                } else {
                                    origin = pool->origin;
                                    src = &origin;
                                }
                                pos = *src;
                                iter_room = fn_80201EB8(iter);
                                iter_id = fn_80201B54(iter);
                                if (room != iter_room) continue;
                                if (fn_80178E94(&state->to, &pos) >= 0xBE) continue;
                                if (caster_obj == iter) continue;
                                if ((u32)(fn_8020123C(0x65, caster, iter_id, 0) & 0xFFFFFFFF) != 1) continue;
                                if (state->hit != 0) continue;

                                if (fn_80066D04(iter, 2) != 0) {
                                    q1a = 2;
                                    q18 = 2;
                                } else {
                                    q1a = 1;
                                    q18 = 1;
                                }
                                if (fn_80066D04(iter, 3) != 0) {
                                    q19 = 3;
                                    q17 = 3;
                                } else {
                                    q19 = 1;
                                    q17 = 1;
                                }
                                h0 = fn_80031BE0(iter, 0x18, q18, &state->to, caster_model, &state->hit_pos[0]);
                                h1 = fn_80031BE0(iter, 0x1A, q1a, &state->to, caster_model, &state->hit_pos[1]);
                                h2 = fn_80031BE0(iter, 0x19, q19, &state->to, caster_model, &state->hit_pos[2]);
                                h3 = fn_80031BE0(iter, 0x17, q17, &state->to, caster_model, &state->hit_pos[3]);
                                if (h0 != 0 || h1 != 0 || h2 != 0 || h3 != 0) {
                                    if (h0 != 0) {
                                        fn_80031A00(0, &state->slots[0], object_id, &state->hit_pos[0], iter_id, 0x18, q18, 10, 3, 0, flag);
                                        fn_8020104C(0x92, self, self, &state->hit_pos[0], lbl_8064E13C);
                                    }
                                    if (h1 != 0) {
                                        fn_80031A00(0, &state->slots[1], object_id, &state->hit_pos[1], iter_id, 0x1A, q1a, 10, 3, 0, flag);
                                        fn_8020104C(0x92, self, self, &state->hit_pos[1], lbl_8064E13C);
                                    }
                                    if (h2 != 0) {
                                        fn_80031A00(0, &state->slots[2], object_id, &state->hit_pos[2], iter_id, 0x19, q19, 10, 3, 0, flag);
                                        fn_8020104C(0x92, self, self, &state->hit_pos[2], lbl_8064E13C);
                                    }
                                    if (h3 != 0) {
                                        fn_80031A00(0, &state->slots[3], object_id, &state->hit_pos[3], iter_id, 0x17, q17, 10, 3, 0, flag);
                                        fn_8020104C(0x92, self, self, &state->hit_pos[3], lbl_8064E13C);
                                    }
                                    state->hit = 1;
                                    continue;
                                }

                                result = 0;
                                fn_801A74A8(handle, iter_id);
                                fn_801AC9F4(0x4A, 100, &pos, 3);
                                if (fn_80204578(iter, &state->to)) {
                                    fn_8020123C(0x37, caster, iter_id, 0);
                                    fn_801A7470(handle, 0xB);
                                } else {
                                    fn_801A7470(handle, 0xC);
                                }
                                fn_800359A0(iter, caster_obj);
                                switch (object_id) {
                                case 1:
                                    fn_801A7538(handle, 1);
                                    fn_801A7518(handle, 10);
                                    fn_801A74D8(handle, 0x400000);
                                    fn_8020123C(0x27, caster, iter_id, handle);
                                    fn_801A7538(handle, 8);
                                    fn_801A7518(handle, 30000);
                                    fn_801A7470(handle, -1);
                                    fn_801A764C(handle, &state->to);
                                    result = fn_8020123C(0x27, caster, iter_id, handle);
                                    if (result & 1) {
                                        fn_80120AD0(lbl_8064E064, lbl_8064E14C, model, 0, 100, 0x22);
                                    }
                                    break;
                                case 2:
                                    fn_801A7538(handle, 5);
                                    fn_801A7518(handle, 5);
                                    fn_801A74D8(handle, 0x400000);
                                    result = fn_8020123C(0x27, caster, iter_id, handle);
                                    if (result & 1) {
                                        fn_8020123C(0x67, caster, iter_id, handle);
                                        fn_8020104C(0x68, caster, iter_id, (void *)handle, lbl_8064E05C);
                                        fn_80120AD0(lbl_8064E064, lbl_8064E150, model, 0, 100, 10);
                                    }
                                    break;
                                case 3:
                                    player = fn_80201AE4();
                                    if (iter_id == player || iter_id == fn_80201B44()) {
                                        fn_8020123C(0x86, caster, player, 1);
                                        fn_8020104C(0x86, caster, player, 0, lbl_8064E04C);
                                    }
                                    fn_801A7538(handle, 3);
                                    fn_801A7518(handle, 5);
                                    fn_801A74D8(handle, 0x400000);
                                    result = fn_8020123C(0x27, caster, iter_id, handle);
                                    if (result & 1) {
                                        fn_80120AD0(lbl_8064E064, lbl_8064E154, model, 0, 100, 0x12);
                                    }
                                    break;
                                }
                                if (result & 1) {
                                    fn_80031A00(1, &state->slots[0], object_id, &state->to, iter_id, 0x18, q18, 10, 3, 0, flag);
                                    fn_80031A00(1, &state->slots[1], object_id, &state->to, iter_id, 0x1A, q1a, 10, 3, 0, flag);
                                    fn_80031A00(1, &state->slots[2], object_id, &state->to, iter_id, 0x19, q19, 10, 3, 0, flag);
                                    fn_80031A00(1, &state->slots[3], object_id, &state->to, iter_id, 0x17, q17, 10, 3, 0, flag);
                                    hit_any = 1;
                                }
                            }
                            if (state->hit != 0) {
                                fn_802006D4(self, self, -1, 0x39, 0);
                                fn_8020104C(0x39, self, self, 0, lbl_8064E120);
                            }
                        }
                        if (room == lbl_8064D18C) {
                            if (hit_any == 0) {
                                fn_80031948(&state->to, object_id);
                                fn_80031694(&state->to, 1, object_id);
                            } else {
                                fn_80031694(&state->to, 0, object_id);
                            }
                        }
                    } else if (state->type == 1) {
                        s32 target;
                        void *target_obj;
                        s32 target_room;
                        s32 is_kind3f;
                        u32 result;
                        s32 q18, q1a, q19, q17;
                        s32 power;
                        s32 delay;
                        u8 count;

                        target = state->target_id;
                        target_obj = fn_80201814(target);
                        if (target_obj != 0) {
                            fn_80201BC8(target_obj);
                            target_room = fn_80201EB8(target_obj);
                            is_kind3f = fn_80201B5C(target_obj) == 0x3F;
                            result = 0;
                            fn_800C43AC(&target_pos, target_obj);
                            if (room == target_room &&
                                (is_kind3f || fn_80178E94(&state->to, &target_pos) < 0xBE) &&
                                caster_obj != target_obj &&
                                (u32)(fn_8020123C(0x3B, caster, target, 1) & 0xFFFFFFFF) == 1 &&
                                state->hit == 0) {
                                hits4 = pool->no_hits4;
                                if (fn_80201B5C(target_obj) != 6) {
                                    if (fn_80066D04(target_obj, 2) != 0) {
                                        q1a = 2;
                                        q18 = 2;
                                    } else {
                                        q1a = 1;
                                        q18 = 1;
                                    }
                                    if (fn_80066D04(target_obj, 3) != 0) {
                                        q19 = 3;
                                        q17 = 3;
                                    } else {
                                        q19 = 1;
                                        q17 = 1;
                                    }
                                    if (lbl_8064D18C != 0x61 || state->caster_id != fn_80201AE4()) {
                                        hits4.v[0] = fn_80031BE0(target_obj, 0x18, q18, &state->to, caster_model, &state->hit_pos[0]);
                                        hits4.v[1] = fn_80031BE0(target_obj, 0x1A, q1a, &state->to, caster_model, &state->hit_pos[1]);
                                        hits4.v[2] = fn_80031BE0(target_obj, 0x19, q19, &state->to, caster_model, &state->hit_pos[2]);
                                        hits4.v[3] = fn_80031BE0(target_obj, 0x17, q17, &state->to, caster_model, &state->hit_pos[3]);
                                    }
                                    if (hits4.v[0] != 0 || hits4.v[1] != 0 || hits4.v[2] != 0 || hits4.v[3] != 0) {
                                        if (hits4.v[0] != 0) {
                                            fn_80031A00(0, &state->slots[0], object_id, &state->hit_pos[0], target, 0x18, q18, 10, 3, 0, flag);
                                            fn_8020104C(0x92, self, self, &state->hit_pos[0], lbl_8064E13C);
                                        }
                                        if (hits4.v[1] != 0) {
                                            fn_80031A00(0, &state->slots[1], object_id, &state->hit_pos[1], target, 0x1A, q1a, 10, 3, 0, flag);
                                            fn_8020104C(0x92, self, self, &state->hit_pos[1], lbl_8064E13C);
                                        }
                                        if (hits4.v[2] != 0) {
                                            fn_80031A00(0, &state->slots[2], object_id, &state->hit_pos[2], target, 0x19, q19, 10, 3, 0, flag);
                                            fn_8020104C(0x92, self, self, &state->hit_pos[2], lbl_8064E13C);
                                        }
                                        if (hits4.v[3] != 0) {
                                            fn_80031A00(0, &state->slots[3], object_id, &state->hit_pos[3], target, 0x17, q17, 10, 3, 0, flag);
                                            fn_8020104C(0x92, self, self, &state->hit_pos[3], lbl_8064E13C);
                                        }
                                        state->hit = 1;
                                        fn_802006D4(self, self, -1, 0x39, 0);
                                        fn_8020104C(0x39, self, self, 0, lbl_8064E120);
                                    }
                                }
                                if (state->hit == 0) {
                                    fn_801A74A8(handle, target);
                                    fn_801AC9F4(0x4A, 100, &target_pos, 3);
                                    fn_800359A0(target_obj, caster_obj);
                                    fn_801A7538(handle, 1);
                                    power = fn_801CEB2C(state->spell_id);
                                    delay = power >> 1;
                                    count = delay + 1;
                                    if ((state->spell_id & 0xF) == 8) {
                                        delay = (s16)(delay * 15);
                                        if (fn_80201B5C(target_obj) != 0x58) {
                                            fn_801DD0A8(state->spell_id, target_obj, 0);
                                        }
                                    } else {
                                        delay = fn_801D1B10((s16)(delay * 10), fn_80035628(target_obj), object_id, count);
                                    }
                                    if (target != fn_80201B44() && fn_80071DD8() != 0) {
                                        delay = 1;
                                    }
                                    fn_801A7518(handle, delay);
                                    fn_801A7588(handle, 0x8000);
                                    fn_801A764C(handle, &state->to);
                                    fn_801A74D8(handle, 0x800);
                                    fn_801A74D8(handle, 0x10000);
                                    switch (power) {
                                    case 3:
                                        fn_801A74D8(handle, 0x40000);
                                        break;
                                    case 5:
                                        fn_801A74D8(handle, 0x80000);
                                        break;
                                    case 7:
                                        fn_801A74D8(handle, 0x100000);
                                        break;
                                    }
                                    fn_801A7668(handle, object_id);
                                    fn_801A7670(handle, count);
                                    if (fn_80201B5C(target_obj) == 0x58) {
                                        fn_8020104C(0xED, caster, target, (void *)handle, lbl_8064E158);
                                        handle = 0;
                                        result = 1;
                                    } else {
                                        result = fn_8020123C(0xB, caster, target, handle);
                                    }
                                    if ((result & 1) && fn_80201B5C(target_obj) != 6 &&
                                        fn_80201B5C(target_obj) != 0x39) {
                                        fn_80031A00(1, &state->slots[0], object_id, &state->to, target, 0x18, q18, 10, 3, 0, flag);
                                        fn_80031A00(1, &state->slots[1], object_id, &state->to, target, 0x1A, q1a, 10, 3, 0, flag);
                                        fn_80031A00(1, &state->slots[2], object_id, &state->to, target, 0x19, q19, 10, 3, 0, flag);
                                        fn_80031A00(1, &state->slots[3], object_id, &state->to, target, 0x17, q17, 10, 3, 0, flag);
                                    }
                                }
                            }
                            if (!(result & 1) && lbl_8064D18C == room) {
                                fn_80031948(&state->to, object_id);
                                fn_80031694(&state->to, 1, object_id);
                            }
                        }
                    }
                }
                fn_801A7228(handle);
            }
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
