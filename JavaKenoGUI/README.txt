Swing GUI based Keno Game

This program was written as the final assignment in an introductory Java course. The 6 previous assignments were console based (or could be done in an applet). This last, 7th assignment was required to be written as an event based GUI program. The Keno game files were to be used unaltered except for the addition of setters and getters as necessary and the removal of console based activities. The only class that was to be added was a class to drive the GUI components of the game. 



Classes:


- Spot:

Every spot on the Keno board is an instanace of the Spot class. Its two data members are an int to represent the value of the spot on the board, and a boolean to indicate whether or not the spot was one of the winning numbers chosen by the KenoBoard class.



- NumberGameInterface:

Abstract class required by the assignment. KenoGame implements this class.



- KenoPlayer:

This class represents the player of the Keno game. Data members are a Spot array to keep track of which spots the player has chosen, currentIndex to keep track of how full the player's Spot array currently is, numMatches to track the number of matches the player made, bet for the bet amount, and winnings to show the player's current winnings. Bets and winnings are not tracked from one round of the game to the next - they are essentially just a part of the assignment, which required GUI based user I/O.



- KenoGameDriver:

Contains the main function. This class contains all of the GUI components, including the event handler method actionPerformed(ActionEvent e). 



- KenoGame:

This class is the class that runs the actual game logic itself. It contains composite data members for KenoPlayer and KenoBoard. This class manages the game's activities through these members as well as other methods.



- KenoBoard:

This class represents the actual Keno board itself. It contains two Spot array data members: one for all of the spots on the board, and one for the winning spots drawn during each round.