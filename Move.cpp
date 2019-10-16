#include "Move.h"
#include "Board.h"
#include <iostream>

using namespace std;


Move * Move::parseMove(std::string moveString, Player &p){
	std::string type;
	std::string tstring;
	int x, y;
	char direction;
	bool horiz;
	Move* mymove;
	Player* myplayer = &p;
	//puts everything to lower case
	for(int i=0; (unsigned)i<moveString.size(); i++)
	{
		moveString[i] = tolower(moveString[i]);
	}
	std::stringstream ss(moveString);
	ss >> type;
	//creates different move objects
	if(type == "pass")
	{
		mymove = new PassMove(myplayer);
	}
	else if(type == "exchange")
	{
		ss >> tstring;
		mymove = new ExchangeMove(tstring, myplayer);
	}
	else if(type == "place")
	{
		ss >> direction >> x >> y >> tstring;
		if(direction == '-')
		{
			horiz = true;
		}
		else 
		{
			horiz = false;
		}
		mymove = new PlaceMove(x, y, horiz, tstring, myplayer);
	}
	return mymove;
}

Move::Move(Player * player){
	_player = player;
}

Move::~Move(){
	
}

void PassMove::execute(Board & board, Bag & bag, Dictionary & dictionary){
	return;
}

PassMove::PassMove(Player * player) : Move(player) {
	_player = player;
}

ExchangeMove::ExchangeMove(std::string tileString, Player * p) : Move(p) {
	input = tileString;
}

void ExchangeMove::execute(Board & board, Bag & bag, Dictionary & dictionary){
	std::vector<Tile*> tileAdd;
	std::vector<Tile*> tileputBack;
	bool canOccur = _player->hasTiles(input, false);
	//if has tile returns true, exchange the tiles
	if(canOccur)
	{
		tileAdd = _player->takeTiles(input, false);
		bag.addTiles(tileAdd);
		tileputBack = bag.drawTiles(input.size());
		_player->addTiles(tileputBack);
	}
	else
	{
		throw invalidRequest("Error: invalid request");
	}
}

PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p) : Move(p){
	xcor = x;
	ycor = y;
	isHoriz = horizontal;
	input = tileString;
	_player = p;
	add = _player->takeTiles(tileString, true);
	
}

std::vector<Tile*> const & PlaceMove::tileVector () const{
	return add;
}

void PlaceMove::execute(Board & board, Bag & bag, Dictionary & dictionary){
	bool validword = true;
std::vector<std::pair<std::string, unsigned int>> vec;
	//try and catch the different types of errors and give players their tiles back
	try
	{
		 vec = board.getPlaceMoveResults(*this);
	}
	catch(notvalidstart& f)
	{
		_player->addTiles(this->tileVector());
		throw notvalidstart("Error: Not a valid start");
	}
	catch(outofbounds& f)
	{
		_player->addTiles(this->tileVector());
		throw outofbounds("Error: It is out of bounds");
	}
	catch(invalidplacement& f)
	{
		_player->addTiles(this->tileVector());
		throw invalidplacement("Error: invalid placement");
	}
	catch(alreadypicked& f)
	{
		_player->addTiles(this->tileVector());
		throw alreadypicked("Error: This square has already been picked");
	}
	//checks if the word is legal for everything in the vector
	for(int i=0; (unsigned)i<vec.size(); i++)
	{
		if(!(dictionary.isLegalWord(vec[i].first)))
		{
			validword = false;
		}
	}
	//if its a valid word, give players the points
	if(validword)
	{
		for(int i=0; (unsigned)i<vec.size(); i++)
		{
			_player->addPoints(vec[i].second);
		}
		board.executePlaceMove(*this);
		std::vector<Tile*> putback = bag.drawTiles(add.size());
		//if everything runs right give player tile back
		_player->addTiles(putback);
	}
	//if its not valid, then throw
	else
	{
		//give back tiles and throw
		_player->addTiles(this->tileVector());
		throw notvalidword("Error: Not a valid word");
	}
}

int PlaceMove::getxcor() const{
	return xcor;
}

int PlaceMove::getycor() const{
	return ycor;
}

bool PlaceMove::getHoriz() const{
	return isHoriz;
}

std::string PlaceMove::getString() const{
	return input;
}

Player* PlaceMove::getPlayer(){
	return _player;
}

