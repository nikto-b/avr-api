# AVR-API [WIP]
Basic API library for Atmel AVR that can replace Arduino library
### Simple blink example:

```C++
gpio::setMode(&PORTB, PB7, gpio::OUTPUT);
while(1)
{
  gpio::setState(&PORTB, {PB7, gpio::State::TOGGLE});
  delay(100);
}
```

### Simple blink example for many pins:
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








