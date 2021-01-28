#include "field.h"
#include "ip.h"
#include "port.h"
#include <iostream>
#include <cstring>
#include <stddef.h>
#include <stdio.h>
#include<cstdlib>




Port::Port(String pattern):Field (pattern, PORT){
}

bool Port::set_value(String val){

	String* substring;
	size_t size = 0;

	val.split("-", &substring, &size); //sending reference

	if(size != 2 ){
		if(size != 0){
			delete[] substring;
		}
		return false;
	}

	this->range[0] = substring[0].trim().to_integer();
	this->range[1] = substring[1].trim().to_integer();

	delete[] substring;

	if((this->range[0]) > (this->range[1])){
		return false;
	}
	else {
		return true;
	}
}


bool Port::match_value(String val) const{

	unsigned int value = val.trim().to_integer();
	if( ((unsigned int)(this->range[0]) <= value) && (unsigned int)(this->range[1]) >=value ){
		return true;
	}
	else{
		return false;
	}
}


