#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Product struct
struct Product {
	char* name;	//array of stock items
	double price;
};
// Stock of Products
struct ProductStock {
	struct Product product;
	int quantity;
};
// Customers Item list of products to buy
struct CustomerList {
	struct Product product;
	int quantity;
};
// Shop product items available
struct Shop {
	double cash;
	struct ProductStock stock[200];	// array of stock items. 200 items in the array
	int index;
};
// Customer struct 
struct Customer {
	char* name;
	double budget;
	struct CustomerList shoppingList[10]; //Maximum items on customers list = 10
	int index;
};
// Utility to print product details
void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
	printf("-------------\n");
}
// Utility to print customer details
void printCustomer(struct Customer c)
{
	printf("-------------\n");
	printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
	
	for(int i = 0; i < c.index; i++)
	{
		printProduct(c.shoppingList[i].product);
		printf("%s ORDERS %d OF ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);
	}
}

// Utility Print Remaining items in the Shop
void printShop(struct Shop s)
{
	//printf("Shop has %.2f in cash\n", s.cash);
	printf("***********.............REMAINING INVENTORY ITEMS IN THE SHOP..............************\n");
	printf("***************************************************************************************\n");
	for (int i = 0; i < s.index; i++)
	{
		printf("Item->%3d  Product Name - %s PRICE: €%7.2f\tQTY: %3d\n", i+1, s.stock[i].product.name, 
		s.stock[i].product.price, s.stock[i].quantity);
	}
}

// Create and Stock the Shop with products
struct Shop createAndStockShop()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock1.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
	printf("**********.....NOW CREATING AND STOCKING THE SHOP WITH INVENTORY ITEMS.....************\n");
	printf("***************************************************************************************\n");
	//Get the first line from shop CSV OR from the Keyboard
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
		// Print items as they are created
		printf("Item->%3d  Product Name - %s  PRICE: €%7.2f\tQTY: %3d\n", shop.index, name, price, quantity);
    }
	printf("**********************************************************************************\n");
	printf("Initial Cash in Shop: €%.2f\n", availableCash);
	printf("**********************************************************************************\n");
	return shop;
}

// Read Customer List of Items from CSV
struct Customer makeCustomer()
{
	FILE * f2p;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    f2p = fopen("items1.csv", "r");
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
	
		struct Product product = { name };
		struct CustomerList listItem = { product, quantity };
		
		// Populate the Array to contain list items for this customer
		customer.shoppingList[customer.index++] = listItem;
		// Print the Customer items list read from .CSV file
		printf("ListItem->%3d | Customer %s wants %3d units of %s \n", 
		customer.index, cname, quantity, name);
		
    }
	printf("***************************************************************************************\n");
	printf("%s has €%.2f available to spend...\n", cname, budget);
	printf("\n");
	printf("***** ORDER Item STATUS Report ***** ***************** ********************* **********\n");
	return customer;
}

// Read freeCustomer Item from keyboard
struct Customer freeCustomer(){
	// Create the customer
	struct Customer freeCustomer = {}; 

	float bgt;
	char temp;
	char *nm;
	int qt;
	
	printf("Please enter customer budget... ");
	scanf("%f", &bgt);	
	
	// printf("Please enter item Quantity here... ");
	// 	scanf("%d", &qt);
	printf("Please enter item name here... ");
	// temp statement to clear buffer, This is needed for next line to work...
	scanf("%c", &temp); 
	//Read strings inasmuch as \n is not encountered --- So as to be able to take in names with spaces in between	
	scanf("%[^\n]s", nm); 

	printf("Please enter item Quantity here... ");
	scanf("%d", &qt);
	
	char *name = malloc(sizeof(char) * 50);	//new memory location to store n as name
	strcpy(name, nm);
	
	printf("***************************************************************************************\n");
	printf("\nCustomer has €%.2f available to spend on %d units of %s...\n", bgt, qt, name);
	
	freeCustomer.name = "Anonymous";
	freeCustomer.budget = bgt;
	freeCustomer.shoppingList[0].quantity = qt;
	freeCustomer.shoppingList[0].product.name = name;
	freeCustomer.index = 1;
	
	printf("\n");
	printf("***** ORDER Item STATUS Report ***** ***************** ********************* **********\n");
	return freeCustomer;
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
	printf("---------------------------------------------------------------------------------------\n");
	printf(">>> '%s' <<< ...SORRY...no such item in the shop: \n", n);
	printf("---------------------------------------------------------------------------------------\n");
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

// Find Product Item Index if item is available in the shop
int findItemIndex(struct Shop s, char* n){
	for (int i = 0; i < s.index; i++){
		struct Product pd = s.stock[i].product;
		char *name = pd.name;
	
		// Item found in store
		if (strcmp(name, n) == 0 ){
			//printf("....findItemIndex...%3d\n", i+1);
			return i;	
		}
	}
	return 0;
} 

// Compare order items with available items in the Shop... 
// Be careful of spelling and Capitalization here...		
int compareOrderWithStock(int cQty, int shopQty, double itemPrice, double customerFund, char *itemToBuy, int indxx, struct Shop s){
	// Loop through the customers shopping list. Process all items with QTY != 0.
	double totalItemCost = cQty * itemPrice;
	//printf("...Cost of %d units of %s is %.2f\n", cQty, itemToBuy,totalItemCost);
	if (cQty > shopQty){
		// printf("...Item in short supply\n");
		return -1;
	}
	else if (totalItemCost > customerFund){
		return -2;
	}
	shopQty -= cQty;
	s.stock[indxx].quantity -= cQty;
	return 0;
}

// Function to process the Sigle Item Purchase	
void singleProcess(){
	printf("Single Item Processing mode...\n");
	// 	"..................................................................
	// 	".............Create & Stock Shop and Create & make Customer List..
	// 	"..................................................................	
	struct Shop shop = createAndStockShop();
	// 	"...................................................................
	// 	"......................Create Customer and his list.................
	// 	"...................................................................
	struct Customer customer = freeCustomer();
	 
	// .....................................................................
	// .........................keep Shop items in an array.................
	// .....................................................................
	
	//array pointers storing all shop items
	char* shopItems[200000] = {};	
	int i;
	//iterate the number of pointer times in the array
	for(i = 0; i < 200; i++){
		shopItems[i] = shop.stock[i].product.name;
	}	
	// "....................................................................
	// "...................keep Customer List Items in an array.............
	// "....................................................................
	//array pointers storing all customer list items
	char* custItems[100] = {};
	int j;
	// iterate the number of pointer times in the array
	for(j = 0; j < 10; j++){
		custItems[j] = customer.shoppingList[j].product.name;
	}

	int cindx = 0;
	double runningTotal = 0.0;
	double itemPrice = 0.0;
	int findIndex = 0;
	double initialCustomerBudget = customer.budget;		
	customer.index = 1;
	
	//  "......................................................................
	//  ".........................PROCESS Customer ORDER.......................
	//  "......................................................................
	
	itemPrice = findProductPrice(shop, customer.shoppingList[0].product.name);
	//printf("This item %s costs %.2f\n", custItems[cindx], itemPrice);
	if (itemPrice != 0.0){
		printf("---------------------------------------------------------------------------------------\n");
		printf("%s costs (€%.2f)\n", customer.shoppingList[0].product.name, itemPrice);
		int qtyInShop = findProductQty(shop, customer.shoppingList[0].product.name);
		findIndex = findItemIndex(shop, customer.shoppingList[0].product.name); 
					
		/*	Compare order with stock. If Qty ordered is > than stock available, report this otherwise
			go ahead and fulfil it.
		*/
		int buyStatus = compareOrderWithStock(customer.shoppingList[0].quantity, qtyInShop, 
		itemPrice, customer.budget, customer.shoppingList[0].product.name, findIndex, shop);
							
		double itemCost = customer.shoppingList[0].quantity * itemPrice;
					
		if (buyStatus == -1){
			printf("CanNOT Buy...Customer Ordered %d (%s)",customer.shoppingList[0].quantity,customer.shoppingList[0].product.name); 
			printf("...Item in short supply\n");
			printf("---------------------------------------------------------------------------------------\n");
		}
		else if (buyStatus == -2){
			printf("CanNOT Buy...Customer ordered %d units of (%s), subTotal is (€%.2f)",customer.shoppingList[cindx].quantity, 
			customer.shoppingList[0].product.name, itemCost);
			printf("...Customer does not have enough money.\n");
		
		}
		else{
			printf("Buy:....\n");
			printf("Customer ordered %d (%s), subTotal (€%.2f)\n",customer.shoppingList[cindx].quantity, 
			customer.shoppingList[0].product.name, itemCost);
			//printf("---------------------------------------------------------------------------------------\n");
			runningTotal += itemPrice * customer.shoppingList[cindx].quantity;
			// Update Shop with quantity sold
			shop.stock[findIndex].quantity -= customer.shoppingList[cindx].quantity;
			customer.budget -= itemCost;
			printf("Customer has €%.2f remaining.\n", customer.budget);
			printf("******************************\n");
		}
	}		
	printf("\n");
	// printf("Final bill for available items on this transaction is €%.2f", runningTotal);
	printf("**********    Final bill for available items on this transaction is €%.2f    *********\n", runningTotal);
	printf("                                                                            \n");
	// If customer does not have enough money to complete the transaction, ROLLBACK
	if (runningTotal > initialCustomerBudget){
		printf("Transaction aborted... Customer %s has no enough money...\n", customer.name);
		printf("\n");
	  
		printf("Cash in Shop is now: €%.2f\n", shop.cash);
		printf("\n");
		printf("\n");
	}
	else {
		printf("Now Updating cash status in the shop...\n");
		printf("                                                                            \n");
	    printf("***************************************************************************************\n");
		   //Update shop cash status
		printf("\n");
		shop.cash += runningTotal;
		printf("Cash in Shop is now: €%.2f\n", shop.cash);
		printf("                                                                            \n");
	   	printf("***************************************************************************************\n");
	}
	//print final list of items in the Shop
	printShop(shop);		
	printf("\n!!!!!!!!!!!    END of PROCESSING        !!!!!!!!!!!!!!!!!!\n\n");
}	//}	//End of singleItem() processing
	
void batchProcess(){
	// printf( "................................................................................\n");
	// printf( ".............Create & Stock Shop and Create & make Customer List................\n");
	// printf( "................................................................................\n");	
	printf("----------------------------Create Shop Stock Items------------------------------------\n");
	printf("***************************************************************************************\n");
	struct Shop shop = createAndStockShop();
	
	// 	printf( "................................................................................\n");
	// 	printf( "......................Create Customer Order list................................\n");
	// 	printf( "................................................................................\n");
	printf("----------------------------Customer List Items----------------------------------------\n");
	printf("***************************************************************************************\n");
	struct Customer customer = makeCustomer();

	// printf( ".........................keep Shop items in an array............................\n");
	// printf( "................................................................................\n");
	//array pointers storing all shop items
	char* shopItems[200000] = {};	
	int i;
	//iterate the number of pointer times in the array
	for(i = 0; i < 200; i++){
		shopItems[i] = shop.stock[i].product.name;
	}
	
	int sindx;
	for( sindx = 0; sindx < (sizeof( shopItems ) / sizeof( shopItems[0] )); sindx++){
		if (shopItems[sindx] != NULL){
	       	// printf( "%s\n", shopItems[sindx] );
		}
	}

	// printf( "...................keep Customer List Items in an array.........................\n");
	// printf( "................................................................................\n");
	//array pointers storing all customer list items
	char* custItems[100] = {};
	int j;
	// iterate the number of pointer times in the array
	for(j = 0; j < 10; j++){
		custItems[j] = customer.shoppingList[j].product.name;
	}

	int cindx;
	double runningTotal = 0.0;
	double itemPrice = 0.0;
	int findIndex = 0;
	double initialCustomerBudget = customer.budget;
	
	// "................................................................................
	// ".........................PROCESS Customer ORDER.................................
	// "................................................................................
	
	for( cindx = 0; cindx < (sizeof( custItems ) / sizeof( custItems[0] )); cindx++){
		if (custItems[cindx] != NULL){
	    	// printf( "%s\n", custItems[cindx] );
			itemPrice = findProductPrice(shop, custItems[cindx]);
			//printf("This item %s costs %.2f\n", custItems[cindx], itemPrice);
			if (itemPrice != 0.0){
				printf("---------------------------------------------------------------------------------------\n");
				printf("%s costs €%.2f\n", custItems[cindx], itemPrice);
				int qtyInShop = findProductQty(shop, custItems[cindx]);
				findIndex = findItemIndex(shop, custItems[cindx]); 
					
				/*	Compare order with stock. If Qty ordered is > than stock available, report this otherwise
					go ahead and fulfil it. Extend this to multiple orders later
				*/
				int buyStatus = compareOrderWithStock(customer.shoppingList[cindx].quantity, qtyInShop, 
										itemPrice, customer.budget, custItems[cindx], findIndex, shop);
				double itemCost = customer.shoppingList[cindx].quantity * itemPrice;
				
				if (buyStatus == -1){
					printf("CanNOT Buy...Customer Ordered - %d (%s)", customer.shoppingList[cindx].quantity, custItems[cindx]);
					printf("...Item in short supply\n");
					printf("---------------------------------------------------------------------------------------\n");
					
				}
				else if (buyStatus == -2){
					printf("CanNOT Buy:....Customer ordered %d (%s), subTotal: (€%.2f)",customer.shoppingList[cindx].quantity, custItems[cindx], itemCost);
					printf("...Customer does not have enough money.\n");

				}
				else{
					printf("Buy:....");
					printf("Customer ordered %d (%s), subTotal: (€%.2f)\n",customer.shoppingList[cindx].quantity, custItems[cindx], itemCost);
					// printf("This item may be purchased.\n");
					runningTotal += itemPrice * customer.shoppingList[cindx].quantity;
					// Update Shop with quantity sold
					shop.stock[findIndex].quantity -= customer.shoppingList[cindx].quantity;
					customer.budget -= itemCost;
					printf("Customer has €%.2f remaining.\n", customer.budget);
					printf("******************************\n");
					}
			}
		}
   }
   
   printf("\n");
   printf("*********    Total bill for available items on this transaction: €%.2f    *********\n", runningTotal);
   printf("\n");
   
   // If customer does not have enough money to complete the transaction, ROLLBACK
   if (runningTotal > initialCustomerBudget){
	   printf("Transaction aborted... Customer %s has no enough money...\n", customer.name);
	   printf("\n");
	  
	   printf("Cash in Shop is now: €%.2f\n", shop.cash);
	   printf("\n");
	   printf("\n");
   }
   else {
	   printf("***************************************************************************************\n");
	   printf("\nNow Updating cash status in the shop...\n");

	   //Update shop items
	   printf("\n");
	   shop.cash += runningTotal;
	   printf("Cash in Shop is now: €%.2f\n", shop.cash);
	   printf("***************************************************************************************\n");

   }
    //print final list of items in the Shop
	printShop(shop);
	printf("\n!!!!!!!!!!!    END of PROCESSING        !!!!!!!!!!!!!!!!!!\n\n");
}	// End of Batch Processing from CSV file

int main(void) 
{
	char resp = '0';
	printf("\n");
	printf("\n");
	printf("***************************************************************************************\n");
	printf("***        GMIT Cee Shop, Inc. Shop Manager on Duty today is: Francis Adepoju       ***\n");
	printf("***        *******************************************************************      ***\n");
	printf("***                       PLEASE ENTER YOUR DESIRED OPTION                          ***\n");	
	printf("***                       Enter  0 ==> End the Program,                             ***\n");
	printf("***                       Enter  1 ==> Single Item Purchase                         ***\n");            
	printf("***                       Enter  2 ==> Multiple Purchase from .CSV file             ***\n"); 
	printf("***                                                                                 ***\n");
	printf("***************************************************************************************\n");
	printf("***************************************************************************************\n");
	printf("Choice: ");
	scanf("%s", &resp);
	while (resp != '0' ){
		if (resp == '1' ){
			singleProcess();
		}
		else if (resp == '2' ){
			batchProcess();
		}
		else{
			printf("!!!!\n");
			printf("!!!! Error... Irregular input detected. Please try again...\n");
			printf("!!!!\n");
			//break;
		}
		printf("***************************************************************************************\n");
		printf("***                                                                                 ***\n");
		printf("***                       PLEASE ENTER YOUR DESIRED OPTION                          ***\n");	
		printf("***                       Enter  0 ==> End the Program,                             ***\n");
		printf("***                       Enter  1 ==> Single Item Purchase                         ***\n");            
		printf("***                       Enter  2 ==> Multiple Purchase from .CSV file             ***\n"); 
		printf("***                                                                                 ***\n");
		printf("***************************************************************************************\n");
		printf("***************************************************************************************\n");
		printf("Choice: ");
		scanf("%s", &resp);
	}
	return 0;
}
