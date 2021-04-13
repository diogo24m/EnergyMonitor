// CT: Voltage depends on current, burden resistor, and turns
#define CT_BURDEN_RESISTOR    22
#define CT_TURNS              1800//2000
#define VOLTAGE               240

class EnergyMonitor
{
  public:
    void setPin(unsigned int _inPinI);

    double calcIrms(unsigned int NUMBER_OF_SAMPLES);
    //Useful value variables
    double Irms;

  private:

    //Set current input pins
    int inPinI;

    int firstrun = 0;

    //--------------------------------------------------------------------------------------
    // Variable declaration for emon_calc procedure
    //--------------------------------------------------------------------------------------
    int lastSampleI, sampleI;

    double lastFilteredI, filteredI;
    double offsetI;                          //Low-pass filter output

    double sqI, sumI;             //sq = squared, sum = Sum
};
