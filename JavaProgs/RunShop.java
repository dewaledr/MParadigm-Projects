package GmitShop;

import java.util.Scanner;

public class RunShop {

	public static void main(String[] args) {
		{
			
			//int ans;
			String str;
			
			Scanner sin = new Scanner(System.in);
//			System.out.println("Enter your Choice: ");
//			str = sin.nextLine();
//			System.out.println("You entered string " + str);
//			sin.close();

			
			
			//char resp = '0';
			System.out.println("\n");
			System.out.println("\n");
			System.out.println("***************************************************************************************");
			System.out.println("***        GMIT JAVA Shop, Inc. Shop Manager on Duty today is: Francis Adepoju      ***");
			System.out.println("***        *******************************************************************      ***");
			System.out.println("***                       PLEASE ENTER YOUR DESIRED OPTION                          ***");	
			System.out.println("***                       Enter  0 ==> End the Program,                             ***");
			System.out.println("***                       Enter  1 ==> Single Item Purchase                         ***");            
			System.out.println("***                       Enter  2 ==> Multiple Purchase from .CSV file             ***"); 
			System.out.println("***                                                                                 ***");
			System.out.println("***************************************************************************************");
			System.out.println("***************************************************************************************");
			//System.out.println("Choice: ");
			
			System.out.println("Enter your Choice: ");
			str = sin.nextLine();
			//System.out.println("You entered string " + str);
			//sin.close();
			

			// While str does not match regex zero, the while loop is active unless str is also not = 1 or 2.
			while (!str.matches("[0]")){
				if (str.matches("1") ){
					//singleProcess();
					System.out.println("Choice: is " + str);
				}
				else if (str.matches("2") ){
					//batchProcess();
					System.out.println("Choice: is " + str);
				}
				else{
					System.out.println("!!!!");
					System.out.println("!!!! Error... Irregular input " + "[" + str + "]" +" detected. Please try again...");
					System.out.println("!!!!");
				}
				
				System.out.println("***************************************************************************************");
				System.out.println("***                                                                                 ***");
				System.out.println("***                       PLEASE ENTER YOUR DESIRED OPTION                          ***");	
				System.out.println("***                       Enter  0 ==> End the Program,                             ***");
				System.out.println("***                       Enter  1 ==> Single Item Purchase                         ***");            
				System.out.println("***                       Enter  2 ==> Multiple Purchase from .CSV file             ***"); 
				System.out.println("***                                                                                 ***");
				System.out.println("***************************************************************************************");
				System.out.println("***************************************************************************************");
				//System.out.println("Choice: ");
				System.out.println("Enter your Choice: ");
				str = sin.nextLine();
				//System.out.println("You entered string " + str);
				
			}
			System.out.println("You entered string " + str + " - END of Program...");
			sin.close();
			//return 0;
		}

	}

}
