// CT: Voltage depends on current, burden resistor, and turns
#define CT_BURDEN_RESISTOR 22
#define CT_TURNS 1800
#define VOLTAGE 240

class EnergyMonitor
{
public:
  void setPin(unsigned int _inPinI);

  double calcIrms(unsigned int NUMBER_OF_SAMPLES);

  double Irms;

private:
  //Set current input pins
  int inPinI;

  int firstrun = 0;

  int lastSampleI, sampleI;

  double lastFilteredI, filteredI;

  double sqI, sumI;
};