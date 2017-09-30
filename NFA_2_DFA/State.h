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

class State{

	public:
		State();	
		~State();	
		State(int name);
		
		int get_name();
		void add_move(char symbol, int state);
		void print_moves();

	private:
		int m_name;		
		std::vector<move *> m_moves;
};

#endif
