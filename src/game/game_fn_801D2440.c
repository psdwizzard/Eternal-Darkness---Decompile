typedef unsigned char u8;
typedef unsigned short u16;
typedef struct GameObject GameObject;
typedef struct Vec3 { float x, y, z; } Vec3;

struct GameObject {
    u8 pad00[4]; void* owner; int type; int id; int handle;
    u8 pad14[0x14]; void (*callback)(GameObject*, void*); void* callback_arg;
    u8 pad30[8]; Vec3 position; void* resource44; u8 pad48[0x74];
    void* actorBC; void* actorC0; void* actorC4; u8 payloadC8[0xF28];
    u8 flagsFF0; u8 padFF1[3]; u16 stateFF4;
};

extern int lbl_8064D18C, lbl_8064C504;
extern void* lbl_8064D558;
extern float lbl_80651088, lbl_8065108C, lbl_80651090;
extern float lbl_80651094, lbl_80651098, lbl_8065109C, lbl_806510A0;

extern int fn_80027948(); extern void fn_8002A4C8(void); extern void fn_8002A508(void);
extern void fn_8002A590(void); extern void fn_8002A754(void); extern void fn_8002AA18(void);
extern void fn_8002AC60(void); extern void* fn_80034708(); extern int fn_80047D6C();
extern int fn_800CC140(); extern int fn_800CCA44(); extern int fn_800DC2B8();
extern int fn_800DC398(); extern int fn_800DBF60(); extern int fn_8011ECF8();
extern int fn_8011F114(); extern int fn_8011FA8C(); extern int fn_8011FCB0();
extern int fn_8011FE3C(); extern int fn_801261F4(); extern int fn_80128E30();
extern int fn_8012B7A0(); extern int fn_8012C62C(); extern int fn_80147E88();
extern void* fn_80149E04(); extern int fn_80149B38(); extern int fn_8014A178();
extern int fn_80155DB4(); extern int fn_801568B8(); extern int fn_801568C0();
extern int fn_801568C8(); extern int fn_801568D8(); extern int fn_801568E4();
extern int fn_801568F0(); extern int fn_801568FC(); extern int fn_80156904();
extern int fn_8015690C(); extern int fn_80156918(); extern void* fn_80156DA0();
extern int fn_80156F80(); extern int fn_801570F8(); extern int fn_80157888();
extern int fn_80157894(); extern int fn_801579F4(); extern int fn_80157B3C();
extern int fn_80157B60(); extern int fn_80157B80(); extern int fn_80157BD0();
extern int fn_80157BE8(); extern int fn_8015821C(); extern int fn_80158264();
extern int fn_80158550(); extern int fn_80158598(); extern int fn_801938FC();
extern int fn_801B05B0(); extern int fn_801CEB2C(); extern int fn_801D1318();
extern int fn_801D1C34(); extern int fn_801D1F78(); extern void fn_801D2FA4(GameObject*);
extern void fn_801D3024(void); extern void fn_801D3088(void); extern int fn_801D38E8();
extern int fn_801D3CAC(); extern int fn_801E2CF4(); extern int fn_801E6CA0();
extern int fn_801E8328(); extern int fn_801FDF74(); extern int fn_801FE22C();
extern int fn_801FE934(); extern int fn_802006D4(); extern void* fn_802015A4();
extern void* fn_80201814(); extern int fn_80201ADC(); extern void* fn_80201AE4();
extern void* fn_80201B54(); extern void* fn_80201BC8(); extern void* fn_80201C24();
extern void* fn_80201C2C(); extern int fn_80201D24(); extern int fn_80201D54();
extern void* fn_80204A8C(); extern int fn_80204CE4(); extern int fn_80204E0C();
extern int fn_80204F54(); extern int fn_8020123C();

void fn_801D2440(GameObject* object)
{
    void *actor, *info, *current, *data, *other, *other_info;
    void *owner, *item, *result, *target;
    int count, value, flag, color;
    Vec3 point;
    float a[3], b[3];
    u8 query[0x30];
    u8* payload;

    if (object->type != lbl_8064D18C) {
        actor = object->actorBC;
        info = fn_80201814(actor);
        current = fn_80201C24();
        if (fn_80157894() & 1) {
            fn_80201ADC();
            current = fn_80201C2C();
            if (object->stateFF4 <= 80) fn_80204E0C(info, current);
            else {
                other_info = fn_80201814(object->actorC0);
                fn_80204F54(info);
                fn_8020123C(57, actor, actor, 0);
                fn_80204E0C(other_info, current);
            }
        } else if (object->stateFF4 != 0) {
            owner = fn_80201AE4();
            target = (void*)fn_80201ADC();
            if (target != 0) {
                other = fn_80201C2C();
                data = (void*)fn_80155DB4(info);
                fn_80204E0C(info, other);
                count = fn_801579F4(current);
                if (count > 0) fn_80204E0C(fn_80201814((void*)count), other);
                fn_801568F0(data); fn_801568E4(data); fn_801568D8(data);
                result = fn_80201BC8(info);
                fn_8011FE3C(result, fn_80201BC8(target));
                fn_80156904(data, fn_8002A754);
                fn_80156F80(data, fn_80155DB4(target));
                value = fn_80158598(owner, 0);
                value = fn_80158264(value, current, 1);
                fn_800CC140(owner, actor, 0,
                             ((void**)*(void**)(*(void**)current))[value], 0);
            }
        }
        fn_801FE22C(object->resource44);
        if (object->handle != -1) fn_801B05B0(object->handle, 10);
        fn_801D2FA4(object);
        if (object->flagsFF0 & 0x10) fn_801D1318(0);
        return;
    }

    owner = object->owner;
    switch (object->stateFF4) {
    case 0:
        actor = object->actorBC; info = fn_80201814(actor); current = fn_80201C24();
        flag = fn_80157888(); other = object->actorC4;
        count = fn_801579F4(current); other_info = fn_80201814((void*)count);
        if (flag & 1) {
            lbl_8064D558 = actor;
            value = fn_80158598(other, 0); value = fn_80158550(value, actor);
            fn_800CC140(other, actor, 0, value, 0); lbl_8064D558 = 0;
            fn_80204E0C(info, fn_80204A8C());
            if (count > 0) fn_80204E0C(other_info, fn_80204A8C());
        }
        data = (void*)fn_80155DB4(info);
        result = fn_80201BC8(info);
        fn_8011FE3C(result, result);
        fn_801568C0(data, fn_801D3024); fn_801568B8(data, fn_8002AC60);
        fn_801568FC(data, 0); fn_80156904(data, 0);
        if (count > 0) {
            result = (void*)fn_80155DB4(other_info);
            target = fn_80201BC8(other_info);
            fn_8011FE3C(target, target);
            fn_801568C0(result, fn_801D3024); fn_801568B8(result, fn_8002AC60);
            fn_801568FC(result, 0); fn_80156904(result, 0);
        }
        if (other != fn_80201AE4()) fn_801570F8(data, fn_80155DB4(fn_80201814(other)));
        payload = object->payloadC8; *(void**)(payload + 0xC0) = fn_80149E04();
        if (*(void**)(payload + 0xC0) == 0) break;
        fn_80147E88(payload); fn_8014A178(payload, *(void**)(payload + 0xC0));
        payload[0xBC] = 4; actor = object->owner; color = fn_801CEB2C(actor);
        *(u8*)*(void**)(payload + 0xC0) = color; fn_80149B38(*(void**)(payload + 0xC0));
        fn_801938FC(payload); *(u16*)(payload + 6) = 80;
        result = (void*)fn_801D38E8(actor); fn_801D3CAC(result, 0, payload + 0x14);
        payload[0x16] = 0; *(int*)(payload + 0x38) |= 0x4800;
        *(void**)(payload + 0xA8) = object->actorBC; payload[0xAC] = (u8)color;
        *(u16*)(payload + 0xAE) = 250; *(Vec3*)(payload + 0xB0) = object->position;
        fn_801D1F78(*(void**)(payload + 0xC0), payload + 0xAC, *(void**)(payload + 0xA8));
        fn_801E8328(17, payload); break;
    case 20:
        fn_801FDF74(object->resource44, 0x7A120);
        fn_801E2CF4(object, object->payloadC8, object->actorBC, 1, 1, 15, 53, 4, 10, 15, 1, 1, 80); break;
    case 30:
        info = fn_80201814(object->actorBC); fn_8011FA8C(fn_80201BC8(info), 0, 0x10000);
        data = (void*)fn_80155DB4(info); fn_801568C0(data, fn_801D3088);
        count = fn_801579F4(fn_80201C24());
        if (count > 0) { data = (void*)fn_80155DB4(fn_80201814((void*)count)); fn_801568C0(data, fn_801D3088); }
        fn_801FE934(object->resource44, 9); break;
    case 40:
        fn_801E2CF4(object, object->payloadC8, object->actorBC, 2, 1, 15, 53, 4, 10, 15, 1, 2, 60); break;
    case 60:
        fn_801E2CF4(object, object->payloadC8, object->actorBC, 3, 1, 15, 53, 4, 10, 15, 1, 3, 40); break;
    case 80:
        if (object->actorC4 != fn_80201AE4()) break;
        actor = object->actorBC; info = fn_80201814(actor); fn_80201C24();
        if (!(fn_80157894() & 1)) break;
        current = fn_80201BC8(info);
        a[2] = lbl_80651088; a[1] = lbl_8065108C; a[0] = lbl_80651090;
        fn_8012C62C(current, 15, &a[2], &a[1], &a[0], 4);
        fn_8011F114(&point, current); fn_801D1C34(query, actor, &point);
        item = fn_80034708(query); target = fn_80201BC8(item);
        if (target != 0) {
            fn_801261F4(target); fn_8012B7A0(target, *(float*)(query + 0xC));
            if (fn_8011FCB0(target)) fn_8011ECF8(target, fn_80128E30(target));
        }
        fn_80201D54(item, *(void**)(query + 0x2C)); fn_80201D24(item, 1);
        fn_802015A4(item); fn_800CCA44(item); data = fn_80156DA0(3, &point);
        if (data != 0) {
            void (*cb)(void) = fn_8002A590;
            if (fn_8011FCB0(target)) cb = fn_8002A508;
            fn_801568C8(data, cb, fn_8002AC60, fn_8002AA18);
            fn_801568C0(data, fn_801D3088); fn_801568B8(data, fn_8002AC60);
            fn_801568FC(data, 0); fn_80156904(data, 0);
            fn_8015690C(data, fn_8002A4C8); fn_80156918(data, item);
        }
        b[2] = lbl_80651094; b[1] = lbl_80651098; b[0] = lbl_8065109C;
        fn_8012C62C(target, 15, &b[2], &b[1], &b[0], 4);
        fn_80204CE4(item, fn_80204A8C()); object->actorC0 = fn_80201B54(item); break;
    case 100:
        owner = fn_80201AE4(); actor = object->actorBC; other = object->actorC4;
        info = fn_80201814(actor); data = (void*)fn_80155DB4(info); current = fn_80201C24();
        if (other == owner) {
            flag = fn_80157888(); fn_801568FC(data, fn_8002AA18);
            if (flag & 1) {
                fn_802006D4(actor, actor, -1, 75, 0);
                fn_80157B60(current, (u8)fn_801D38E8(object->owner));
                color = ((short)fn_801CEB2C(object->owner) >> 1) + 1;
                fn_80157B3C(current, (u8)color); fn_80157B80(current, 2); flag = 1;
                count = fn_801579F4(current);
                if (count > 0) {
                    fn_80201814((void*)count); target = fn_80201C24();
                    fn_802006D4((void*)count, (void*)count, -1, 75, 0);
                    fn_80157B60(target, (u8)fn_801D38E8(object->owner));
                    color = ((short)fn_801CEB2C(object->owner) >> 1) + 1;
                    fn_80157B3C(target, (u8)color);
                }
            } else {
                fn_80204F54(info); fn_8020123C(57, actor, actor, 0);
                actor = object->actorC0; fn_80201814(actor); current = fn_80201C24(); flag = 0;
                if (fn_8015821C(current) == 131) {
                    value = (u8)fn_801D38E8(object->owner);
                    color = (u8)(((short)fn_801CEB2C(object->owner) >> 1) + 1);
                    fn_80157B60(current, value); fn_80157B3C(current, color);
                    fn_800DC398(color); fn_800DC2B8(actor, value, color);
                }
                fn_80157B80(current, 0x200);
            }
            if (object->id != (int)owner && fn_80157BD0(current) == 18) value = 24;
            else value = fn_80157BE8(current);
            result = (void*)fn_801E6CA0(lbl_8064C504, 0, value, 0, 1);
            fn_80027948(result, 0, owner, actor, flag, 0, 0);
        } else {
            value = fn_80047D6C(); fn_802006D4(actor, actor, -1, 75, 0);
            fn_80157B60(current, (u8)fn_801D38E8(object->owner));
            color = (u8)(((short)fn_801CEB2C(object->owner) >> 1) + 1);
            fn_80157B3C(current, color); fn_800DBF60(other, info, color, value, lbl_806510A0);
            fn_801568F0(data); fn_801568E4(data); fn_801568D8(data);
            result = fn_80201BC8(info); other_info = fn_80201814(other);
            fn_8011FE3C(result, fn_80201BC8(other_info));
            fn_80156904(data, fn_8002A754); fn_80156F80(data, fn_80155DB4(other_info));
            value = fn_80158598(other, 0); value = fn_80158264(value, current, 1);
            fn_800CC140(other, actor, 0,
                         ((void**)*(void**)(*(void**)current))[value], 0);
        }
        if (object->callback != 0) object->callback(object, object->callback_arg);
        fn_801D2FA4(object); break;
    }
}
