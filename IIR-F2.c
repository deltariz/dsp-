// L138_iirsostr_intr.c
//
// IIR filter implemented using second order sections
// floating point coefficients read from file
//

#include "L138_LCDK_aic3106_init.h"

#define NUM_SECTIONS 2

/*float b[NUM_SECTIONS][3] = {
{8.70333474E-01, -1.74066695E+00, 8.70333474E-01},
{8.83663494E-01, -8.83663494E-01, 0.00000000E+00} };

float a[NUM_SECTIONS][3] = {
{1.00000000E+00, -1.71049705E+00, 7.70836849E-01},
{1.00000000E+00, -7.67326988E-01, 0.00000000E+00} };//Butterworth-HPF-Fc=2Khz */

float b[NUM_SECTIONS][3] = {
{1.50849506E-02, 3.01699012E-02, 1.50849506E-02},
{1.16336506E-01, 1.16336506E-01, 0.00000000E+00} };

float a[NUM_SECTIONS][3] = {
{1.00000000E+00, -1.71049705E+00, 7.70836849E-01},
{1.00000000E+00, -7.67326988E-01, 0.00000000E+00} };  //Butterworth-LPF-Fc=2Khz */

/*float b[NUM_SECTIONS][3] = {
{3.54002555E-01, 0.00000000E+00, -3.54002555E-01},
{3.54002555E-01, 0.00000000E+00, -3.54002555E-01} };

float a[NUM_SECTIONS][3] = {
{1.00000000E+00, -1.51487827E+00, 6.78067401E-01},
{1.00000000E+00, -5.28847571E-01, 4.14769770E-01} };  //Butterworth-BPF-Fc=3Khz-10KHz */



float w[NUM_SECTIONS][2] = {0};



interrupt void interrupt4(void) // associated in intvecs.asm with INT4
{
  int section;   // index for section number
  float input;   // input to each section
  float yn, wn;   // intermediate and output values in each stage

  input = (float)input_left_sample();

  for (section=0 ; section< NUM_SECTIONS ; section++)
  {
    yn = b[section][0]*input + w[section][0];
    w[section][0] = b[section][1]*input + w[section][1] - a[section][1]*yn;
    w[section][1] = b[section][2]*input - a[section][2]*yn;
    input = yn;              // output of current section will be input to next */

  }

  output_left_sample((int16_t)(yn)); // before writing to codec

  return;
}
int main(void)
{

	L138_initialise_intr(FS_48000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);

  while(1);

}  // end of main()
