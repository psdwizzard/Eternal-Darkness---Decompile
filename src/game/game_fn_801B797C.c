typedef unsigned char u8;
typedef unsigned int u32;

typedef struct VoiceNode VoiceNode;
struct VoiceNode {
    VoiceNode* next;
    u32 unk4;
    u8 index;
    u8 state;
};

typedef struct VoiceList {
    VoiceNode* head;
} VoiceList;

extern u8* synthVoice;

void HandleJobQueue(VoiceList* list, void (*callback)(u32))
{
    VoiceNode* node = list->head;
    while (node != 0) {
        VoiceNode* next = node->next;
        node->state = 0xFF;
        if (synthVoice[node->index * 0x404 + 0x11C] == 0) {
            callback(node->index);
        }
        node = next;
    }
    list->head = 0;
}
