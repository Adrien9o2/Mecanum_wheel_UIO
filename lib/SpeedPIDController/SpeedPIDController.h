#pragma once
#include "BlocMoteurs.h"
#include "Encoder4Mot.h"
#include <algorithm>
#include <vector>
#include <valarray>
#include "Reglages.h"

typedef struct _robotSpeed
{
    double vx;
    double vy;
    double vtheta;
}robotSpeed;

class SpeedPIDController
{
    private:
        std::valarray<double> Kp;
        std::valarray<double> Ki;
        std::valarray<double> Kd;
        std::valarray<double> e;
        std::valarray<double> ei;
        std::valarray<double> ed;
        std::valarray<double> T;
        std::valarray<double> tau;
        std::valarray<double> setpoint_speed;
        uint32_t rate_ms;
        double delta;
        uint32_t lastCall_date_ms;
        BlocMoteurs* motors;
        Encoder4Mot* encoders;
        robotSpeed speed_robot_frame_robot_encoder;
        robotSpeed speed_robot_frame_robot_gyro;
        double RayonRoues;
        double L1pL2;
        
    public:
        SpeedPIDController(BlocMoteurs* motors_ptr, Encoder4Mot* encoders_ptr, uint32_t input_rate_ms = 100 , double RayonRoues_i = RAYONROUES, double L1pL2_i = L1PL2) ;
        SpeedPIDController(uint32_t input_rate_ms = 100, double RayonRoues_i = RAYONROUES, double L1pL2_i = L1PL2);
        ~SpeedPIDController();
        void define_setpoint(double w_M1_FD, double w_M2_FG, double w_M3_BD, double w_M4_BG);
        bool update_controller();
        void stop_mot(){ 
            setpoint_speed-=setpoint_speed;
            motors->motors_stop();
        };
        robotSpeed getSpeedEncoder(){return speed_robot_frame_robot_encoder;};
        robotSpeed getSpeedGyro(){return speed_robot_frame_robot_gyro;};
        void readingsToRobotSpeedInItsFrameEnco(std::valarray<double> readings);
        void readingsToRobotSpeedInItsFrameGyro(std::valarray<double> readings,double wgyro);
};


