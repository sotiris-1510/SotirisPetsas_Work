package hw3ask1;

public class ClockMonitorImpl implements ClockMonitor{
	
	private int cTicks=0;

	
	public synchronized void tick() {
		
		cTicks++;
		System.out.println("Current value of ticks :" + cTicks);
		notifyAll();
	}
	
	
	public synchronized void sleepTicks(int clockTicks) throws InterruptedException {
		
		int wakeup = cTicks + clockTicks;
		
		System.out.println( Thread.currentThread().getName() + "is going to sleep for " + clockTicks + " and wake up at " + wakeup);
		
		while(cTicks< wakeup) {
			wait();
		}
		
		System.out.println( Thread.currentThread().getName() + " has woken up");
		
	}
}
