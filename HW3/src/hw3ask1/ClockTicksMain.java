package hw3ask1;

public class ClockTicksMain  {
	
	public static void main ( String[] args) {
		
		ClockMonitor monitor = new ClockMonitorImpl();
		
		Thread daemon = new Thread( new DaemonThread( monitor , 200), "DaemonThread");
		daemon.start();
		
		
		int n = 10;
		Thread clients[]= new Thread [n];
		
		for( int i=0 ; i<10 ; i++) {
			
			clients[i]= new Thread( new ClientThread (monitor), "ClientThread"+i);
		}
		
		for( int i=0 ; i<10 ; i++) {
			
			clients[i].start();
		}
		
		
		
	
		
		
	}

}
