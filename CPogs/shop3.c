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

    fp = fopen("stock3.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
	printf("********************** SHOP ITEMS ************************************************\n");
	
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
		printf("Item no.-> %3d  Product Name - %s  PRICE: €%7.2f\tQTY: %3d\n", shop.index, name, price, quantity);
    }
	printf("**********************************************************************************\n");
	printf("Initial Cash in Shop: €%.2f\n", availableCash);
	printf("**********************************************************************************\n");
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

    f2p = fopen("items3.csv", "r");
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
	
	printf("***************************************************************************************\n");
	printf("%s has €%.2f available to spend...\n", cname, budget);
	printf("***************************************************************************************\n");
	printf("***** ORDER Item STATUS Report ***** ***************** ********************* **********\n");
	return customer;
}

// Read freeCustomer Item from keyboard
struct Customer freeCustomer(){
	// Create the customer with budget
	struct Customer freeCustomer = {}; 

	float bgt;
	char temp;
	char *nm;
	int qt;
	
	printf("Please enter customer budget... ");
	scanf("%f", &bgt);	
	
	printf("Please enter item Quantity here... ");
	scanf("%d", &qt);
	
	printf("Please enter item name here... ");
	scanf("%c", &temp); 	// temp statement to clear buffer, This is needed for next line to work...
	scanf("%[^\n]s", nm); //Read strings inasmuch as \n is not encountered --- So as to be able to take in names with spaces in between

	char *name = malloc(sizeof(char) * 50);	//new memory location to store n as name
	strcpy(name, nm);
	
	printf("***************************************************************************************\n");
	printf("Customer has €%.2f available to spend on %d units of %s...\n", bgt, qt, name);
	
	freeCustomer.name = "Anonymous";
	freeCustomer.budget = bgt;
	freeCustomer.shoppingList[0].quantity = qt;
	freeCustomer.shoppingList[0].product.name = name;
	freeCustomer.index = 1;
	
	// printf("Anonymous customer\n");
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
		//printf("---------------------------------------------------------------------------------------\n");
		printf(">>>SORRY<<<...no such item in the shop: '%s'\n", n);
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

void printShop(struct Shop s)
{
	printf("Shop has %.2f in cash\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		printf("Item no.-> %3d  Product Name - %s PRICE: €%7.2f\tQTY: %3d\n", i+1, s.stock[i].product.name, 
		s.stock[i].product.price, s.stock[i].quantity);
	}
}
			
int compareOrderWithStock(int cQty, int shopQty, double itemPrice, double customerFund, char *itemToBuy, int indxx, struct Shop s){
	// Loop through the customers shopping list. Process all items with QTY != 0, for now, just provide appropriate message.
	// First, locate the item and its index number in the Shop

			double totalItemCost = cQty * itemPrice;
			//printf("...Cost of %d units of %s is %.2f\n", cQty, itemToBuy,totalItemCost);
			if (cQty > shopQty){

				printf("...NOT enough items in stock to fulfil this order: '%s'\n", itemToBuy);
				printf("...Customer Ordered - %d units of %s\n", cQty, itemToBuy);
				return -1;
			}
			else if (totalItemCost > customerFund){
				//printf("Cost of %d units of %s is %.2f\n", cQty, itemToBuy,totalItemCost);
				return -2;
			}
			shopQty -= cQty;
			s.stock[indxx].quantity -= cQty;
		return 0;
	}
	
	void singleProcess(){
		printf("Single Item Processing mode...\n");
	// 	"................................................................................\n");
	// 	".............Create & Stock Shop and Create & make Customer List................\n");
	// 	"................................................................................\n");	
	
		struct Shop shop = createAndStockShop();
	// 	"................................................................................\n");
	// 	"......................Create Customer and his list..............................\n");
	// 	"................................................................................\n");
		struct Customer customer = freeCustomer();
	 
		// printf( "................................................................................\n");
		// printf( ".........................keep Shop items in an array............................\n");
		// printf( "................................................................................\n");
		char* shopItems[200000] = {};	//array pointers storing all shop items
		int i;
		for(i = 0; i < 200; i++)		//iterate the number of pointer times in the array
		{
			shopItems[i] = shop.stock[i].product.name;
		
		}
	
/*		int sindx;
		for( sindx = 0; sindx < (sizeof( shopItems ) / sizeof( shopItems[0] )); sindx++){
			if (shopItems[sindx] != NULL){
			}
		}
*/	
		// "................................................................................\n");
		// "...................keep Customer List Items in an array.........................\n");
		// "................................................................................\n");
		char* custItems[100] = {};//array pointers storing all customer list items
		int j;
		for(j = 0; j < 10; j++)// iterate the number of pointer times in the array
		{
			custItems[j] = customer.shoppingList[j].product.name;
		}

		int cindx = 0;
		double runningTotal = 0.0;
		double itemPrice = 0.0;
		int findIndex = 0;
		
		customer.index = 1;
		// 		freeCustomer.name = "Anonymous";
		// 		freeCustomer.budget = bgt;
		// 		freeCustomer.shoppingList[0].product.name = name;
		// 		freecustomer.shoppingList[0].quantity = qty;
		// 		freeCustomer.index = 1;
	
		//  "................................................................................\n");
		//  ".........................PROCESS Customer ORDER.................................\n");
		//  "................................................................................\n");
	
				itemPrice = findProductPrice(shop, customer.shoppingList[0].product.name);
				//printf("This item %s costs %.2f\n", custItems[cindx], itemPrice);
				if (itemPrice != 0.0){
					printf("---------------------------------------------------------------------------------------\n");
					printf("Item - %s costs %.2f\n", customer.shoppingList[0].product.name, itemPrice);
					int qtyInShop = findProductQty(shop, customer.shoppingList[0].product.name);
					findIndex = findItemIndex(shop, customer.shoppingList[0].product.name); 
					
					/*	Compare order with stock. If Qty ordered is > than stock available, report this otherwise
						go ahead and fulfil it.
					*/
					int buyStatus = compareOrderWithStock(customer.shoppingList[0].quantity, qtyInShop, 
							itemPrice, customer.budget, customer.shoppingList[0].product.name, findIndex, shop);
							
					double itemCost = customer.shoppingList[0].quantity * itemPrice;
					
					if (buyStatus == -1){
						printf("...This item cannot be purchased at this time\n");
						printf("---------------------------------------------------------------------------------------\n");
					}
					else if (buyStatus == -2){
						printf("Customer ordered %d units of %s, subTotal is %.2f\n",customer.shoppingList[cindx].quantity, 
						customer.shoppingList[0].product.name, itemCost);
						printf("...Customer Does not have enough money to buy this item/item quantity\n");
						printf("...Please reduce quantity and try again....\n");
						//printf("\n----------------------------------\n");
					}

					else{
						printf("NOTE:....\n");
						printf("Customer ordered %d units of %s, subTotal is %.2f\n",customer.shoppingList[cindx].quantity, 
						customer.shoppingList[0].product.name, itemCost);
						printf("...This item may be purchased.\n");
						printf("---------------------------------------------------------------------------------------\n");
						runningTotal += itemPrice * customer.shoppingList[cindx].quantity;
						// Update Shop with quantity sold
						shop.stock[findIndex].quantity -= customer.shoppingList[cindx].quantity;
						///
						}
				}
			
	   printf("\n");
   	   printf("***************************************************************************************\n");
	   printf("Final bill for available items on this transaction is €%.2f", runningTotal);
	   printf("                                                                            \n");
	   //printf("\n");
   
	   // If customer does not have enough money to complete the transaction, ROLLBACK
	   if (runningTotal > customer.budget){
		   printf("Transaction aborted... Customer %s has no enough fund...\n", customer.name);
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
		printShop(shop);
		printf("\n!!!!!!!!!!!    END of PROCESSING        !!!!!!!!!!!!!!!!!!\n\n");
	}	//}	//End of singleItem()
	
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

	// printf( "...................keep Customer List Items in an array.........................\n");
	// printf( "................................................................................\n");
	char* custItems[100] = {};//array pointers storing all customer list items
	int j;
	for(j = 0; j < 10; j++)// iterate the number of pointer times in the array
	{
		custItems[j] = customer.shoppingList[j].product.name;
	}

	int cindx;
	double runningTotal = 0.0;
	double itemPrice = 0.0;
	int findIndex = 0;
	
	// "................................................................................\n");
	// ".........................PROCESS Customer ORDER.................................\n");
	// "................................................................................\n");
	
	for( cindx = 0; cindx < (sizeof( custItems ) / sizeof( custItems[0] )); cindx++){
		if (custItems[cindx] != NULL){
	    // printf( "%s\n", custItems[cindx] );
			itemPrice = findProductPrice(shop, custItems[cindx]);
			//printf("This item %s costs %.2f\n", custItems[cindx], itemPrice);
			if (itemPrice != 0.0){
				printf("---------------------------------------------------------------------------------------\n");
				printf("Item - %s costs %.2f\n", custItems[cindx], itemPrice);
				int qtyInShop = findProductQty(shop, custItems[cindx]);
				findIndex = findItemIndex(shop, custItems[cindx]); 
					
				/*	Compare order with stock. If Qty ordered is > than stock available, report this otherwise
					go ahead and fulfil it. Extend this to multiple orders later
				*/
				int buyStatus = compareOrderWithStock(customer.shoppingList[cindx].quantity, qtyInShop, 
						itemPrice, customer.budget, custItems[cindx], findIndex, shop);
				double itemCost = customer.shoppingList[cindx].quantity * itemPrice;
				if (buyStatus == -1){
					printf("...This item cannot be purchased at this time\n");
					printf("---------------------------------------------------------------------------------------\n");
					//printf("***************************************************************************************\n");
				}
				else if (buyStatus == -2){
					printf("Customer ordered %d units of %s, subTotal is %.2f\n",customer.shoppingList[cindx].quantity, custItems[cindx], itemCost);
					printf("...Customer does not seem to have enough fund to buy this item.\n");
					printf("...You may reduce the quantity and try again!\n");
					//printf("\n--------------------------------------------------------------\n");
				}

				else{
					//printf("-------------------------------------------------\n");
					printf("NOTE:....\n");
					printf("Customer ordered %d units of %s, subTotal is %.2f\n",customer.shoppingList[cindx].quantity, custItems[cindx], itemCost);
					printf("This item may be purchased.\n");
					printf("---------------------------------------------------------------------------------------\n");
					//printf("***************************************************************************************\n");
					runningTotal += itemPrice * customer.shoppingList[cindx].quantity;
					// Update Shop with quantity sold
					shop.stock[findIndex].quantity -= customer.shoppingList[cindx].quantity;
					///
					}
			}
		}
   }
   
   printf("\n");
   //printf("*********************************************************\n");
   printf("*****  ");
   printf("Final bill for available items on this transaction is €%.2f", runningTotal);
   printf("  *****\n");
   printf("\n");
   
   // If customer does not have enough money to complete the transaction, ROLLBACK
   if (runningTotal > customer.budget){
	   printf("Transaction aborted... Customer %s has no enough fund...\n", customer.name);
	   printf("\n");
	   //Rollback... Qty update
	  
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
// 	printCustomer(dominic);
	printShop(shop);
	printf("\n!!!!!!!!!!!    END of PROCESSING        !!!!!!!!!!!!!!!!!!\n\n");
}

int main(void) 
{
	int resp = 0;
	printf("***************************************************************************************\n");
	printf("***************************************************************************************\n");
	printf("*** PLEASE MAKE A CHOICE:                                                           ***\n");	
	printf("*** Enter  0 ==> End the Program,                                                   ***\n");
	printf("*** Enter  1 ==> Single Item Purchase                                               ***\n");            
	printf("*** Enter  2 ==> Multiple Purchase from .CSV file                                   ***\n"); 
	printf("***                                                                                 ***\n");
	printf("***************************************************************************************\n");
	printf("***************************************************************************************\n");
	printf("Choice: ");
	scanf("%d", &resp);
	while (resp != 0 ){
		if (resp == 1 ){
			singleProcess();
		}
		else if (resp == 2 ){
			batchProcess();
		}
		else{
			printf("!!!!\n");
			printf("!!!! Error... Irregular input detected. Please try again...\n");
			printf("!!!!\n");
			//break;
		}
		printf("***************************************************************************************\n");
		printf("***************************************************************************************\n");
		printf("*** PLEASE MAKE A CHOICE:                                                           ***\n");	
		printf("*** Enter  0 ==> End the Program,                                                   ***\n");
		printf("*** Enter  1 ==> Single Item Purchase                                               ***\n");            
		printf("*** Enter  2 ==> Multiple Purchase from .CSV file                                   ***\n"); 
		printf("***                                                                                 ***\n");
		printf("***************************************************************************************\n");
		printf("***************************************************************************************\n");
		printf("Choice: ");
		scanf("%d", &resp);
	}
	return 0;
}
