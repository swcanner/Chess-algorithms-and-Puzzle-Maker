File Overview:
.txt extensions are the overview files- documentation of sorts
.h and .cpp are the code
.png is the UML Diagram

If there are any questions feel to contact me on Github

Title: Walking fast, Dijkstras path, and Im Homebound

Description: Path finding algorithm using chess pieces to have them not only
	get to the final state, but also avoid objects set on the board
	AND avoid the areas of attack of placed towers. 4 paths in total

	There is also a puzzle maker for chess board that allows the user to try and find the optimal
	path to the destination, as well as the knight's tour

**Please note that I will be referring to the Chess pieces themselves as "Towers"**

User: Chess Players, Computer Scientists with an interest in chess AI

Problem: Tries to find the best path for one to take in a given area
	Also allows the user to work on their problem solving skills with the puzzles and knowledge on how the knights tour
	works on boards of small sizes (5x5) to large sizes (25x25)

Technologies: MY CODE WILL BE THE END ALL BE ALL
	I do not intend to build a full GUI: only the console in this
	That said, I will create a UI that is discussed below (In UI)

Use Case: The text file will be included in the same directory as this (UseCase.txt)

Data: Nodes and Linked Lists
	I will have the board be a linked list created in accordance with the board rules
	Nodes will hold a String- its position
			  Tower
			  An old tower for reverting after certain paths have been completed
		and hold these for linking:
				up, right, down, left
		possible moves for the knights tour

	The linked list will be stored as the board class which handles the manipulation, with
		a god class to handle the board

UI:
	(For MCP)
	Prompt User for the password to WHOPPER
	If is correct - "JOSHUA"
		Ask User if they want to do the chess path finder, path finder game, or knights tour
		Loop until want to exit
	Exit

	(For the PATH FINDER)
	Prompts User for the size of board
	Prompts the User for the Piece they have
	Prompts User for position of said piece
	Prompts User for presence of other pieces
	--Prompts User for the positions of each enemy piece
	Prompt User for destination of their piece in question
	Compute the paths
	Display paths that are possible, prompt which they would like to see
	Display the one the user would like to see
	Repeat the past 2 steps until they want to leave
	Ask user if they would like to have a new destination with the same setup
	Ask User if they would like to enter in a new scenario
	Exit

	(For the PATH GAME)
	Prompt User for the difficulty of game they want to play (easy, medium, hard)
	Give the user the setup of the game
	Ask User for next move position until destination reached
	If not reached in minimum amount
		ask if they want to redo the puzzle, see the answer, or try a new Puzzle
	If is reached in minimum amount
		Return to top and ask for a new puzzle if they want to escape
	Exit

	(For the KNIGHTS TOUR)
	Prompt User for size of board they want to test out
	Ask User for start position
	Compute the path
	Ask User if they want to see the path, change the start position of the main knight, or try a different board size
	Exit

	King: K
	Queen: Q
	Rook: R
	Bishop: B
	Knight: H
	Pawn: P

	** Designate that it is the piece we are looking at
	#  Designate that the space is the destination


      A    B    C    D    E    F    G    H
	  ----------------------------------------
	1 |   |    |    |    |    |    |    |    |
	  ----------------------------------------
	2 |   |    |    |    |    |    |    |    |
	  ----------------------------------------
	3 |   |    |    |    |    |    |    |    |
    ----------------------------------------
  4 |   |    |    |    |    |    |    |    |
    ----------------------------------------
	5 |   |    |    |    |    |    |    |    |
    ----------------------------------------
  6 |   |    |    |    |    |    |    |    |
    ----------------------------------------
	7 |   |    |    |    |    |    |    |    |
    ----------------------------------------
  8 |   |    |    |    |    |    |    |    |
    ----------------------------------------

Algorithm: Discussed in an attachment in this directory (alg.txt), the entire program is psuedocoded out on paper
	Attached in this file is the psuedocoded code in several pictures
