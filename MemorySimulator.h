#include "CacheRow.h"
#include <string>

#ifndef MEM_SIM
#define MEM_SIM

class MemorySimulator{
	private:
		short main_mem[0x800];
		CacheRow *memCache;
		void pushBack(short);
	public:
		MemorySimulator();
		std::string read(short);
		std::string write(short, short);
		std::string display();		
};
#endif