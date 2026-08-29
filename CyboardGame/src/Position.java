
public class Position {
	
	private int row;
	private int col;
	
	// point constructor
	public Position(int row ,int collum) {
		
		this.row=row;
		this.col=collum;
	}
	
	//returns the row of a point object
	public int getRow() {
		
		return this.row;
	}
	
	//returns the column of a point object
	public int getColumn() {
		return this.col;
	}
	
	// returns the String form o position
	public String toString() {
		
		return "("+this.row+","+this.col+")";
		
	}
	
	

}
