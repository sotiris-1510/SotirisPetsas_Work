
public class Player {
	
	private char pawn;
	private String player;
	private Board board;
	
	// player constructor
	public Player(String playerType, Board board, char pawnType) {
		
		pawn=pawnType;
		player=playerType;
		this.board=board;
		
		
	}
	
	// method so a player can set a piece in a position they would like
	public void setPiece() {
		
		int x,y;
		if(player=="Human") {
		System.out.print("Enter row and collum to place your pawn (0-"+(board.getSize()-1)+ "): ");
		
		x=StdIn.readInt();
		y=StdIn.readInt();
		
		Position p = new Position(x,y);
		
		//checks if the position provided is valid
		while(x>=board.getSize() || y>=board.getSize() || !board.isEmpty(p) ) {
			
			System.out.println("Invalid position, give other position : ");
			
			x=StdIn.readInt();
			y=StdIn.readInt();
			
			p = new Position(x,y);
			
		
		}
		
		board.setCell(p,pawn);
		
		
	}
}
		
		// moves a piece from a certain position to an other position
		public void movePiece() {
			
			System.out.print("Enter row and column to move from and place your pawn :");
			
			int x1,y1,x2,y2;
			
			x1=StdIn.readInt();
			y1=StdIn.readInt();
			
			x2=StdIn.readInt();
			y2=StdIn.readInt();
			
			Position p1= new Position(x1,y1);
			Position p2 = new Position(x2,y2);
			
			// checks if the first position provided is inside the board , that the pawn is the player's 
			// currently playing, and there ara available moves for the pawn chosen 
			while( board.getCell(p1)!=pawn || checkAround(p1)==false) {
			
				
				if(checkAround(p1)==false) {
					System.out.println("No available moves for this position give another first and second position:");
				}else {
				System.out.println("Invalid first  position, give another first and second position : ");
				}
				x1=StdIn.readInt();
				y1=StdIn.readInt();
				
				p1=new Position(x1,y1);
				x2=StdIn.readInt();
				y2=StdIn.readInt();
				
				 p2 = new Position(x2,y2);
				
				
			}
			
			/*checks if the second position provided is inside the board 
			*is not the same position as the first , is empty ,and is next to the first position
			*/
			
			
			while((x2==x1&&y2==y1) || board.getCell(p2)!='E' || getDistance(p1, p2)>1) {
				
				System.out.println("Invalid second  position, give again your second position : ");
				
				x2=StdIn.readInt();
				y2=StdIn.readInt();
				
				p2= new Position(x2,y2);

			}
			//moves the piece 
			board.moveSquare(p1, p2);
			
			
			
				
		}
	
	// returns the pawn of the player playing	
	public String toString() {
			
			return player+":"+pawn;
		}
	//returns the Manhattan distance between two cells
	private  int getDistance(Position p1 ,Position p2) {
		return Math.abs(p1.getRow()-p2.getRow())+Math.abs(p1.getColumn()-p2.getColumn());
		
	}
	
	// checks the cells below ,above,right and left of a position and returns true if there is at least one empty 
	private  boolean checkAround(Position currentp) {
		
					Position pos1 = new Position(currentp.getRow()-1,currentp.getColumn());
					Position pos2 = new Position(currentp.getRow()+1,currentp.getColumn());
					Position pos3 = new Position(currentp.getRow(),currentp.getColumn()-1);
					Position pos4 = new Position(currentp.getRow(),currentp.getColumn()+1);
					
					
					if(board.getCell(pos1)!='E'&& board.getCell(pos2)!='E'&&board.getCell(pos3)!='E'&&board.getCell(pos4)!='E') {
			return false;
					}
					
				return true;	
				
			}
		
		
		
	}
		
	
	


