#pragma once


#include <vector>
#include <iostream>
using namespace std;
#include <Arduino.h>

#define MAX_ISR 4


typedef enum _motorPlacement
{
    FD,
    FG,
    BD,
    BG
}motorPlacement;

class Encoder
{
    private:

        uint8_t myISRIdA;
        uint8_t myISRIdB;

        uint32_t pinIntA;
        uint32_t pinIntB;            // The interrupt pin used
        uint8_t myISRId;           // This is my instance ISR Id for myInstance[x] and encoderISRx
        volatile uint32_t count; // Encoder interrupt counter
        
        static uint8_t ISRUsedA;        // Keep track of which ISRs are used (global bit field)
        static uint8_t ISRUsedB;
        static Encoder* myInstanceA[]; // Callback instance for the ISR to reach instanceISR()
        static Encoder* myInstanceB[];

        void instanceISRA(void);    // Instance ISR handler called from static ISR globalISRx
        void instanceISRB(void); 
        bool stateA;
        bool stateB;
        bool _inversePolarity;
        uint32_t timer;
        uint32_t lastCount;
        double lastSpeed;
        double speed;


        // declare all the [MAX_ISR] encoder ISRs
        static void globalISR0_A(void);
        static void globalISR1_A(void);
        static void globalISR2_A(void);
        static void globalISR3_A(void);
        static void globalISR0_B(void);
        static void globalISR1_B(void);
        static void globalISR2_B(void);
        static void globalISR3_B(void);

        motorPlacement placementEncoder;

    public:
        Encoder(PinName pin_Name_CH_A, PinName pin_Name_CH_B, motorPlacement placement, bool inversePolarity );
        ~Encoder();
        uint32_t getCount() {return count;};
        uint32_t getLastCount() {return lastCount;};
        uint32_t getEllapsedTick() { return count - lastCount;};
        uint32_t getEllapsedTime() {return micros() - timer;};
        double getSpeed() { return speed;};
        double getLastSpeed() { return lastSpeed;};
        double update();


};


class Encoder4Mot
{
private:
    std::vector<double> speeds;
    std::vector<double> last_speeds;
    std::vector<Encoder*> encoders;

public:
    Encoder4Mot();
    ~Encoder4Mot();
    const std::vector<double> & Encoder4MotUpdate();
    const std::vector<double> & GetSpeeds()const{ return speeds;};
    const std::vector<double> & GetLastSpeeds()const{ return last_speeds;};
    friend ostream& operator<<(ostream& os, const Encoder4Mot& enc);


};

