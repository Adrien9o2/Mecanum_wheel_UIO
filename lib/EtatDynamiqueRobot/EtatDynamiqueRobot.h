#ifndef ETATDYNAMIQUEROBOT
#define ETATDYNAMIQUEROBOT

/**
 * Version récupérée sur le code des robots de la coupe 2021 (kraken et levi)
 * Modifiée pour les roues mecanum (4 roues plutot que 2 originalement)
 **/

#include <Arduino.h>

#define MEAN_SAMPLES 35

class EtatDynamiqueRobot
{
    public:
        EtatDynamiqueRobot(double x, double y, double theta_i);

        // Pour passer vers un nouvel etat
        // Effectue le calcul des nouvelles vitesses
        void versPosition(double n_x, double n_y, double n_theta, uint32_t dt);
        void setPosition(double n_x, double n_y, double n_theta);
        void translatePosition(double n_x, double n_y, double n_theta);

        double getThetaRadian() const;
        double getX() const;
        double getY() const;
        double getV() const;
        double getVTheta() const;
        double getVX() const;
        double getVY() const;

        double deltaAngleTo(double initial, double target) ;

        void containTheta(double & theta_i){
            if(theta_i > PI || theta_i < -PI )
            {
                int k = theta_i/(2.0*PI);
                theta_i = theta_i - k*2.0*PI;
            }
        };

    private:
        double x;
        double y;
        double theta;
        
        double v_xy;
        double v_theta;

        double v_x;
        double v_y;

        uint32_t last_dt;
};

#endif