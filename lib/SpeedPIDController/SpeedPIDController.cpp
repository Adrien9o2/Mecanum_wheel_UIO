#include "SpeedPIDController.h"

SpeedPIDController::SpeedPIDController(uint32_t input_rate_ms, double RayonRoues_i, double L1pL2_i ) : Kp(4,0),  Ki(4,0),  Kd(4,0),
e(4,0),  ei(4,0), ed(4,0), rate_ms(input_rate_ms), lastCall_date_ms(millis()), T(4,0), tau(4,0),setpoint_speed(4,0), RayonRoues(RayonRoues_i), L1pL2(L1pL2_i)
{
    delta = ((double)rate_ms)/1000.0;
    T = {T_M1_FD,T_M2_FG,T_M3_BD,T_M3_BG};
    tau = {TAU_M1_FD,TAU_M2_FG,TAU_M3_BD,TAU_M3_BG};
    Kd = (0.6/delta)*tau;
    Ki = (0.6*delta*T)/((0.5*delta + tau)*(0.5*delta + tau));
    Kp = (1.2*T)/(tau+delta) - Ki;
    motors = new BlocMoteurs();
    encoders = new Encoder4Mot();
    motors->motors_stop();
    
    std::cout<< "Kp :"<<std::endl;    
    std::cout << Kp[0] << " "<< Kp[1] << " "<< Kp[2] << " "<< Kp[3] << " "<<  std::endl;
    std::cout<< "Ki :"<<std::endl;    
    std::cout << Ki[0] << " "<< Ki[1] << " "<< Ki[2] << " "<< Ki[3] << " "<<  std::endl;
    std::cout<< "Kd :"<<std::endl;    
    std::cout << Kd[0] << " "<< Kd[1] << " "<< Kd[2] << " "<< Kd[3] << " "<<  std::endl;

    
}


SpeedPIDController::SpeedPIDController(BlocMoteurs* motors_ptr, Encoder4Mot* encoders_ptr, uint32_t input_rate_ms, double RayonRoues_i, double L1pL2_i) : Kp(4,0),  Ki(4,0),  Kd(4,0),
e(4,0),  ei(4,0), ed(4,0), rate_ms(input_rate_ms), lastCall_date_ms(millis()), T(4,0), tau(4,0), setpoint_speed(4,0), RayonRoues(RayonRoues_i), L1pL2(L1pL2_i)
{
    delta = ((double)rate_ms)/1000.0;
    T = {T_M1_FD,T_M2_FG,T_M3_BD,T_M3_BG};
    tau = {TAU_M1_FD,TAU_M2_FG,TAU_M3_BD,TAU_M3_BG};
    Kd = (0.6/delta)*tau;
    Ki = (0.6*delta*T)/((0.5*delta + tau)*(0.5*delta + tau));
    Kp = (1.2*T)/(tau+delta) - Ki;
    if(motors_ptr == NULL)
    {
        motors = new BlocMoteurs();
    }
    else
    {
        motors = motors_ptr;
    }
    if(encoders_ptr == NULL)
    {
        encoders = new Encoder4Mot();
    }
    else
    {
        encoders=encoders_ptr;
    }
    motors->motors_stop();


    
}

void SpeedPIDController::define_setpoint(double w_M1_FD, double w_M2_FG, double w_M3_BD, double w_M4_BG)
{
    setpoint_speed[0] = w_M1_FD;
    setpoint_speed[1] = w_M2_FG;
    setpoint_speed[2] = w_M3_BD;
    setpoint_speed[3] = w_M4_BG;
    motors->motors_on();
    
};

bool SpeedPIDController::update_controller()
{
    if(millis() > lastCall_date_ms + rate_ms)
    {
        std::vector<double> readings_vector = encoders->Encoder4MotUpdate();
        std::valarray<double> readings = {readings_vector[0], readings_vector[1], readings_vector[2], readings_vector[3] };
        readingsToRobotSpeedInItsFrameEnco(readings);
        ed = (setpoint_speed - readings) - e;
        e = setpoint_speed - readings;
        ei+=delta*e;
        std::valarray<double> u = Kp*e + Kd*ed + Ki*ei;
        motors->commande_vitesses(u[0],u[1],u[2],u[3]);
        lastCall_date_ms = millis();
        return true;       

    }
    else
    {
        return false;
    }
}

void SpeedPIDController::readingsToRobotSpeedInItsFrameEnco(std::valarray<double> readings)
{

    speed_robot_frame_robot_encoder.vx = (RayonRoues/4.0) * (readings[0] + readings[1] + readings[2] + readings[3]);
    speed_robot_frame_robot_encoder.vy = (RayonRoues/4.0) * (readings[0] - readings[1] - readings[2] + readings[3]);
    speed_robot_frame_robot_encoder.vtheta = (RayonRoues/(4.0*(L1pL2))) * (-readings[1] + readings[2] - readings[3] + readings[4]);

}

void SpeedPIDController::readingsToRobotSpeedInItsFrameGyro(std::valarray<double> readings, double wgyro)
{

    
    speed_robot_frame_robot_encoder.vtheta = wgyro;

    double w1th = ((wgyro*4*L1pL2)/RayonRoues)               - readings[2] + readings[3] - readings[4];
    double w2th = ((wgyro*4*L1pL2)/RayonRoues) + readings[1]               + readings[3] - readings[4];
    double w3th = ((wgyro*4*L1pL2)/RayonRoues) + readings[1] - readings[2]               - readings[4];
    double w4th = ((wgyro*4*L1pL2)/RayonRoues) + readings[1] - readings[2] + readings[3]              ;

    std::valarray<double> wth = { w1th, w2th, w3th, w4th};
    std::valarray<double> w_error = wth - readings;
    auto index = max_element(std::begin(w_error),std::end(w_error));
    int pos = index - std::begin(w_error);
    readings[pos] = wth[pos]; 

    speed_robot_frame_robot_encoder.vx = (RayonRoues/4.0) * (readings[0] + readings[1] + readings[2] + readings[3]);
    speed_robot_frame_robot_encoder.vy = (RayonRoues/4.0) * (readings[0] - readings[1] - readings[2] + readings[3]);
}


SpeedPIDController::~SpeedPIDController()
{
}