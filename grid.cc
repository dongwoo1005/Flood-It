#include "grid.h"
using namespace std;

void Grid::clearGrid(){
	for (int i=0; i<gridSize; ++i){
		delete [] theGrid[i];
	}
	delete [] theGrid;
}

Grid::Grid():gridSize(2){
	theGrid = new Cell * [gridSize];
	for (int i=0; i<gridSize; ++i){
		theGrid[i] = new Cell[gridSize];
	}
	td = NULL;
}

Grid::~Grid(){
	clearGrid();
	delete td;
}

bool Grid::isWon(){
	if (td->isFilled()){
		cout << "Won" << endl;
		return true;
	} else {
		return false;
	}
}

void Grid::init(int n){
	clearGrid();
	delete td;
	gridSize = n;
	td = new TextDisplay(gridSize);
	theGrid = new Cell * [gridSize];
	for (int i=0; i<gridSize; ++i){
		theGrid[i] = new Cell[gridSize];
	}
	for (int r=0; r<gridSize; ++r){
		for (int c=0; c<gridSize; ++c){
			theGrid[r][c].setCoords(r,c);
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

void Grid::change(const int & state){
	theGrid[0][0].notify(state);
}

void Grid::init(int r, int c, int state){
	// if the triple is valid
	if (((r >= 0 && r < gridSize) && (c >= 0 && c < gridSize)) && (state >= 0 && state <= 4)){
		theGrid[r][c].setState(state);
	}
}

ostream& operator<<(ostream &out, const Grid &g){
	out << *g.td;
	return out;
}
