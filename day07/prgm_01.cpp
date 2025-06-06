#pragma once
#include <string>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR };

class Logger {
public:
    static void log(LogLevel level, const std::string& msg);
};
logger.cpp
cpp
Copy code
#include "logger.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

void Logger::log(LogLevel level, const std::string& msg) {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string prefix;

    switch (level) {
        case LogLevel::DEBUG:   prefix = "[DEBUG]"; break;
        case LogLevel::INFO:    prefix = "[INFO] "; break;
        case LogLevel::WARNING: prefix = "[WARN] "; break;
        case LogLevel::ERROR:   prefix = "[ERROR]"; break;
    }

    std::cout << std::put_time(std::localtime(&now), "[%H:%M:%S] ")
              << prefix << " " << msg << std::endl;
}
memory.hpp
cpp
Copy code
#pragma once
#include <vector>

class Memory {
private:
    std::vector<int> mem;

public:
    Memory(size_t size = 65536);
    int read(int address);
    void write(int address, int value);
    void dump(int limit = 16);
};
memory.cpp
cpp
Copy code
#include "memory.hpp"
#include <iostream>

Memory::Memory(size_t size) {
    mem.resize(size, 0);
}

int Memory::read(int address) {
    return mem[address];
}

void Memory::write(int address, int value) {
    mem[address] = value;
}

void Memory::dump(int limit) {
    for (int i = 0; i < limit; ++i) {
        std::cout << "[" << i << "] = " << mem[i] << std::endl;
    }
}
instruction.hpp
cpp
Copy code
#pragma once
#include <string>

struct Instruction {
    std::string opcode;
    std::string operand1;
    std::string operand2;
};
cpu.hpp
cpp
Copy code
#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "memory.hpp"
#include "instruction.hpp"

class CPU {
private:
    std::unordered_map<std::string, int> registers;
    std::vector<Instruction> program;
    Memory memory;
    int pc;

public:
    CPU();
    void loadProgram(const std::string& filename);
    void execute();
    void printState();

private:
    int resolveValue(const std::string& val);
    void assignValue(const std::string& target, int value);
    void runInstruction(const Instruction& inst);
};
cpu.cpp
cpp
Copy code
#include "cpu.hpp"
#include "logger.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

CPU::CPU() : memory(65536), pc(0) {
    registers["AX"] = 0;
    registers["BX"] = 0;
    registers["CX"] = 0;
    registers["DX"] = 0;
}

void CPU::loadProgram(const std::string& filename) {
    std::ifstream in(filename);
    std::string line;
    program.clear();

    while (getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        Instruction inst;
        ss >> inst.opcode >> inst.operand1;

        if (inst.operand1.back() == ',') inst.operand1.pop_back();
        ss >> inst.operand2;
        program.push_back(inst);
    }

    Logger::log(LogLevel::INFO, "Loaded " + std::to_string(program.size()) + " instructions.");
}

int CPU::resolveValue(const std::string& val) {
    if (val.front() == '[') {
        int addr = std::stoi(val.substr(1, val.size() - 2));
        return memory.read(addr);
    } else if (registers.count(val)) {
        return registers[val];
    } else {
        return std::stoi(val);
    }
}

void CPU::assignValue(const std::string& target, int value) {
    if (target.front() == '[') {
        int addr = std::stoi(target.substr(1, target.size() - 2));
        memory.write(addr, value);
    } else if (registers.count(target)) {
        registers[target] = value;
    }
}

void CPU::runInstruction(const Instruction& inst) {
    std::string op = inst.opcode;
    std::string a = inst.operand1;
    std::string b = inst.operand2;

    Logger::log(LogLevel::DEBUG, "Executing: " + op + " " + a + (b.empty() ? "" : ", " + b));

    if (op == "MOV") {
        assignValue(a, resolveValue(b));
    } else if (op == "ADD") {
        registers["AX"] = resolveValue(a) + resolveValue(b);
    } else if (op == "SUB") {
        registers["AX"] = resolveValue(a) - resolveValue(b);
    } else if (op == "MUL") {
        registers["AX"] = resolveValue(a) * resolveValue(b);
    } else if (op == "DIV") {
        int divisor = resolveValue(b);
        if (divisor != 0)
            registers["AX"] = resolveValue(a) / divisor;
        else
            Logger::log(LogLevel::ERROR, "Division by zero");
    } else if (op == "HLT") {
        Logger::log(LogLevel::INFO, "HLT encountered. Halting execution.");
        pc = program.size(); // Force stop
    } else {
        Logger::log(LogLevel::ERROR, "Unknown instruction: " + op);
    }
}

void CPU::execute() {
    Logger::log(LogLevel::INFO, "Beginning program execution.");
    while (pc < program.size()) {
        runInstruction(program[pc++]);
    }
    Logger::log(LogLevel::INFO, "Execution finished.");
    printState();
}

void CPU::printState() {
    std::cout << "\n--- Final Registers ---\n";
    for (auto& [reg, val] : registers) {
        std::cout << reg << ": " << val << std::endl;
    }

    std::cout << "\n--- First 16 Memory Locations ---\n";
    memory.dump();
}
🏁 main.cpp
cpp
Copy code
#include "cpu.hpp"

int main() {
    CPU cpu;
    cpu.loadProgram("instructions.txt");
    cpu.execute();
    return 0;
}
🧪 Sample instructions.txt
css
Copy code
MOV [4], 5
MOV [5], 10
MOV AX, [4]
MOV BX, [5]
ADD AX, BX
MOV [6], AX
HLT
This version improves:

Code clarity and maintainability with clear separation.

Easy to extend with new instructions.

Full logging support with debug levels.

Would you like this zipped as a code package? Or should I add error handling, unit testing, or visualization next?









