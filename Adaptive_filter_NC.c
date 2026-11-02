#include "L138_LCDK_aic3106_init.h"
#define beta 1E-13         //rate of convergence
#define N 30
float delay[N];
float w[N];

void main()
{
    int i,T;
    for (T = 0; T < 30; T++)
                {
                    w[T] = 0;                 //init buffer for weights
                    delay[T] = 0;             //init buffer for delay samples
                }


    L138_initialise_intr(FS_48000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);
    while(1);
}


interrupt void interrupt4(void)           //ISR
 {

  short i;
  //int32_t output;
  float yn=0, E=0, dplusn=0, desired=0, noise=0;

  desired = input_left_sample();
  noise = input_right_sample();
  dplusn = desired + noise;         //desired+noise
  delay[0] = noise;             //noise as input to adapt FIR

        for (i = 0; i < N; i++)          //to calculate out of adapt FIR
            yn += (w[i] * delay[i]);       //output of adaptive filter

  E = dplusn - yn;      //"error" signal=(d+n)-yn

        for (i = N-1; i >= 0; i--)       //to update weights and delays
        {
            w[i] = w[i] + beta*E*delay[i]; //update weights
            delay[i] = delay[i-1];       //update delay samples
        }



  //output=();//error signal as overall output

  output_sample((int16_t)E);
}
