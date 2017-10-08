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
 * @param NFA		A 2D array of std::vector<int> representing the NFA table
 * @return		A pointer to a std::set<int> containing all the states
 * 			reachable from the input state on epsilon input
 * @notes		Will always be non-empty, since every state's epsilon-
 * 			closure includes itself.
 */
std::set<int>* epsilon_closure(int s, int sigmaSize, std::vector<int> ***NFA){
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
 * @param NFA		A 2D array of std::vector<int> representing the NFA table
 * @return		A pointer to a std::set<int> representing all the states
 *  			reachable from the input state on the input symbol.
 */
std::set<int>* get_moves(int s, int c, std::vector<int> ***NFA){
	
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
	

	/**********************************************************************
	 * Assemble Input States
	 *********************************************************************/

	// pointers are fun
	std::vector<int> ***NFA_table = new std::vector<int>**[numStates];

	for(int i = 0; i<numStates; ++i){
		std::vector<int>** sigma_indirection = new std::vector<int>*[sigmaSize];
		NFA_table[i] = sigma_indirection;
	}

	// start blank
	for(int i = 0; i < numStates; ++i){
		for(int j=0; j<sigmaSize; ++j){
			NFA_table[i][j] = nullptr;	
		}	
	}

	// Handle input "#	{#,#..}	{#,#...} ..."
	std::getline(std::cin, buff);
	while(buff.size() > 1){

		// Tokenize
		std::vector<std::string> *pieces= split_str(buff.data());
	
		// First element is this state's name
		int name = std::stol(pieces->at(0));

		len = pieces->size();

		// For each set
		for(int i = 1; i<len; ++i){
			
			// Skip empty sets
			if(2 < pieces->at(i).size()){
				
				// Strip braces from ends
				std::string temp = pieces->at(i).substr(1, pieces->at(i).size()-2);

				std::vector<int> *transitions = split_int(temp.data());
				
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
		}

		delete pieces;
		pieces = nullptr;
		std::getline(std::cin, buff);
		
	}// End while(buff.size() > 1)


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
	std::map<
		std::set<int>*, std::set<int>**
	>DFA_table;

	// We need to keep track of visited (marked) DFA states
	std::map<
		std::set<int>*,
		int
	>DFA_marked;

	// Compute epsilon closure of the initial state.  This is the first
	// DFA state.
	std::set<int> * init = epsilon_closure(initialState, sigmaSize, NFA_table);

	std::cout << "Epsilon closure, initial state: " << std::endl;
	print_int_set(init);
	std::cout << std::endl;
	
	// Create and initialize an array represnting the sigma mapping
	std::set<int>** sigma_indirection = new std::set<int> *[sigmaSize];
	for(int i = 0; i<sigmaSize; ++i){
		sigma_indirection[i] = nullptr;	
	}

	DFA_table.insert(
		std::pair< std::set<int>*, std::set<int>** >(
			init, sigma_indirection
		)
	);

	DFA_marked.insert(
		std::pair< std::set<int>*, int>(
			init, 0
		)
	);

	std::cout << "Created DFA table entry for initial state..." << std::endl;

	std::set<int>* curr = find_unmarked(DFA_marked);
	// While there are DFA states left to mark
	while( curr != nullptr){
		
		// Mark this DFA state
		DFA_marked[curr] = 1;
		
		std::cout << "Marked state: ";
		print_int_set(curr);
		std::cout << std::endl;
		
		std::set<int>::iterator curState;

		// For each input symbol, except E
		for(int i = 0; i<sigmaSize - 1; ++i){

			std::set<int>* moves = new std::set<int>;
			
			// Generate the moves on the current set from the
			// current input

			for(curState = curr->begin(); curState != curr->end(); curState++){
				std::set<int> *temp = get_moves(*(curState), i, NFA_table);
				
				// If moves exist, add them the the transition
				// on this symbol for the DFA state at hand
				if(temp != nullptr){
					moves->insert(temp->begin(), temp->end());
				}
			
			} // end for(curState = curr->begin()...
			

			// For clarity's sake, use the same name as in the
			// algorithm
			std::set<int> * U = new std::set<int>;
				
			// if we found moves...
			if(moves->size() > 0){
				std::cout << "Found moves on input " << c_unmap(i) << ":";
				print_int_set(moves);
				std::cout << std::endl;

				// Generate the epsilon closure of the
				// result
				std::set<int>::iterator iter;

				for(iter = moves->begin(); iter != moves->end(); iter++){
					std::set<int>* eps = epsilon_closure( (*iter), sigmaSize, NFA_table);
					
					std::cout << "Found moves: ";
					print_int_set(eps);

					U->insert(eps->begin(), eps->end());
				}
				
				std::cout << "Searching for ";
				print_int_set(U);
				std::cout << " in known DFA states..." << std::endl;

				// If the epsilon closure is not in
				// the DFA table...
				std::map< std::set<int>*, std::set<int>** >::iterator thisone;
				thisone = DFA_table.find(U);
				if(thisone == DFA_table.end()){
					// Create a new entry in the
					// DFA table
					std::cout << "Creating new DFA state: ";
					print_int_set(U);
					std::cout << std::endl;

					// Create and initialize an array represnting the sigma mapping
					std::set<int>** sigma_indirection = new std::set<int> *[sigmaSize];
					for(int i = 0; i<sigmaSize; ++i){
						sigma_indirection[i] = nullptr;	
					}

					DFA_table.insert(
						std::pair< std::set<int>*, std::set<int>** >(
							U, sigma_indirection
						)
					);

					// Create a new entry for
					// marking
					DFA_marked.insert(
						std::pair< std::set<int>*, int >(
							U, 0
						)
					);
				} // end if(thisone != DFA_table.end())
				else{
					std::cout << "This DFA state already exists..." << std::endl;
				}

				// In both cases, add a transition on
				// the current letter to the epsilon
				// closure set
				DFA_table[curr][i] = U;

			}
			else{
				std::cout << "\t\tEmpty set" << std::endl;
			}

		} // end for(int i = 0; i<sigmaSize; ++i)

		// Move on to another DFA state
		curr = find_unmarked(DFA_marked);

	} // end while(curr != nullptr)

	std::cout << "Found " << DFA_marked.size() << " DFA states: " << std::endl;
	std::map< std::set<int>*, int >::iterator iter;
	for(iter = DFA_marked.begin(); iter != DFA_marked.end(); iter++){
		std::cout << "\t";
		print_int_set(iter->first);
		std::cout <<std::endl;
	}
	


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
