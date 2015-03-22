#include "gridb.h"
using namespace std;

void Gridb::clearGrid(){
	for (int i=0; i<gridSize; ++i){
		delete [] theGrid[i];
	}
	delete [] theGrid;
}

Gridb::Gridb():gridSize(2){
	theGrid = new Cellb * [gridSize];
	for (int i=0; i<gridSize; ++i){
		theGrid[i] = new Cellb[gridSize];
	}
	td = NULL;
	theWindow = new Xwindow;	
}

Gridb::~Gridb(){
	clearGrid();
	delete td;
	delete theWindow;
}

bool Gridb::isWon(){
	if (td->isFilled()){
		cout << "Won" << endl;
		return true;
	} else {
		return false;
	}
}

void Gridb::init(int n){
	clearGrid();
	delete td;
	gridSize = n;
	int cellWidth = 500 / gridSize;
	td = new TextDisplay(gridSize);
	theGrid = new Cellb * [gridSize];
	for (int i=0; i<gridSize; ++i){
		theGrid[i] = new Cellb[gridSize];
	}
	for (int r=0; r<gridSize; ++r){
		for (int c=0; c<gridSize; ++c){
			theGrid[r][c].setCoords(r,c,c*cellWidth,r*cellWidth,cellWidth,cellWidth,theWindow);
			theGrid[r][c].setDisplay(td);
			if (r-1>=0){		// North Neighbour
				theGrid[r][c].addNeighbour(&theGrid[r-1][c]);	
			}
			if (c-1>=0){		// West Neighbour
				theGrid[r][c].addNeighbour(&theGrid[r][c-1]);
			}
			if (r+1<gridSize){	// South Neighbour
				theGrid[r][c].addNeighbour(&theGrid[r+1][c]);
			}
			if (c+1<gridSize){	// East Neighbour
				theGrid[r][c].addNeighbour(&theGrid[r][c+1]);
			}
		}
	}
}

void Gridb::change(const int & state){
	theGrid[0][0].notify(state);
}

void Gridb::init(int r, int c, int state){
	// if the triple is valid
	if (((r >= 0 && r < gridSize) && (c >= 0 && c < gridSize)) && (state >= 0 && state <= 4)){
		theGrid[r][c].setState(state);
	}
}

ostream& operator<<(ostream &out, const Gridb &g){
	out << *g.td;
	return out;
}
