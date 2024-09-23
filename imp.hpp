#pragma once
#include "lang.hpp"
#include <iostream>
#include <vector>

class Stack {
public:
	void push(int e) {
		stack.push_back(e);
	}
	void pop() {
		stack.pop_back();
	}
	int get() {
		return stack[stack.size() - 1];
	}
private:
	std::vector<int> stack{};
};

void runInstructions(std::vector<Instruction> instructions) {

	Stack* stack = new Stack();
	
    for (const Instruction i : instructions)
    {
		switch (i.operand)
		{
		case OP::OP_PUSH:
			stack->push(i.param);
			break;
		case OP::OP_OUTC:
			std::cout << (char)stack->get();
			break;
		default:
			break;
		}
    }
}