// L138_loopbuf_intr.c
//

#include "L138_LCDK_aic3106_init.h"
interrupt void interrupt4(void) // interrupt service routine
{
  int32_t sample_data;

  sample_data = input_sample();

  output_sample(sample_data);

  return;
}

int main(void)
{
  L138_initialise_intr(FS_48000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);
  while(1);
}
