uint8_t duty_cycle_to_percent(uint8_t duty_cylce);
float adc_to_float(uint16_t value);
float voltage_divider(int r1, int r2);


uint8_t duty_cycle_to_percent(uint8_t duty_cycle)
{
  if (duty_cycle == 0)
  {
    return 0;
  }
  else if (duty_cycle == 255)
  {
    return 100;
  }
  else
  {
    return (uint8_t)(((float)duty_cycle / 255) * 100);
  }
}

float adc_to_float(uint16_t value)
{
  return (float)(((float)value / 1024.00) * 5.00);
}

float voltage_divider(int r1, int r2)
{
  return r1 / (r1 + r2);
}
