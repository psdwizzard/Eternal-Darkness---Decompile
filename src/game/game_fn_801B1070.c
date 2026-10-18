extern void AISetStreamVolLeft(int);
extern void AISetStreamVolRight(int);
extern void AISetStreamPlayState(int);

void __DTKStopAi(void)
{
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AISetStreamPlayState(0);
}
