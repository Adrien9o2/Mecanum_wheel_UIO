#include "Encoder4Mot.h"

#include "Global.h"

Encoder4Mot::Encoder4Mot()
{
    for(int i = 0; i<4; i++)
    {
        speeds.push_back(0.0);
        last_speeds.push_back(0.0);
    }
    EncM4_BG.init();
    EncM4_BG.enableInterrupts(doA_M4_BG,doB_M4_BG);
    EncM3_BD.init();
    EncM3_BD.enableInterrupts(doA_M3_BD,doB_M3_BD);
    EncM2_FG.init();
    EncM2_FG.enableInterrupts(doA_M2_FG,doB_M2_FG);
    EncM1_FD.init();
    EncM1_FD.enableInterrupts(doA_M1_FD,doB_M1_FD);

}

Encoder4Mot::~Encoder4Mot()
{
}

const std::vector<float> & Encoder4Mot::Encoder4MotUpdate()
{

    last_speeds.assign(speeds.begin(),speeds.end());

    
    EncM1_FD.update();
    speeds[0] = EncM1_FD.getVelocity();
    EncM2_FG.update();
    speeds[1] = EncM2_FG.getVelocity();
    EncM3_BD.update();
    speeds[2] = EncM3_BD.getVelocity();
    EncM4_BG.update();
    speeds[3] = EncM4_BG.getVelocity();
    return speeds;
}

ostream& operator<<(ostream& os, const Encoder4Mot& enc)
{
    os<<"FG "<<enc.speeds[1]<<" FD "<<enc.speeds[0]<<std::endl<<"BG "<<enc.speeds[3]<<" BD "<<enc.speeds[2]<<std::endl;
    return os;
}