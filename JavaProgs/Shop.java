/*
 =============================================================================
 Name        : Multi-Paradigm PRogramming, Shop.java Assignment, 2019 NOVEMBER
 Author      : Francis Adepoju - G00364694
 Version     :
 Copyright   : 
 Description : 
 =============================================================================
 */
package GmitShop;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Shop {

	private double cash;
	private ArrayList<ProductStock> stock;

	// Numeric Formatter utility in Java
	static NumberFormat formatter = new DecimalFormat("#,##0.00");

	// Shop constructor
	public Shop(String fileName) {
		stock = new ArrayList<>();
		List<String> lines = Collections.emptyList();
		try {
			lines = Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
			// System.out.println(lines.get(0));
			cash = Double.parseDouble(lines.get(0));
			// i am removing at index 0 as it is the only one treated differently
			lines.remove(0);
			for (String line : lines) {
				String[] arr = line.split(",");
				String name = arr[0];
				double price = Double.parseDouble(arr[1]);
				int quantity = Integer.parseInt(arr[2].trim());
				Product p = new Product(name, price);
				ProductStock s = new ProductStock(p, quantity);
				stock.add(s);
			}

		}

		catch (IOException e) {
			// print stack trace
			e.printStackTrace();
		}
	}

	public double getCash() {
		return cash;
	}

	public void setCash(double moneyIn) {
		cash += moneyIn;
	}

	public ArrayList<ProductStock> getStock() {
		return stock;
	}

	@Override
	public String toString() {
		// return "Shop cash=" + cash +"\n" + , stock=" + stock + "]";
		String ret = "Cash available in Shop is:\t€" + formatter.format(cash) + "\nShop Item List:\n"
				+ "===============\n";
		for (ProductStock productStock : stock) {
			// Return All items with their indices in the shop array
			ret += "Item " + (stock.indexOf(productStock) + 1) + "    " + productStock.getProduct().getName()
					+ "\tPrice: €" + formatter.format(productStock.getProduct().getPrice()) + "\tQuantity: " + productStock.getQuantity()
					+ "\n";
		}
		return ret;
	}

	static int checkItemsExistsInShop(Shop s, String item) {
		
		int okItem = 0;
		// String itemName
		for (int j = 0; j < s.getStock().size(); j++) {
			if (s.getStock().get(j).getProduct().getName().equalsIgnoreCase(item)) {
				// Return the item name with correct capitalization from the shop List item
				// 'item' is as written by customer, with possible wrong capitalization
				System.out.println(s.getStock().get(j).getProduct().getName());
				
				return okItem;
			}
		}
		System.out.println(">>> " + item + " <<<" + "\nNOT AVAILABLE in the Shop");
		return -1;
	}

	// Method to Confirm that there are enough items to meet customer order in the shop
	static int checkEnoughItemsInShop(Shop s, String item) {
		int qty = 0;
		for (int k = 0; k < s.getStock().size(); k++) {
			if (s.getStock().get(k).getProduct().getName().equalsIgnoreCase(item)) {
				qty = s.getStock().get(k).getQuantity();
			}
		}
		return qty;
	}

	// Method to retrieve item price from the shop
	static double itemGetPrice(Shop s, String item) {
		double itemPrice = 0.0;
		for (int i = 0; i < s.getStock().size(); i++) {
			if (s.getStock().get(i).getProduct().getName().equalsIgnoreCase(item)) {
				itemPrice = s.getStock().get(i).getProduct().getPrice();
			}
		}
		return itemPrice;
	}

	// Method to Confirm that Customer has enough money to purchase this item
	static double checkCustomerBudget(Customer c) {
		double myCash = c.getBudget();
		return myCash;
	}

	// Method to Update Shop cash with total of purchase updateShopCash(shop,itemCost);
	static void updateShopCash(Shop s, double currentItemCost) {
		s.setCash(currentItemCost);
	}

	// Method to Update Shop inventory level updateShopInventory(shop,
	// p.getProduct().getName());
	static void updateShopInventory(Shop s, String name, int qtyBought) {
		for (int i = 0; i < s.getStock().size(); i++) {
			if (s.getStock().get(i).getProduct().getName().equalsIgnoreCase(name)) {

				// Get original quantity before transaction 
				//int oldQty = s.getStock().get(i).getQuantity();
				// System.out.println("Old QTY = " + oldQty);
				//oldQty -= qtyBought;...nope!

				// Set inventory quantity after transaction
				s.getStock().get(i).setQuantity(qtyBought);
				// System.out.println("New QTY = " + s.getStock().get(i).getQuantity());
			}
		}

	}

////////////////////////////////////////////////////////////////////////////////
	static void batchProcess() {
		// Batch processing logic
		// Create and stock Shop and Customer Objects
		Shop shop = new Shop("src/GmitShop/stockItems.csv");
		Customer customer = new Customer("src/GmitShop/custItems.csv");

		System.out.println("Printing Shop Items");
		System.out.println(shop);
		System.out.println("-------------------- End Shop List -----------------------\n");
		System.out.println("Printing Customer List Items");
		System.out.println(customer);
		System.out.println("---------------------- End Customer List -----------------\n");

		// Customer declared budget must be stored here before being updated subsequently.
		double customerMoneyYTD = customer.getBudget();
		
		ArrayList<ProductStock> itemsList = customer.getShoppingList();
		
		double customerExcess = customer.getBudget();

		System.out.println("Processing Customer items");
		System.out.println("=========================");
		for (int i = 0; i < itemsList.size(); i++) {

			ProductStock p = itemsList.get(i);
			
			// Fetch item price from shop
			double pdtPrice = itemGetPrice(shop, p.getProduct().getName());

			// Confirm that items in the customers List is/are available in the Shop
			int exists = checkItemsExistsInShop(shop, p.getProduct().getName());
			
			if (exists == 0) {
				// Confirm that there are enough items to meet customer order in the shop
				int itemQtty = checkEnoughItemsInShop(shop, p.getProduct().getName());
				//System.out.println("QTY in Shop: " + itemQtty);
				System.out.println("Customer wants " + p.getQuantity() + " " + p.getProduct().getName() +
						", Unit cost: €" + formatter.format(pdtPrice));

				// Confirm that Customer has enough money to purchase
				double itemCost = p.getQuantity() * pdtPrice;

				if (itemQtty < p.getQuantity()) {
					System.out.println(
							"SORRY... " + "(" + p.getProduct().getName() + ")" + " Not enough quantity in stock");
				} else {
					double custMoney = checkCustomerBudget(customer);
					System.out.println("Cost to customer: €" + formatter.format(itemCost));
					if ((customer.getBudget() < itemCost) || (customerMoneyYTD < itemCost)) {
						System.out.println("Sorry...Customer does not have enough money to buy this item.");
						System.out.println("CUSTOMER has... €" + formatter.format(custMoney) + " Remaining.");
					} else {
						custMoney -= itemCost;
						customerExcess = custMoney;
						
						// Update customer budget
						customer.setBudget(custMoney);

						// Update Shop cash with total of purchase and
						updateShopCash(shop, itemCost);

						System.out.println("CUSTOMER has... €" + formatter.format(custMoney) + " Remaining.");

						// Update Shop inventory level on this item
						updateShopInventory(shop, p.getProduct().getName(), p.getQuantity());
					}
				}

				System.out.println("-----------------------------------------");
			} else {
				
				System.out.println("-----------------------------------------");
			}
		} 
		// Print New Shop inventory level
		System.out.println(shop);
		System.out.println("-------------------------------------------------------------");
		System.out.println("                  ... END OF PROCESSING ...                  ");
		System.out.println("-------------------------------------------------------------");
		
		// Print New Shop and Customer cash status
		System.out.println("\nCUSTOMER has... \t€" + formatter.format(customerExcess) + " Remaining.");
		System.out.println("\nCash in SHOP is now... \t€" + formatter.format(shop.getCash()));
		System.out.println("-----------------------------------------");
	} 	/// End of batchProcess()

	
////////////////////////////////////////////////////////////////////////////////

	static void singleProcess() {
	// Single Item processing logic
		
		
		//Test data
		//	double cusBudget = 5000;
		//	String itemName = "imac computer";
		//	int itemQty = 2;
		
		// Take customer inputs from sysin
		double cusBudget = 0.00;
		String itemName = "";
		int itemQty = 0;
		
		Scanner sinC = new Scanner(System.in);
		try {
			// Declare how much money customer is willing to spend
			System.out.println("How much money do you have to spend? ");
			cusBudget = Double.parseDouble(sinC.nextLine());
			// Provide item name of interest
			System.out.println("What Product do you want to buy? ");
			itemName = sinC.nextLine();
			// Quantity of item desired
			System.out.println("How many "+ itemName + " do you want? ");
			itemQty = Integer.parseInt(sinC.nextLine());
		}
		catch (NoSuchElementException e) {
			e.printStackTrace();
			sinC.close();
		}
		// Re-echo customer inputs
		System.out.println("OK, you want to buy " + itemQty + " " + itemName + " and you have €" + formatter.format(cusBudget) + ".\n");
		
		// Create and Stock Shop and Customer objects
		Shop 			shop = new Shop("src/GmitShop/stockItems.csv");
		Customer 	customer = new Customer(cusBudget, itemName, itemQty);
		

		System.out.println("Printing Shop Items");
		System.out.println(shop);
		System.out.println("-------------------- End Shop List -----------------------\n");
		System.out.println("Printing Customer List Items");
		System.out.println(customer);
		System.out.println("---------------------- End Customer List -----------------\n");
		
		// Customer declared budget must be stored here before being updated subsequently.
		double customerMoneyYTD = customer.getBudget();
		
		// Read Customer Lists into an array
		ArrayList<ProductStock> itemsList = customer.getShoppingList();

		double customerExcess = customer.getBudget();

		System.out.println("Processing Customer items");
		System.out.println("=========================");
		for (int i = 0; i < itemsList.size(); i++) {

			ProductStock p = itemsList.get(i);
			// String pdtName = shop.getStock().get(i).getProduct().getName();

			double pdtPrice = itemGetPrice(shop, p.getProduct().getName());
			// System.out.println("PriceFromFILE " + p.getProduct().getPrice());

			// Confirm that items in the customers List is/are available in the Shop
			int exists = checkItemsExistsInShop(shop, p.getProduct().getName());
			
			if (exists == 0) {
				// Confirm that there are enough items to meet customer order in the shop
				int itemQtty = checkEnoughItemsInShop(shop, p.getProduct().getName());
				//System.out.println("QTY in Shop: " + itemQtty);
				System.out.println("Customer wants " + p.getQuantity() + " " + p.getProduct().getName() +
								", Unit cost: €" + formatter.format(pdtPrice));

				// Confirm that Customer has enough money to purchase
				double itemCost = p.getQuantity() * pdtPrice;

				if (itemQtty < p.getQuantity()) {
					System.out.println(
							"SORRY... " + "(" + p.getProduct().getName() + ")" + " Not enough quantity in stock");
				} else {
					double custMoney = checkCustomerBudget(customer);
					System.out.println("Cost to customer: €" + formatter.format(itemCost));
					if ((customer.getBudget() < itemCost) || (customerMoneyYTD < itemCost)) {
						System.out.println("Sorry...Customer does not have enough money to buy this item.");
						System.out.println("CUSTOMER has... €" + formatter.format(custMoney) + " Remaining.");
					} else {
						
						custMoney -= itemCost;
						customerExcess = custMoney;
						
						// Update customer budget
						customer.setBudget(custMoney);

						// Update Shop cash with total of purchase and
						updateShopCash(shop, itemCost);

						System.out.println("CUSTOMER has... €" + formatter.format(custMoney) + " Remaining.");

						// Update Shop inventory level on this item
						updateShopInventory(shop, p.getProduct().getName(), p.getQuantity());
					}
				}

				System.out.println("-----------------------------------------");

			} else {
				
				System.out.println("-----------------------------------------");
			}
		} 
		
		// Print New Shop inventory level
		System.out.println(shop);
		System.out.println("-------------------------------------------------------------");
		System.out.println("                  ... END OF PROCESSING ...                  ");
		System.out.println("-------------------------------------------------------------");
		
		// Print New Shop and Customer cash status
		System.out.println("\nCUSTOMER has... \t€" + formatter.format(customerExcess) + " Remaining.");
		System.out.println("\nCash in SHOP is now... \t€" + formatter.format(shop.getCash()));
		System.out.println("-----------------------------------------");
	}	/// End of sigleProcess()

///////////////////////////////////////////////////////////////////////////////////////////////////////
//@SuppressWarnings("unlikely-arg-type")f
	public static void main(String[] args) {

		String str;

		Scanner sin = new Scanner(System.in);

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

		System.out.println("Enter your Choice: ");
		str = sin.nextLine();

		// While str does not match regex zero, the while loop is active.
		// Therefore, continue to loop irrespective of input until 1 or 2 is entered.
		while (!str.matches("[0]")) {
			if (str.matches("1")) {
				// Run the single process function taking customer transaction details from the keyboard
				singleProcess();
			} else if (str.matches("2")) {
				// Run the batch Process function taking customer items from .CSV file
				batchProcess();
			} else {
				System.out.println("!!!!");
				System.out
						.println("!!!! Error... Irregular input " + "[" + str + "]" + " detected. Please try again...");
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

			System.out.println("Enter your Choice: ");
			str = sin.nextLine();
		}
		System.out.println("!!! You entered " + str + " - Shop program will now END...");
		sin.close();
		// return 0;
	} 		/// End of main
} 			/// END of class
