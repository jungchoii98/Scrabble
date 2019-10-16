#include "Dictionary.h"
#include <fstream>

using namespace std;

Dictionary::Dictionary(std::string dictionary_file_name){
	ifstream iFile(dictionary_file_name.c_str());
	if(iFile.fail())
	{
		return;
	}

	string words = "";
	while(getline(iFile, words))
	{
		myset.insert(words);
	}

}

Dictionary::~Dictionary(){

}

bool Dictionary::isLegalWord (std::string const & word) const{
	std::set<string>::iterator it = myset.begin();
	string temp = "";
	for (int i = 0; (unsigned)i < word.length(); ++i)
	{
		temp += tolower(word[i]);
	}
	
	it = myset.find(temp);

	if(it == myset.end())
		return false;

	return true;
}

