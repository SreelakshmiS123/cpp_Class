#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
    static void log(const string& msg) {
        cout << msg << endl;
    }
};

class Memory {
    vector<int> mem;
public:
    Memory(size_t s = 65536) {
        mem.resize(s, 0);
    }
    int read(int addr) {
        return mem[addr];
    }
    void write(int addr, int val) {
        mem[addr] = val;
    }
};

struct instructions {
    string opr, arg1, arg2;
};

class Emulator {
    unordered_map<string, int> reg;
    vector<instructions> prg;
    Memory mem;
    int pc = 0;

    int resolve(const string& operand) {
        // If memory reference [num]
        if (operand.size() > 2 && operand[0] == '[' && operand.back() == ']') {
            int addr = stoi(operand.substr(1, operand.size() - 2));
            return mem.read(addr);
        }
        // If register
        if (reg.count(operand)) {
            return reg[operand];
        }
        // Otherwise, immediate number
        return stoi(operand);
    }

    void assign(const string& target, int val) {
        if (target.size() > 2 && target[0] == '[' && target.back() == ']') {
            int addr = stoi(target.substr(1, target.size() - 2));
            mem.write(addr, val);
        } else if (reg.count(target)) {
            reg[target] = val;
        } else {
            Logger::log("Invalid assignment target: " + target);
        }
    }

    void run(const instructions& i) {
        if (i.opr == "MOV") {
            int val = resolve(i.arg2);
            assign(i.arg1, val);
        } else if (i.opr == "ADD") {
            int val = resolve(i.arg1) + resolve(i.arg2);
            reg["AX"] = val;
        } else if (i.opr == "SUB") {
            int val = resolve(i.arg1) - resolve(i.arg2);
            reg["AX"] = val;
        } else if (i.opr == "MUL") {
            int val = resolve(i.arg1) * resolve(i.arg2);
            reg["AX"] = val;
        } else if (i.opr == "HLT") {
            Logger::log("Program halted");
            pc = (int)prg.size(); // stop execution
        } else {
            Logger::log("Unknown instruction: " + i.opr);
        }
    }

public:
    Emulator() {
        reg["AX"] = 0;
        reg["BX"] = 0;
        reg["CX"] = 0;
        reg["DX"] = 0;
    }

    void loadProgram(const string& fileName) {
        ifstream in(fileName);
        string line;
        while (getline(in, line)) {
            if (line.empty())
                continue;
            instructions i;
            stringstream ss(line);
            ss >> i.opr >> i.arg1 >> i.arg2;
            if (!(i.opr.empty() && i.arg1.empty() && i.arg2.empty())) {
                prg.push_back(i);
            }
        }
        Logger::log("Loaded program successfully");
    }

    void execute() {
        while (pc < (int)prg.size()) {
            run(prg[pc++]);
        }
    }

    void printState() {
        cout << "\nRegisters:\n";
        for (auto& [r, v] : reg)
            cout << r << ": " << v << endl;
        cout << "\nMemory [0..15]:\n";
        for (int i = 0; i < 16; ++i) {
            cout << "[" << i << "] = " << mem.read(i) << endl;
        }
    }
};

int main() {
    Emulator e;
    e.loadProgram("instructions.txt");
    e.execute();
    e.printState();
    return 0;
}
