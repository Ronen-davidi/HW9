#include "field.h"
#include "ip.h"
#include "port.h"
#include <iostream>
#include <cstring>
#include <stddef.h>
#include <stdio.h>
#include "input.h"


extern int check_args(int arg, char** argv );
extern void parse_input(Field&);



int main(int argc, char** argv){

	if(check_args(argc, argv) != 0){
			return 1;
		}


	String* substring;
	String new_filter(argv[1]);
	size_t size = 0;



	new_filter.split("=", &substring, &size); //passing refernce


	if((substring[0]).trim().equals(String("dst-ip")) || (substring[0]).trim().equals(String("src-ip"))){

		Ip filter_ip(substring[0].trim());
		filter_ip.set_value(substring[1].trim());

		parse_input(filter_ip);
	}



	if((substring[0]).trim().equals(String("src-port")) || (substring[0]).trim().equals(String("dst-port"))){

			Port filter_port(substring[0].trim());
			filter_port.set_value(substring[1].trim());

			parse_input(filter_port);
		}

	delete[] substring;
}



