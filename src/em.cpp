#include "em.h"
#include "Arduino.h"

void EnergyMonitor::setPin(unsigned int _inPinI)
{
  inPinI = _inPinI;
  pinMode(inPinI, INPUT);
  adcAttachPin(inPinI);
}

double EnergyMonitor::calcIrms(unsigned int Number_of_Samples)
{
  for (int n = 0; n < Number_of_Samples; n++)
  {
    //Used for offset removal
    lastSampleI = sampleI;

    //Read in voltage and current samples.
    sampleI = analogRead(inPinI);

    //Used for offset removal
    lastFilteredI = filteredI;

    //Digital high pass filters to remove 1.6V DC offset.
    filteredI = 0.9989 * (lastFilteredI + sampleI - lastSampleI);

    //Root-mean-square method current
    //1) square current values
    sqI = filteredI * filteredI;
    //2) sum
    sumI += sqI;
    delay(0.00002);
  }

  double ICAL = 1.08;
  // Initial gueses for ratios, modified by VCAL/ICAL tweaks
  double I_RATIO = (long double)CT_TURNS / CT_BURDEN_RESISTOR * 3.3 / 4096 * ICAL;
  //Calibration coeficients applied.
  Irms = (I_RATIO * sqrt(sumI / Number_of_Samples)) - 0.16;
  if ((Irms < 0) || (firstrun < 2))
    Irms = 0; //Set negative Current to zero and ignore the first 2 calculations

  sumI = 0;

  if (firstrun <= 2)
    firstrun++; //Counter for Trash Data

  return Irms;
}
