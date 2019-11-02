package GmitShop;

import java.util.Scanner;

public class RunShop {

	public static void main(String[] args) {
		{
			
			var keyboard = new Scanner(System.in);

			
			
			//char resp = '0';
			System.out.println("\n");
			System.out.println("\n");
			System.out.println("***************************************************************************************\n");
			System.out.println("***        GMIT JAVA Shop, Inc. Shop Manager on Duty today is: Francis Adepoju       ***\n");
			System.out.println("***        *******************************************************************      ***\n");
			System.out.println("***                       PLEASE ENTER YOUR DESIRED OPTION                          ***\n");	
			System.out.println("***                       Enter  0 ==> End the Program,                             ***\n");
			System.out.println("***                       Enter  1 ==> Single Item Purchase                         ***\n");            
			System.out.println("***                       Enter  2 ==> Multiple Purchase from .CSV file             ***\n"); 
			System.out.println("***                                                                                 ***\n");
			System.out.println("***************************************************************************************\n");
			System.out.println("***************************************************************************************\n");
			System.out.println("Choice: ");
			//scanf("%s", &resp);
			//System.out.println("enter an integer");
			//String myInput = keyboard.nextLine();
			
			String myInput = keyboard.next();
			while (!myInput.isEmpty() || !myInput.isBlank() ){
				if (myInput == "1" ){
					//singleProcess();
					System.out.println("Choice: is " + myInput);
				}
				else if (myInput == "2" ){
					//batchProcess();
					System.out.println("Choice: is " + myInput);
				}
				else if (myInput == "0") {
					System.out.println("Choice: is " + myInput);
					break;
				}
				else{
					System.out.println("!!!!\n");
					System.out.println("!!!! Error... Irregular input detected. Please try again...\n");
					System.out.println("!!!!\n");
					//break;
				}
				System.out.println("***************************************************************************************\n");
				System.out.println("***                                                                                 ***\n");
				System.out.println("***                       PLEASE ENTER YOUR DESIRED OPTION                          ***\n");	
				System.out.println("***                       Enter  0 ==> End the Program,                             ***\n");
				System.out.println("***                       Enter  1 ==> Single Item Purchase                         ***\n");            
				System.out.println("***                       Enter  2 ==> Multiple Purchase from .CSV file             ***\n"); 
				System.out.println("***                                                                                 ***\n");
				System.out.println("***************************************************************************************\n");
				System.out.println("***************************************************************************************\n");
				System.out.println("Choice: ");
				//scanf("%s", &resp);
				myInput = keyboard.nextLine();
			}
			//return 0;
		}

	}

}
