package hw3ask1;

public class DaemonThread extends Thread implements Runnable{
	
	ClockMonitor monitor;
	int clockIntervals;
	
	DaemonThread(ClockMonitor m , int interv) {
		
		this.monitor = m;
		this.clockIntervals = interv;
		setDaemon(true);
		
	}
	
	
	public void run(){
		
		while ( true) {
			try {
				Thread.sleep( clockIntervals);
				monitor.tick();
			
		}catch( InterruptedException e ) {
			e.printStackTrace();
			System.out.println("TickThread interrupted, stopping clock.");
		}
		
	}
  }

}
