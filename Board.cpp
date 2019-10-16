#include "Board.h"
#include <iostream>

using namespace std;

Board::Board (std::string board_file_namey){
	std::ifstream bFile(board_file_namey);
	bFile >> columns >> rows >> xstart >> ystart;
	gameBoard = new Square**[columns];
	char converter;
	std::string line;
	getline(bFile, line);
	bool start = false;
	for(int i=0; i<rows; i++)
	{
		gameBoard[i] = new Square*[columns];
	}
	for(int i=0; i<rows; i++)
	{
		getline(bFile, line);
		std::stringstream ss(line);
		for(int j=0; j<columns; j++)
		{
			if(xstart-1 == j && ystart-1 == i)
			{
				start = true;
			}
			ss >> converter;
			if(converter == '.')
			{
				gameBoard[i][j] = new Square(1, 1, start);
			}
			else if(converter == '2')
			{
				gameBoard[i][j] = new Square(2, 1, start);
			}
			else if(converter == '3')
			{
				gameBoard[i][j] = new Square(3, 1, start);
			}
			else if(converter == 'd')
			{
				gameBoard[i][j] = new Square(1, 2, start);
			}
			else if(converter == 't')
			{
				gameBoard[i][j] = new Square(1, 3, start);
			}
			start = false;
		}
	}
}

Board::~Board(){
	
	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < columns; j++) {

			delete gameBoard[i][j];
		}
		delete [] gameBoard[i];
	}
	delete [] gameBoard;

}

std::vector<std::pair<std::string, unsigned int>> Board::getPlaceMoveResults(const PlaceMove &m) const{
	std::string newInput = m.getString();
	int newxcor = m.getxcor();
	int newycor = m.getycor();
	bool newHoriz = m.getHoriz();
	bool startcheckone = false;
	bool startchecktwo = false;
	int wordtotal = 0;
	bool isAdjacent = false;
	std::string temp = "";
	std::vector<std::pair<std::string, unsigned int>> pushVec;
	std::vector<Tile*> place = m.tileVector();
	//checks if the coordinates the user chooses have already been picked
	if(gameBoard[newxcor-1][newycor-1]->isOccupied())
	{
		throw alreadypicked("Error: This square has already been picked");
	}
	//checks if it is the starting move
	if(gameBoard[xstart-1][ystart-1]->isOccupied())
	{
		startcheckone = true;
	}
	//if start square not occupied
	if(!startcheckone)
	{
		//check if the player places tile on start square horizontally
		if(newHoriz)
		{
			for(int i=0; (unsigned)i<place.size(); i++)
			{
				if(newxcor+i == xstart && newycor == ystart && newxcor+i <= columns)
				{
					startchecktwo = true;
				}
			}
		}
		//check if the player places tile on start square vertically
		else
		{
			for(int i=0; (unsigned)i<place.size(); i++)
			{
				if(newxcor == xstart && newycor+i == ystart && newycor+i <= rows)
				{
					startchecktwo = true;
				}
			}
		}
		//throw because player did not make valid start move and give back tiles
		if(!startchecktwo)
		{
			throw notvalidstart("Error: Not a valid start");
		}
		else
		{
			//calculate the starting word and return
			for(int i=0; (unsigned)i<place.size(); i++)
			{
				wordtotal += place[i]->getPoints();
				temp += place[i]->getLetter();
			}
			std::pair<std::string, unsigned int> pushPairthree(temp, wordtotal);
			pushVec.push_back(pushPairthree);
			return pushVec;
		}
	}

	//checks if the tile is adjacent to another word
	if(newHoriz)
	{
		//iterates horizontally and checks the surrounding of every tile
		for(int i=0; (unsigned)i<place.size(); i++)
		{
			//checks if the tiles go out of bounds
			if(newxcor+i > columns)
			{
				throw outofbounds("Error: It is out of bounds");
			}
			if(newxcor+i == columns)
			{
				if(gameBoard[newxcor-1-1+i][newycor-1]->isOccupied()
				|| gameBoard[newxcor-1+i][newycor-1-1]->isOccupied() || gameBoard[newxcor-1+i][newycor-1+1]->isOccupied())
				{
					isAdjacent = true;
				}
			}
			else if(newxcor-1 == 1)
			{
				if(gameBoard[newxcor-1+1+i][newycor-1]->isOccupied()
				|| gameBoard[newxcor-1+i][newycor-1-1]->isOccupied() || gameBoard[newxcor-1+i][newycor-1+1]->isOccupied())
				{
					isAdjacent = true;
				}
			}
			else if(newycor == 1)
			{
				if(gameBoard[newxcor-1-1+i][newycor-1]->isOccupied() || gameBoard[newxcor-1+1+i][newycor-1]->isOccupied()
				|| gameBoard[newxcor-1+i][newycor-1+1]->isOccupied())
				{
					isAdjacent = true;
				}
			}
			else if(newycor == rows)
			{
				if(gameBoard[newxcor-1-1+i][newycor-1]->isOccupied() || gameBoard[newxcor-1+1+i][newycor-1]->isOccupied()
				|| gameBoard[newxcor-1+i][newycor-1-1]->isOccupied())
				{
					isAdjacent = true;
				}
			}
			else if(gameBoard[newxcor-1-1+i][newycor-1]->isOccupied() || gameBoard[newxcor-1+1+i][newycor-1]->isOccupied()
				|| gameBoard[newxcor-1+i][newycor-1-1]->isOccupied() || gameBoard[newxcor-1+i][newycor-1+1]->isOccupied())
			{
				isAdjacent = true;
			}
		}
	}
	else
	{
		//iterates vertically and checks the surrounding of every tile
		for(int i=0; (unsigned)i<place.size(); i++)
		{
			if(newycor+i > rows)
			{
				throw outofbounds("Error: It is out of bounds");
			}
			if(newycor+i == rows)
			{
				if(gameBoard[newxcor-1][newycor-1-1+i]->isOccupied() 
				|| gameBoard[newxcor-1-1][newycor-1+i]->isOccupied() || gameBoard[newxcor-1+1][newycor-1+i]->isOccupied())
				{
					isAdjacent = true;
				}
			}
			else if(newycor-1 == 1)
			{
				if(gameBoard[newxcor-1][newycor-1+1+i]->isOccupied()
				|| gameBoard[newxcor-1-1][newycor-1+i]->isOccupied() || gameBoard[newxcor-1+1][newycor-1+i]->isOccupied())
				{
					isAdjacent = true;
				}
			}
			else if(newxcor == columns)
			{
				if(gameBoard[newxcor-1][newycor-1-1+i]->isOccupied() || gameBoard[newxcor-1][newycor-1+1+i]->isOccupied()
				|| gameBoard[newxcor-1-1][newycor-1+i]->isOccupied())
				{
					isAdjacent = true;
				}
			}
			else if(newxcor == 1)
			{
				if(gameBoard[newxcor-1][newycor-1-1+i]->isOccupied() || gameBoard[newxcor-1][newycor-1+1+i]->isOccupied()
				|| gameBoard[newxcor-1+1][newycor-1+i]->isOccupied())
				{
					isAdjacent = true;
				}
			}
			else if(gameBoard[newxcor-1][newycor-1-1+i]->isOccupied() || gameBoard[newxcor-1][newycor-1+1+i]->isOccupied()
				|| gameBoard[newxcor-1-1][newycor-1+i]->isOccupied() || gameBoard[newxcor-1+1][newycor-1+i]->isOccupied())
			{
				isAdjacent = true;
			}
		}
	}
	//if bool flag is still false, invalid placement
	if(isAdjacent == false)
	{
		throw invalidplacement("Error: invalid placement");
	}

	if(newHoriz)
	{
		//checks vertical words that the horizontal word makes
		for(int i=0; (unsigned)i<place.size(); i++)
		{
			int j = 0;
			temp = "";
			wordtotal = 0;
			bool flag = false;
			//checks if the tile is out of bounds
			if((unsigned)newxcor+place.size()-1 > (unsigned)columns)
			{
				throw outofbounds("Error: It is out of bounds");
			}
			//skips over occupied squares
			if(gameBoard[newxcor-1+i][newycor-1]->isOccupied())
			{
				continue;
			}
			//keeps track of the starting position of the word
			while(gameBoard[newxcor-1+i][newycor-2+j]->isOccupied() && newycor+j-1 != 0)
			{
				j--;
			}
			if(j == 0)
			{
				temp += place[i]->getLetter();
			}
			else if(j < 0)
			{
				flag = true;
			}
			//calculate the score and creates the string
			while(gameBoard[newxcor-1+i][newycor-1+j]->isOccupied() && newycor+j-1 >= 1 && newycor+j+1 <=rows)
			{
				temp += gameBoard[newxcor-1+i][newycor-1+j]->getLetter();
				wordtotal += gameBoard[newxcor-1+i][newycor-1+j]->getScore();
				j++;
			}
			if(flag)
			{
				temp += place[i]->getLetter();
			}
			//pushes if the word is larger than a single letter
			if(temp.size() > 1 /*|| place[i]->getLetter() == 'a'*/)
			{
				std::pair<std::string, unsigned int> pushPair(temp, wordtotal);
				pushVec.push_back(pushPair);
			}
		}
		//checks the actual word
		int i=0;
		wordtotal = 0;
		temp = "";
		int wordMultiplier = 1;
		//finds the starting position of the word
		while(gameBoard[newxcor-2+i][newycor-1]->isOccupied() && newxcor+i-1 >= 1)
		{
			i--;
		}
		int vectorCounter = 0;
		//if the square is occupied and not all tiles have been accounted for
		while((gameBoard[newxcor-1+i][newycor-1]->isOccupied() || place.size() != (unsigned)vectorCounter))
		{
			int lettertotal = 0;
			if(!(gameBoard[newxcor-1+i][newycor-1]->isOccupied()))
			{
				//calculate the string and score/multipliers, iterates to keep track of how many tiles are left
				lettertotal = place[vectorCounter]->getPoints()*gameBoard[newxcor-1+i][newycor-1]->getLMult();
				wordMultiplier *= gameBoard[newxcor-1+i][newycor-1]->getWMult();
				wordtotal += lettertotal;
				if(place[vectorCounter]->getLetter() == '?')
				{
					temp += place[vectorCounter]->getUse();
				}
				else
				{
					temp += place[vectorCounter]->getLetter();
				}
				vectorCounter++;
				i++;
				if(newxcor+i > columns)
				{
					break;
				}
			}
			//if the square is not occupied
			else
			{
				//calculate the string and score
				wordtotal += gameBoard[newxcor-1+i][newycor-1]->getScore();
				temp += gameBoard[newxcor-1+i][newycor-1]->getLetter();
				i++;
				if(newxcor+i > columns)
				{
					break;
				}
			}
		}
		//calculate the total word score
		wordtotal *= wordMultiplier;
		std::pair<std::string, unsigned int> pushPairtwo(temp, wordtotal);
		pushVec.push_back(pushPairtwo);
		return pushVec;
	}
	//if its a vertical word
	else
	{
		for(int i=0; (unsigned)i<place.size(); i++)
		{
			int j = 0;
			temp = "";
			wordtotal = 0;
			bool flag = false;
			//throw if out of bounds
			if((unsigned)newycor+place.size()-1 > (unsigned)rows)
			{
				throw outofbounds("Error: It is out of bounds");
			}
			//starts back at top if it is occupied
			if(gameBoard[newxcor-1][newycor-1+i]->isOccupied())
			{
				continue;
			}
			//get the starting position
			while(gameBoard[newxcor-2+j][newycor-1+i]->isOccupied() && newxcor+j-1 != 0)
			{
				j--;
			}
			if(j == 0)
			{
				temp += place[i]->getLetter();
			}
			else if(j < 0)
			{
				flag = true;
			}
			while(gameBoard[newxcor-1+j][newycor-1+i]->isOccupied() && newxcor+j-1 >= 1 && newxcor+j+1 <=columns)
			{
				temp += gameBoard[newxcor-1+j][newycor-1+i]->getLetter();
				wordtotal += gameBoard[newxcor-1+j][newycor-1+i]->getScore();
				j++;
			}
			if(flag)
			{
				temp += place[i]->getLetter();
			}
			if(temp.size() > 1 /*|| place[i]->getLetter() == 'a'*/)
			{
				std::pair<std::string, unsigned int> pushPair(temp, wordtotal);
				pushVec.push_back(pushPair);
			}
		}
		//everything works the same as the horizontal orientation except flipped
		int i=0;
		wordtotal = 0;
		temp = "";
		int wordMultiplier = 1;
		while(gameBoard[newxcor-1][newycor-2+i]->isOccupied() && newycor+i-1 >= 1)
		{
			i--;
		}
		int vectorCounter = 0;
		while((gameBoard[newxcor-1][newycor-1+i]->isOccupied() || place.size() != (unsigned)vectorCounter))
		{
			int lettertotal = 0;
			if(!(gameBoard[newxcor-1][newycor-1+i]->isOccupied()))
			{
				lettertotal = place[vectorCounter]->getPoints()*gameBoard[newxcor-1][newycor-1+i]->getLMult();
				wordMultiplier *= gameBoard[newxcor-1][newycor-1+i]->getWMult();
				wordtotal += lettertotal;
				if(place[vectorCounter]->getLetter() == '?')
				{
					temp += place[vectorCounter]->getUse();
				}
				else
				{
					temp += place[vectorCounter]->getLetter();
				}
				vectorCounter++;
				i++;
				if(newycor+i > rows)
				{
					break;
				}
			}
			else
			{
				wordtotal += gameBoard[newxcor-1][newycor-1+i]->getScore();
				temp += gameBoard[newxcor-1][newycor-1+i]->getLetter();
				i++;
				if(newycor+i > rows)
				{
					break;
				}
			}
		}
		wordtotal *= wordMultiplier;
		std::pair<std::string, unsigned int> pushPairtwo(temp, wordtotal);
		pushVec.push_back(pushPairtwo);
		return pushVec;
	}
}

void Board::executePlaceMove (const PlaceMove & m){
	std::string newInput = m.getString();
	int newxcor = m.getxcor();
	int newycor = m.getycor();
	bool newHoriz = m.getHoriz();
	std::vector<Tile*> newVec = m.tileVector();
	std::vector<Tile*>::iterator it = newVec.begin();
	Tile* temp;
	int i=0;
	int vecIt=0;
	if(newHoriz)
	{
		while(it != newVec.end()){
			//if the tile is not occupied, place tile
			if(!(gameBoard[newxcor-1+i][newycor-1]->isOccupied()))
			{
				temp = newVec[vecIt];
				gameBoard[newxcor-1+i][newycor-1]->placeTile(temp);
				vecIt++;
				++it;
				i++;
			}	
			//else just skip over it
			else
			{
				i++;
			}
		}
	}
	else
	{
		//same as the horizontal orientation except its flipped
		while(it != newVec.end()){
			if(!(gameBoard[newxcor-1][newycor-1+i]->isOccupied()))
			{
				temp = newVec[vecIt];
				gameBoard[newxcor-1][newycor-1+i]->placeTile(temp);
				vecIt++;
				++it;
				i++;
			}
			else
			{
				i++;
			}
		}
	}
}

size_t Board::getRows() const{
	return rows;
}

size_t Board::getColumns() const{
	return columns;
}

Square * Board::getSquare (size_t x, size_t y) const{
	return gameBoard[x-1][y-1];
}
