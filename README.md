# AVR-API [WIP]
Basic API library for Atmel AVR that can replace Arduino library
## GPIO module
### Example of single pin blink

```C++
gpio::setMode(&PORTB, PB7, gpio::OUTPUT);
while(1)
{
  gpio::setState(&PORTB, {PB7, gpio::State::TOGGLE});
  delay(100);
}
```

### Example of many pins blinking
```C++
gpio::setMode(&PORTB, PB7, gpio::OUTPUT);
gpio::setMode(&PORTB, PB5, gpio::OUTPUT);
gpio::setMode(&PORTB, PB3, gpio::OUTPUT);
gpio::setMode(&PORTB, PB1, gpio::OUTPUT);
while(1)
{
  gpio::setStates(&PORTB, {{PB1, gpio::State::TOGGLE},
                           {PB3, gpio::State::TOGGLE},
                           {PB5, gpio::State::TOGGLE},
                           {PB7, gpio::State::TOGGLE}});
  delay(100);
}
```
## USART module
### Example using USART0 on 115200 baud
```C++
usart::begin<0>(115200);
sei();
usart::println<0>();
long i = 0;
while(1)
{
    usart::print<0>("NICE");    
    usart::println<0>(i);
    i++;
    delay(200);
}
```
## Timers and interrupts module
Warning: timers module is under refactor now, methods Will be changed
```C++
void schedule(void)
{
  //foo
}

int main() 
{
  interrupt::set(interrupt::TC0_COMPA, schedule);
  TIMER0Init(TIMER0_COMA_NPWM_NORMAL, TIMER0_WF_CTC, TIMER0_CLK_SRC_1024);
  TIMER0EnableCOMPAInterrupt();
  TIMER0SetA(255);
  while(1) asm("NOP");
}
```
## ADC module
```C++
adc::init();
adc::setRef(adc::ref::AREF);
sei();
adc::analogRead(0);
```



