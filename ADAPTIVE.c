/*
 * Adaptive FIR filter for noise cancellation
 *
 *  Created on: 13-Aug-2023
 *      Author: sultan.m
 */


#include "L138_LCDK_aic3106_init.h"
#include<math.h>

#define beta 1E-15       		//rate of convergence
#define N 30                  	//# of weights (coefficients)
#define REF_NOISE_FREQ 2500		// Reference Noise sin(2500)
float w[N];                  	      //buffer weights of adapt filter
float delay[N];              	      //input buffer to adapt filter
short output;		            //overall output



void main()
{
    int j,T;
    for (T = 0; T < 30; T++)
                {
                    w[T] = 0;                 //init buffer for weights
                    delay[T] = 0;             //init buffer for delay samples
                }

    L138_initialise_intr(FS_8000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_MIC_INPUT);
    while(1);
}


interrupt void interrupt4(void)           //ISR
{
 short i,j;
 static short buffercount=0;		//init count of # out samples
 float dplusn[128]=0, desired=0, yn, E=0;               		//output filter/"error" signal
 float refnoise[128];               // stores noise samples

 for(buffercount=0;buffercount<128;buffercount++)
                {
                refnoise[buffercount]=30000*sin(2*3.14*REF_NOISE_FREQ*buffercount/8000);

 desired = (float)input_right_sample();		// desired Signal sin(500)
 dplusn[buffercount] =  desired+refnoise[buffercount]; //desired+noise
 delay[0] = refnoise[buffercount];  //sin(500Hz) input to adapt FIR

 yn = 0;                            //init output of adapt filter
 for (i = 0; i < N; i++)            //to calculate out of adapt FIR
     yn += (w[i] * delay[i]);       //output of adaptive filter

 E = dplusn[buffercount] - yn;      //"error" signal=(d+n)-yn

 for (i = N-1; i >= 0; i--)         //to update weights and delays
   {
     w[i] = w[i] + beta*E*delay[i]; //update weights
     delay[i] = delay[i-1];         //update delay samples
   }

      output = ((short)E);        //"error" signal overall output

      output_right_sample(output);	            //overall output result
  }
 return;					//return from ISR
}


