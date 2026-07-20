import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class ImageProcessing {
	
	
	
	// LoadBMP
		public static int [][][] loadBMP(String filename) {
			
			
		  BufferedImage img = null;
		  try {
		      img = ImageIO.read(new File(filename));
		     } catch (IOException e) {
		    	 
		     System.out.println(e);
		}
		 int height = img.getHeight();
		
	     int width = img.getWidth();
		
		  
	     int image[][][] = new int[height][width][3];
		 int rgb;
		 
		 
		for (int h=0; h<height; h++) {
			
		
		    for (int w = 0; w<width; w++) {
		
		       rgb = img.getRGB(w, h);
		       image[h][w][0] = (rgb >> 16 ) & 0x000000FF;
		       image[h][w][1] = (rgb >> 8 ) & 0x000000FF;
		       image[h][w][2] = (rgb) & 0x000000FF;
	        	}
		}
		return image;
}
		
	//SAVE BMP	
		public static void saveBMP(int image[][][], String filename) {
			
			int height = image.length;
			int width = image[0].length;
			
			BufferedImage img = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
			
			int p, r, g, b;
			
			for (int h=0; h<height; h++){
			
			    for (int w = 0; w<width; w++){
			
			       r = image[h][w][0];
			       g = image[h][w][1];
			       b = image[h][w][2];
			// set the pixel value
			       p = (r << 16) | (g << 8) | b;
			       img.setRGB(w, h, p);
			   }
	      }
			
			
			try {
				
		    	File f = new File(filename);
			    ImageIO.write(img, "bmp", f);
			}
			catch (IOException e) {
			    System.out.println(e);
		}
	}
		
	// SAVE GRAYSCALE BMP	
		public static void saveGrayscaleBMP(int image[][], String filename) {
			
			int height = image.length;
			int width = image[0].length;
			
			BufferedImage img = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
			
			for (int h=0; h<height; h++) {
			
			    for (int w = 0; w<width; w++) {
			
			        int p = (image[h][w] << 16) | (image[h][w] << 8) | image[h][w];
			        img.setRGB(w, h, p);
		}
	}
			// write image
			try {
				
			   File f = new File(filename);
			   ImageIO.write(img, "bmp", f);
			    
			}
			catch (IOException e) {
			System.out.println(e);
		}
	}



	public static int[] display(String file,int x ,int y) {
		
		int[] colour= new int[3];
		
		if(!file.endsWith(".bmp")) {
			System.out.println("Image is not bmp . Program is terminated !");
		}
		
		
	    int[][][] image=loadBMP(file);
	    
	    if (x>image.length) {
	    	System.out.println("Height out of Bounds!");
	    	
	    }else if (y>image[x].length) {
	    	System.out.println("Width out of Bounds !");
	    	
	    }else {
	    	colour[0]=image[x][y][0];
	    	colour[1]=image[x][y][1];
	    	colour[2]=image[x][y][2];
	    
	    }
	
	
	return colour;
	}
	
	public static int[][][] hflip (int img[][][]){
		
		int height = img.length;
		int width = img[0].length;
		
		int[][][] flipped = new int[height][width][3];
		
		for (int h=0; h<height; h++) {
			for (int w=0; w<width; w++) {
				flipped[h][w][0] = img[h][width-1-w][0];
				flipped[h][w][1] = img[h][width-1-w][1];
				flipped[h][w][2] = img[h][width-1-w][2];
			}
		}
		
	return flipped;
		}
	
	
	public static int[][][] vflip (int img [][][] ) {
		
		int height = img.length;
		int width = img[0].length;
		
		int[][][] flipped = new int[height][width][3];
		
		for (int h=0; h<height; h++) {
			for (int w=0; w<width; w++) {
				flipped[h][w][0] = img[height-1-h][w][0];
				flipped[h][w][1] = img[height-1-h][w][1];
				flipped[h][w][2] = img[height-1-h][w][2];
			}
		}
		
	return flipped;
	}
	
	public static int[][][] rrotate (int img [][][]) {
		
		int height = img.length;
		int width = img[0].length;
		
		// rotating 90 degrees swaps width and height
		int[][][] rotated = new int[width][height][3];
		
		for (int h=0; h<height; h++) {
			for (int w=0; w<width; w++) {
				rotated[w][height-1-h][0] = img[h][w][0];
				rotated[w][height-1-h][1] = img[h][w][1];
				rotated[w][height-1-h][2] = img[h][w][2];
			}
		}
		
	return rotated;
	}
	
	public static int[][][] lrotate (int img[][][]) {
		
		int height = img.length;
		int width = img[0].length;
		
		// rotating 90 degrees swaps width and height
		int[][][] rotated = new int[width][height][3];
		
		for (int h=0; h<height; h++) {
			for (int w=0; w<width; w++) {
				rotated[width-1-w][h][0] = img[h][w][0];
				rotated[width-1-w][h][1] = img[h][w][1];
				rotated[width-1-w][h][2] = img[h][w][2];
			}
		}
		
	return rotated;
	}
	
	public static int [][] grayscale(int img[][][]) {
		
		
		int x,y;
		
		int[][] grayimg= new int[img.length][img[0].length];
		
		
		
		for (x=0;x<grayimg.length;x++) {
			
			for(y=0;y<grayimg[x].length;y++) {
				
				grayimg[x][y]= (int)Math.round(img[x][y][0]*0.299+img[x][y][1]*0.587+img[x][y][2]*0.114);
			
			}
		}
		
		
		
	return grayimg;
	}

	public static void main(String[] args) {
		
		
		String option= args[0];
		String file;
		int argsnum;
		
		
		
		
		
		switch (option) {
			
			
			case "-display": 
				
				 file= args[1];
				int x=Integer.parseInt(args[2]);
				int y=Integer.parseInt(args[3]);
				
				int[] colour = display(file,x,y);
				
				System.out.println("RGB ["+x+','+y+']'+"   =   ("+colour[0]+','+colour[1]+','+colour[2]+')');
				
				break;
				
			case "-hflip":
				file = args[1];
				
				if(!file.endsWith(".bmp")) {
					System.out.println("Image is not bmp . Program is terminated !");
					break;
				}
				
				int[][][] imgH = loadBMP(file);
				int[][][] flippedH = hflip(imgH);
				saveBMP(flippedH, "hflip-"+file);
				break;
				
			case "-vflip":
				file = args[1];
				
				if(!file.endsWith(".bmp")) {
					System.out.println("Image is not bmp . Program is terminated !");
					break;
				}
				
				int[][][] imgV = loadBMP(file);
				int[][][] flippedV = vflip(imgV);
				saveBMP(flippedV, "vflip-"+file);
				break;
				
			case "-rrotate":
				file = args[1];
				
				if(!file.endsWith(".bmp")) {
					System.out.println("Image is not bmp . Program is terminated !");
					break;
				}
				
				int[][][] imgRR = loadBMP(file);
				int[][][] rotatedR = rrotate(imgRR);
				saveBMP(rotatedR, "rrotate-"+file);
				break;
				
			case"-lrotate":
				file = args[1];
				
				if(!file.endsWith(".bmp")) {
					System.out.println("Image is not bmp . Program is terminated !");
					break;
				}
				
				int[][][] imgLR = loadBMP(file);
				int[][][] rotatedL = lrotate(imgLR);
				saveBMP(rotatedL, "lrotate-"+file);
				break;
				
			case"-grayscale":
				argsnum=1;
				
				
				while(!StdIn.isEmpty()){
					
					file=args[argsnum];
					
					
					if(!file.endsWith(".bmp")) {
						
						System.out.println("Image is not bmp . Program is terminated !");
						break;
						
					}else {
						
						
					int[][][]img=loadBMP(file);	
					int[][] gray=grayscale(img);
					
					saveGrayscaleBMP(gray,"gray-"+file);
					
					
					
					
					}
					
					
					
				  
					
					
					
				   argsnum++;
				
				}
				
				break;
				
			default:
				System.out.println("Option not available. Program is terminated ");
		}	
				
			
			
		

	}

}
