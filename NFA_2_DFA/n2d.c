#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_ALPHABET 27

// llist member node, represents a symbol destination pair
typedef struct node{
        struct node *next;
        char symbol;
        int state;
}node;


// llist head node. represents a state and its transitions list
typedef struct state{
        int name;
        int length;
        node* next;
}state;


/* @brief               Adds a new transition and its enclosing node to the
 *                      given state's list of transitions.
 * @param s             The state struct to which the transition should be added
 * @param symbol        A character representing the input symbol for the new
 *                      transition.
 * @param dest          An integer representing the name of the destination
 *                      state for the new transition on the input symbol.
 * @return              void
 * @notes               No error state, be careful
 */
void add_transition(state *s, char symbol, int dest){
        node* stepper;

        // Case empty llist
        if(NULL == s->next){
                stepper = malloc(sizeof (node));
                stepper->symbol = symbol;
                stepper->state = dest;
                s->length++;
                s->next = stepper;
        }
        else{
                stepper = s->next;

                // Find the end of the llist and create a new node, transition
                while( NULL != stepper->next){
                        stepper = stepper->next;
                }
                node *newnode = malloc(sizeof (node));
                newnode->symbol = symbol;
                newnode->state = dest;
                stepper->next = newnode;
                s->length++;
        }
        return;
}


int main(void){


        /*
         * Fetches input
        */

        char * input = NULL;
        size_t size = 0;        // Using zero defaults to entire line

        while(-1 != getline(&input, &size, stdin)){
                printf("Got a line:\n%s\n", input);
        }

        free(input);            // Clean up after last getline

        state myState;
        myState.name = 0;
        myState.length = 0;
        myState.next = NULL;
        add_transition(&myState, 'a', 1);
        add_transition(&myState, 'b', 2);
        add_transition(&myState, 'c', 3);

        node *stepper = myState.next;

        printf("State %d:\n", myState.name);
        while(NULL != stepper){
                printf("\t( %c --> %d )\n", stepper->symbol, stepper->state);
                stepper = stepper->next;
        }

        return 0;
}
