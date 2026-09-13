typedef unsigned int u32;

extern void fn_8011F950(void *object);
extern int fn_80201A84(void *object);
extern void *fn_8012E568(void *object, int value, int type);
extern void fn_80120874(void *object);
extern u32 fn_8011FA8C(void *object, int value, u32 flags);
extern void *fn_80204758(int type);
extern void fn_80201DD0(void *object, void *resource);
extern void fn_80201D3C(void *object, int value);
extern void fn_8011EAFC(void *object, int value);
extern int fn_80201B44(void);
extern void fn_802015A4(void *object);
extern void fn_8012E524(void *resource, void *object, int value);
extern void fn_80128DA8(void *object, void *resource);
extern void fn_80128DCC(void *object, void *resource);
extern void *fn_80128E30(void *object);
extern void fn_8012880C(void *object, int first, int second);
extern void fn_801296E8(void *object, int value);
extern int fn_80128F40(void *object);
extern void fn_8011FED4(void *object, int value);
extern void fn_8011EBFC(void *object);
extern void fn_801E8328(int type, void *object);

void *fn_80205730(void *object, int value, int type, u32 flags)
{
    void *resource;
    void *created;
    void *component;
    int owner;

    fn_8011F950(object);
    owner = fn_80201A84(object);
    resource = fn_8012E568(object, value, type);
    fn_80120874(object);
    fn_8011FA8C(resource, 0, flags & ~0x20000000);

    created = fn_80204758(3);
    fn_80201DD0(created, resource);
    fn_80201D3C(created, 3);
    fn_8011EAFC(resource, 5);
    if (owner == fn_80201B44()) {
        fn_8011EAFC(resource, 6);
    }

    fn_802015A4(created);
    fn_8012E524(resource, object, value);
    fn_80128DA8(object, resource);
    fn_80128DCC(object, resource);
    component = fn_80128E30(resource);
    fn_8012880C(component, 1, 1);
    fn_801296E8(component, 0);
    fn_8011FED4(resource, fn_80128F40(object));
    fn_8011EBFC(resource);
    fn_801E8328(0xF, created);
    return created;
}
