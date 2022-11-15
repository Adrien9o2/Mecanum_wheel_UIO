#pragma once
#include "BlocMoteurs.h"
#include "Encoder4Mot.h"
#include <algorithm>
#include <vector>
#include <valarray>


class SpeedPIDController
{
private:
    std::valarray<float> Kp;
    std::valarray<float> Ki;
    std::valarray<float> Kd;
    std::valarray<float> e;
    std::valarray<float> ei;
    std::valarray<float> ed;
    std::valarray<float> T;
    std::valarray<float> tau;
    uint32_t rate_ms;
    float delta;
    uint32_t lastCall_date_ms;
public:
    SpeedPIDController(/* args */);
    ~SpeedPIDController();
};


