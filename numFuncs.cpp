#include "numFuncs.h"

/*
 *  Function:constrain
 *  Desc:   check if the val is on the range of valid values
 *  Input:  _VAR_TYPE_ x: val
            _VAR_TYPE_ a: start val of range
            _VAR_TYPE_ b: end val of range
 *  Output: _VAR_TYPE_
 */
 #define FUNC(_VAR_TYPE_)                                         \
_VAR_TYPE_ constrain( _VAR_TYPE_ x, _VAR_TYPE_ a, _VAR_TYPE_ b)   \
{                                                                 \
  if(x < a)                                                       \
    return a;                                                     \
  else if(x > b)                                                  \
    return b;                                                     \
  else                                                            \
    return x;                                                     \
}

FUNC(uint64_t)
FUNC(int64_t)
FUNC(uint32_t)
FUNC(int32_t)
FUNC(uint16_t)
FUNC(int16_t)
FUNC(uint8_t)
FUNC(int8_t)
FUNC(double)
FUNC(float)

#undef FUNC
