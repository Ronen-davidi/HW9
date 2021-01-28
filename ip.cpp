#include "field.h"
#include "ip.h"
#include "string.h"
#include <iostream>
#include <cstring>
#include <stddef.h>
#include <stdio.h>



Ip::Ip(String pattern):Field(pattern,IP){};

bool Ip::set_value(String val)
{
	String* substring;
	size_t size = 0;


	val.split("/", &substring, &size);

	if (2 != size )
	{
		if (size != 0)
		{
			delete[] substring;
		}
		return false;
	}

	int ip = substring[0].trim().to_integer();
	int n = 32 - substring[1].trim().to_integer(); // 32 - val = nubmer of lower bits to ignore
	delete[] substring;

	if((n < 0) || (n > 32)) {
		return false;
	}



	unsigned int bitmask = (n == 32) ? 0xFFFFFFFF : ((unsigned int)1 << n) - 1;

	low = ip & (~bitmask); //zero the lower bits    192.0.0.0.
	high = ip | bitmask; //set lower bits to 1		192.255.255.255


	return true;
}



bool Ip::match_value(String val) const
{
	unsigned int intVal = (unsigned int)val.trim().to_integer();

	return ((low <= intVal) && (intVal <= high));
}






