#include "State.h"

State::State(){
	m_name = '-';	
}

State::State(int name){	
	m_name = name;
}

State::~State(){
	move* temp;
	int len = m_moves.size();
	for(int i = 0; i<len; ++i){
		temp = m_moves.at(i);
		delete temp;
	}
	while(len > 0){
		m_moves.pop_back();
		len--;
	}
}

void State::add_move(char symbol, int state){
	move *newmove = new move;
	newmove->symbol = symbol;
	newmove->state = state;
	m_moves.push_back(newmove);
}

void State::print_moves(){
	int len = m_moves.size();
	std::cout<< len << " moves: " << std::endl;
	for(int i = 0; i<len; ++i){
		std::cout << "( " << m_moves.at(i)->symbol << "->" << m_moves.at(i)->state << " )" << std::endl;
	}
	return;
}
