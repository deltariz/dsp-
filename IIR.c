/*
 * IIR.c
 *
 *  Created on: 15-Nov-2022
 *      Author: sultan.m
 */

#include "L138_LCDK_aic3106_init.h"

const signed int h[] =
{
    //12730,-12730,12730,32767,-18324,21137 /*HP 2500 */
    // 312,312,312,32767,-27943,24367       /*LP 800 */
     //1455,1455,1455,32767,-23140,21735	/*LP 2500 */
     //9268,-9268,9268,32767,-7395,18367	/*HP 4000*/
	//7215,-7215,7215,32767,5039,6171,		/*HP 7000*/
			538,538,538,32767, -27621,24628   /*LPF-Chebyshev */
		   //28572,-28572,28572,32767,-28123,25276     /*HPF-Chebyshev */


};

interrupt void interrupt4(void)
{
	static signed int x[6] = { 0, 0, 0, 0, 0, 0 };  /* x(n), x(n-1), x(n-2). Must be static */
  	static signed int y[6] = { 0, 0, 0, 0, 0, 0 };  /* y(n), y(n-1), y(n-2). Must be static */
  	long temp=0;

  temp = input_right_sample(); // input from ADC; /* Copy input to temp */

  x[0] = (signed int) temp; /* Copy input to x[stages][0] */


  temp =  ( (long)h[0] * x[0]) ;   /* B0 * x(n)   */

     temp += ( (long)h[1] * x[1]);    /* B1/2 * x(n-1) */

     temp += ( (long)h[1] * x[1]);    /* B1/2 * x(n-1) */

     temp += ( (long)h[2] * x[2]);    /* B2 * x(n-2) */

     temp -= ( (long)h[4] * y[1]);    /* A1/2 * y(n-1) */

     temp -= ( (long)h[4] * y[1]);   /* A1/2 * y(n-1) */

     temp -= ( (long)h[5] * y[2]);   /* A2 * y(n-2) */

     /* Divide temp by coefficients[A0] */

     temp >>= 15;

    if ( temp > 32767 )
       {
         temp = 32767;
       }
     else if ( temp < -32767)
       {
         temp = -32767;
       }
 y[0] = (short int) ( temp );

     /* Shuffle values along one place for next time */

     y[2] = y[1];   /* y(n-2) = y(n-1) */
     y[1] = y[0];   /* y(n-1) = y(n)   */

     x[2] = x[1];   /* x(n-2) = x(n-1) */
     x[1] = x[0];   /* x(n-1) = x(n)   */

     /* temp is used as input next time through */
     output_right_sample((short)(temp));  // output to DAC
       return;

}

int main(void)
{

	L138_initialise_intr(FS_48000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);

  while(1);

}  // end of main()
