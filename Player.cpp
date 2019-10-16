#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(std::string const & name, size_t maxTiles){
	pname = name;
	points = 0;
	maximumTiles = maxTiles;
}

Player::~Player(){
}

std::set<Tile*> Player::getHandTiles() const{
	return ptiles;
}

bool Player::hasTiles(std::string const & move, bool resolveBlanks) const{
	string themove = move;
	bool isBlanks = resolveBlanks;
	std::set<Tile*>::iterator temp = ptiles.begin();
	std::vector<Tile*> tempVec;
	for(; temp != ptiles.end(); temp++)
	{
		tempVec.push_back(*temp);
	}
	int ogtempVecsize = tempVec.size();
	//checks if the word is longer than the amount of tiles
	if(themove.size() > ptiles.size())
	{
		return false;
	}
	//checks if its PlaceMove
	std::vector<Tile*>::iterator it;
	if(isBlanks){
		for(int j=0; (unsigned)j<themove.size(); j++)
		{
			for(it = tempVec.begin(); it != tempVec.end(); ++it)
			{
				if(tolower(themove[j]) == (*it)->getLetter())
				{
					tempVec.erase(it);
					if(it == tempVec.end())
					{
						it--;
					}
					if(themove[j] == '?')
					{
						ogtempVecsize++;
						j++;
					}
					break;
				}
			}
			if (it == tempVec.end()) {
				return false;
			}
		}
	}
	//executes for ExchangeMove
	else
	{
		for(int j=0; (unsigned)j<themove.size(); j++)
		{
			for(it = tempVec.begin(); it != tempVec.end(); ++it)
			{
				if(tolower(themove[j]) == (*it)->getLetter())
				{
					tempVec.erase(it);
					break;
				}
			}
		}
	}
	//checks if PlaceMove is possible
	if(tempVec.size() == ogtempVecsize-move.size())
	{
		return true; 
	}
	if(tempVec.size() != ogtempVecsize-move.size())
	{
		throw invalidRequest("Error: invalid request");
	}

	return false;
}

std::vector<Tile*> Player::takeTiles (std::string const & move, bool resolveBlanks){
	string themove = move;
	string themovetwo = move;
	bool isBlanks = resolveBlanks;
	bool canMove = hasTiles(themove, isBlanks);
	vector<Tile*> playertiles;
	//enter if player has the right tiles and is PlaceMove
	if(isBlanks && canMove)
	{
		for(int i=0; i<(signed)themovetwo.size();)
		{
			for(std::set<Tile*>::iterator it = ptiles.begin(); it != ptiles.end(); ++it)
			{
				//eats the question mark and sets it as the next letter
				if((*it)->getLetter() == '?' && themovetwo[i] == '?')
				{	
					(*it)->useAs(themovetwo[i+1]);
					playertiles.push_back(*it);
					ptiles.erase(it);
					i += 2;
					break;

				}
				//if it isn't a question mark, normally push it
				else if((*it)->getLetter() == themovetwo[i])
				{
					playertiles.push_back(*it);
					ptiles.erase(it);
					i++;
					break;
				}
			}
		}
	}
	else if(!isBlanks && canMove)
	{
		for(int j=0; (unsigned)j<themovetwo.size(); j++)
		{
			for(std::set<Tile*>::iterator it = ptiles.begin(); it != ptiles.end(); ++it)
			{
				if((*it)->getLetter() == themovetwo[j])
				{
					//pushes the tile to the vector
					playertiles.push_back(*it);
					//erases the tile from our set
					ptiles.erase(it);
					break;
				}
			}
		}
	}
	return playertiles;
}

void Player::addTiles (std::vector<Tile*> const & tilesToAdd){
	if(ptiles.size() > maximumTiles)
	{
		//exception
	}
	for(int i=0; (unsigned)i<tilesToAdd.size(); i++)
	{
		ptiles.insert(tilesToAdd[i]);
	}
}

int Player::getPoints(){
	return points;
}

void Player::addPoints(int amount){
	points += amount;
}

const size_t Player::getMaxTiles() const{
	return maximumTiles;
}

std::string Player::getName(){
	return pname;
}