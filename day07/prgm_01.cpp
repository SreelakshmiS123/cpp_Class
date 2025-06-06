#include<iostream>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<sstream>
#include<string>
using namespace std; 
class Logger
{
	static void log(const string& msg)
	{
		cout << msg << endl;
	}
};
class Memory
{
	vector<int>mem;
public:
	Memory(size_t s = 65536);//64 kb *1024
	void read(int addr, int val)
	{
		mem[addr] = val;
	}
	int write(int addr)
	{
		return mem[addr];
	}
};
struct instructions
{
	string opr, arg1, arg2;
};
class Emulator
{
	unordered_map<string, int> reg;
	vector<instructions> prg;
	Memory mem;
	int pc = 0;

	void assign(const string position, int val)
	{
		if (position[0] == '[')
		{
			int addr=
			mem.write(addr, val);
		}
	}
	void run(instructions i)
	{
		if (i.opr == "MOV")
		{
			assign(i.arg1, i.arg2);
        }
		else if (i.opr == "ADD")
		{
			reg["AX"] = i.arg1 + i.arg2;
		}
		else if (i.opr == "SUB")
		{
			reg["AX"] = i.arg1 - i.arg2;
		}
		else if (i.opr == "MUL")
		{
			reg["AX"] = i.arg1 * i.arg2;
		}
		else if (i.opr == "HLT")
		{
			Logger::log("Program halted");
		}
	}
public:
	Emulator() {
		reg["AX"] = 0;
		reg["BX"] = 0;
		reg["CX"] = 0;
		reg["DX"] = 0;
	}

	void loadProgram(const string& fileName)
	{
		ifstream in(fileName);
		string line;
		while (getline(in, line))
		{
			if (line.empty())
				continue;
			instructions i;
			stringstream ss(line);
			ss >> i.opr >> i.arg1 >> i.arg2;//opr(MOV),arg1(AX),arg2(BX)
			if (!(i.opr.empty() && i.arg1.empty() && i.arg2.empty()))
			{
				prg.push_back(i);
			}
			Logger::log("Loaded program successfully");
		}
		
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
};
int main()
{
	Emulator e;
	e.loadProgram("instructions.txt");
	e.execute();
	return 0;
}
