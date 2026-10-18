typedef int (*Callback)(int, void*);

typedef struct CallbackOwner {
    unsigned char pad00[0x18];
    void* argument;
} CallbackOwner;

extern Callback salMessageCallback;

int salSynthSendMessage(CallbackOwner* owner, int value)
{
    if (salMessageCallback == 0) {
        return 0;
    }

    return salMessageCallback(value, owner->argument);
}
