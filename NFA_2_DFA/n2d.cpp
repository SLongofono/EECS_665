/* @file n2d.cpp
 * @brief       Given a specific input format representing a nondeterministic
 *              finite state automata, converts it to a deterministic finite
 *              automata and prints the result.
 *
 * @author      Stephen Longofono
 * @created     September 2017
 * @notes       This program is ill-equipped to handle malformed input.
 *              See the example input for the correct form.
 *
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <cassert>
#include <stdexcept>
#include "State.h"
#include "helpers.h"


/*
 * @brief       Retrieve a vector of ints representing the States reachable
 *              on the given input symbol for the given State
 * @param s     A pointer to the State struct representing the State at hand
 * @param c     A char reprenting an input symbol from the alphabet
 * @return      A vector of ints representing the states reachable from s on c
 */
std::vector<int>* get_moves(State *s, char c){
        //TODO Cleanup memory
        std::vector<int> * v = new std::vector<int>;
        // For each member in the state's moves, if the input symbol matches,
        // and it is not already in v, add its state value to v as an integer
        int size = s->m_moves.size();
        char* temp;
        for(int i = 0; i< size; ++i){
                temp = &(s->m_moves.at(i)->symbol);
                if (c == *temp){
                        std::cout << "Matched the input symbol..." << std::endl;
                        if( !(is_member(v, s->m_moves.at(i)->state)) ){
                                std::cout << "New state encountered, adding to result..." << std::endl;
                                v->push_back(s->m_moves.at(i)->state);
                        }
                }
        }
        return v;
}


/*
 * @brief       Retrieve a vector of ints representing the States reachable
 *              from a list of states on NULL input (or epsilon, or lambda,
 *              or whatever else you want to call it)
 * @param s     A pointer to all the possible states at hand
 * @param moves A pointer to a vector of ints representing states to check
 * @return      A pointer to an std::vector<int> containing all the states
 *              reachable via NULL input from the given list of states in
 *              moves.  Note that at minimum, this will be the vector moves.
 */
std::vector<int>* get_epsilon_closure(std::vector<State *> *s, std::vector<int>* moves){
        //TODO Cleanup memory
        std::vector<int>* v = new std::vector<int>;
        int pos, size_moves, size_transitions;
        State* curr;

        /* For each of the states given in moves:
        *       Find the state in the list of states s
        *               For each move in the current state
        *                       If the move has epsilon, add the resultant
        *                       state to the output vector.  When adding, use
        *                       set rules.
        */

        size_moves = moves->size();

        for(int i = 0; i<size_moves; ++i){
                // Every state can reach itself on NULL input
                if( !(is_member(v, moves->at(i)))){
                        v->push_back(moves->at(i));
                }

                // Locate the move's state in our list of known states
                pos = get_position(s, moves->at(i));
                curr = s->at(pos);
                assert(s != nullptr);

                // For each symbol transition in the current state, if the
                // symbol is 'E', add the resultant state to the results.
                // Only do so if the state is not already in the results.
                size_transitions = curr->m_moves.size();
                for(int j = 0; j<size_transitions; ++j){
                        if('E' == curr->m_moves.at(j)->symbol){
                                if( !(is_member(v, curr->m_moves.at(j)->state))){
                                        v->push_back(curr->m_moves.at(j)->state);
                                }
                        }
                }

        }

        return v;
}


int main(int argc, char** argv){


        State testState(99);
        testState.print_moves();
        testState.add_move('a', 100);
        testState.print_moves();

        /**********************************************************************
         * Parsing Input
         *********************************************************************/

        int numStates;                          // How many total states
        int initialState;                       // Where to begin
        std::vector<std::string> finalStates;   // Any of these states is accepted
        std::vector<std::string> sigma;         // Input alphabet

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


        /**********************************************************************
         * Assemble Input States
         *********************************************************************/

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

                        std::cout << std::endl << "Creating state " << newState->m_name <<std::endl;

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

        std::cout << "Finished parsing input.  The input states:" << std::endl;

        int temp = states->size();
        State* s;
        for(int i = 0; i<temp; ++i){
                s = states->at(i);
                std::cout << "State " << s->m_name << ":" << std::endl;
                s->print_moves();
        }

        s = states->at(1);
        std::cout << "Getting moves for 2nd state on input a..." << std::endl;
        std::vector<int> *damoves = get_moves(s, 'a');
        temp = damoves->size();
        for(int i = 0; i<temp; ++i){
                std::cout << damoves->at(i) << std::endl;
        }

        std::cout << "Getting E-closure for 2nd state..." << std::endl;
        std::vector<int> *daclosure = get_epsilon_closure(states, damoves);
        temp = daclosure->size();
        for(int i =0; i<temp; ++i){
                std::cout << daclosure->at(i) << std::endl;
        }


        /**********************************************************************
         * The Algorithm
         *********************************************************************/

        /*
         * The start state is added to set of DFA states, unmarked, with no
         * transitions
         *
         * For each unmarked state in the set of dfa states...
         *      For each input symbol on a state
         *              Assemble the moves on that input.
         *              Determine the epsilon closure of the resultant list
         *              If this list doesn't match a state in the DFA states,
         *                      add it to the DFA state
         *
         * Repeat until DFA states are marked.
         *
         * Now, look at each of the DFA states, and if it contains one of the
         * original final states, then it is final.
         *
         * Print the DFA states.
         */

        std::vector<State *> * DFA_states = new std::vector<State *>;
        State *start = new State(initialState);
        start->m_marked = 1;
        DFA_states->push_back(start);



        /**********************************************************************
         * Housekeeping
         *********************************************************************/


        std::cout << "Cleaning up..." << std::endl;

        temp = states->size();

        for(int i = 0; i<temp; ++i){
                s = states->at(i);
                delete s;
        }


        delete states;

        return 0;

}
