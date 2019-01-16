#include "MemorySimulator.h"
#include <sstream>
#include <iostream>


using namespace std;

MemorySimulator::MemorySimulator(){
	for(short x=0; x<0x800; x++){
		main_mem[x]=x&0xFF;
	}
	memCache= new CacheRow[0x10];
}

void MemorySimulator::pushBack(short begin_address){
	short tag=memCache[(begin_address>>4)&0xF].getTag();
	short address;
	address=((tag<<8)+(begin_address&0xF0));
	for(short x=0x0; x<0x10; x++){
		main_mem[address+x]=memCache[(begin_address&0xF0)>>4].getVal(x);
	}
}

string MemorySimulator::read(short address){
	stringstream output;
	short begin_address;
	short tag;
	short offset;
	offset=address&0xF;
	tag=(address>>8)&0xFF;
	begin_address=address&0xFF0;
	if((memCache[(address&0xF0)>>4].isValid())&&(memCache[(address&0xF0)>>4].getTag()==tag)){
		output<<"At that byte there is the value "
			<<hex<<memCache[(address&0xF0)>>4].getVal(offset)
			<<" (Cache hit)"<<endl;
	}
	else if((memCache[(address&0xF0)>>4].getTag()!=tag)&&(memCache[(address&0xF0)>>4].isDirty())){
		pushBack(address&0xF0);
		for(short x=0x0; x<0x10; x++){
			memCache[(address&0xF0)>>4].writeVal(x, main_mem[begin_address+x]);
		}
		memCache[(address&0xF0)>>4].setTag(tag);
		output<<"At that byte there is the value "
			<<hex<<memCache[(address&0xF0)>>4].getVal(offset)
			<<" (Cache miss)"<<endl;
	}
	else{	
		for(short x=0x0; x<0x10; x++){
			memCache[(address&0xF0)>>4].writeVal(x, main_mem[begin_address+x]);
		}
		memCache[(address&0xF0)>>4].setTag(tag);
		output<<"At that byte there is the value "
			<<hex<<memCache[(address&0xF0)>>4].getVal(offset)
			<<" (Cache miss)"<<endl;
	}
	return output.str();
}

string MemorySimulator::write(short address, short newValue){
	stringstream output;
	short begin_address;
	short tag;
	short offset;
	offset=address&0xF;
	tag=(address>>8)&0xFF;
	begin_address=address&0xFF0;
	if((memCache[(address&0xF0)>>4].isValid())&&(memCache[(address&0xF0)>>4].getTag()==tag)){
		memCache[(address&0xF0)>>4].modVal(offset, newValue);
		output<<"Value "<<hex<<newValue<<" has been written to address "
			<<hex<<address<<" (Cache hit)"<<endl;
	}
	else if((memCache[(address&0xF0)>>4].isValid())&&(memCache[(address&0xF0)>>4].getTag()!=tag)){
		pushBack(address);
		for(short x=0x0; x<0x10; x++){
			memCache[(address&0xF0)>>4].writeVal(x, main_mem[begin_address+x]);
		}
		memCache[(address&0xF0)>>4].setTag(tag);
		memCache[(address&0xF0)>>4].modVal(offset, newValue);
		output<<"Value "<<hex<<newValue<<" has been written to address "
			<<hex<<address<<" (Cache miss)"<<endl;
	}
	else{	
		for(short x=0x0; x<0x10; x++){
			memCache[(address&0xF0)>>4].writeVal(x, main_mem[begin_address+x]);
		}
		memCache[(address&0xF0)>>4].setTag(tag);
		memCache[(address&0xF0)>>4].modVal(offset, newValue);
		output<<"Value "<<hex<<newValue<<" has been written to address "
			<<hex<<address<<" (Cache miss)"<<endl;
	}	
	return output.str();
}

string MemorySimulator::display(){
	stringstream output;
	output<<"Slot\tValid\tTag\t\tData"<<endl;
	for(short x=0x0; x<0x10; x++){
		output<<hex<<x<<'\t'<<memCache[x].display();
	}
	return output.str();
}