#include "SpeedPIDController.h"

SpeedPIDController::SpeedPIDController(/* args */) : Kp(4,0),  Ki(4,0),  Kd(4,0),
e(4,0),  ei(4,0), ed(4,0), rate_ms(0), lastCall_date_ms(millis()), T(4,0), tau(4,0)
{
    delta = ((float)rate_ms)/1000.0;
    T = {T_M1_FD,T_M2_FG,T_M3_BD,T_M3_BG};
    tau = {TAU_M1_FD,TAU_M2_FG,TAU_M3_BD,TAU_M3_BG};
    Kd = (0.6/delta)*tau;
    Ki = (0.6*delta*T)/((0.5*delta + tau)*(0.5*delta + tau));
    Kp = (1.2*T)/(tau+delta) - Ki;


    
}

SpeedPIDController::~SpeedPIDController()
{
}