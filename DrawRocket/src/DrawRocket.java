/* Written: 01/10/2024

* Last updated: 06/10/2024
*
*
*
* Το προγραμμα για να μπορει να σχηματισει τον επιθυμητο πυραυλο τονχ χωριζει σε 4 κομματια , την πυραμιδα 
* που χχρησιμοποιειται ως κορθφυ και βαση , την διαχωριστικη γραμμη , τις 2 πυραμιδες ππου βλεπουν προς τα πανω
* και τις δυο που βλεπουν προς τα κατω .Με την χρηση του for και των if εντοπιζει που χρειαζεται να τυπωθει το καθε κομματι 
* 
*
*/

public class DrawRocket {

	public static void main(String[] args) {
		
		int num= Integer.parseInt(args[0]);
		
		int flag=Integer.parseInt(args[1]);
		
		int vasipyr=2*num-1;
		int rows=2*(vasipyr)+3+4*num;
		int collums=2*(vasipyr)+4;
		int x,y,counter=0;      
		int kena1 = vasipyr;   //τα κενα της κορυφης/βασης
		int kena2=0;           // τα κενα για τις πυραμιδες που βλεπουν προς τα κατω
		int kena3=num-1;       // τα κενα για τις πυραμιδες που βλεπουν προς τα πανω
		double random;
	    char ch1,ch2,ch3,ch4,ch5,ch6;
		
	if(num%2==0)
			counter=1;

	for( x=0 ;x<rows ;x++) {
		
		
		ch1='/';
		ch2='*';
		ch3='\\';
		ch4='+';
		ch5='=';
		ch6='|';
		
		
		
		if(flag==1) {
			
			random=Math.random();
			
			if(random>0.95) {
				ch1=ch2=ch3=ch4=ch5=ch6='#';
				
				
				
			}
			
		}
		
         		
		
		
		
		if(x==vasipyr+2*num+1) {                  // κανουν reset ολοι οι δεικτες για να μην επηρεαστει 
			kena2=0;                           // το δευτερο μισο του πυραβλου 
			kena3=num-1;
			kena1=vasipyr;
			counter=0;
		}
		
		if(x<vasipyr||x>rows-vasipyr-1) {
		
			  
           
			
            kena1 --;                                         // μειωνει τον αριθμο των κενων σε καθε γραμμη
			for( y=0;y<collums;y++) {
				if((y>kena1)&& y<collums/2-1) {                // κωδικας που δημιουργει την κορυφη και την 
					                                           // βαση του πυραβλου 
					System.out.print( ch1 );
				}
			
				
				else if(y==collums/2-1 || y==(collums/2 )) {
					
					System.out.print(ch2);
					
				}
				else if((y>collums/2 )&&(y<collums -kena1-1)){
			      System.out.print(ch3);
			      
								
				}
				else {
					System.out.print(" ");
			
			}   
	    }		
	}
	

    	if(x==vasipyr || x== vasipyr+2*num+1 || x== vasipyr+4*num+2 ) {         //δημιουργεια διαχωριστικης γραμμης
			
		
		for (y=0;y<collums;y++) {
			if(y==0 || y==collums-1) {
				System.out.print(ch4);
			}else if(y%2==1){
				System.out.print(ch5);
				
			}else 
				System.out.print(ch2);
		}
    }
	
	
	if((x<vasipyr+2*num +1 && x>vasipyr+num )||(x>vasipyr+2*num+1&&x<=vasipyr+3*num+1 )) {        // δημιουργεια για τις πυραμιδες
		                                                                              // που βλεπουν προς τα κατω
	      
			
			for(y=0;y<collums;y++) {
			
			if(y==0 || y==collums-1) {
				
				System.out.print(ch6);
			}
			
			else if((y>kena2&& y<collums/2- kena2)  || (y>collums/2-1 +kena2 && y<collums-kena2-1)) {
				if(counter%2==1)
					if(y%2==1) {
						System.out.print(ch3);
					}else 
						System.out.print(ch1);
				else if (counter%2==0){
					if(y%2==0) {
						System.out.print(ch3);
					}else 
						System.out.print(ch1);		
				}
				
			}else
				System.out.print(" ");
			
			
			
			}
			
			kena2++;		                                      //αυξανει τον αριθμο των κενων που θα εχει σε καθε γραμμη
			
	}
		
	     if((x>vasipyr&&x<=vasipyr+num)||(x>vasipyr+3*num+1 && x<vasipyr+4*num+2)){ // δυμιουργεια πυραμιδων που βλεπουν προς τα πανω 
		
			
			
			for(y=0;y<collums;y++) {
				
				if(y==0 || y==collums-1) {
					System.out.print(ch6);
					
				}else if(( y>kena3 && y<collums/2-kena3)||(y>collums/2+kena3-1 && y<collums-kena3-1 ) ){
					
					if(counter%2==0) {
						if(y%2==0) {
							System.out.print(ch3);}
						else 
							System.out.print(ch1);
					}
					else {
						if(y%2==0) {
							System.out.print(ch1);
						}else { 
							System.out.print(ch3);
					
						}
					}
							
					
					
				}else 
					System.out.print(" ");
					  
		        }
	         kena3--;                                     //μειωνει τον αριθμο των κενων που θα εχει σε καθε γραμμη
        }
	   System.out.println();
	   counter++;
	   
	}	
		 
		 
	} 

}

