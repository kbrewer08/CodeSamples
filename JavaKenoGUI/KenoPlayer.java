/*
 * Class for the Keno player and related information and activities. 
 */
public class KenoPlayer {
	private Spot[] markedSpots;
	private int    currentIndex = 0;
	private int    numMatches   = 0;
	private int    bet          = 1;
	private double winnings     = 0.0;

	public KenoPlayer(int numSpots, int newBet){
		if(numSpots > 0 && numSpots < KenoGame.PAYOFF.length)
			markedSpots = new Spot[numSpots];
		else
			markedSpots = new Spot[1];
		if(newBet > 0)
			bet = newBet;
	}

	public Spot[] getMarkedSpots()
	{
		return markedSpots;
	}
	
	public int getMarkedSpotsArraySize(){
		return markedSpots.length;
	}
	
	public int getBet(){
		return bet;
	}
	
	public int getNumMatches(){
		return numMatches;
	}
	
	public double getWinnings(){
		return winnings;
	}
	
	public boolean setSpot(Spot newSpot){
		int i = 0;
		if(newSpot != null && currentIndex < this.markedSpots.length){
			while(i <= currentIndex){
				if(newSpot != this.markedSpots[i])
					i++;
				else
					return false; //spot already marked
			}
			this.markedSpots[currentIndex] = newSpot;
			currentIndex++;
			return true;
		}
		return false; //else some other error
	}

	public void calcNumMatches(){
		numMatches = 0;
		for(int i = 0; i < this.markedSpots.length; i++)
			if(this.markedSpots[i].getChosen() == true)
				numMatches++;
	}
	
	public void calcWinnings(){
		winnings = winnings + ((double)bet * KenoGame.PAYOFF[markedSpots.length][numMatches]);
	}
	
	public String toString(){
		StringBuilder sb = new StringBuilder("Player's spots: ");

		for(int i = 0; i < markedSpots.length; i++)
			if(markedSpots[i] != null)
				if(i == markedSpots.length - 1)
					sb.append(markedSpots[i].getValue() + ";");
				else
					sb.append(markedSpots[i].getValue() + ", ");
		
		sb.append("\nNumber of Matches: " + numMatches + "\nBet: " + bet + "\nWinnings: " + winnings);
		
		return sb.toString();
	}
}
