#ifndef HELP_H
#define HELP_H

#include <stdio.h>
#include <iostream>
#include <cassert>
#include <vector>
#include <set>

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


// Traverse the DFA marked mapping and find the first unmarked set.  Returns
// nullptr if no such set exists.
std::set<int>* find_unmarked(std::map< std::set<int>*, int > DFA_marked){
	std::map<std::set<int>*, int>::iterator i;
	for(i = DFA_marked.begin(); i != DFA_marked.end(); ++i){
		if(0 == i->second){
			return i->first;
		}	
	}
	return nullptr;
}

// Prints an int set on a single line, no return
void print_int_set(std::set<int> *s){
	std::set<int>::iterator i;
	std::cout << "{ ";
	for(i = s->begin(); i != s->end(); i++){
		std::cout << *(i) << " ";	
	}
	std::cout << "}";
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


/*
 * @brief	Converts a vector into a set
 * @param v	A pointer to a std::vector<int> to be converted
 * @return	A pointer to a std::set<int> composed of all unique elements
 * 		in input std::vector<int> v
 * @notes	I am amazed that this even works, given how clunky C++ is.
 * 		Kudos to the developers that decided the stardard types should
 * 		work so well together.
 */
std::set<int>* vec_to_set(std::vector<int>* v){
	std::set<int>* ret = new std::set<int>;
	ret->insert(v->begin(), v->end());
	return ret;
}

#endif
