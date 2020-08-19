#include "pwm.h"

/// GPO
nBlock_PWM::nBlock_PWM(PinName pinPwm, uint32_t Frequency): _pwm(pinPwm) {
	duty_float = 0.0;
	is_updated = 0;
    _pwm.period(1.0/((float)Frequency));
    _pwm.write(0);
    return;
}
void nBlock_PWM::triggerInput(nBlocks_Message message) {
    // Stores the duty cycle we would like to use
    // when updating in the end of this frame
	if (message.dataType == OUTPUT_TYPE_FLOAT) {
		// If received a float, assign directly
		duty_float = message.floatValue;
		// flag as updated
		is_updated = 1;
	}
	else if (message.dataType == OUTPUT_TYPE_INT) {
		// If received an integer, normalize it
		float tmp;
		tmp = (message.intValue & 0x0000FFFF);
		tmp = tmp / 0x0000FFFF;
		duty_float = tmp;
		// flag as updated
		is_updated = 1;
	}
	// Other types are ignored
}
void nBlock_PWM::step(void) {
	if (is_updated) {
		// de-flag updated
		is_updated = 0;
		// Apply the value
		_pwm.write(duty_float);
	}
    return;
}
