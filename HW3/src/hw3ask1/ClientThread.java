package hw3ask1;

public class ClientThread implements Runnable{
	
	ClockMonitor monitor;
	
	
	ClientThread( ClockMonitor m) {
		
		monitor = m;
	}
	
	
	
	public void run() {
		
		
		while ( true ){
			
			try {
				
				int sleep = 1 + (int )( Math.random()* 10);
			
				monitor.sleepTicks(sleep);
				
			}catch( InterruptedException e) {
				
				e.printStackTrace();
				
			}
		}
	}

}
