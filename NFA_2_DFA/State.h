#ifndef STATE_H
#define STATE_H
#include <vector>
#include <iostream>

// Stores a transition as a symbol-state pair
typedef struct move{
        // The input symbol
        char symbol;

        // The state resulting from the input symbol
        int state;
}move;

// Stores a transition as a symbol-vector pair
typedef struct move_vec{
        // The input ssymbol
        char symbol;

        // The vector of ints representing the destination
        std::vector<int> *state;
}move_vec;

class State{

        public:
                State();
                ~State();
                State(int name);

                // If this is an input state, it will have a vector of moves
                // with input symbols and destination states
                std::vector<move *> m_moves;

                // If this is an output state, it will have a vector of ints
                // representing its relationship to the input states.
                std::vector<move_vec *>  v_moves;
                int m_name;
                int m_marked;
                int m_final;
                void add_move(char symbol, int state);
                void add_move_vec(char symbol, std::vector<int> *state);
                void print_moves();
};

#endif
