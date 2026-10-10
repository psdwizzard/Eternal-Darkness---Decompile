extern void* fn_80201B9C(void);
extern void* fn_80201BC0(void* node);
extern void fn_800468D0(void* node, void* arg);

void fn_80046B0C(void* arg) {
    void* node;
    for (node = fn_80201B9C(); node != 0; node = fn_80201BC0(node)) {
        fn_800468D0(node, arg);
    }
}
