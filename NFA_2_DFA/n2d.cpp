/* @file n2d.cpp
 * @brief       Given a specific input format representing a nondeterministic
 *              finite state automata, converts it to a deterministic finite
 *              automata and prints the result.
 *
 * @author      Stephen Longofono
 * @created     September 2017
 * @notes       This program is ill-equipped to handle malformed input.
 *              The exact input must be of the following form:
 *
 *              Initial State: {1}
 *              Final States: {11}
 *              Total States: 11
 *              State   a       b       E
 *              1       {}      {}      {2,5}
 *              2       {3}     {}      {}
 *              3       {}      {4}     {}
 *              4       {}      {}      {8}
 *              5       {}      {6}     {}
 *              6       {7}     {}      {}
 *              7       {}      {}      {8}
 *              8       {}      {}      {9,11}
 *              9       {10}    {}      {}
 *              10      {}      {}      {9,11}
 *              11      {}      {}      {}
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
// Modified to handle tabs and spaces alike
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


/*
 * @brief       Helper function to determine if an integer is a member of a
 *              vector<int>
 * @param v     A pointer to an std::vector<int> to check for membership
 * @param n     An integer to find in v
 * @return      Returns 1 if the integer is a member of the vector, or 0
 *              otherwise
 */
int is_member(std::vector<int> * v, int n){
        int size = v->size();
        for(int i = 0; i<size; ++i){
                if(n == v->at(i)){
                        return 1;
                }
        }
        return 0;
}


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
 * @brief       Finds the position of a state with name name in the given
 *              vector of states.
 * @param v     A pointer to a std::vector<State> with all known states
 * @param name  An integer representing the name of a state to check for
 * @return      An integer representing the position of the state with
 *              name name in the vector, or -1 if no such state exists.
 *              Note that the latter is an error.
 */
int get_position(std::vector<State *> *v, int name){
        int numstates = v->size();
        for(int i = 0; i<numstates; ++i){
                if( v->at(i)->m_name == name){
                        return i;
                }
        }
        return -1;
}


/*
 * @brief       Determines if two int vectors are equivalent sets
 * @param a     A pointer to a std::vector of ints representing a set of
 *              states
 * @param b     A pointer to a std::vector of ints representing a set of
 *              states
 * @return      Returns 1 if the sets are equivalent, or 0 otherwise
 */
int set_equivalent(std::vector<int> *a, std::vector<int> *b){
        return 0;
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

        std::cout << "Cleaning up..." << std::endl;

        temp = states->size();

        for(int i = 0; i<temp; ++i){
                s = states->at(i);
                delete s;
        }


        delete states;

        return 0;

}
