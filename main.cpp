#include "base.h"
#include "api.h"

int main()
{
	ADCInit();
	WDSetMode(0);
	digitalWrite(0, 1);
	return 0;
}