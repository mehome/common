#include "loger.h"
#include <iostream>

int main(void)
{
	Loger loger;

	for(int i = 0; i < (1<<30); i++)
	{
		loger << "just move to the limit";
	}

	return 0;
}
