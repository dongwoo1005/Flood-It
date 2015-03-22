#include "cell.h"
using namespace std;

void Cell::notifyDisplay(){
	td->notify(r,c, '0' + state);
}

Cell::Cell(): state(0), prevState(0), numNeighbours(0), r(0), c(0), td(NULL){
	for (int i=0; i<maxNeighbours; ++i){
		neighbours[i] = NULL;
	}
}

char Cell::getState(){
	return '0' + state;
}

void Cell::setState(const int& change){
	prevState = state;
	state = change;
	notifyDisplay();
}

void Cell::setCoords(const int r, const int c){
	this->r = r;
	this->c = c;
}

void Cell::setDisplay(TextDisplay* t){
	td = t;
}

void Cell::addNeighbour(Cell *neighbour){
	neighbours[numNeighbours] = neighbour;
	numNeighbours++;
}

void Cell::notify(const int& change){
	setState(change);
	notify(state, prevState);
}

void Cell::notify(const int& current, const int& previous){
	for (int i=0; i<numNeighbours; ++i){
		if (neighbours[i]->state == previous) {
			neighbours[i]->setState(current);
			neighbours[i]->notify(current, previous);
		}
	}
}
