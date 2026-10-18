extern unsigned char __files[];
extern char lbl_80239DE0[];
extern int fprintf(void *, const char *, ...);
extern void abort(void);

void __assertion_failed(void *a, void *b, void *c)
{
    fprintf(__files + 0xA0, lbl_80239DE0, a, b, c);
    abort();
}
