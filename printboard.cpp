#include <iostream>
#include "ConsolePrinter.h"
#include "Board.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
	//print board
	ConsolePrinter printer;
	Board board(argv[1]);
	printer.printBoard(board);
	//print hand
	Player p1("john", 7);
	/*Tile t1('a', 1);
	Tile t2('b', 2);
	Tile t3('c', 3);
	Tile* t1p = &t1;
	Tile* t2p = &t2;
	Tile* t3p = &t3;
	vector<Tile*> tiles;
	tiles.push_back(t1p);
	tiles.push_back(t2p);
	tiles.push_back(t3p);
	p1.addTiles(tiles);
	bool yes = false;
	bool can = p1.hasTiles("abc", yes);*/
	//cout << can << endl;
	//vector<Tile*> extile = p1.takeTiles("abc", yes);
	Dictionary dict(argv[3]);
	Bag mybag(argv[2], 1000);
	Player* p1p = &p1;
	vector<Tile*> temp = mybag.drawTiles(7);
	p1.addTiles(temp);
	printer.printHand(p1);
	//Move* mymove = new ExchangeMove("beo", p1p);
	//see if exchange works
	//mymove->execute(board, mybag, dict);
	//printer.printBoard(board);
	//printer.printHand(p1);
	//delete mymove;
	Move* mymove = new PlaceMove(8, 8, true, "beo", p1p);
	mymove->execute(board, mybag, dict);
	printer.printBoard(board);
	printer.printHand(p1);
	mymove = new PlaceMove(10,7, false, "?ht", p1p);
	mymove->execute(board, mybag, dict);
	printer.printBoard(board);
	printer.printHand(p1);
	mymove = new PlaceMove(11,7, true, "ax", p1p);
	mymove->execute(board,mybag,dict);
	printer.printBoard(board);
	printer.printHand(p1);
	mymove = new ExchangeMove("ahkio", p1p);
	mymove->execute(board,mybag,dict);
	printer.printBoard(board);
	printer.printHand(p1);
	mymove = new PlaceMove(12, 4, false, "hea", p1p);
	mymove->execute(board,mybag,dict);
	printer.printBoard(board);
	printer.printHand(p1);
	mymove = new PlaceMove(13, 4, true, "eeh", p1p);
	mymove->execute(board,mybag,dict);
	printer.printBoard(board);
	printer.printHand(p1);
}