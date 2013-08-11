
public class Spot {
	private int value      = 0;
	private boolean chosen = false;
	
	public Spot(int val){
		if(val > 0)
			value = val;
	}
	
	public Spot(){}
	
	public int getValue(){
		return value;
	}
	
	public boolean getChosen(){
		return chosen;
	}
	
	public void setChosen(boolean isChosen){
		chosen = isChosen;
	}
}
