typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

/* Retail embeds seven 0xC4-byte attachment records after the effect handles. */
typedef struct Attachment {
    u8 bytes[0xC0];
    void* resource;
} Attachment;

typedef struct EffectBlock {
    u8 positions[0x4D0];
    u8 velocities[0x4D0];
    void* effects[7];
    Attachment attachments[7];
    void* children[7];
} EffectBlock;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Direction { u32 word; u16 half; } Direction;
typedef struct ParticleParams { u8 bytes[0x90]; } ParticleParams;
typedef struct Descriptor { u8 bytes[0xC0]; } Descriptor;

typedef struct Object { u8 bytes[0x1000]; } Object;

extern int lbl_8064D18C;
extern void* fn_80201814(u32);
extern int fn_80201B64(void);
extern void* fn_80201BC8(void*);
extern int fn_800A0C0C(int);
extern void fn_801D88D4(u32, u32);
extern void fn_801FE22C(u32);
extern void fn_801B05B0(int, int);
extern void fn_801D884C(Object*);
extern s16 fn_801CEB2C(u32);
extern void fn_8017FF04(void*, int);
extern u16 fn_8017FEA4(void*);
extern void fn_8017FF14(void*, u16);
extern u8 fn_801911D0(void*);
extern void fn_801911F4(void*, u8);
extern int fn_8012F674(void*, int, int);
extern void fn_80121104(void*, float);
extern void fn_80182430(void*, int);
extern void fn_80182440(void*, int);
extern void fn_80182428(void*, int);
extern s16 fn_801D3A34(u32, int);
extern void fn_80153A24(float*, int, int, s16, s16, u8*, u8*, int);
extern void fn_801FDF74(u32, u32);
extern void fn_8012C62C(void*, int, u32*, u32*, u32*, int);
extern void fn_8012F58C(void*, int, int, int, int, int);
extern void* fn_80149E04(void);
extern void fn_80147E88(void*);
extern void fn_801495FC(Attachment*, void*);
extern void fn_80149B0C(void*, void*, void*);
extern void fn_801913F4(Attachment*);
extern void fn_8017FF0C(void*, int);
extern void fn_8017FE24(void*, int);
extern void* fn_80155DB4(void*);
extern void fn_801570F8(void*, void*);
extern void fn_8015690C(void*, int);
extern void fn_80156FF4(void*);
extern void fn_800073D8(int);
extern void fn_80157438(int, int);
extern void fn_80149EB8(void*);
extern void* fn_80148300(void*, void*, void*);
extern void fn_80148E04(void);
extern void fn_80156904(void*, void (*)(void));
extern void fn_80156F80(void*, void*);
extern const u32 lbl_80651118;
extern const u16 lbl_8065111C;
extern const float lbl_806510F8;
extern const float lbl_80651150;
extern const float lbl_80651154;
extern const float lbl_80651158;
extern const u32 lbl_802FC5BC[];
extern void fn_80182380(ParticleParams*);
extern float fn_80048C2C(float);
extern float fn_80048C50(float);
extern void fn_80182448(void);
extern void* fn_80148008(Vec3*, Direction*, ParticleParams*, void (*)(void));
extern void* fn_80156938(void*);
extern void fn_8017FF1C(void*, int);
extern void fn_801489B4(Descriptor*, void*);
extern void fn_80149B38(void*);
extern void fn_80184740(Descriptor*);
extern void fn_80182370(void*, void*, int);
extern void fn_801FE934(u32, int);
extern const u32 lbl_80651120;
extern const u32 lbl_80651124;
extern const u32 lbl_80651128;
extern const u32 lbl_8065112C;
extern const u32 lbl_80651130;
extern const u32 lbl_80651134;
extern const u32 lbl_80651138;
extern const u32 lbl_8065113C;
extern const u32 lbl_80651140;
extern const u32 lbl_80651144;
extern const u32 lbl_80651148;
extern const u32 lbl_8065114C;

void fn_801D8E40(void* arg)
{
    Object* object = arg;
    EffectBlock* data = (EffectBlock*)(object->bytes + 0xBC);
    u32 flags;
    void* subject;
    void** effect;
    s16 count;
    int i;
    u16 timer;

    flags = *(u32*)(object->bytes + 4);
    subject = fn_80201814(*(u32*)(object->bytes + 0xC));
    if (*(int*)(object->bytes + 8) != lbl_8064D18C || (object->bytes[0xFF0] & 1) != 0) {
        if (*(u16*)(object->bytes + 0xFF4) == 0 && fn_800A0C0C(0) == 0)
            fn_801D88D4(flags, *(u32*)(object->bytes + 0xC));
        fn_801FE22C(*(u32*)(object->bytes + 0x44));
        if (*(int*)(object->bytes + 0x10) != -1)
            fn_801B05B0(*(int*)(object->bytes + 0x10), 10);
        fn_801D884C(object);
        return;
    }

    if (subject != 0 && fn_80201B64() == 8) {
        if (*(u16*)(object->bytes + 0xFF4) > 30) {
            count = fn_801CEB2C(flags);
            if (*(u16*)(object->bytes + 0xFF4) > 110) {
                for (i = 0; i < count; i++) {
                    effect = &data->effects[i];
                    if (*effect != 0) {
                        fn_8017FF04(*effect, -24);
                        fn_801911F4(*effect, fn_801911D0(*effect) & ~1);
                    }
                }
            } else {
                for (i = 0; i < count; i++) {
                    effect = &data->effects[i];
                    if (*effect != 0)
                        fn_8017FF14(*effect, (u16)(fn_8017FEA4(*effect) - 1));
                }
            }
        }
        fn_801FE22C(*(u32*)(object->bytes + 0x44));
        if (*(int*)(object->bytes + 0x10) != -1)
            fn_801B05B0(*(int*)(object->bytes + 0x10), 10);
        fn_801D884C(object);
        return;
    }

    timer = *(u16*)(object->bytes + 0xFF4);
    if (timer >= 130 && timer < 160) {
        subject = fn_80201BC8(subject);
        if ((fn_8012F674(subject, 15, 0) & 8) == 0)
            fn_80121104(subject, lbl_806510F8 + (float)(*(u16*)(object->bytes + 0xFF4) - 129) / lbl_80651150);
    }

    switch (*(u16*)(object->bytes + 0xFF4)) {
    case 0:
        if (fn_800A0C0C(0) == 0) {
            fn_801D88D4(flags, *(u32*)(object->bytes + 0xC));
        } else {
            fn_801FE22C(*(u32*)(object->bytes + 0x44));
            if (*(int*)(object->bytes + 0x10) != -1)
                fn_801B05B0(*(int*)(object->bytes + 0x10), 10);
            fn_801D884C(object);
        }
        break;
    /* Build the ring of particle effects and their child objects. */
    case 30:
        {
            Direction direction;
            ParticleParams params;
            Vec3 position;
            Vec3 submit_position;
            Descriptor descriptor;
            direction.word = lbl_80651118;
            direction.half = lbl_8065111C;
            fn_80182380(&params);
            params.bytes[0] = 3;
            params.bytes[1] = 8;
            *(u16*)(params.bytes + 4) = fn_801D3A34(flags, 49);
            *(u16*)(params.bytes + 6) = 110;
            *(u16*)(params.bytes + 8) = 4;
            *(u16*)(params.bytes + 0x1A) = 1;
            params.bytes[0x1F] = 7;
            params.bytes[0x20] = 0;
            params.bytes[0x27] = 1;
            count = fn_801CEB2C(flags);
            for (i = 0; i < count; i++) {
                float angle = lbl_80651154 * i / count;
                void* spawned;
                position.x = *(float*)(object->bytes + 0x38) + lbl_80651158 * fn_80048C2C(angle);
                position.y = *(float*)(object->bytes + 0x3C) + lbl_80651158 * fn_80048C50(angle);
                position.z = *(float*)(object->bytes + 0x40);
                submit_position = position;
                spawned = fn_80148008(&submit_position, &direction, &params, fn_80182448);
                if (spawned != 0) {
                    void* particle = fn_80156938(spawned);
                    u8* resource;
                    fn_8017FF1C(particle, 4);
                    resource = fn_80149E04();
                    if (resource != 0) {
                        void** child = &data->children[i];
                        fn_80147E88(&descriptor);
                        fn_801489B4(&descriptor, resource);
                        *(u32*)(descriptor.bytes + 0x94) = 0;
                        descriptor.bytes[0xBC] = 4;
                        resource[0] = params.bytes[0];
                        fn_80149B38(resource);
                        fn_80184740(&descriptor);
                        descriptor.bytes[1] = params.bytes[1];
                        descriptor.bytes[0] = 32;
                        *(u16*)(descriptor.bytes + 4) = fn_801D3A34(flags, 78);
                        *(u32*)(descriptor.bytes + 0x2C) = lbl_802FC5BC[3];
                        descriptor.bytes[0x14] = 7;
                        descriptor.bytes[0x2F] = 224;
                        *child = fn_80148300(spawned, &descriptor, resource);
                        if (*child != 0) {
                            int j;
                            for (j = 0; j < params.bytes[0]; j++)
                                fn_80182370(particle, ((void**)(resource + 0x88))[j], j);
                        } else {
                            fn_80149EB8(resource);
                        }
                    }
                    data->effects[i] = fn_80156938(spawned);
                }
            }
            fn_801FE934(*(u32*)(object->bytes + 0x44), 25);
        }
        break;
    case 32:
        count = fn_801CEB2C(flags);
        for (i = 0; i < count; i++) {
            effect = &data->effects[i];
            if (*effect != 0) {
                fn_80182430(*effect, 8);
                fn_80182440(*effect, 3);
            }
        }
        fn_80153A24((float*)(object->bytes + 0x38), count, 250, fn_801D3A34(flags, 70),
                    fn_801D3A34(flags, 74), data->positions, data->velocities, 4);
        break;
    case 36:
        count = fn_801CEB2C(flags);
        for (i = 0; i < count; i++) {
            effect = &data->effects[i];
            if (*effect != 0) fn_80182430(*effect, 10);
        }
        break;
    case 44:
        count = fn_801CEB2C(flags);
        for (i = 0; i < count; i++) {
            effect = &data->effects[i];
            if (*effect != 0) {
                fn_80182430(*effect, 14);
                fn_80182440(*effect, 7);
            }
        }
        break;
    case 54:
        count = fn_801CEB2C(flags);
        for (i = 0; i < count; i++) {
            effect = &data->effects[i];
            if (*effect != 0) fn_80182430(*effect, 18);
        }
        break;
    case 70:
        count = fn_801CEB2C(flags);
        for (i = 0; i < count; i++) {
            effect = &data->effects[i];
            if (*effect != 0) fn_80182430(*effect, 20);
        }
        break;
    case 82:
        count = fn_801CEB2C(flags);
        for (i = 0; i < count; i++) {
            effect = &data->effects[i];
            if (*effect != 0) fn_80182430(*effect, 24);
        }
        break;
    case 100:
        count = fn_801CEB2C(flags);
        for (i = 0; i < count; i++) {
            effect = &data->effects[i];
            if (*effect != 0) fn_80182428(*effect, 1);
        }
        break;
    /* Transfer the effects to attachments on the current subject. */
    case 110: {
        void* target = fn_80201814(*(u32*)(object->bytes + 0xC));
        if (target != 0) {
            count = fn_801CEB2C(flags);
            for (i = 0; i < count; i++) {
                if (data->effects[i] != 0) {
                    void* resource;
                    if ((resource = data->attachments[i].resource = fn_80149E04()) != 0) {
                        Attachment* attachment = &data->attachments[i];
                        void* particle;
                        void* owner;
                        Attachment* slot;
                        void* attached;
                        fn_80147E88(attachment);
                        fn_801495FC(attachment, resource);
                        attachment->bytes[0xBC] = 4;
                        *(u32*)(attachment->bytes + 0xA8) = *(u32*)(object->bytes + 0xC);
                        fn_80149B0C(resource, 0, 0);
                        fn_801913F4(attachment);
                        particle = data->effects[i];
                        *(void**)(attachment->bytes + 0xC) = particle;
                        fn_8017FF04(particle, -4);
                        fn_8017FF0C(particle, 240);
                        fn_8017FF14(particle, (u16)(fn_8017FEA4(particle) + 1));
                        fn_8017FE24(particle, 240);
                        attachment->bytes[0x14] = 1;
                        attachment->bytes[0x16] = 40;
                        attachment->bytes[0x15] = 3;
                        attachment->bytes[0x17] = 5;
                        *(u32*)(attachment->bytes + 0x28) = *(u32*)(object->bytes + 0xC);
                        *(u32*)(attachment->bytes + 0x2C) = 0;
                        owner = fn_80155DB4(particle);
                        fn_801570F8(data->children[i], owner);
                        fn_8015690C(owner, 0);
                        fn_80156FF4(owner);
                        slot = &data->attachments[i];
                        owner = fn_80155DB4(target);
                        if (owner == 0) {
                            fn_800073D8(-1);
                            fn_80157438(9, 0);
                            fn_80149EB8(slot->resource);
                            slot->resource = 0;
                        } else {
                            attached = fn_80148300(owner, slot, slot->resource);
                            if (attached != 0) {
                                fn_80156904(data->children[i], fn_80148E04);
                                fn_80156F80(data->children[i], attached);
                            } else {
                                fn_80149EB8(slot->resource);
                                slot->resource = 0;
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    case 140:
        fn_801FDF74(*(u32*)(object->bytes + 0x44), 0x7A120);
        break;
    case 150: {
        void* actor;
        subject = fn_80201814(*(u32*)(object->bytes + 0xC));
        if (subject != 0) {
            actor = fn_80201BC8(subject);
            if (actor != 0 && (fn_8012F674(actor, 15, 0) & 8) == 0) {
                switch (flags & 0xF) {
                case 1: {
                    u32 a;
                    u32 b;
                    u32 c;
                    c = lbl_80651128;
                    b = lbl_80651124;
                    a = lbl_80651120;
                    fn_8012C62C(actor, 15, &a, &b, &c, 2);
                    break;
                }
                case 2: {
                    u32 a;
                    u32 b;
                    u32 c;
                    c = lbl_80651134;
                    b = lbl_80651130;
                    a = lbl_8065112C;
                    fn_8012C62C(actor, 15, &a, &b, &c, 2);
                    break;
                }
                case 4: {
                    u32 a;
                    u32 b;
                    u32 c;
                    c = lbl_80651140;
                    b = lbl_8065113C;
                    a = lbl_80651138;
                    fn_8012C62C(actor, 15, &a, &b, &c, 2);
                    break;
                }
                case 8: {
                    u32 a;
                    u32 b;
                    u32 c;
                    c = lbl_8065114C;
                    b = lbl_80651148;
                    a = lbl_80651144;
                    fn_8012C62C(actor, 15, &a, &b, &c, 2);
                    break;
                }
                }
                fn_8012F58C(actor, 15, 0, 0, 0, 4);
            }
        }
        break;
    }
    case 160:
        if (*(void (**)(Object*, u32))(object->bytes + 0x28) != 0)
            (*(void (**)(Object*, u32))(object->bytes + 0x28))(object, *(u32*)(object->bytes + 0x2C));
        fn_801D884C(object);
        break;
    }
}
