#include "cellb.h"
using namespace std;

void Cellb::notifyDisplay(){
	td->notify(r,c, '0' + state);
}

void Cellb::draw(){
	window->fillRectangle(x,y,width,height,state);
}

Cellb::Cellb(): state(0), prevState(0), numNeighbours(0), r(0), c(0), td(NULL), x(0), y(0), width(0),
	height(0), window(NULL){
	for (int i=0; i<maxNeighboursb; ++i){
		neighbours[i] = NULL;
	}
}

char Cellb::getState(){
	return '0' + state;
}

void Cellb::setState(const int& change){
	prevState = state;
	state = change;
	notifyDisplay();
	draw();
}

void Cellb::setCoords(const int r, const int c){
	this->r = r;
	this->c = c;
}

void Cellb::setCoords(int r, int c, int x, int y, int width, int height, Xwindow *w){
	this->r = r;
	this->c = c;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	window = w;
}

void Cellb::setDisplay(TextDisplay* t){
	td = t;
}

void Cellb::addNeighbour(Cellb *neighbour){
	neighbours[numNeighbours] = neighbour;
	numNeighbours++;
}

void Cellb::notify(const int& change){
	setState(change);
	notify(state, prevState);
}

void Cellb::notify(const int& current, const int& previous){
	for (int i=0; i<numNeighbours; ++i){
		if (neighbours[i]->state == previous) {
			neighbours[i]->setState(current);
			neighbours[i]->notify(current, previous);
		}
	}
}
