#include <iostream>
#include "lang.hpp"
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include "imp.hpp"
#define printword(XX) #XX

const char* imps[] =
{
    "STACK_MANIP",
    "ARITH",
    "HEAP",
    "FLOW",
    "IO"
};

const char* ops[] = {
    "OP_PUSH",
    "OP_DUB",
    "OP_COPY",
    "OP_SWAP",
    "OP_DISCARD",
    "OP_SLIDE",
    "OP_ADD",
    "OP_SUB",
    "OP_MUL",
    "OP_DIV",
    "OP_MOD",
    "OP_STORE",
    "OP_RETR",
    "OP_MARK",
    "OP_CALL",
    "OP_JMP",
    "OP_JZ",
    "OP_JBZ",
    "OP_ENDSUB",
    "OP_END",
    "OP_OUTC",
    "OP_OUTN",
    "OP_READC",
    "OP_READN",
    "OP_NOP",
};

Instruction parseInstruction(std::string line) {
    // Returns instruction and instr length
    Instruction instr{};
    instr.param = 0;
    instr.operand = OP::OP_NOP;
    instr.lfend = false;

    switch (line[0])
    {
    case ' ':
        instr.imp = IMP::STACK_MANIP;
        instr.size = 1;
        break;
    case '\t':
        if (line[1] == ' ')
        {
            instr.size = 2;
            instr.imp = IMP::ARITH;
        }
        else if (line[1] == '\t')
        {
            instr.imp = IMP::HEAP;
            instr.size = 2;
        }
        else if (line[1] == '\n')
        {
            instr.imp = IMP::IO;
            instr.size = 2;
            instr.lfend = true;
        }
        break;
    case '\n':
        instr.imp = IMP::FLOW;
        instr.lfend = true;
        instr.size = 1;
        break;
    default:
        break;
    }

    if (instr.lfend) {
        return instr;
    }

    switch (instr.imp)
    {
    case IMP::STACK_MANIP:
        if (line[instr.size] == ' ')
        {
            instr.operand = OP::OP_PUSH;
            instr.param = parseNumber(line.substr(instr.size + 1));
            instr.size += line.substr(instr.size + 1).length();
        }
        else
        {
            std::cout << "[WARN] Operand not implemented!\n";
        }
        break;
    default:
        std::cout << "[WARN] IMP not implemented!\n";
        break;
    }

    return instr;
}

std::pair<Instruction, int> lfParse(Instruction instr_, std::string line) {
    Instruction instr = instr_;
    switch (instr.imp)
    {
    case IMP::IO:
        if (line[0] == ' ' && line[1] == ' ')
        {
            instr.operand = OP::OP_OUTC;
            instr.size += 2;
        }
        break;
    default:
        std::cout << "[WARN] LF IMP not implemented\n";
        break;
    }
    return std::make_pair(instr, instr.size-instr_.size);
}

int main()
{
    std::cout << "Whitespace lang!\n";
    std::cout << "Enter filename: \n";

    std::string fname = "C:\\Users\\sasiska\\source\\repos\\whitespace\\x64\\Debug\\hi.ws";

    //std::cin >> fname;

    std::fstream inputFile(fname);

    if(!inputFile.is_open()){
        std::cout << "Failed to open file\n";
        return 1;
    }

    std::string line;

    Instruction lastInstr{};
    std::vector<Instruction> instructions{};

    while (std::getline(inputFile, line))
    {
        line += '\n';
        std::string filteredLine = "";
        int index = 0;
        

        for (char& c: line)
        {
            if (c == '\t' || c == ' ' || c == '\n') {
                filteredLine += c;
            }
        }

        line = filteredLine;

        if (lastInstr.lfend == true) {
            auto lfparsed = lfParse(lastInstr, line);
            lastInstr = lfparsed.first;
            index += lfparsed.second;
            lastInstr.lfend = false;

            instructions.push_back(lastInstr);
            //std::cout << imps[lastInstr.imp] << ": " << ops[lastInstr.operand] << " " << lastInstr.param << "\n";
        }

        while (true)
        {
            if (index >= line.length() - 1) {
                break;
            }
            lastInstr = parseInstruction(line.substr(index));
            index += lastInstr.size;
            if (!lastInstr.lfend) {
                instructions.push_back(lastInstr);
                //std::cout << imps[lastInstr.imp] << ": " << ops[lastInstr.operand] << " " << lastInstr.param << "\n";
            }
            else {

            }
        }
        
    }

    std::cout << "PARSED OUTPUT\n";

    for (const Instruction i: instructions)
    {
        std::cout << ops[i.operand] << " " << i.param << "\n";
    }

    std::cout << "Now running\n";

    runInstructions(instructions);
    //int i = 0b00000;
    //i |= 0b10;
    //std::cout << std::bitset<8>{(unsigned int)(i)} << "\n";
}