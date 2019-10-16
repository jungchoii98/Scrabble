#include <iostream>
#include <set>
#include <vector>
#include "Player.h"
#include "Tile.h"

using namespace std;

int main(){
	Player p1("john", 7);
	Tile t1('a', 1);
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
	bool can = p1.hasTiles("abc", yes);
	cout << can << endl;
	vector<Tile*> extile = p1.takeTiles("abc", yes);
	for(int i=0; i<extile.size(); i++)
	{
		cout << (extile[i])->getLetter() << endl;
	}
	set<Tile*> playerset = p1.getHandTiles();
	for(std::set<Tile*>::iterator it = playerset.begin(); it != playerset.end(); ++it)
	{
		cout << (*it)->getLetter() << endl;;
	}
	/*vector<Tile*> newtile;
	Tile t4('d', 4);
	Tile t5('e', 5);
	Tile t6('f', 6);
	Tile* t4p = &t4;
	Tile* t5p = &t5;
	Tile* t6p = &t6;
	newtile.push_back(t4p);
	newtile.push_back(t5p);
	newtile.push_back(t6p);
	p1.addTiles(newtile);
	can = p1.hasTiles("def", yes);
	cout << can << endl;
	extile = p1.takeTiles("def", yes);
	for(int i=0; i<extile.size(); i++)
	{
		cout << (extile[i])->getLetter() << endl;
	}*/
	return 0;
}