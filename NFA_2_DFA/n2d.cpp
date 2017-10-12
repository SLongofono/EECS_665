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
	//	std::cout << " found states " << std::endl;
		ret = new std::set<int>;
		ret->insert( NFA[s][c]->begin(), NFA[s][c]->end() );
	}
	
	return ret;
}


int main(int argc, char **argv){
	
	/**********************************************************************
	 * Parsing Metadata
	 *********************************************************************/
	std::vector<std::string> *strFinalStates;// Any of these states is accepted
	std::vector<int>	 *finalStates;	 // In integer form
	int numStates;				 // How many total states
	int initialState;			 // Where to begin
	int sigmaSize = 27;	 		 // To make things simple,
						 // assume lower case alphabet
						 // plus E
	int input_len;				 // Keep track of actual input
						 // for printing at the end
	std::string buff;

	// Fetch initial state
	// Handle input "Initial State: {#}"
	std::getline(std::cin, buff);
	buff.pop_back();
	initialState = std::stoi(buff.substr(16));

	// Fetch final states as a vector
	// Handle input "Final States: {#,#,#,#...}"
	std::getline(std::cin, buff);
	buff.pop_back();
	strFinalStates = split_str(buff.substr(15).data());
	finalStates = new std::vector<int>;
	for(size_t i = 0; i<strFinalStates->size(); ++i){
		finalStates->push_back(std::stoi(strFinalStates->at(i)));	
	}

	// Fetch total number of states
	// Handle input "Total States: #"
	std::getline(std::cin, buff);
	numStates = std::stoi(buff.substr(14));

	// Fetch input alphabet and do nothing with it
	// Handle input "State	a	b	..	E"
	std::getline(std::cin, buff);
	std::vector<std::string>* trash = split_str(buff.data());
	input_len = trash->size() - 2;
	delete trash;

	/**********************************************************************
	 * Assemble Input States
	 *********************************************************************/

	// NOTE: using numStates + 1 since we are using states indexed from 1
	// for some insane reason.
	int arbitrary_introduction_of_unneccesary_complexity = 1;

	std::vector<int> ***NFA_table = new std::vector<int>**[numStates+arbitrary_introduction_of_unneccesary_complexity];

	for(int i = 0; i<numStates+arbitrary_introduction_of_unneccesary_complexity; ++i){
		std::vector<int>** sigma_indirection = new std::vector<int>*[sigmaSize];
		NFA_table[i] = sigma_indirection;
	}

	// start blank
	for(int i = 0; i < numStates+arbitrary_introduction_of_unneccesary_complexity; ++i){
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

		int len = pieces->size();

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

	// Finally, we need to give our output states a simple name because
	// that's what the rubric calls for
	std::map<
		std::set<int>*,
		int
	>DFA_familiar_names;

	int familiarCount = 1;

	// Compute epsilon closure of the initial state.  This is the first
	// DFA state.
	std::set<int> * init = epsilon_closure(initialState, sigmaSize, NFA_table);

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

	DFA_familiar_names.insert(
		std::pair< std::set<int>*, int>(
			init, familiarCount
		)
	
	);

	familiarCount++;
	
	std::cout << "E-closure(IO) = ";
	print_int_set(init);
	std::cout << " = " << DFA_familiar_names.find(init)->second << std::endl;

	std::set<int>* curr = find_unmarked(DFA_marked);

	// While there are DFA states left to mark
	while( curr != nullptr){
		
		// Mark this DFA state
		DFA_marked[curr] = 1;
		
		std::cout << std::endl << "Mark " << DFA_familiar_names.find(curr)->second << std::endl;
		
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
				print_int_set(curr);
				std::cout << " --" << c_unmap(i) << "--> ";
				print_int_set(moves);
				std::cout << std::endl;

				// Generate the epsilon closure of the
				// result
				std::set<int>::iterator iter;
				std::set<int>* eps;

				size_t setlen = U->size();

				for(iter = moves->begin(); iter != moves->end(); iter++){
					eps = epsilon_closure( (*iter), sigmaSize, NFA_table);
					
					U->insert(eps->begin(), eps->end());
				}
				// Also need to account for the epsilon
				// closure of the other states, for as long as
				// the length is unchanged.
				while(setlen != U->size()){
					for(iter = U->begin(); iter != U->end(); iter++){
						eps = epsilon_closure( (*iter), sigmaSize, NFA_table);
					}
					U->insert(eps->begin(), eps->end());
					setlen = U->size();
				}
			
				// If the epsilon closure is not in
				// the DFA table...
				std::map< std::set<int>*, std::set<int>** >::iterator thisone;

				for(thisone = DFA_table.begin(); thisone != DFA_table.end(); thisone++){
					if(set_compare(U, thisone->first )){
						// Found an equivalent set,
						// kick out
						break;
					}
				}
				if(thisone == DFA_table.end()){
				

					// Create and initialize an array represnting the sigma mapping
					std::set<int>** sigma_indirection = new std::set<int> *[sigmaSize];
					for(int i = 0; i<sigmaSize; ++i){
						sigma_indirection[i] = nullptr;	
					}

					// Create a new entry in the
					// DFA table
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
					
					// Update our familiar names with the
					// new state
					DFA_familiar_names.insert(
						std::pair< std::set<int>*, int>(
							U, familiarCount
						)
	
					);

					familiarCount++;

				} // end if(thisone != DFA_table.end())

				// Add a transition on
				// the current letter to the epsilon
				// closure set
				DFA_table[curr][i] = U;

				// Feedback
				std::cout << "E-closure";
				print_int_set(moves);
				std::cout << " = ";
				print_int_set(U);
				std::cout << " = " << set_name_match(U, DFA_familiar_names) << std::endl;

			}
			else{
				delete U;
				delete moves;
			}

		} // end for(int i = 0; i<sigmaSize; ++i)

		// Move on to another DFA state
		curr = find_unmarked(DFA_marked);

	} // end while(curr != nullptr)

	// Determine new final states;
	std::set<int>* fstates = new std::set<int>;
	std::map< std::set<int>*, int>::iterator it;
	int len = finalStates->size();
	for(it = DFA_familiar_names.begin(); it != DFA_familiar_names.end(); ++it){
		for(int j = 0; j<len; ++j){
			if(set_member( it->first, finalStates->at(j) )){
				fstates->insert(it->second);
			}		
		}
	}


	/**********************************************************************
	 * Display Results
	 *********************************************************************/

	std::cout << std::endl << "Initial state: {" << set_name_match(init, DFA_familiar_names) << "}" << std::endl;

	std::cout << "Final States: ";
	print_int_set(fstates);
	std::cout << std::endl;

	std::cout << "State\t";
	for(int i = 0; i<input_len; ++i){
		std::cout << c_unmap(i);
		if(i < input_len){
			std::cout << "\t";	
		}
	}
	std::cout << std::endl;

	len = DFA_familiar_names.size();
	for(int i = 0; i<len; ++i){
		std::cout << i+1 << "\t";

		// Find the set associated with the current number
		std::set<int>* curr = set_name_int_match(i+1, DFA_familiar_names);

		for(int j = 0; j<input_len; ++j){
			
			// Find the output transition associated with this
			// input character and display it.
			std::set<int>* thisone = DFA_table.at(curr)[j];
			if(nullptr != thisone){

				std::cout << "{" << set_name_match(thisone, DFA_familiar_names)<< "}";
			
			}
			else{
				std::cout << "{}";	
			}

			if(j < input_len-1){
				std::cout << "\t";	
			}
		}
		std::cout << std::endl;

	}


	/**********************************************************************
	 * Housekeeping
	 *********************************************************************/

	// Clean up initial state
	delete init;

	// Clean up finalstates
	delete finalStates;
	delete strFinalStates;
	delete fstates;

	// Clean up NFA_table
	for(int i = 0; i<numStates; ++i){
		for(int j=0; j<sigmaSize; ++j){
			delete NFA_table[i][j];
		}	
	}


	// Clean up DFA_table
	std::map<std::set<int>*, std::set<int>**>::iterator it2;
	for(it2 = DFA_table.begin(); it2 != DFA_table.end(); ++it2){
		for(int i = 0; i<sigmaSize; ++i){
			delete it2->second[i];
		}
	}
	DFA_table.clear();

	// Clean up names and marked tables
	DFA_familiar_names.clear();
	DFA_marked.clear();

	

	return 0;
}
