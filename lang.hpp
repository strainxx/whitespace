#pragma once

enum OP {
	OP_PUSH,
	OP_DUB,
	OP_COPY,
	OP_SWAP,
	OP_DISCARD,
	OP_SLIDE,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_MOD,
	OP_STORE,
	OP_RETR,
	OP_MARK,
	OP_CALL,
	OP_JMP,
	OP_JZ,
	OP_JBZ,
	OP_ENDSUB,
	OP_END,
	OP_OUTC,
	OP_OUTN,
	OP_READC,
	OP_READN,
	OP_NOP
};



enum IMP {
	STACK_MANIP,
	ARITH,
	HEAP,
	FLOW,
	IO
};

struct Instruction {
	IMP imp;
	OP operand;
	int param;
	int size; // used by parser
	bool lfend; // used by parser
};

static int parseNumber(std::string seq) {
	bool isNegative = seq[0] == '\t';

	int result = 0;

	for (size_t i = 1; i < seq.size() - 1; ++i) {  // Exclude the last character (linefeed)
		if (seq[i] == ' ') {
			result = (result << 1);      // Shift left and add 0 for space
		}
		else if (seq[i] == '\t') {
			result = (result << 1) | 1;  // Shift left and add 1 for tab
		}
		else {
			throw std::invalid_argument("Invalid character in sequence");
		}
	}

	return isNegative ? -result : result;
}