
public class Cell {
	
	private char pawn;
	
	
	//no argument cell constructor
	public Cell() {
		
		pawn=' ';
	}
	
	// sets pawn to a character provided
	public void  setPawn(char pawnType) {
		
		pawn=pawnType;
	}
	
	// returns the pawn 
	public char getPawn() {
		
		if(pawn==' ') {
			return 'E';
		}else 
			return pawn;
	}
	
	// checks if a cell is empty
	public boolean isEmpty() {
		
		if(pawn==' ') {
			return true;
		}else return false ;
	}
	
	// returns the character in a cell
	public String toString() {
		
		return  " "+pawn+" ";
	}

}
