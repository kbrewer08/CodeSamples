/*
 * Program    : Keno
 * Name       : Keith Brewer
 * Date       : November 24, 2010 (updates made 8/10/2013)
 * System     : Windows 7 Professional, Intel Core i5 3570K
 * Compiler   : JDK 6 Update 22; original (updated for JDK 7)
 * Description: This program plays a GUI based version of the game Keno 
 */

/*
 * This class runs all of the GUI components of the program.
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


@SuppressWarnings("serial")
public class KenoGameDriver extends JFrame implements ActionListener{
	private KenoGame          game = new KenoGame();
	private Spot[]            winningSpots, playerMarkedSpots;
	private int               numSpots, bet, totalPicked = 0;
	private JLabel            spotsCBLabel, betLabel, winningsLabel;
	private JComboBox<String> spotsCB;
	private JTextField        betInput, winningsField;
	private JButton           playKenoButton, playAgainButton;
	private JTextArea         legend;
	private JPanel            mainPanel, spotPanel, topPanel, bottomPanel;
	private JButton[]         buttonArray;

	private String[] numSpotsArray = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};
	private static Color buttonDefaultBG = new Color(210, 210, 210); //default spot color is gray
	private static Color buttonDrawnBG   = new Color(102, 153, 255); //drawn spots are blue
	private static Color buttonChosenBG  = new Color(255, 255, 0);   //user chosen spots are yellow
	private static Color buttonMatchedBG = new Color(0, 204, 51);    //ergo, matched spots are green!

// Constructor - Gets the interface up and running
	public KenoGameDriver(){
		super("Keno");

		mainPanel    = new JPanel(new BorderLayout()); //Parent panel for everything else
		spotPanel    = new JPanel(new GridLayout(8, 10)); //for Keno spots
		topPanel     = new JPanel(new FlowLayout());//for top information: bet, spots dropdown, play keno button
		bottomPanel  = new JPanel(new FlowLayout());//winnings info, play again, etc.
		
		spotsCBLabel = new JLabel("Number of Spots");
		spotsCB = new JComboBox<String>(numSpotsArray);
		spotsCB.addActionListener(this);
		betLabel = new JLabel("Bet");
		betInput = new JTextField(10);
		betInput.addActionListener(this);
		playKenoButton = new JButton("Play Keno");
		playKenoButton.addActionListener(this);

		topPanel.add(spotsCBLabel);
		topPanel.add(spotsCB);
		topPanel.add(betLabel);
		topPanel.add(betInput);
		topPanel.add(playKenoButton);
		
		legend = new JTextArea("Yellow: Your spots\nBlue: Drawn Spots\nGreen: Matched spots");
		legend.setBackground(new Color(240, 240, 240));
		winningsLabel = new JLabel("Winnings");
		winningsField = new JTextField(10);
		winningsField.setEditable(false);
		playAgainButton = new JButton("Play Again");
		playAgainButton.addActionListener(this);
		playAgainButton.setEnabled(false);
		
		bottomPanel.add(legend);
		bottomPanel.add(winningsLabel);
		bottomPanel.add(winningsField);
		bottomPanel.add(playAgainButton);

		buttonArray = new JButton[KenoGame.MAX_KENO_NUMBER + 1];
		for(int i = 1; i < buttonArray.length; i++){
			buttonArray[i] = new JButton("" + i);
			buttonArray[i].setBackground(buttonDefaultBG);
			buttonArray[i].setBorder(BorderFactory.createRaisedBevelBorder());
			buttonArray[i].setPreferredSize(new Dimension(50, 50));
			buttonArray[i].addActionListener(this);
			buttonArray[i].setEnabled(false);
			spotPanel.add(buttonArray[i]);
		}

		mainPanel.add(topPanel, BorderLayout.NORTH);
		mainPanel.add(spotPanel, BorderLayout.CENTER);
		mainPanel.add(bottomPanel, BorderLayout.SOUTH);
		
		getContentPane().add(mainPanel);
	}

//Event handler function - Responds to the playKenoButton button, playAgainButton,
//	                       betInput field, and any of the buttonArray JButtons
	public void actionPerformed(ActionEvent e ){
		Object obj = e.getSource();

	//if playAgainButton clicked, disable it, then enable everything else
		if(obj == playAgainButton)
		{
			playAgainButton.setEnabled(false);
			playKenoButton.setEnabled(true);
			spotsCB.setEnabled(true);
			betInput.setEditable(true);
			betInput.setText("");
			winningsField.setText("");
			for(int i = 1; i < KenoGame.MAX_KENO_NUMBER + 1; i++)
			{
				buttonArray[i].setBackground(buttonDefaultBG);
				buttonArray[i].setEnabled(false);
			}
			totalPicked = 0;
			
			return;
		}

	//when clicking on playKenoButton or pressing enter from betInput field
		if(obj == playKenoButton || obj == betInput){
			game.resetGame();

			numSpots = Integer.parseInt((String)spotsCB.getSelectedItem());
			try{ //having a try...catch was required by the assignment
				bet = Integer.parseInt(betInput.getText());
			}catch(NumberFormatException nfe){
				JOptionPane.showMessageDialog(null, "The data in the bet field must be a number");
				return;
			}

			if(bet < 1)
			{
				JOptionPane.showMessageDialog(null, "Your bet must be greater than 0");
				return;
			}

			for(int i = 1; i < buttonArray.length; i++)
				buttonArray[i].setEnabled(true);

			game.newPlayer(numSpots, bet);
			playKenoButton.setEnabled(false);
			spotsCB.setEnabled(false);
			betInput.setEditable(false);
			playAgainButton.setEnabled(false);

			game.drawNumbers();
			
			return;
		}

	//if any of the number buttons were pressed
		for(int i = 0; i < KenoGame.MAX_KENO_NUMBER + 1; i++)
		{
			if((obj == buttonArray[i]) && //if a Spot button is chosen...
				totalPicked < numSpots && //AND we haven't chosen all our spots yet
				(buttonArray[i].getBackground() == buttonDefaultBG)) //AND the button hasn't been chosen yet
			{
				JButton pressed = (JButton)e.getSource();
				pressed.setBackground(buttonChosenBG); //set player spot yellow
				totalPicked++;
				game.setOneSpot(i);

				if(totalPicked == numSpots) //if player finished choosing spots
				{
					//mark the spots that were chosen by the game to blue
					winningSpots = game.getDrawnSpots();
					for(int j = 0; j < KenoGame.DRAWN_NUMBERS; j++)
						buttonArray[winningSpots[j].getValue()].setBackground(buttonDrawnBG);
					
					//mark the player's winning spots green
					playerMarkedSpots = game.getPlayerMarkedSpots();
					for(int k = 0; k < game.getNumberOfSpotsMarked(); k ++)
						if(playerMarkedSpots[k].getChosen() == true)
							buttonArray[playerMarkedSpots[k].getValue()].setBackground(buttonMatchedBG);

					//Show winnings
					game.getResults();
					winningsField.setText(game.getPlayerWinnings() + "");
					playAgainButton.setEnabled(true);
				}
			}
		}

		return;
	}

// Main function
	public static void main(String[] args){
		KenoGameDriver kenoGUI = new KenoGameDriver();
		kenoGUI.pack();
		kenoGUI.setLocationRelativeTo(null);
		kenoGUI.setVisible(true);
		kenoGUI.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		
	}

}