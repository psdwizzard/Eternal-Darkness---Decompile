typedef unsigned int u32;
typedef int s32;

typedef struct Request {
    u32 field_0;
    u32 field_4;
    u32 field_8;
    s32 field_C;
    u32 field_10;
    u32 field_14;
    u32 field_18;
    u32 field_1C;
} Request;

typedef struct QueueRecord {
    u32 field_0;
    u32 field_4;
    u32 field_8;
    u32 field_C;
} QueueRecord;

extern s32 lbl_8064D2C4;
extern u32 lbl_8064D2C8;
extern void* lbl_8064D2D8;
extern void* lbl_8064D2DC;
extern void fn_801CD538(Request*);
extern void OSSendMessage(void*, void*, int);
extern void ARQPostRequest(Request*, u32, u32, u32, u32, u32, u32, u32);

void fn_801AA398(Request* request)
{
    u32 base;
    QueueRecord* record;

    switch (request->field_C) {
    case 0:
        goto no_field_C;
    default:
        goto has_field_C;
    }

no_field_C:
    base = lbl_8064D2C8;
    if (base != 0 && request->field_10 >= base && request->field_10 < base + 0x600000) {
        lbl_8064D2C4 = (lbl_8064D2C4 + 1) % 1024;
        record = (QueueRecord*)((char*)lbl_8064D2DC + lbl_8064D2C4 * 16);
        record->field_0 = 0;
        record->field_8 = request->field_10 - lbl_8064D2C8;
        record->field_4 = request->field_14;
        record->field_C = request->field_18;
        OSSendMessage(lbl_8064D2D8, record, 0);
        fn_801CD538(request);
    } else {
        ARQPostRequest(request, request->field_4, request->field_8, request->field_C,
                     request->field_10, request->field_14, request->field_18,
                     request->field_1C);
    }
    goto done;

has_field_C:
    ARQPostRequest(request, request->field_4, request->field_8, request->field_C,
                 request->field_10, request->field_14, request->field_18,
                 request->field_1C);
done:
    return;
}
