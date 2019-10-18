#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product {
	char* name;	//array of stock items
	double price;
};

struct ProductStock {
	struct Product product;
	int quantity;
};

struct CustomerList {
	struct Product product;
	int quantity;
};

struct Shop {
	double cash;
	struct ProductStock stock[200];	// array of stock items. 200 items in the array
	int index;
};

struct Customer {
	char* name;
	double budget;
	struct CustomerList shoppingList[10]; //Maximum items on customers list = 10
	int index;
};

void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
	printf("-------------\n");
}

void printCustomer(struct Customer c)
{
	printf("-------------\n");
	printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
	
	for(int i = 0; i < c.index; i++)
	{
		printProduct(c.shoppingList[i].product);
		printf("%s ORDERS %d OF ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);
		// double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price;
		// printf("The cost to %s will be €%.2f\n", c.name, cost);
	}
}

struct Shop createAndStockShop()
{
	//struct Shop shop = { 1200.99 };	//Shop has 1200.99 on hand and 200 items in the shop
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock5.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
	printf("*************************\n");
	
	//Get the first line from shop CSV
	getline(&line, &len, fp);
	double availableCash = atof(line);
	struct Shop shop = {availableCash};	
	//Get subsequent lines from shop CSV
    while ((read = getline(&line, &len, fp)) != -1) {
		//read first line for cash on hand
		char *n = strtok(line, ",");
		char *p = strtok(NULL, ",");
		char *q = strtok(NULL, ",");
		
		int quantity = atoi(q);
		double price = atof(p);
		char *name = malloc(sizeof(char) * 50);	//new memory location to store n as name
		strcpy(name, n);
		struct Product product = { name, price };

		struct ProductStock stockItem = { product, quantity };
		shop.stock[shop.index++] = stockItem;
		printf("Item no.-> %3d | Product Name - %s \t\t| PRICE:%.2f \t| QTY:%3d\n", shop.index, name, price, quantity);
    }
	printf("*******************************\n");
	printf("Money-in-Shop: €%.2f\n", availableCash);
	printf("*******************************\n");
	return shop;
}

// Read Customer List of Items from CSV
struct Customer makeCustomer()
{
	//struct Customer customer = { "dominic", 55.99}; // Create the customer with budget
	FILE * f2p;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    f2p = fopen("items5.csv", "r");
    if (f2p == NULL)
        exit(EXIT_FAILURE);

	printf("\n");
	// Get first line from Customer List showing customer name and budget
	getline(&line, &len, f2p);
	char *cn = strtok(line, ",");
	char *bd = strtok(NULL, ",");
	
	//Customer name
	char *cname = malloc(sizeof(char) * 100);	//new memory location to store n as name
	strcpy(cname, cn);
	double budget = atof(bd);
	// Create the customer with budget
	struct Customer customer = {cname, budget}; 
	// Get subsequent lines from the Shop items
    while ((read = getline(&line, &len, f2p)) != -1) {
		
		char *nm = strtok(line, ",");
		char *qt = strtok(NULL, ",");
		
		//Product to buy... price & product name
		int quantity  = atoi(qt);
		char *name = malloc(sizeof(char) * 50);	//new memory location to store n as name
		strcpy(name, nm);
	
		//struct Product product = { name, price };
		struct Product product = { name };
		struct CustomerList listItem = { product, quantity };
		
		//Array to contain list items for this customer
		customer.shoppingList[customer.index++] = listItem;
		
		printf("ListItem -> %3d | Customer %s wants %3d units of %s \n", 
		customer.index, cname, quantity, name);
		
    }
	printf("*******************************\n");
	printf("%s has €%.2f available to spend...\n", cname, budget);
	printf("*******************************\n");
	return customer;
}


// Find if Product exists in shop
double findProductPrice(struct Shop s, char* n){
	
	for (int i = 0; i < s.index; i++){
		struct Product pd = s.stock[i].product;
		char *name = pd.name;
	
		// Item found in Store
		if (strcmp(name, n) == 0 ){
			return pd.price;	
		}
	}
		printf(">>>SORRY<<<, this shop does not have any such item: '%s' \n", n);
		return 0;
}

// Find Product Quantity if available in the shop
int findProductQty(struct Shop s, char* n){
	for (int i = 0; i < s.index; i++){
		struct Product pd = s.stock[i].product;
		int qty = s.stock[i].quantity;
		char *name = pd.name;
	
		// Item found in store
		if (strcmp(name, n) == 0 ){
			return qty;	
		}
	}
		return 0;
}

void printShop(struct Shop s)
{
	printf("Shop has %.2f in cash\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf("The shop has %d of the above\n", s.stock[i].quantity);
		printf("-------------\n");
	}
}

int compareOrderWithStock(int cQty, int shopQty, char *itemToBuy){
// Loop through the customers shopping list. Process all items with QTY != 0, for now, just provide appropriate message.
// First, locate the item and its index number in the Shop
	 
			if (cQty > shopQty){

				printf("...NOT enough items in stock to fulfil this order: '%s'\n", itemToBuy);
				//printf("Customer Ordered - %d units of %s\n", c.shoppingList[i].quantity, c.shoppingList[i].product.name);
				printf("...Customer Ordered - %d units of %s\n", cQty, itemToBuy);
				return -1;
			}
			
		return 0;
	}

int main(void) 
{
// 	Create a Customer and his items to buy
// 	struct Customer dominic = { "Dominic", 500.0 };
// 	
// 	WHY can't I just read this from the stock file?
//  	struct Product coke = { "Can Coke", 1.10 };
//  	struct Product bread = { "Bread", 0.7 };
//  	struct Product tomato = { "Tomato Sauce", 0.8 };
//  	struct Product binbag = { "Bin Bag", 2.50  };
// 	printProduct(coke);
// 
// 	Customers Shopping List
//  	struct ProductStock cokeStock = { coke, 120 };
//  	struct ProductStock breadStock = { bread, 2 };
//  	struct ProductStock tomatoStock = { tomato, 50 };
//  	struct ProductStock binbagStock = { binbag, 5 };
// 
// 	Customers Items stored inside Shopping Cart
//  	dominic.shoppingList[dominic.index++] = cokeStock;
//  	dominic.shoppingList[dominic.index++] = breadStock;
//  	dominic.shoppingList[dominic.index++] = tomatoStock;
//  	dominic.shoppingList[dominic.index++] = binbagStock;
	
	struct Shop shop = createAndStockShop();

	struct Customer customer = makeCustomer();
	
	// Shop items in an array
	char* shopItems[200000] = {};	//array pointers storing all shop items
	int i;
	for(i = 0; i < 200; i++)		//iterate the number of pointer times in the array
	{
		shopItems[i] = shop.stock[i].product.name;
		
	}
	
	int sindx;
	for( sindx = 0; sindx < (sizeof( shopItems ) / sizeof( shopItems[0] )); sindx++){
		if (shopItems[sindx] != NULL){
	       	// printf( "%s\n", shopItems[sindx] );
		}
	}
	
	printf( "...............................\n" );
	printf( "...............................\n" );
	printf( "...PROCESSING Customer ORDER...\n" );
	printf( "...............................\n" );
	printf( "...............................\n" );
	

	//Customer items in an array
	char* custItems[100] = {};//array pointers storing all customer list items
	int j;
	for(j = 0; j < 10; j++)// iterate the number of pointer times in the array
	{
		custItems[j] = customer.shoppingList[j].product.name;
	}


	int cindx;
	double runningTotal = 0.0;
	double itemPrice = 0.0;
	
	for( cindx = 0; cindx < (sizeof( custItems ) / sizeof( custItems[0] )); cindx++){
		if (custItems[cindx] != NULL){
	    // printf( "%s\n", custItems[cindx] );
			itemPrice = findProductPrice(shop, custItems[cindx]);
			//printf("This item %s costs %.2f\n", custItems[cindx], itemPrice);
			if (itemPrice != 0.0){
				printf("Item - %s costs %.2f\n", custItems[cindx], itemPrice);
				int qtyInShop = findProductQty(shop, custItems[cindx]);
					
				/*	Compare order with stock. If Qty ordered is > than stock available, report this otherwise
					go ahead and fulfil it. Extend this to multiple orders later
				*/
				int buyStatus = compareOrderWithStock(customer.shoppingList[cindx].quantity, qtyInShop, custItems[cindx]);
				if (buyStatus == -1){
					printf("...This item cannot be purchased at this time\n");
					// printf("notOK ARRAY %s\n", badItems[i]);
				}
				else{
					printf("...This item may be purchased if there's adequate credit to cover the order TOTAL.\n");
					runningTotal += itemPrice * customer.shoppingList[cindx].quantity;
					}
			}
		}
   }
   printf("*********************************************************\n");
   printf("Final bill for available items on this transaction is €%.2f\n", runningTotal);
   printf("*********************************************************\n");
   if (runningTotal > customer.budget){
	   printf("Transaction aborted... Customer %s has no enough fund...\n", customer.name);
   }
   else {
	   printf("Success... Updating shop inventory and cash status now...");
	   
	   /*
	   NEED TO COMPLETE...
	   //Update shop items
	   //Update shop cash status
	   //Print shop...
	   THEN, do the operate in live mode version...
	   */
   }
		// printCustomer(customer);
		// printShop(shop);
	
	printf("\n!!!!!!!!!!!    END of PROCESSING        !!!!!!!!!!!!!!!!!!\n\n");
		
// 	printCustomer(dominic);
// 	printShop(shop);
	
    return 0;
}

