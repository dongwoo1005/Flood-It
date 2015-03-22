#include "textdisplay.h"
#include "cell.h"
#include "cellb.h"
#include "grid.h"
#include "gridb.h"
#include "window.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
// Note:
// Created a seprate classes of Cellb and Gridb in cellb.h and gridb.h respectively.
// These were created to make difference between the grid when the Graphicmode is ON and OFF.
// (since the assignment did not allow us to create any public field/method other than provided,
// I created the new classes as above to implement graphical grid instead of creating Grid(*Xwindow)
// to make difference between graphical display and texture display.

using namespace std;

// Flood It, a one player game
// Written by Dongwoo Son
// Written for CS246 a4q2bb
// on March 20, 2015

int main(int argc, char* argv[]){
	// to check if the graphicmode (-graphicps) is turned on
	bool isGraphicmode;
	if (argc == 2) {
		string mode = argv[1];
		if (mode == "-graphics"){
			isGraphicmode = true;
		}
	} else if (argc == 1){
		isGraphicmode = false;
	} else {
		cerr << "Invalid Argument" << endl;
		return 0;
	}
	// to track if the program is done
	bool done = false;
	// to track if the command game is called
	bool gameCalled = false;
	// to track if the command new is called
	bool newCalled = false;
	int g; // game count;

	
	// Graphic mode OFF
	if (!isGraphicmode){
		// Initializes the Grid for no graphic mode
		Grid grid;
		while(!done){
			// to track if invalid input is received
			bool invalid = false;
			// take command from cin
			string command;
			cin >> command;
			// terminate if the input is exhausted
			if (cin.eof()) break;


			// new n command
			if (command == "new"){
				// new cannot be called once game is called
				if (gameCalled){
					cerr << "game was already called" << endl;
					invalid = true;
				} // end if
				else {
					int n;
					cin >> n;
					// Creates a new n x n Grid, where n>=2
					if (!cin.fail() && n>=2){
						grid.init(n);
						newCalled = true;
					} // end if 
					else {
						invalid = true;
					} // end else
				} // end else
			} // end if for new command


			// init command
			else if (command == "init"){
				// init cannot be called if new is not called
				if (newCalled == false){
					cerr << "new was not called" << endl;
					invalid = true;
				}
				// Enters init mode
				// reads triple of integer r c s
				else {
					int r, c, state;
					while (1){
						cin >> r >> c;
						if (!cin.fail()){
							// coordinate -1 -1 ends the init mode
							if (r == -1 && c == -1){
								cout << grid;
								// if it was called during the game, check if the game ended
								if (gameCalled) {
									if (grid.isWon()) done = true;
								} // end if
								break;
							} // end if
							cin >> state;
							// sets the cell at row, column c to state s
							if (!cin.fail()){
								grid.init(r,c,state);
							} // end if
							else{
								invalid = true;
								break;
							} // end else
						} // end if
						else {
							invalid = true;
							break;
						} // end else
					} // end while
				} // end else	
			} // end else if for init command


			// include f command
			else if (command == "include"){
				// include cannot be called if new is not called
				if (!newCalled){
					invalid = true;
				} // end if

				// reads the file f
				string filename;
				cin >> filename;
				ifstream file(filename.c_str());

				if (file.fail()){
					invalid = true;
				} // end if
				else{
					int r, c, state;
					while (1){
						// reads the triple r c s
						// and finish the reading when -1 -1 is read
						file >> r >> c;
						if (!file.fail()){
							if (r == -1 && c == -1){
								cout << grid;
								// if it was during the game check if the game ended
								if (gameCalled){
									if (grid.isWon()) done = true;
								} // end if
								break;
							} // end if
							file >> state;
							// sets the cell at row r, column c to state s
							if (!file.fail()){
								grid.init(r,c,state);
							} // end if
							else {
								invalid = true;
								break;
							} // end else
						} // end if
						else {
							// finish the reading at the end of file
							if (file.eof()){
								cout << grid;
								// if it was during the game check if the game ended
								if (gameCalled){
									if (grid.isWon()) done = true;
								} // end if
								break;
							} // end if
							else {
								invalid = true;
								break;
							} // end else
						} // end else
					} // end while
				} // end else
			} // end else if for include command


			// game g command
			else if (command == "game"){
				// game cannot be called if game is called already or new is not called
				if(!newCalled || gameCalled){
					invalid = true;
				} // end if
				else {
					// save the number of moves allowed in the game
					cin >> g;
					// print out the moves left and check the winning condition
					if (!cin.fail()){
						if (g == 1){
							cout << g << " move left" << endl;
						} // end if
						else{
							cout << g << " moves left" << endl;
						} // end else
						if (grid.isWon()){
							done = true;
						} // end if
					} // end if
					else {
						invalid = true;
					} // end else
					// starts a new game
					gameCalled = true;
				} // end else
			} // end else if for game g command

			
			// switch s command
			else if (command == "switch"){
				// cannot be called if the game has not started
				if(!gameCalled){
					cerr << "game was not called" << endl;
					invalid = true;
				} // end if
				else {
					int state2;
					cin >> state2;
					if (!cin.fail()){
						// invalid state s
						if (state2 > 4) {
							cerr << "given state is greater than 4" << endl;
							invalid = true;
						} // end if
						// switch the top-left (0,0) cell to s, changing all appropriate neighbours
						// then redisplays the grid
						// and print out the result
						else {
							grid.change(state2);
							cout << grid;
							g--;
							if (g == 1){
								cout << g << " move left" << endl;
								if (grid.isWon()){
									done = true;
								} // end if
							} // end if 
							else {
								cout << g << " moves left" << endl;
								if (grid.isWon()){
									done = true;
								} // end if
								else if (g == 0){
									cout << "Lost" << endl;
									done = true;
								} // end else if
							} // end else
						} // end else
					} // end if
					else {
						cerr << "cinfail" << endl;
						invalid = true;
					} // end else
				} // end else
			} // end else if for command switch s
		
	
			// ? command prints out the corresponding colours to the number 0-4
			else if (command == "?"){
				cout << "White:" << setw(2) << "0" << endl;
				cout << "Black:" << setw(2) << "1" << endl;
				cout << "Red:" << setw(4) << "2" << endl;
				cout << "Green:" << setw(2) << "3" << endl;
				cout << "Blue:" << setw(3) << "4" << endl;
			} // end else if for command ?
		
			// if the invalid flag is on, terminate the program
			if (invalid){
				cerr << "INVALID INPUT GIVEN" << endl;
				done = true;
			} // end if
		} // end while
	} // end if


	// Graphicmode ON
	// command lines are exactly the same as Graphicmode OFF case
	// except that Gridb is initialized instead of Grid
	else {
		Gridb grid;
		while(!done){
			// to track if invalid input is received
			bool invalid = false;
			// take command from cin
			string command;
			cin >> command;
			// terminate if the input is exhausted
			if (cin.eof()) break;


			// new n command
			if (command == "new"){
				// new cannot be called once game is called
				if (gameCalled){
					cerr << "game was already called" << endl;
					invalid = true;
				} // end if
				else {
					int n;
					cin >> n;
					// Creates a new n x n Grid, where n>=2
					if (!cin.fail() && n>=2){
						grid.init(n);
						newCalled = true;
					} // end if 
					else {
						invalid = true;
					} // end else
				} // end else
			} // end if for new command


			// init command
			else if (command == "init"){
				// init cannot be called if new is not called
				if (newCalled == false){
					cerr << "new was not called" << endl;
					invalid = true;
				}
				// Enters init mode
				// reads triple of integer r c s
				else {
					int r, c, state;
					while (1){
						cin >> r >> c;
						if (!cin.fail()){
							// coordinate -1 -1 ends the init mode
							if (r == -1 && c == -1){
								cout << grid;
								// if it was called during the game, check if the game ended
								if (gameCalled) {
									if (grid.isWon()) done = true;
								} // end if
								break;
							} // end if
							cin >> state;
							// sets the cell at row, column c to state s
							if (!cin.fail()){
								grid.init(r,c,state);
							} // end if
							else{
								invalid = true;
								break;
							} // end else
						} // end if
						else {
							invalid = true;
							break;
						} // end else
					} // end while
				} // end else	
			} // end else if for init command


			// include f command
			else if (command == "include"){
				// include cannot be called if new is not called
				if (!newCalled){
					invalid = true;
				} // end if

				// reads the file f
				string filename;
				cin >> filename;
				ifstream file(filename.c_str());

				if (file.fail()){
					invalid = true;
				} // end if
				else{
					int r, c, state;
					while (1){
						// reads the triple r c s
						// and finish the reading when -1 -1 is read
						file >> r >> c;
						if (!file.fail()){
							if (r == -1 && c == -1){
								cout << grid;
								// if it was during the game check if the game ended
								if (gameCalled){
									if (grid.isWon()) done = true;
								} // end if
								break;
							} // end if
							file >> state;
							// sets the cell at row r, column c to state s
							if (!file.fail()){
								grid.init(r,c,state);
							} // end if
							else {
								invalid = true;
								break;
							} // end else
						} // end if
						else {
							// finish the reading at the end of file
							if (file.eof()){
								cout << grid;
								// if it was during the game check if the game ended
								if (gameCalled){
									if (grid.isWon()) done = true;
								} // end if
								break;
							} // end if
							else {
								invalid = true;
								break;
							} // end else
						} // end else
					} // end while
				} // end else
			} // end else if for include command


			// game g command
			else if (command == "game"){
				// game cannot be called if game is called already or new is not called
				if(!newCalled || gameCalled){
					invalid = true;
				} // end if
				else {
					// save the number of moves allowed in the game
					cin >> g;
					// print out the moves left and check the winning condition
					if (!cin.fail()){
						if (g == 1){
							cout << g << " move left" << endl;
						} // end if
						else{
							cout << g << " moves left" << endl;
						} // end else
						if (grid.isWon()){
							done = true;
						} // end if
					} // end if
					else {
						invalid = true;
					} // end else
					// starts a new game
					gameCalled = true;
				} // end else
			} // end else if for game g command

			
			// switch s command
			else if (command == "switch"){
				// cannot be called if the game has not started
				if(!gameCalled){
					cerr << "game was not called" << endl;
					invalid = true;
				} // end if
				else {
					int state2;
					cin >> state2;
					if (!cin.fail()){
						// invalid state s
						if (state2 > 4) {
							cerr << "given state is greater than 4" << endl;
							invalid = true;
						} // end if
						// switch the top-left (0,0) cell to s, changing all appropriate neighbours
						// then redisplays the grid
						// and print out the result
						else {
							grid.change(state2);
							cout << grid;
							g--;
							if (g == 1){
								cout << g << " move left" << endl;
								if (grid.isWon()){
									done = true;
								} // end if
							} // end if 
							else {
								cout << g << " moves left" << endl;
								if (grid.isWon()){
									done = true;
								} // end if
								else if (g == 0){
									cout << "Lost" << endl;
									done = true;
								} // end else if
							} // end else
						} // end else
					} // end if
					else {
						cerr << "cinfail" << endl;
						invalid = true;
					} // end else
				} // end else
			} // end else if for command switch s
		
	
			// ? command prints out the corresponding colours to the number 0-4
			else if (command == "?"){
				cout << "White:" << setw(2) << "0" << endl;
				cout << "Black:" << setw(2) << "1" << endl;
				cout << "Red:" << setw(4) << "2" << endl;
				cout << "Green:" << setw(2) << "3" << endl;
				cout << "Blue:" << setw(3) << "4" << endl;
			} // end else if for command ?
		
			// if the invalid flag is on, terminate the program
			if (invalid){
				cerr << "INVALID INPUT GIVEN" << endl;
				done = true;
			} // end if
		} // end while
	} // end if
} // end main
