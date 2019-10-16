#include "Board.h"
#include "Move.h"
#include "ConsolePrinter.h"
#include "Tile.h"
#include "Dictionary.h"
#include "Bag.h"
#include "Exceptions.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
	ifstream configFile(argv[1]);
	int maxHand = 0;
	int seed = 0;
	string board;
	string bag;
	string dict;
	string line;
	vector<Player> players;
	//stores the values 
	while(configFile>>line)
	{
		if(line == "HANDSIZE:")
		{
			configFile >> maxHand;
		}
		else if(line == "TILES:")
		{
			configFile >> bag;
		}
		else if(line == "DICTIONARY:")
		{
			configFile >> dict;
		}
		else if(line == "BOARD:")
		{
			configFile >> board;
		}
		else if(line == "SEED:")
		{
			configFile >> seed;
		}
	}
	//create game piece variables
	Dictionary dictionary(dict);
	Board gameBoard(board);
	Bag mybag(bag, (uint32_t)seed);
	ConsolePrinter printer;
	cout << "Enter number of players 1-8" << endl;
	int numPlayers = 0;
	cin >> numPlayers;
	//gets all the players
	for(int i=0; i<numPlayers; i++)
	{
		cout << "Enter player name" << endl;
		cin >> line;
		Player individual(line, maxHand);
		vector<Tile*> hand = mybag.drawTiles(maxHand);
		individual.addTiles(hand);
		players.push_back(individual);
	}
	

	printer.printBoard(gameBoard);
	getline(cin,line);

	bool playGame = true;
	int consecutivepassCounter = 0;
	//starts our game loop
	while(playGame)
	{
		for(int i = 0; (unsigned)i<players.size(); i++)
		{
			printer.printHand(players[i]);
			cout << players[i].getName() << ", " << "Please enter your move" << endl;
			getline(cin,line);
			Move* move;
			//execute  the moves while catching exceptions
			try
			{
				move = Move::parseMove(line,players[i]);
			}
			catch(invalidRequest& f)
			{
				cout << f.getMessage() << endl;
				i--;
			}
			if(move->isPass())
			{
				consecutivepassCounter++;
				cout << consecutivepassCounter << endl;
			}
			else
			{
				consecutivepassCounter = 0;
			}
			try
			{
				move->execute(gameBoard, mybag, dictionary);
				printer.printBoard(gameBoard);
			}
			catch(invalidRequest& f)
			{
				cout << f.getMessage() << endl;
				i--;
			}
			catch(notvalidstart& f)
			{
				cout << f.getMessage() << endl;
				i--;
			}
			catch(outofbounds& f)
			{
				cout << f.getMessage() << endl;
				i--;
			}
			catch(invalidplacement& f)
			{
				cout << f.getMessage() << endl;
				i--;
			}
			catch(notvalidword& f)
			{
				cout << f.getMessage() << endl;
				i--;
			}
			catch(alreadypicked& f)
			{
				cout << f.getMessage() << endl;
				i--;
			}
			for(int j=0; (unsigned)j<players.size(); j++)
			{
				cout << '\n' << '\n' << players[j].getName() << "'s score is: " << players[j].getPoints() << endl;
			}
			delete move;
			line = "";
			//conditions to check if the game is finished
			if((mybag.tilesRemaining() == 0 && (players[i].getHandTiles()).size() == 0) || (unsigned)consecutivepassCounter == players.size())
			{
				playGame = false;
				break;
			}
		}
	}

	int max = 0;
	int maxCounter = 1;
	bool multiplewinners = false;
	//finds the number of winners
	for(int i=0; (unsigned)i<players.size(); i++)
	{
		if(players[i].getPoints() > max)
		{
			max = players[i].getPoints();
			maxCounter = 1;
		}
		else if(players[i].getPoints() == max)
		{
			maxCounter++;
		}
	}
	//checks if there is a singular winner or many winners
	if(maxCounter > 1)
	{
		multiplewinners = true;
	}
	//prints the singular winner
	if(!multiplewinners)
	{
		for(int i=0; (unsigned)i<players.size(); i++)
		{
			if(players[i].getPoints() == max)
			{
				cout << "Winner: " << players[i].getName();
			}
		}
	}
	//prints the multiple winners
	else
	{
		cout << "Winners: ";
		for(int i=0; (unsigned)i<players.size(); i++)
		{
			if(players[i].getPoints() == max)
			{
				cout << players[i].getName() << " ";
			}
		}
	}
	//deletes the players hand
	for (unsigned int i = 0; i < players.size(); ++i) {

		std::set<Tile*> hand_temp = players[i].getHandTiles();

		for(std::set<Tile*>::iterator it = hand_temp.begin(); it != hand_temp.end(); ++it)
		{
			delete (*it);
		}
	}
	cout << endl;
	return 0;
}