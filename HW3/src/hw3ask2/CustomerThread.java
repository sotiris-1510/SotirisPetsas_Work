package hw3ask2;


import java.util.concurrent.Semaphore;

public class CustomerThread extends Thread{
	

	String name ;
	String myIngredient;
	Semaphore mySem;
	WaiterThread w;
	
	CustomerThread (String name , String myIngredient , Semaphore mySem ,WaiterThread w){
		
		this.name=name;
		this.myIngredient=myIngredient;
		this.mySem=mySem;
		this.w=w;
	
		
	}
	
	
	public void run() {
		
		while( true ) {
			
			try {
				
				mySem.acquire();
				
				System.out.println(name+ " has "+ myIngredient + " and is taking the rest needed from the table");
				
				Thread.sleep((long) (Math.random() * 800) + 200);
				
				w.waiterSem.release();
			}catch(InterruptedException e) {
				
			  e.printStackTrace();
			  break;
			}
			
		}
	}

}
