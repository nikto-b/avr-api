#include "base.hpp"
#include "digitalRegisters.hpp"


namespace gpio
{

	PinState::PinState(const uint8_t _pin, const State _state) : pin(_pin), state(_state) {}
    
} // namespace gpio
