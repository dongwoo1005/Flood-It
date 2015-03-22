#ifndef __GRIDB_H__
#define __GRIDB_H__
#include <iostream>
#include "cellb.h"
#include "textdisplay.h"
#include "window.h"

class Gridb {
  Cellb **theGrid;                   // The actual n x n grid. 
  int gridSize;                     // Size of the grid (n)
  TextDisplay *td;                  // The text display.
  Xwindow * theWindow;

  void clearGrid();                 // Frees the theGrid field.

  // Add private members, if necessary.


 public:
  Gridb();
  ~Gridb();  

  /* 
   * The following method is used to determine if the game has been won
   * An, inefficient implementation would be to use nested for loops to determine 
   * that all Cells in theGrid are of the same color.
   * A more efficient approach is to compute this information during the game as 
   * Cells change colors 
   * Look through the textdisplay.h file for hints on how to do this
   */
  bool isWon();						
  
  void init(int n);                 // Sets up an n x n grid.  Clears old grid, if necessary.
  void change(const int & state);  // Notify Cellb (0,0) of the change to new state: state 
  void init(int r, int c, int state); //set the state for r,c to state
  friend std::ostream &operator<<(std::ostream &out, const Gridb &g);
};

#endif
