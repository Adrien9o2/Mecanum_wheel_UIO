#pragma once

#include "Global_extern.h"
#include "Reglages.h"
#include <SimpleFOC.h>

Encoder EncM4_BG = Encoder(pinNametoDigitalPin(PA_13), pinNametoDigitalPin(PA_14),4*PPR);
Encoder EncM3_BD = Encoder(pinNametoDigitalPin(PC_13), pinNametoDigitalPin(PC_14),4*PPR);
Encoder EncM2_FG = Encoder(pinNametoDigitalPin(PH_0), pinNametoDigitalPin(PH_1),4*PPR);
Encoder EncM1_FD = Encoder(pinNametoDigitalPin(PC_2), pinNametoDigitalPin(PC_3),4*PPR);

void doA_M1_FD(){EncM1_FD.handleA();};
void doB_M1_FD(){EncM2_FG.handleB();};

void doA_M2_FG(){EncM2_FG.handleA();};
void doB_M2_FG(){EncM2_FG.handleB();};

void doA_M3_BD(){EncM3_BD.handleA();};
void doB_M3_BD(){EncM3_BD.handleB();};

void doA_M4_BG(){EncM4_BG.handleA();};
void doB_M4_BG(){EncM3_BD.handleB();};