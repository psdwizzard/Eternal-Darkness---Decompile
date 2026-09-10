typedef void (*CommFunction)(void);

extern int OSReport(const char *, ...);
extern int Hu_IsStub(void);
extern int AMC_IsStub(void);
extern void EXI2_Init(void);
extern void EXI2_EnableInterrupts(void);
extern void EXI2_Poll(void);
extern void EXI2_ReadN(void);
extern void EXI2_WriteN(void);
extern void EXI2_Reserve(void);
extern void EXI2_Unreserve(void);
extern void DBInitComm(void);
extern void DBInitInterrupts(void);
extern void DBQueryData(void);
extern void DBRead(void);
extern void DBWrite(void);
extern void DBOpen(void);
extern void DBClose(void);
extern CommFunction gDBCommTable[7];
extern char lbl_80239C88[];
extern char lbl_80239CAC[];

int InitMetroTRKCommTable(int hardware)
{
    int result;

    if (hardware == 1) {
        OSReport(lbl_80239C88);
        result = Hu_IsStub();
        gDBCommTable[0] = DBInitComm;
        gDBCommTable[1] = DBInitInterrupts;
        gDBCommTable[2] = DBQueryData;
        gDBCommTable[3] = DBRead;
        gDBCommTable[4] = DBWrite;
        gDBCommTable[5] = DBOpen;
        gDBCommTable[6] = DBClose;
    } else {
        OSReport(lbl_80239CAC);
        result = AMC_IsStub();
        gDBCommTable[0] = EXI2_Init;
        gDBCommTable[1] = EXI2_EnableInterrupts;
        gDBCommTable[2] = EXI2_Poll;
        gDBCommTable[3] = EXI2_ReadN;
        gDBCommTable[4] = EXI2_WriteN;
        gDBCommTable[5] = EXI2_Reserve;
        gDBCommTable[6] = EXI2_Unreserve;
    }

    return result;
}
