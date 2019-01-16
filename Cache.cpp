#include "Cache.h"
#include <sstring>

using namespace std;

Cache::Cache{
	hit=false;
}

String Cache::read(short address){
	hit=false;
	
}

Cache::write(short address, short ){
	hit=false;

}

Cache::display(){
	sstring output;
	output<<"Slot\tValid\tTag\t\tData"<<endl;
	for(int x=0x0; x<0x10; x++){
		output<<hex<<x<<'\t'<<memCache[x].display();
	}
	return output.string();
}