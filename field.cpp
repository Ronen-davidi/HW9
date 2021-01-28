
#include "field.h"
#include "ip.h"
#include "port.h"
#include <iostream>
#include <cstring>
#include <stddef.h>
#include <stdio.h>

// pattern - IP source IP - destination
Field::Field(String pattern, field_type type){
	this->pattern = pattern;
	this->type = type;
}


Field::Field(String pattern){
	this->pattern = pattern;
	this->type = GENERIC;
}

Field::~Field(){};

field_type Field::get_type() const{
	return this->type;
}



bool Field::match_value(String val)const{
	if(this->type == PORT){
		return ((Port*)this)->match_value(val);

	}
	if(this->type == IP){
		return ((Ip*)this)->match_value(val);

	}
	return false;
}



bool Field ::set_value(String val){
	if(this->type == PORT){
		return ((Port*)this)->set_value(val);
	}
	if(this->type == IP){
			return ((Ip*)this)->set_value(val);
		}
	return false;
}



bool Field::match(String packet){
	String* substr_packet;
	String* value_substr;
	size_t number_of_substr=0, number_of_value_subtr=0;
	const char *my_const = ",";
	const char *my_const2 = "=";
	bool corrector_not = false;


	packet.split(my_const, &substr_packet,&number_of_substr);

	if(number_of_substr == 0 ){
		delete[] substr_packet;
		return false;
	}


	for(unsigned int i = 0; i < number_of_substr ; i++){

		substr_packet[i].split(my_const2, &value_substr, &number_of_value_subtr);
		if(number_of_value_subtr == 0){
			continue;
		}
		if(number_of_value_subtr == 2){
			if((this->pattern).trim().equals(value_substr[0].trim())){
				corrector_not = (match_value(value_substr[1].trim()));
			}
		}

	}
	delete[] value_substr;
	delete[] substr_packet;

	return corrector_not;

}
