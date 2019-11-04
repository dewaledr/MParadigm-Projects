
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

public class Customer {
	
	private String name;
	private double budget;
	private ArrayList<ProductStock> shoppingList;
	
	static NumberFormat formatter = new DecimalFormat("#,##0.00");
	
	public Customer(String fileName) {
		shoppingList = new ArrayList<>();
		List<String> lines = Collections.emptyList();
		try {
			lines = Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
			String[] firstLine = lines.get(0).split(",");
			name = firstLine[0];
			budget = Double.parseDouble(firstLine[1]);
			// i am removing at index 0 as it is the only one treated differently
			lines.remove(0);
			for (String line : lines) {
				String[] arr = line.split(",");
				String name = arr[0];
				int quantity = Integer.parseInt(arr[1].trim());
				Product p = new Product(name, 0);
				ProductStock s = new ProductStock(p, quantity);
				shoppingList.add(s);
			}
			
		}

		catch (IOException e) {

			// do something
			e.printStackTrace();
		}
	}
	
	/// 3-arg Constructor for singlePRocess()....FA
	public Customer(double bgt, String nm, int qty) {
		shoppingList = new ArrayList<>();
		name = nm;
		budget = bgt;
		int quantity = qty;
		Product p = new Product(name, 0);
		ProductStock s = new ProductStock(p, quantity);
		shoppingList.add(s);			
	}
			
	
	public String getName() {
		return name;
	}


	public double getBudget() {
		return budget;
	}

	public void setBudget(double moneyIn) {
		budget = moneyIn;
	}

	public ArrayList<ProductStock> getShoppingList() {
		return shoppingList;
	}


	@Override
	public String toString() {
		// return All Customer detail plus index of items in her shopping list
		String ret = "Customer: name = " + name + ", Budget = €" + formatter.format(budget) + 
					"\nshoppingList:\n" + "==============\n";
		for (ProductStock productStock : shoppingList) {
			ret+= "Item " + (shoppingList.indexOf(productStock) + 1) + "    " +
					productStock.getProduct().getName() + "\tQty: " + 
					productStock.getQuantity() + "\n";
		}
		return ret;
	}
	
//	public static void main(String[] args) {
//		Customer james = new Customer("src/items3.csv");
//		System.out.println(james);
//	}
	
	

}
