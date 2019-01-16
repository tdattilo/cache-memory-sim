#include <sstream>
#include "CacheRow.h"
using namespace std;

CacheRow::CacheRow(){
	dirty=false;
	valid=false;
	tag=0x0;
	for(int x=0x0; x<0x10; x++){
		values[x]=0x0;
	}
}
string CacheRow::display(){
	stringstream output;
	output<<hex<<valid<<'\t'<<hex<<tag<<'\t'<<'\t';
	for(int x=0x0; x<0x10; x++){
		output<<hex<<values[x]<<'\t';
	}
	output<<endl;
	return output.str();
}
bool CacheRow::isValid(){
	return valid;
}
bool CacheRow::isDirty(){
	return dirty;
}
short CacheRow::getTag(){
	return tag;
}
void CacheRow::setTag(short val){
	tag=val;
}
short CacheRow::getVal(short slot){
	return values[slot];
}
void CacheRow::writeVal(short slot, short val){
	if(!valid){
		valid=true;
	}
	if(dirty){
		dirty=false;
	}
	values[slot]=val;
}
void CacheRow::modVal(short slot, short newVal){
	if(!dirty){
		dirty=true;
	}
	values[slot]=newVal;
}