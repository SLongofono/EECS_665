/* @file n2d.cpp
 * @brief 	Given a specific input format representing a nondeterministic
 * 		finite state automata, converts it to a deterministic finite
 * 		automata and prints the result.
 *
 * @author 	Stephen Longofono
 * @created	September 2017
 * @notes	This program is ill-equipped to handle malformed input.
 * 		The exact input must be of the following form:
 *
 *		Initial State: {1}
 *		Final States: {11}
 *		Total States: 11
 *		State	a	b	E
 *		1	{}	{}	{2,5}
 *		2	{3}	{}	{}
 *		3	{}	{4}	{}
 *		4	{}	{}	{8}
 *		5	{}	{6}	{}
 *		6	{7}	{}	{}
 *		7	{}	{}	{8}
 *		8	{}	{}	{9,11}
 *		9	{10}	{}	{}
 *		10	{}	{}	{9,11}
 *		11	{}	{}	{}
 *
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include "State.h"
#include <cassert>
#include <stdexcept>

// Credit to Adam Pierce, string tokenizer for C++ without resorting to Boost
// Modified to handle tabs, commas, and spaces alike
// Retrieved from https://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
// Sept. 29, 2017
std::vector<std::string> split_str(const char *str)
{
    std::vector<std::string> result;

    do
    {
        const char *begin = str;

        while(*str != ' ' && *str != '\t' && *str)
            str++;

        result.push_back(std::string(begin, str));
    } while (0 != *str++);

    return result;
}

std::vector<int> split_int(const char *str)
{
    std::vector<int> result;

    do
    {
        const char *begin = str;

        while(*str != ' ' && *str != '\t' && *str != ',' && *str)
            str++;

        result.push_back(std::stoi(std::string(begin, str)));
    } while (0 != *str++);

    return result;
}



int main(int argc, char** argv){


	State testState(99);
	testState.print_moves();
	testState.add_move('a', 100);
	testState.print_moves();

	int numStates;				// How many total states
	int initialState;			// Where to begin
	std::vector<std::string> finalStates;	// Any of these states is accepted
	std::vector<std::string> sigma;		// Input alphabet

	std::string buff;

	// Fetch initial state
	std::getline(std::cin, buff);
	buff.pop_back();
	initialState = std::stoi(buff.substr(16));
	std::cout << "Initial state: " << initialState << std::endl;
	

	// Fetch final states as a vector
	std::getline(std::cin, buff);
	buff.pop_back();
	finalStates = split_str(buff.substr(15).data());
	int len = finalStates.size();
	std::cout << "Final states (" << len << "): ";
	for(int i = 0; i<len; ++i){
		std::cout << finalStates.at(i) << " ";
	}
	std::cout << std::endl;
	

	// Fetch total number of states
	std::getline(std::cin, buff);
	numStates = std::stoi(buff.substr(14));
	std::cout << "Number of states: " << numStates << std::endl;
	

	// Fetch input alphabet
	std::getline(std::cin, buff);
	sigma = split_str(buff.substr(6).data());
	len = sigma.size();
	std::cout << "Sigma:  { ";
	for(int i = 0; i< len; ++i){
		std::cout << sigma.at(i) << " ";	
	}
	std::cout << "}" << std::endl;
	

	// Assemble state structs

	// Input states vector
	std::vector<State *> *states = new std::vector<State *>;
	
	try{
		std::cout << "Looking for more input..." << std::endl;
		std::getline(std::cin, buff);
		while(buff.size() > 1){
			std::cout << "Read in state: " << buff << std::endl;

			// Tokenize
			std::vector<std::string> pieces= split_str(buff.data());
		
			len = pieces.size();
			for(int i = 0; i<len; ++i){
				std::cout << pieces.at(i) << " ";	
			}
		
			// First element is this state's name
			State *newState = new State(std::stol(pieces.at(0)));

			std::cout << std::endl << "Creating state " << newState->get_name() <<std::endl;

			assert(sigma.size() == pieces.size() - 1);

			// For each set
			for(int i = 1; i<len; ++i){
				
				// Skip empty sets
				if(2 < pieces.at(i).size()){
						
					// Strip braces from ends
					std::string temp = pieces.at(i).substr(1, pieces.at(i).size()-2);

					std::cout << "Read set: " << temp << std::endl;
					std::vector<int> transitions = split_int(temp.data());
					int length = transitions.size();
	
					for(int j = 0; j<length; ++j){
						std::cout << transitions.at(j) << std::endl;
					
						char c[2];
						int temp = sigma.at(i-1).copy(c, 1);
						c[temp] = '\0';
						newState->add_move(c[0], transitions.at(j));
					}
				}
				else{
					std::cout << "Empty set, moving on..." << std::endl;	
				}
			}
		
			std::cout << "Completed a state.  Details: " << std::endl;
			newState->print_moves();
			std::cout << buff << std::endl;	
			std::getline(std::cin, buff);
			states->push_back(newState);
		}
	}
	catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}

	int temp = states->size();
	State* s;
	for(int i = 0; i<temp; ++i){
		s = states->at(i);
		delete s;
	}

	delete states;

	return 0;

}
