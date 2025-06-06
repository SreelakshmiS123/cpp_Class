#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//Logger class for stroing events
class Logger {
public:
    static void log(const string& msg) {
        cout << msg << endl;
    }
};

//vector container for memory
class Memory {
    vector<int> mem;
public:
    Memory(size_t s = 65536) //64 kb* 1024
    {}
    void write(int addr, int val) {
        mem[addr] = val;
    }
    int read(int addr) {
        return mem[addr];
    }
   
};

//structure for the command seperatly
struct instructions {
    string opr, arg1, arg2;//Eg: MOV AX,BX -opr:MOV, arg1:AX, arg2:BX
};

class Emulator {
    unordered_map<string, int> reg;
    vector<instructions> prg;
    Memory mem;
    int pc = 0;

    int getValue(const string& operand) {
        // [13]
        if (operand[0] == '[' && operand.back() == ']') {
            int addr = stoi(operand.substr(1, operand.size() - 2));
            return mem.read(addr);
        }
        // register
        if (reg.count(operand)) {
            return reg[operand];
        }
        // a number
        return stoi(operand);
    }

    void assign(const string& position, int val) {
        if (position[0] == '[' && position.back() == ']') {
            int addr = stoi(position.substr(1, position.size() - 2));
            mem.write(addr, val);
        }
        else if (reg.count(position)) {
            reg[position] = val;
        }
        else {
            Logger::log("Invalid position");
        }
    }

    void run(const instructions& i) {
        if (i.opr == "MOV") {
            int val =getValue(i.arg2);
            assign(i.arg1, val);
        }
        else if (i.opr == "ADD") {
            int val = getValue(i.arg1) + getValue(i.arg2);
            reg["AX"] = val;
        }
        else if (i.opr == "SUB") {
            int val = getValue(i.arg1) - getValue(i.arg2);
            reg["AX"] = val;
        }
        else if (i.opr == "MUL") {
            int val = getValue(i.arg1) * getValue(i.arg2);
            reg["AX"] = val;
        }
        else if (i.opr == "HLT") {
            Logger::log("Program got halted");
            pc = (int)prg.size(); // stop execution
        }
        else {
            Logger::log("Invalid instruction" );
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

    void execute()
    {
        while (pc < prg.size())
        {
            instructions current = prg[pc];
            run(current);
            pc++;
        }
    }

    void printFinal() 
    {
      for(auto& pair:reg)
      {
          cout << pair.first << ":" << pair.second<<endl;
      }
    }
    
};

int main() {
    Emulator e;
    e.loadProgram("instructions.txt");
   e.execute();
    e.printFinal();
    return 0;
}
