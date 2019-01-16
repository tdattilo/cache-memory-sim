#include "CacheRow.h"
#ifndef Cache
#define Cache

class Cache{
	private:
		CacheRow memCache[0xF];
		bool hit;
	public:
		Cache();
		String read(short);
		write(short, short);
		String display();
};
#endif Cache