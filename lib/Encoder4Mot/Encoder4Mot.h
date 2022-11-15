#pragma once
#include <SimpleFOC.h>
#include <vector>
#include <Reglages.h>
#include <iostream>
using namespace std;

typedef enum _motorPlacement
{
    FD,
    FG,
    BD,
    BG
}motorPlacement;

class Encoder4Mot
{
private:
    std::vector<float> speeds;
    std::vector<float> last_speeds;

public:
    Encoder4Mot();
    ~Encoder4Mot();
    const std::vector<float> & Encoder4MotUpdate();
    const std::vector<float> & GetSpeeds()const{ return speeds;};
    const std::vector<float> & GetLastSpeeds()const{ return last_speeds;};
    friend ostream& operator<<(ostream& os, const Encoder4Mot& enc);


};

