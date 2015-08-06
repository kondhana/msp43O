#include "driverlib.h"

#define PORT6 GPIO_PORT_P6
#define INPUT_PIN GPIO_PIN1

void port1_isr(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    if (status & GPIO_PIN1)
    {
        printf("Sending high on Port 3 pin 2");
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);

    }
}


void port4_isr(void){
	 printf("Sending high on Port 3 pin 2");
	uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P6);
	MAP_GPIO_clearInterruptFlag(GPIO_PORT_P6, status);

	if (status & GPIO_PIN1)
	{
		uint32_t value=MAP_GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN1);
		 MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2,GPIO_PIN5);
	}
}

void startTimerA(){
	uint8_t pinvalue=GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN1);
	printf("Starting timer now");
	printf("String pin value=%d",pinvalue);

	GPIO_clearInterruptFlag(GPIO_PORT_P6,GPIO_PIN1);
}

int main(void) 
{
    WDT_A_holdTimer();

    MAP_GPIO_setAsInputPin(PORT6,INPUT_PIN);

    GPIO_clearInterruptFlag(PORT6,INPUT_PIN);

    void (* startimerisr)(void) =&startTimerA;

    GPIO_registerInterrupt(PORT6,startimerisr);

    //GPIO_interruptEdgeSelect(PORT6,INPUT_PIN,GPIO_LOW_TO_HIGH_TRANSITION);

    GPIO_enableInterrupt(PORT6,INPUT_PIN);



    while(1){
        MAP_PCM_gotoLPM0();
    }
}



