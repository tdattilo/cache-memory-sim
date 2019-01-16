#include <iostream>
#include <fstream>
#include <sstream>
#include "MemorySimulator.h"

using namespace std;

int main(){
	ofstream outFile;
	outFile.open("output.txt");
	MemorySimulator simulator;
	char function;
	short address;
	short value;

	while(!cin.eof()&&cin.good()){
		cout<<"(R)ead, (W)rite, or (D)isplay Cache?"<<endl;
		outFile<<"(R)ead, (W)rite, or (D)isplay Cache?"<<endl;
		cin>>function;
		function=toupper(function);
		outFile<<function<<endl;
		stringstream results;
		switch(function){
			case 'R':
				cout<<"What address would you like to read?"<<endl;
				outFile<<"What address would you like to read?"<<endl;
				cin>>hex>>address;
				outFile<<hex<<address<<endl;
				results<<simulator.read(address);
				cout<<results.str();
				outFile<<results.str();
				results.flush();
				break;
			case 'W':
				cout<<"What address would you like to write to?"<<endl;
				outFile<<"What address would you like to write to?"<<endl;
				cin>>hex>>address;
				outFile<<hex<<address<<endl;
				cout<<"What data would you like to write at that address?"<<endl;
				outFile<<"What data would you like to write at that address?"<<endl;
				cin>>hex>>value;
				results<<simulator.write(address, value);
				cout<<results.str();
				outFile<<results.str();
				results.flush();
				break;
			case 'D':
				results<<simulator.display();
				cout<<results.str();
				outFile<<results.str();
				results.flush();
				break;
			default:
				cout<<"Error! Not one of the three options. Please select again or input the EOF character to end."<<endl;
		}	
	}
	outFile.close();
	return 0;
}