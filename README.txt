README
Text-Based Graph Theory Logging Program

This is a text-based game for running Monte Carlo simulations for 
Petersen Graphs and Complete Graphs (more in development).

To run this on OS X, you need to install Xcode for the C++ compiler. 

To run this game (assuming using OS X):

1. Open Terminal
2. Navigate to directory where you downloaded the files
3. Type “./RunProgram.sh”
	-> This will compile the program and create the “output_data” folder, and run the
		program

In “output_data”, the following files will be created after the program has run:
“master_data.txt”, “player1_moves.txt”, “player2_moves.txt”, and “results.txt”.

“master_data.txt” - This is the raw, unsorted, unparsed data at outputted by the program.
	->The last number at the end of the string is the winner of this game
	-> It is written in the following format: 1-2-3-4, where move 1 is from 1 to 2, move 2 is
		from 2 - 3, etc.

“player1_moves” - All the player one moves after the analysis algorithm is run

“player2_moves” - All the player two moves after the analysis algorithm is run

“results.txt” - Same output of the results as what is at the end of the Terminal

NOTE: You must move these four files into a separate folder in “output_data” or out of “output_data”.
	The way this program works is by adding onto the end of the files already there.

Author: Kyle Rodgers
Email: krodgers@ole.augie.edu