typedef unsigned char u8;

typedef struct EventState {
    int unknown00;
    int unknown04;
    int type;
} EventState;

typedef struct EventRequest {
    int unknown00;
    int unknown04;
    int unknown08;
    int object_id;
    int type;
} EventRequest;

typedef u8 (*EventHandler)(EventState *, int, EventRequest *, int *);

typedef struct EventHandlerEntry {
    EventHandler handler;
    int unknown04;
    int unknown08;
    int unknown0C;
} EventHandlerEntry;

extern EventHandlerEntry lbl_80640448[];

u8 fn_80200B20(EventState *state, int object_id, EventRequest *request,
               int *result)
{
    if ((request->object_id != -1 && request->object_id != object_id) ||
        (request->type != -1 && request->type != state->type)) {
        return 0;
    }

    if (state->type != 0) {
        return lbl_80640448[state->type].handler(state, object_id, request,
                                                 result);
    }

    return 0;
}
