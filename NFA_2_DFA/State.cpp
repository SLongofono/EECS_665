
#include "State.h"

State::State(){
        m_name = '-';
        m_marked = 0;
        m_final = 0;
}

State::State(int name){
        m_name = name;
        m_marked = 0;
        m_final = 0;
}

State::~State(){
        move* temp;
        move_vec* temp2;
        int len = m_moves.size();
        for(int i = 0; i<len; ++i){
                temp = m_moves.at(i);
                delete temp;
        }
        while(len > 0){
                m_moves.pop_back();
                len--;
        }
        len = v_moves.size();
        for(int i =0; i<len; ++i){
                temp2 = v_moves.at(i);
                delete temp2;
        }
        while(len > 0){
                v_moves.pop_back();
                len--;
        }
}

void State::add_move(char symbol, int state){
        move *newmove = new move;
        newmove->symbol = symbol;
        newmove->state = state;
        m_moves.push_back(newmove);
}

void State::add_move_vec(char symbol, std::vector<int>* state){
        move_vec *newmove = new move_vec;
        newmove->symbol = symbol;
        newmove->state = state;
        v_moves.push_back(newmove);
}

void State::print_moves(){
        int len = m_moves.size();
        std::cout<< len << " moves: " << std::endl;
        for(int i = 0; i<len; ++i){
                std::cout << "( " << m_moves.at(i)->symbol << "->" << m_moves.at(i)->state << " )" << std::endl;
        }
        return;
}
