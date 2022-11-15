#pragma once
#include <SimpleFOC.h>

extern Encoder EncM4_BG;
extern Encoder EncM3_BD;
extern Encoder EncM2_FG; 
extern Encoder EncM1_FD; 

extern void doA_M1_FD();
extern void doB_M1_FD();

extern void doA_M2_FG();
extern void doB_M2_FG();

extern void doA_M3_BD();
extern void doB_M3_BD();

extern void doA_M4_BG();
extern void doB_M4_BG();