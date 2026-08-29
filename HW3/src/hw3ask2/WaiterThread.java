package hw3ask2;
import java.util.concurrent.Semaphore;
public class WaiterThread extends Thread {
	
	 Semaphore pitaSem;
	 Semaphore kreasSem;
	 Semaphore laxanikaSem ;
	
	
	 Semaphore waiterSem;
	
	WaiterThread(Semaphore pS, Semaphore kS, Semaphore lS, Semaphore wS){
		pitaSem=pS;
		kreasSem=kS;
		laxanikaSem=lS;
		waiterSem=wS;
	}
	
	
	
	
	String[] ingredients = { "PITA", "KREAS", "LAXANIKA"};
	
	
	public void run() {
		
		
		while (true ) {
			
			try {
				
				waiterSem.acquire();
				
				int putOnTable = (int)( (Math.random() *3));
				
				int ingredient1= (putOnTable+1) % 3;
				int ingredient2= (putOnTable+2) % 3;
				
				System.out.println("The waiter has brought to the table "+ 
				ingredients[ingredient1]+ " and " +ingredients[ingredient2]);
				
				switch(putOnTable) {
				
					case 0 : 
						
						pitaSem.release();
						break;
					case 1 :
						
						kreasSem.release();
						break;
					case 2 : 
						
						laxanikaSem.release();
						break;
				}
				
				
			}catch(InterruptedException e) {
				e.printStackTrace();
				break;
			}
		}
		
		
	}

}
