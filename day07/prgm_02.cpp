#ifndef MEMORY_UNIT_H
#define MEMORY_UNIT_H

#include <map>

class MemoryUnit {
private:
    std::map<int, int> memory;

public:
    void write(int address, int value);
    int read(int address);
    void displayFirst16();
};

#endif
#include "memory_unit.h"
#include <iostream>

void MemoryUnit::write(int address, int value) {
    if (address >= 0 && address < 65536)
        memory[address] = value;
}

int MemoryUnit::read(int address) {
    return memory.count(address) ? memory[address] : 0;
}

void MemoryUnit::displayFirst16() {
    for (int i = 0; i < 16; ++i)
        std::cout << i << " -> " << read(i) << std::endl;
}
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>

struct Instruction {
    std::string opcode;
    std::string operand1;
    std::string operand2;

    Instruction(std::string op, std::string o1, std::string o2 = "")
        : opcode(op), operand1(o1), operand2(o2) {}
};

std::vector<Instruction> parseInstructions(const std::string& filename);

#endif
#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "register_bank.h"
#include "memory_unit.h"
#include "instruction.h"
#include <vector>

class Processor {
private:
    RegisterBank reg;
    MemoryUnit mem;
    std::vector<Instruction> instructions;
    int pc;

    int resolveOperand(const std::string& operand);
    void execute(const Instruction& instr);

public:
    Processor(const std::vector<Instruction>& instrList);
    void run();
};

#endif
#include "processor.h"
#include <iostream>
#include <cctype>
#include <sstream>

Processor::Processor(const std::vector<Instruction>& instrList)
    : instructions(instrList), pc(0) {}

int Processor::resolveOperand(const std::string& operand) {
    if (operand.empty()) return 0;
    if (operand[0] == '[') {
        int addr = std::stoi(operand.substr(1, operand.size() - 2));
        return mem.read(addr);
    } else if (reg.get(operand) || operand == "AX" || operand == "BX" || operand == "CX" || operand == "DX") {
        return reg.get(operand);
    } else {
        return std::stoi(operand);
    }
}

void Processor::execute(const Instruction& instr) {
    std::string op = instr.opcode;
    std::string a = instr.operand1;
    std::string b = instr.operand2;

    if (op == "MOV") {
        if (a[0] == '[') {
            int addr = std::stoi(a.substr(1, a.size() - 2));
            int val = resolveOperand(b);
            mem.write(addr, val);
        } else if (b[0] == '[') {
            int val = resolveOperand(b);
            reg.set(a, val);
        } else if (reg.get(a) || a == "AX" || a == "BX" || a == "CX" || a == "DX") {
            int val = resolveOperand(b);
            reg.set(a, val);
        } else {
            int addr = std::stoi(a);
            int val = resolveOperand(b);
            mem.write(addr, val);
        }
    } else if (op == "ADD") {
        reg.set("AX", reg.get("AX") + resolveOperand(b));
    } else if (op == "SUB") {
        reg.set("AX", reg.get("AX") - resolveOperand(b));
    } else if (op == "MUL") {
        reg.set("AX", reg.get("AX") * resolveOperand(b));
    } else if (op == "DIV") {
        int divisor = resolveOperand(b);
        if (divisor != 0)
            reg.set("AX", reg.get("AX") / divisor);
    }
}

void Processor::run() {
    while (pc < instructions.size()) {
        if (instructions[pc].opcode == "HLT") {
            std::cout << "Received Interrupt\nSnapshot of the processor:\n";
            reg.display();
            std::cout << "First 16 Memory Contents\n";
            mem.displayFirst16();
            break;
        }
        execute(instructions[pc]);
        ++pc;
    }
}
#include "instruction.h"
#include "processor.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Instruction> parseInstructions(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Instruction> list;
    std::string line;

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string op, o1, o2;
        iss >> op >> o1;
        if (iss >> o2) {
            if (o2.back() == ',') o2.pop_back();
        }
        if (o1.back() == ',') o1.pop_back();
        list.emplace_back(op, o1, o2);
    }

    return list;
}

int main() {
    std::vector<Instruction> instrs = parseInstructions("instructions.txt");
    Processor processor(instrs);
    processor.run();
    return 0;
}
