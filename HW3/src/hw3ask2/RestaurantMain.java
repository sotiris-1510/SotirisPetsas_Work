package hw3ask2;

import java.util.concurrent.Semaphore;

public class RestaurantMain {
	
	public static void main (String[] args) {
		
		 Semaphore pitaSem= new Semaphore(0);
		 Semaphore kreasSem= new Semaphore(0);
		 Semaphore laxanikaSem = new Semaphore(0);
		
		
		 Semaphore waiterSem = new Semaphore(1);
		 
		 WaiterThread waiter = new WaiterThread(pitaSem,kreasSem,laxanikaSem,waiterSem);

	     CustomerThread c1 = new CustomerThread("Customer A", "PITA",pitaSem,waiter);
	     CustomerThread c2 = new CustomerThread("Customer B", "KREAS",kreasSem,waiter);
	     CustomerThread c3 = new CustomerThread("Customer C", "LAXANIKA",laxanikaSem,waiter);

	     waiter.start();
	     c1.start();
	     c2.start();
	     c3.start();
		
		
		
	}

}
