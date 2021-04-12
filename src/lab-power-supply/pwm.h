volatile uint8_t voltage_duty_cycle = 0;
volatile uint8_t current_duty_cycle = 0;
// duty cycle clamps

void pwm_setup(void);
void pwm_set_duty_cycle(uint8_t pin, uint8_t duty_cycle);
void pwm_start(void);
void increase_pwm(uint8_t pin);
void decrease_pwm(uint8_t pin);