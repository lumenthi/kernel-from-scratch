#

#include "kernlib.h"

void poweroff(void)
{
	outw(0x604, 0x2000);
}
