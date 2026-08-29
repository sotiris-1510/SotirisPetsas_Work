
public class Game {
	
	
	private String player1;
	private String player2;
	private final int boardsize;
	
	
	// game constructor
	public Game(String playerType1, String playerType2 ,int boardsize) {
		
		player1=playerType1;
		player2=playerType2;
	    this.boardsize=boardsize;
		
		
	}
	
	// plays the game
	public void play() {
		
		
		//creates the board
		Board board= new Board(boardsize);	
		
		char pawn1='X';
		char pawn2='O';

		Player p1= new Player(player1,board,pawn1);
		Player p2 = new Player(player2,board,pawn2);
		
		// stage where each player sets there pawns
		for(int x=1;x<=boardsize;x++) {
			
			System.out.println("Curerent player : "+pawn1);
			p1.setPiece();
			System.out.print(board);
			
			if(board.winningState()==true) {
	    		
	    		System.out.println("The winner is : "+pawn1);
	    		return;
	    	}
			
			
			
			System.out.println("Curerent player : "+pawn2);
			p2.setPiece();
			System.out.print(board);
			
			if(board.winningState()==true) {
	    		
	    		System.out.println("The winner is : "+pawn2);
	    		return;
	    	}


		}
		
		// stage where each player moves there pawns
		
		int plays=0;
		int plithos;
		char currentpawn;
		Player currentplayer;
		
	    while(board.winningState()==false) {
			
			
			if(plays%2==0) {
				currentpawn=pawn1;
				currentplayer=p1;
				
			}else {
				currentpawn=pawn2;
				currentplayer=p2;
			}
			
			plithos=0;
			// checks if a player is "prisoned"
           for(int x=0;x<board.getSize();x++) {
				
				for(int y=0 ; y<board.getSize();y++) {
					
					Position currentp= new Position(x,y);

					if(board.getCell(currentp)==currentpawn) {
						
						
						Position pos1 = new Position(x-1,y);
						Position pos2 = new Position(x+1,y);
						Position pos3 = new Position(x,y-1);
						Position pos4 = new Position(x,y+1);
						
						
						if(board.getCell(pos1)!='E'&& board.getCell(pos2)!='E'&& board.getCell(pos3)!='E'&& board.getCell(pos4)!='E') {
							plithos++;
						}
						
						
					}
				}
			}
			
			
			if(plithos==board.getSize()) {
				System.out.println("No available moves  , you lose your turn!");
				
			}else {
			
			System.out.println("Curerent player : "+currentpawn);
			currentplayer.movePiece();
			System.out.print(board);

			if(board.winningState()==true) {
				
				System.out.println("The winner is player : "+currentpawn);
				
			      }
			}
			plays++;
      }
	}
	
}
	
	
	
	

