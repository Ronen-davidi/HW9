#include "string.h"
#include "ip.h"
#include <iostream>
#include <cstring>
#include <stddef.h>
#include <stdio.h>
#define NUMBERSUBSTRING 4
using namespace std;



//static int mekrekatez (const char *delimiters, char *copy_string, int size);
//my constructors

/**
     * @brief Initiates an empty string
     */

String::String(){
	this->length = 0;
	this->data = NULL;
}

/**
     * @brief Initiates string from other string
     */
String::String(const char *str){

	if(str == NULL){
		this->data = NULL;
		this->length = 0;
		return;
	}

	length = strlen(str);
	data = new char[length+1]; // +1 for \n

	if(this->data != NULL){
		strcpy(this->data,str);
	}
	else{
		this->length = 0;
		this->data = NULL;

	}
}

// my de-structors

String::~String(){

	delete[] (this->data);
}

String::String(const String &str){
	this->length = str.length;
	if(this->length == 0){
		this->data = NULL;
	}
	else{
		this->data = new char[this->length +1];
		strcpy(this->data, str.data);
	}
}

/**
    * @brief Changes this from String
    */
String& String::operator=(const String &rhs){
	if(this->data != NULL){
		delete[] this->data;
	}

	this->length = rhs.length;

	if(this->length == 0){
		this->data = NULL;
	}
	else {
		this->data = new char[(this->length) +1];
		strcpy(this->data, rhs.data);
	}

	return *this;

   }



/**
     * @brief Changes this from char array
     */
String& String::operator=(const char *str){
	if(str == NULL){
		this->length = 0;
		this->data = NULL;
		return *this;
	}

		delete[] this->data;

	this->length = strlen(str);
	this->data = new char[(this->length) + 1];
	if(this->data != NULL){
		strcpy(this->data,str);
	}
	else{
		this->data = NULL;
		this->length = 0;
	}

	return *this;
}




/**
     * @brief Returns true iff the contents of this equals to the
     * contents of rhs
     */
bool String::equals(const String &rhs) const{
	if(rhs.length != (this->length)){
		return false;
	}
	if(strcmp(this->data,rhs.data) != 0){
		return false;
	}
	return true;
}



bool String::equals(const char *rhs)const{
	if(rhs == NULL){
		return false;
	}
	if(this->length != strlen(rhs)){
		return false;
	}

	if(strcmp(this->data,rhs) != 0){
		return 0 ;
	}
	return true;
}


/**
     * @brief Splits this to several sub-strings according to delimiters.
     * Allocates memory for output that the user must delete (using delete[]).
     * @note Does not affect this.
     * @note If "output" is set to NULL, do not allocated memory, only
     * compute "size".
     */
void String::split(const char *delimiters, String **output, size_t *size) const{



	if(delimiters == NULL || output == NULL || size == NULL){
	//		if(size == NULL){
	//			*size=0;
	//		}
			*size = 2;
			return;
		}
	*size=0;
	char copy_string[(this->length) + 1];
	char helper_string[(this->length) + 1];
	strcpy(helper_string,this->data);
	strcpy(copy_string,this->data);
	copy_string[(this->length)] = '\0';
	int sub = 0;





	char *splitpointers = strtok(helper_string, delimiters);
	while(splitpointers){
		splitpointers = strtok(NULL, delimiters);
		(*size)++;
	}

	*(output) = new String[*size];

	splitpointers = strtok(copy_string, delimiters);
	while (splitpointers){
		(*output)[sub] = String(splitpointers);
		splitpointers = strtok(NULL, delimiters);
		sub++;
	}

	//*output = new String[numbers_of_substring];

	/*
	while(tokens[k]){
		strcpy(*(output)[sub], *(tokens[k]));

	}
	*/
	/*
	for (unsigned int i = 0; i < this->length; i ++){
		for (int j = 0; j < numbers_of_substring; j ++){
			if(copy_string[i] == delimiters[j]){
				copy_string[i] = '\0';
				(*output)[sub] = String(&copy_string[begin]);
				begin = i+1;
				sub++;
			}

		}
	}

	(*output)[sub] = String(&copy_string[begin]);
	*/
}
	//start copy substrings





/**
     * @brief Try to convert this to an integer. Returns 0 on error.
     */
int String::to_integer() const
{

	int ret = 0;
	String* substrs = NULL;
	size_t size = 0;
	unsigned int i = 0;


	split(".", &substrs, &size);


	if(size == SEGMENTS)
	{

		for(i = 0; i < size; i++){
			int byte = substrs[i].trim().to_integer();

			if ( (byte > 255) || (byte<0) )
			{
				delete[] substrs;
				return 0;  // return 0 or -1?
			}

			ret |= byte << (24 - (8 * i));
		}

		delete[] substrs;
		return ret;
	}
	else
	{
		ret = atoi(data);
		if(0 != ret)
		{
			delete[] substrs;
			return ret;
		}
	}

	delete[] substrs;

	return 0;
}



String String::trim() const
{
	string temp = this->data;
    size_t first = temp.find_first_not_of(' ');
    size_t last = temp.find_last_not_of(' ');
    temp = temp.substr(first, (last - first + 1));
    char trimmed_data[last-first+1];

    strcpy(trimmed_data,temp.c_str());

    return String(trimmed_data);
}


















