#include "Parser.h"
#include "Expr.h"
#include <iostream>

void Parser::parse(){

	PAction action;
	int prod_size;

	token = lexer.getNextToken();
	state_stack.push(0);

	std::cout << "Initial token: " << lexer.tokenToString(token) << " | " << lexer.getText() << std::endl;

	while(true){
		action = lr_action(state_stack.top(), token);

		if(action.isShift()){
			token_stack.push(token);
			state_stack.push(action.getValue());
			token = lexer.getNextToken();
			std::cout << "Shifted to token: " << lexer.tokenToString(token) << " | " << lexer.getText() << std::endl;
			continue;
		}
		else if(action.isReduce()){
			const Rule& prod = rule(action.getValue());
			prod_size = prod.rhs.size();
			for(int i = 0; i < prod_size; i++){
				token_stack.pop();
				state_stack.pop();
			}
			if(lr_goto(state_stack.top(), prod.lhs) == -1)
				throw std::string("Unexpected token ") + lexer.tokenToString(token);

			token_stack.push(prod.lhs);
			state_stack.push(lr_goto(state_stack.top(), prod.lhs));
			continue;
		}
		else if(action.isAccept()){
			if(!token_stack.empty() && token != Symbol::Eof){
				throw std::string("Unexpected token ") + lexer.tokenToString(token);
			}
			else {
				std::cout << "Input Accepted\n";
				break;
			}
		}
		else if(action.isEmpty()){
			throw std::string("Unexpected token ") + lexer.tokenToString(token);
		}
	}

}