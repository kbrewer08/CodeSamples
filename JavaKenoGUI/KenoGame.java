/*
 * This class runs the Keno game itself. It manages the Keno board and the
 * player through the 'board' and 'player' variables, which are private. 
 */

public class KenoGame implements NumberGameInterface{
	public static final int MAX_KENO_NUMBER = 80;
	public static final int DRAWN_NUMBERS   = 20;
	static double[][] PAYOFF = {
		 {0},
		 {0, 2.75},
		 {0, 1., 5.},
		 {0, 0, 2.50, 25.00},
		 {0, 0, 1.0, 5.0, 80.0},
		 {0, 0, 0,  2.0, 10.0, 600.0},
		 {0, 0, 0,  1.0, 8.0, 50., 1499.0},
		 {0, 0, 0,  0, 5.0, 10.0, 250., 1500.0},
		 {0, 0, 0,  0, 4.00, 8.00, 40.00, 400.00, 10000.00},
		 {0, 0, 0,  0, 2.00, 5.00, 20.00, 80.00, 2500.00, 15000.00},
		 {0, 0, 0,  0,  0, 0, 2.00, 30.00, 100.00, 500.00, 3000.00, 17500.00},
		 {0, 0, 0,  0,  0, 0, 2.00, 15.00, 50.00, 80.00, 800.00, 8000.00, 27500.00},
		 {0, 0, 0,  0,  0, 0, 1.00, 5.00, 30.00, 90.00, 500.00, 2500.00, 15000.00, 30000.00},
		 {0, 0, 0,  0,  0, 0, 1.00, 2.00, 10.00, 50.00, 500.00, 1000.00, 10000.00, 15000.00, 30,000.00},
		 {0, 0, 0,  0,  0, 0, 2.00, 8.00, 32.00, 300.00, 800.00, 2500.00, 12000.00, 18000.00, 30000.00},
		 {0, 0, 0,  0,  0, 0, 1.00, 7.00, 21.00, 100.00, 400.00, 2000.00, 8000.00, 12000.00, 25000.00, 30000.00}};
	
	private KenoBoard board;
	private KenoPlayer player;
	
	public KenoGame()
	{
		board = new KenoBoard();
	}
	
	public void newPlayer(int numSpots, int bet){
		player = new KenoPlayer(numSpots, bet);
	}

	public void resetGame()
	{
		board = new KenoBoard();
		
		return;
	}
	
	public Spot[] getDrawnSpots()
	{
		return board.getDrawnSpots();
	}

	public Spot[] getPlayerMarkedSpots()
	{
		return player.getMarkedSpots();
	}
	
	public int setOneSpot(int newSpot){
		if(player == null)
			return -2; //no-player error
		else
			if(newSpot < 1 || newSpot > MAX_KENO_NUMBER)
				return -1; //invalid spot
			else
				if(player.setSpot(board.getSpot(newSpot)) == true)
					return 0; //no error; everything ok
				else
					return 1; // spot already marked, or some other error
	}

	public int getNumberOfSpotsMarked(){
		return player.getMarkedSpotsArraySize();
	}

	public void drawNumbers(){
		board.resetChosen();
		board.chooseSpots();
	}
	
	public void getResults(){
		player.calcNumMatches();
		player.calcWinnings();
	}

	public double getPlayerWinnings()
	{
		return player.getWinnings();
	}
	
	public void displayResults(){
		System.out.println(board.toString());
		System.out.println(player.toString());
	}

	public String getBoardToString()
	{
		return board.toString();
	}

	public String getPlayerToString()
	{
		return player.toString();
	}
}
