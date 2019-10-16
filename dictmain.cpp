#include <iostream>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]){
	Dictionary dict(argv[1]);
	bool trueOfalse = false;
	string w("abasement");
	trueOfalse = dict.isLegalWord(w);
	cout << trueOfalse << endl;
}
