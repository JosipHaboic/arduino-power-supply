volatile uint8_t duty_cycle = 0;
// duty cycle clamps
const uint8_t DUTY_CYCLE_MIN = 0;
const uint8_t DUTY_CYCLE_MAX = 255;

void pwm_setup(void);
void pwm_set_duty_cycle(uint8_t pin, uint8_t duty_cycle);
void pwm_start(void);
void increase_pwm(uint8_t pin);
void decrease_pwm(uint8_t pin);