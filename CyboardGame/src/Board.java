
public class Board {
	
	private static Cell[][] board;
	private int board_size;
	
	//board constructor
	public Board(int board_size) {
		
		this.board_size=board_size;
		
		 board= new Cell[this.board_size][this.board_size];
		
		for (int x=0;x<this.board_size;x++) {
			
			for(int y=0;y<this.board_size;y++) {
				
				board[x][y]= new Cell();
				board[x][y].setPawn(' ');
			}
		}
}
	
	//checks if a certain cell of the board is a empty
	public boolean isEmpty(Position p) {
		
		
		return board[p.getRow()][p.getColumn()].isEmpty();
		
	}
	
	//sets a certain cell a char value
	public  void setCell(Position p, char pawnType) {
		
		
		board[p.getRow()][p.getColumn()].setPawn(pawnType);
		
	}
	
	// swaps two cells of a board
	public void moveSquare(Position p1, Position p2) {
		
		char temp;
		
		temp=board[p1.getRow()][p1.getColumn()].getPawn();
		
		board[p1.getRow()][p1.getColumn()].setPawn(' ');

		
		board[p2.getRow()][p2.getColumn()].setPawn(temp);
		
		
		

	}
	
	// prints out the board
	public String toString() {
		
		int output_size=2*board_size+1;
		String finalGame="";
		
		int x,y;
		
          for(x=0;x<output_size;x++) {
			
			for(y=0;y<output_size;y++) {
				
				
				if(x%2==0) {
					finalGame+="- ";
				}else if(y%2==0) {
					finalGame+='|';
					
				}else finalGame+=board[x/2][y/2].toString();
				
			}
			
			finalGame+="\n";
			
		}

		return finalGame;
		
		
	}
	
	// checks if we have a winning condition inside the board
	public boolean winningState() {
		
		int pl=0;
		int x,y;
		boolean flag=false;
		
		//firstly checks each column
		for (x=0;x<board_size;x++) {
			pl=0;
			
			for(y=0;y<board_size;y++) {
				
				if(board[y][x].getPawn()==board[0][x].getPawn()&& !board[0][x].isEmpty())
					pl++;
			}
			if(pl==board_size)
				flag=true;
		}
		
		//secondly checks each row for the winning condition
		for (y=0;y<board_size;y++) {
			pl=0;
			
			for(x=0;x<board_size;x++) {
				
				if(board[y][x].getPawn()==board[y][0].getPawn() && !board[y][0].isEmpty())
					pl++;
			}
			if(pl==board_size)
				flag=true;
		}
		

	return flag;
	
	}
	
	//returns how many rows the board has
	public int getSize() {
		
		return board_size;
	}
	
	//returns the value of a certain cell
	public char getCell(Position p){
		
		if(p.getColumn()>=board_size||p.getColumn()<0||p.getRow()>=board_size||p.getRow()<0) {
			return 'I';
		}else {
		return board[p.getRow()][p.getColumn()].getPawn();
		}
	}

}

    



	

	
	


