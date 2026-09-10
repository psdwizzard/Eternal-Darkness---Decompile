typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct EventRequest {
    int type;
    int unknown04;
    int object_id;
    int has_primary;
    int unknown10;
    float time;
} EventRequest;

typedef struct EventState {
    int unknown00;
    int unknown04;
    int first_id;
    int second_id;
    int owner_id;
    int current_id;
    int final_id;
    int unknown1C;
    u8 replay_primary;
    u8 replay_secondary;
} EventState;

typedef struct ReplayRequest {
    int mode;
    int first_id;
    int second_id;
    int object_id;
    int owner_id;
    int unknown14;
    int unknown18;
    int unknown1C;
} ReplayRequest;

extern EventState *fn_80201814(int);
extern void fn_80200C38(EventRequest *);
extern void fn_801A7228(void);
extern float fn_80200BDC(void);
extern void fn_80200B9C(EventRequest *);
extern u8 fn_80200B20(EventState *, int, EventRequest *, int *);
extern u64 fn_8020123C(int, int, int, int);

u64 fn_8020088C(EventRequest *request)
{
    int status;
    EventState *state;
    int result;
    int replay_result;

    state = fn_80201814(request->object_id);
    result = 0;
    status = 0;

    if (state == 0) {
        if (request->type == 0xED || request->type == 0x3A) {
            fn_80200C38(request);
            fn_801A7228();
        }
        return ((u64)8 << 32) | (u32)result;
    }

    if ((request->type == 0xED || request->type == 0x3A) &&
        state->first_id == 0) {
        fn_80200C38(request);
        fn_801A7228();
        return ((u64)8 << 32) | (u32)result;
    }

    if (request->time > fn_80200BDC()) {
        fn_80200B9C(request);
        return ((u64)0x40 << 32) | (u32)result;
    }

    status |= 1;
    if (request->has_primary != 0) {
        if (fn_80200B20(state, state->current_id, request, &result)) {
            goto checked;
        }
    }

    status &= 0xFFFFFFFE;
    if (request->type != 3) {
        if (fn_80200B20(state, 0, request, &result)) {
            status |= 2;
        }
    } else {
        status |= 2;
    }

checked:
    {
        int neither = 0;
        if ((status & 2) == 0 && (status & 1) == 0) {
            neither = 1;
        }
        if (neither != 0) {
        status |= 4;
        }
    }

    while (state->replay_primary != 0) {
        ReplayRequest replay;

        if (state->current_id == state->final_id) {
            state->replay_primary = 0;
        } else {
            replay.second_id = state->owner_id;
            replay.first_id = state->owner_id;
            replay.object_id = -1;
            replay.owner_id = -1;
            state->replay_primary = 0;
            replay.mode = 2;
            fn_80200B20(state, state->current_id, (EventRequest *)&replay,
                        &replay_result);

            state->current_id = state->final_id;
            replay.mode = 1;
            fn_80200B20(state, state->current_id, (EventRequest *)&replay,
                        &replay_result);
            status |= 0x10;
        }
    }

    while (state->replay_secondary != 0) {
        ReplayRequest replay;

        if (state->first_id == state->second_id) {
            state->replay_secondary = 0;
        } else {
            replay.second_id = state->owner_id;
            replay.first_id = state->owner_id;
            replay.object_id = -1;
            replay.owner_id = -1;
            state->replay_secondary = 0;
            replay.mode = 2;
            fn_80200B20(state, state->current_id, (EventRequest *)&replay,
                        &replay_result);

            state->current_id = 0;
            state->first_id = state->second_id;
            replay.mode = 1;
            fn_8020123C(1, state->owner_id, state->owner_id, 0);
            status |= 0x20;
        }
    }

    return ((u64)(u32)status << 32) | (u32)result;
}
