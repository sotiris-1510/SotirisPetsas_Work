/**
* Author: SOTIRIS PETSAS
* Written: 17/11/2024
* Last updated: 01 /12/2024
* 
* 
* In this project we have created several objects to create and play the Cyboard game .
* Only the HUMAN VS HUMAN option is implemented.
* The other options , plus the graphics are not implemented.
* 
* 
*/



public class TestGame {

	public static void main(String[] args) {
		
		
			
			
			System.out.println("Welcome to the Game!\r\n"
					+ "1. Human vs Human\r\n"
					+ "2. Human vs Computer – not implemented\r\n"
					+ "3. Computer vs Computer – not implemented\r\n"
					+ "Choose game mode (1-3) and board size (>2 and <6): ");
			
			int mode=StdIn.readInt();	
			int size=StdIn.readInt();

			// checks if the size provided is right 
			while(size<2 || size>6) {
				
				System.out.println("Wrong size , give again !");
				size=StdIn.readInt();
			}
			
			if(mode==1) {
				Game game = new Game("Human","Human",size);
			game.play();		
					
			}
		
		


	}

}
