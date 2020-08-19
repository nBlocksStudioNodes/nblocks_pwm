#ifndef __NB_PWM
#define __NB_PWM

#include "mbed.h"
#include "nworkbench.h"

class nBlock_PWM: public nBlockNode {
public:
    nBlock_PWM(PinName pinPwm, uint32_t Frequency);
    void triggerInput(nBlocks_Message message);
    void step(void);
private:
    PwmOut _pwm;
	float duty_float;
	uint32_t is_updated;
};



#endif
