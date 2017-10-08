#ifndef HELP_H
#define HELP_H

#include <stdio.h>
#include <iostream>
#include <cassert>
#include <vector>

// Map lowercase letters to [0, 25] and 'E' to 26
int c_map(char c){
	int num = c;
	std::cout << "Mapping " << num << std::endl;
	assert( ( c < 123 && c > 96 ) || (c == 'E') );
	if('E' == c){
		return 26;
	}
	return (c-97);
}

// Undo map for printing
char c_unmap(int i){
	if(26 == i){
		return 'E';	
	}
	return (i+97);
}


// Prints an int vector on a single line, no return
void print_int_vec(std::vector<int> *v){
	std::cout << "{ ";
	for(std::vector<int>::iterator i = v->begin(); i != v->end(); ++i){
		std::cout << *(i) << " ";
	}
	std::cout << "} " << std::endl;
}


// Credit to Adam Pierce, string tokenizer for C++ without resorting to Boost
// Modified to handle tabs and spaces alike
// Retrieved from https://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
// Sept. 29, 2017
std::vector<std::string> *split_str(const char *str)
{
    std::vector<std::string> *result = new std::vector<std::string>;

    do
    {
        const char *begin = str;

        while(*str != ' ' && *str != '\t' && *str)
            str++;

        result->push_back(std::string(begin, str));
    } while (0 != *str++);

    return result;
}


std::vector<int> *split_int(const char *str)
{
    std::vector<int> *result = new std::vector<int>;

    do
    {
        const char *begin = str;

        while(*str != ' ' && *str != '\t' && *str != ',' && *str)
            str++;

        result->push_back(std::stoi(std::string(begin, str)));
    } while (0 != *str++);

    return result;
}


#endif
