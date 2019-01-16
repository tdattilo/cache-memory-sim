#ifndef CACHEROW
#define CACHEROW
#include <string>

class CacheRow{
	private:
		short values[0x10];
		bool valid;
		bool dirty;
		short tag;
	public:
		CacheRow();
		std::string display();
		bool isValid();
		bool isDirty();
		void setTag(short);
		short getTag();
		short getVal(short);
		void writeVal(short, short);
		void modVal(short, short);
};
#endif