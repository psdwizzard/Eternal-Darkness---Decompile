extern int lbl_8064C3C8;
extern void fn_8020AE7C(int heap, void *ptr);

/* Release a cached resource from the resource heap. */
void fn_8022C668(void *resource)
{
    fn_8020AE7C(lbl_8064C3C8, resource);
}
