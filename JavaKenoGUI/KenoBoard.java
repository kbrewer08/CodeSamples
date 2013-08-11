/*
 * Class for the Keno board itself. Holds the entire array of board spots as
 * well as an array of the spots that were drawn. The board itself chooses its
 * winning numbers.
 */

public class KenoBoard {
	private Spot[] kenoSpots;  //all of the spots on the board
	private Spot[] drawnSpots; //the winning spots chosen by the game
	
	public KenoBoard(){
		kenoSpots  = new Spot[KenoGame.MAX_KENO_NUMBER + 1];
		drawnSpots = new Spot[KenoGame.DRAWN_NUMBERS];
		
		for(int i = 0; i < kenoSpots.length; i++)
			kenoSpots[i] = new Spot(i);
	}
	
	public Spot[] getDrawnSpots()
	{
		return drawnSpots;
	}

	public void resetChosen(){
		for(int i = 0; i < kenoSpots.length; i++)
			kenoSpots[i].setChosen(false);
		for(int i = 0; i < drawnSpots.length; i++)
			drawnSpots[i] = null;
	}

	public Spot getSpot(int spotNum){
		if(spotNum > 0 && spotNum <= KenoGame.MAX_KENO_NUMBER)
			return kenoSpots[spotNum];
		else
			return null;
	}

	public int getDrawnSpotValue(int num){
		return drawnSpots[num].getValue();
	}

	public void chooseSpots(){
		int index;
		int num = 0;
		
		while(num < KenoGame.DRAWN_NUMBERS){
			index = (int)((Math.random() * (KenoGame.MAX_KENO_NUMBER - 0)) + 1);
			if(kenoSpots[index].getChosen() == false){
				this.drawnSpots[num] = kenoSpots[index];
				kenoSpots[index].setChosen(true);
				num++;
			}
		}
	}
	
	public String toString(){
		StringBuilder sb = new StringBuilder("Spots drawn: ");
		
		for(int i = 0; i < drawnSpots.length; i++)
			if(i == drawnSpots.length - 1)
				sb.append(drawnSpots[i].getValue());
			else
				sb.append(drawnSpots[i].getValue() + ", ");
	
		return sb.toString();
	}
}
