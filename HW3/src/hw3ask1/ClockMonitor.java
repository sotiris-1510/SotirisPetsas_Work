package hw3ask1;

public interface ClockMonitor {
	
	void tick();
	void sleepTicks(int clockTicks ) throws InterruptedException;
	
	
}


