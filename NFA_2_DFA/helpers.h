/*
 * Helper Functions for the NFA to DFA project
 */

#ifndef HELPERS_H
#define HELPERS_H
#include <vector>
#include <cassert>
#include <string>
#include <stdlib.h>
#include "State.h"


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
 * @notes       Assumes that both vectors are in fact sets, with no
 *              duplicate elements.  That is, if there are no duplicate
 *              members, and both sets have equal length, then if every member
 *              of a is a member of b, so too is every member of b a member of
 *              a.
 */
int set_equivalent(std::vector<int> *a, std::vector<int> *b){
        int sza = a->size();
        int szb = b->size();
        int found = 0;
        int ret = 0;

        if(sza == szb){

                for(int i =0; i<sza; ++i){

                        for(int j=0; j<szb; ++j){
                                if(a->at(i) == b->at(j)){
                                        found = 1;
                                }
                        }
                        if(0 == found){
                                std::cout << "No match for member " << a->at(i) << std::endl;
                                break;
                        }
                        else{
                                found = 0;
                        }
                }

        }
        return ret;
}




#endif
