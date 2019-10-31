package GmitShop;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

public class Shop {

	private double cash;
	private ArrayList<ProductStock> stock;

	// Shop constructor
	public Shop(String fileName) {
		stock = new ArrayList<>();
		List<String> lines = Collections.emptyList();
		try {
			lines = Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
			System.out.println(lines.get(0));
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
			// do something
			e.printStackTrace();
		}
	}

	public double getCash() {
		return cash;
	}

	public ArrayList<ProductStock> getStock() {
		return stock;
	}

	@Override
	public String toString() {
		// return "Shop cash=" + cash +"\n" + , stock=" + stock + "]";
		String ret = "Shop cash = " + cash + " \n" + "Item List = [\n";
		for (ProductStock productStock : stock) {

			ret += productStock.getProduct().getName() + " Price: " + productStock.getProduct().getPrice()
					+ " Quantity: " + productStock.getQuantity() + "\n";
		}
		return ret + "]";
	}
	
	static int checkItemsExistsInShop(Shop s, String item) {
		int stat = 0;
		
		//String itemName 
		for (int j = 0; j < s.getStock().size(); j++) {
			if (s.getStock().get(j).getProduct().getName().equalsIgnoreCase(item)){
				System.out.println("AVAILABLE in SHOP - " + item);
				return stat;
			}
		}
		System.out.println("NOT AVAILABLE in SHOP - " + item);
		return -1;
	}
//
//
	@SuppressWarnings("unlikely-arg-type")
	public static void main(String[] args) {
		
		Shop 		shop 		= new Shop("src/stock3.csv");
		Customer 	customer 	= new Customer("src/items3.csv");
		
		System.out.println("Printing Shop Items List");
		System.out.println(shop);
		System.out.println("Printing Customer List");
		System.out.println(customer);
		
		// Batch Purchase
		// Read Shop and Customer Lists into an array
		//ArrayList<ProductStock> stockItems = shop.getStock();
		
		ArrayList<ProductStock> itemsList = customer.getShoppingList();
		
		for (int i = 0; i < itemsList.size(); i++) {
			// Car c = car.get(i);
			// System.out.println (c.getPrice());
//			Product p = itemsList.getName(i);
			ProductStock p = itemsList.get(i);
//			System.out.println("----itemsList---");
//			System.out.println("ItemsList " + itemsList.get(i));
//			System.out.println("From Shop " + shop.getStock().get(i).getProduct().getName());
//			System.out.println("From List " + p.getProduct().getName());
			
			// Confirm that items in the customers List is in the Shop
			int stats = checkItemsExistsInShop(shop, p.getProduct().getName());
			
			if (stats == 0) {
				System.out.println("Process purchase");
				System.out.println("-------------------------------");
			}
			else {
				System.out.println("REPORT item inventory status");
				System.out.println("-------------------------------");
			}
		}
		
		
//		for (int i = 0; i < stockItems.size(); i++) {
			// Car c = car.get(i);
			// System.out.println (c.getPrice());
//			Product p = stockItems.getName(i);
//			ProductStock p = stockItems.get(i);
//			System.out.println("----stockItems---");
//			System.out.println("ItemsList " + stockItems.get(i));
//			System.out.println("From Shop " + shop.getStock().get(i).getProduct().getName());
//			System.out.println("From List " + p.getProduct().getName());
			
//			int stats = checkItemsExistsInShop(shop, p);
			
			//if (searchList.get(i).getName().contains(search))
//			System.out.println("Returned " + stats);
			
//			if(shop.getStock().get(i).getProduct().getName().contains(p.getProduct().getName())){
////			if(shop.getStock().contains(p.getProduct().getName())){
//				System.out.println("Item " + p.getProduct().getName() + " is available");
//			}
//			else {
//				System.out.println("Item " + p.getProduct().getName() + " is NOT available");
//				
//			}
//		}
		
		
// TO DOs		
		// Confirm that Enough items to meet the order exists in the shop
		// Confirm that Customer has enough money to purchase
		// Update Shop cash with total of purchase
		// Decrement Shop with quantity of item purchased - successfully passed
		// Print New Shop cash level
		// Print New Shop inventory level
	}

}
