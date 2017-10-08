/*
 * @file 	n2d.cpp
 * @author 	Stephen Lonogofono
 * @created 	October 2017
 * @brief	Given an input file representing a non-deterministic
 * 		finite-state automata, converts it to an equivalent
 * 		deterministic FSA.
 *
 * @notes	This is my first foray into c++ with standard data types.
 * 		So far, all our programming classes have forced us to roll
 * 		our own data structures. We wrote everything from scratch.
 * 		Why should you care?  It's likely that I've used a few types
 * 		in strange ways, perhaps in ways that were not intended by the
 * 		c++ folks.  This is my advance warning/apology for that.
 *
 */
#include <iterator>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include "helpers.h"


/*
 * @brief 		Given the input  state, assembles and returns a set
 * 			containing the states reachable on epsilon input
 * @param s		An integer representing the state
 * @param sigmaSize	The length of the alphabet
 * @param NFA		A 2D array of std::set<int> representing the NFA table
 * @return		A pointer to a std::set<int> containing all the states
 * 			reachable from the input state on epsilon input
 * @notes		Will always be non-empty, since every state's epsilon-
 * 			closure includes itself.
 */
std::set<int>* epsilon_closure(int s, int sigmaSize, std::set<int> ***NFA){
	std::set<int> *ret = new std::set<int>;
	
	ret->insert(s);

	// if there are states to be found
	if(NFA[s][sigmaSize-1] != nullptr){
		ret->insert( NFA[s][sigmaSize-1]->begin(), NFA[s][sigmaSize-1]->end() );
	}	
		
	return ret;
}


/*
 * @brief		Given the input state and a symbol, returns a set
 * 			containing all the states reachable on the symbol input
 * @param s		An integer representing the state
 * @param c		An integer representing the input symbol
 * @param numStates	The number of states in the NFA table
 * @param sigmaSize	The length of the alphabet
 * @param NFA		A 2D array of std::set<int> representing the NFA table
 * @return		A pointer to a std::set<int> representing all the states
 *  			reachable from the input state on the input symbol.
 */
std::set<int>* moves(int s, int c, int numStates, int sigmaSize, std::set<int> ***NFA){
	
	std::set<int> *ret = nullptr;
	
	// if there are states to be found
	if(NFA[s][c] != nullptr){
		ret = new std::set<int>;
		ret->insert( NFA[s][c]->begin(), NFA[s][c]->end() );
	}
	return ret;
}


int main(int argc, char **argv){
	
	/**********************************************************************
	 * Parsing Metadata
	 *********************************************************************/
	std::vector<std::string> *finalStates;	// Any of these states is accepted
	int numStates;				// How many total states
	int initialState;			// Where to begin
	int sigmaSize = 27;	 		// To make things simple,
						// assume lower case alphabet
						// plus E
	std::string buff;

	// Fetch initial state
	// Handle input "Initial State: {#}"
	std::getline(std::cin, buff);
	buff.pop_back();
	initialState = std::stoi(buff.substr(16));
	std::cout << "Initial state: " << initialState << std::endl;
	

	// Fetch final states as a vector
	// Handle input "Final States: {#,#,#,#...}"
	std::getline(std::cin, buff);
	buff.pop_back();
	finalStates = split_str(buff.substr(15).data());
	int len = finalStates->size();
	std::cout << "Final states (" << len << "): ";
	for(int i = 0; i<len; ++i){
		std::cout << finalStates->at(i) << " ";
	}
	std::cout << std::endl;
	

	// Fetch total number of states
	// Handle input "Total States: #"
	std::getline(std::cin, buff);
	numStates = std::stoi(buff.substr(14));
	std::cout << "Number of states: " << numStates << std::endl;
	

	// Fetch input alphabet and do nothing with it
	// Handle input "State	a	b	..	E"
	std::getline(std::cin, buff);
	
	std::cout << "Maximum alphabet : " << std::endl;
	for(int i = 0; i<sigmaSize; ++i){
		std::cout << i << " maps to " << c_unmap(i) << std::endl;
	}


	/**********************************************************************
	 * Assemble Input States
	 *********************************************************************/
	

	std::vector<int>* NFA_table[numStates][sigmaSize];

	// start blank
	for(int i = 0; i < numStates; ++i){
		for(int j=0; j<sigmaSize; ++j){
			NFA_table[i][j] = nullptr;	
		}	
	}

	// Handle input "#	{#,#..}	{#,#...} ..."
	std::getline(std::cin, buff);
	while(buff.size() > 1){
		std::cout << "Read in state: " << buff;

		// Tokenize
		std::vector<std::string> *pieces= split_str(buff.data());
	
		// First element is this state's name
		int name = std::stol(pieces->at(0));

		std::cout << std::endl << "Creating state: " << name <<std::endl;

		len = pieces->size();

		// For each set
		for(int i = 1; i<len; ++i){
			
			// Skip empty sets
			if(2 < pieces->at(i).size()){
				
				// Strip braces from ends
				std::string temp = pieces->at(i).substr(1, pieces->at(i).size()-2);

				std::vector<int> *transitions = split_int(temp.data());
				
				std::cout << "Parsed set: ";
				print_int_vec(transitions);
				std::cout << std::endl;

				// If there is less than a full
				// alphabet, the last will not
				int cval;
				if(len == 26){
					cval = i-1;
				}
				else{
					// If we don't have a full
					// alphabet, make sure the
					// last character is set to E
					cval = (i == len-1) ? 26 : i-1;
				}

				NFA_table[name][cval] = transitions;

			}
			else{
				std::cout << "Empty set, moving on..." << std::endl;	
			}
		}

		delete pieces;
		pieces = nullptr;
		std::getline(std::cin, buff);
		
	}// End while(buff.size() > 1)

	std::cout << "Input table complete" << std::endl;

	for(int i = 0; i< numStates; ++i){
		for(int j = 0; j<sigmaSize; ++j){
			
			if(nullptr != NFA_table[i][j]){
				std::cout << "State " << i+1 << ":" << std::endl;
				std::cout << "\t" << "On input " << c_unmap(j) << ": ";
				print_int_vec(NFA_table[i][j]);
				std::cout << std::endl;
			}
		}
	}


	/**********************************************************************
	 * Main Algorithm
	 *********************************************************************/
	
	// The DFA table maps some input set to an array of output sets,
	// indexed by the input alphabet.
	std::map< std::set<int>, std::vector< std::set<int> > >DFA_table;

	// Compute epsilon closure of the initial state.  This is the first
	// DFA state.
	
	
	


	/**********************************************************************
	 * Housekeeping
	 *********************************************************************/
	
	// Clean up finalstates
	delete finalStates;


	// Clean up NFA_table
	for(int i = 0; i<numStates; ++i){
		for(int j=0; j<sigmaSize; ++j){
			delete NFA_table[i][j];
		}	
	}

	// Clean up DFA_table
	// TODO

	return 0;
}
