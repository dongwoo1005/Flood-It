#include "textdisplay.h"
using namespace std;

// Refer to testdisplay.h for implementation details

TextDisplay::TextDisplay(int n): gridSize(n){
	theDisplay = new char*[gridSize];
	for (int i=0; i<gridSize; ++i){
		theDisplay[i] = new char[gridSize];
	} // end for
	for (int r=0; r<gridSize; ++r){
		for( int c=0; c<gridSize; ++c){
			theDisplay[r][c] = '0';
		} // end for
	} // end for

	colourCount[0] = gridSize * gridSize;
	for (int i=1; i<5; ++i){
		colourCount[i] = 0;
	} // end for
}

void TextDisplay::notify(int r, int c, char ch){
	int prevState = theDisplay[r][c] - '0';
	int currState = ch - '0';
	theDisplay[r][c] = ch;
	colourCount[prevState]--;
	colourCount[currState]++;
	
}

bool TextDisplay::isFilled(){
	for (int i=0; i<5; ++i){
		if (colourCount[i] == (unsigned)gridSize*gridSize){
			return true;
		} // end if
	} // end for
	return false;
}

TextDisplay::~TextDisplay(){
	for (int i=0; i<gridSize; ++i){
		delete [] theDisplay[i];
	} // end for
	delete [] theDisplay;
}

ostream& operator<<(ostream &out, const TextDisplay &td){
	for (int r=0; r < td.gridSize; ++r){
		for (int c=0; c < td.gridSize; ++c){
			out << td.theDisplay[r][c];
		} // end for
		out << endl;
	} // end for
	return out;
}
