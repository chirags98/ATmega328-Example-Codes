
#ifndef ADC_H_
#define ADC_H_

void adc_pin_config (void);
unsigned int read_adc(void);
void adc_config(void);
unsigned int read_adc_channel(char);
unsigned int avg_read_adc_channel(char, char);

#endif /* ADC_H_ */