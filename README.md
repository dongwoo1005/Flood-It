Flood-It
================
Requirements:
----------------
###X11
- Linux: be sure to pass –Y option if using an ssh connection.
- Windows with Putty: make sure you run an X server such as XMing
- Mac: install XQuartz on a newer Mac OS.

###Compiling:
g++ main.cc -lX11
or if above doesn’t work on Mac, you need to explicitly tell g++ where X11 is located:
g++ main.cc -lX11 -L/usr/X11/lib -I/usr/X11/include

Available Commands:
--------------------
- *new n* Creates a new n X n grid, where n >= 2. If there was already an active grid, that grid is destroyed and replaced with the new one.
- *init* Enters initialization mode. Subsequently, reads triples of integers r c s and sets the cell at row r, column c to state s. The top-left corner is row 0, column 0. The coordinates -1 -1 end initialization mode. It is possible to enter initialization mode more than once, and even while the game is running. If the triple r c s refers to invalid co-ordinates, the triple is ignored. When initialization mode ends, the board should be displayed.
- *include f* The file f is a list of cell initializations of the same format of initialization from init. Reading from f will end either when end-of-_le is reached or a -1 -1 is read. Include is called independently of init.
- *game g* Once the board has been initialized, this command starts a new game, with a commitment to solve the game in g moves or fewer (g > 0). game and new cannot be called once a game has been started.
- *switch s* Within a game, switches the top-left (0,0) cell to s, changes all appropriate neighbours, and then redisplays the grid.
- *?* Prints out the encoding between the text version and graphics version

Command line option:
---------------------
•	-graphics produces a graphical display for the game

Sample interaction: 
---------------------
(responses from the program are in italics)

new 4
init
0 0 4
0 2 3
0 3 2
1 1 1
1 3 3
2 0 4
2 2 2
2 3 1
3 1 2
3 3 3
-1 -1
4032
0103
4021
0203
game 4
4 moves left
switch 0
0032
0103
4021
0203
3 moves left
switch 4
4432
4103
4021
0203
2 moves left
switch 0
0032
0103
0021
0203
1 move left
switch 2
2232
2103
2221
2203
0 moves left
Lost
