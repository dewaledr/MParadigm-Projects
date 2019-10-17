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

// struct Customer {
// 	char* name;
// 	double budget;
// 	struct ProductStock shoppingList[10];
// 	int index;
// };

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
		double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price; 
		printf("The cost to %s will be €%.2f\n", c.name, cost);
	}
}

struct Shop createAndStockShop()
{
	//struct Shop shop = { 1200.99 };	//Shop has 1200.99 on hand and 200 items in the shop
	struct Shop shop = { };	//Shop has 1200.99 on hand and 200 items in the shop
	//shop.cash = 1000.59;	//Initial cash in the shop
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock6.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
	printf("*************************\n");
	//printf("Money-in-Shop:€%.2f\n", shop.cash);
	printf("*************************\n");

	double availableCash;
    while ((read = getline(&line, &len, fp)) != -1) {
		//read first line for cash on hand
		char *v = strtok(line,",");
		char *n = strtok(NULL, ",");
		char *p = strtok(NULL, ",");
		char *q = strtok(NULL, ",");
		
		int quantity = atoi(q);
		double price = atof(p);
		availableCash = atof(v);
		
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
	struct Customer customer = {}; // Create the customer with budget
    
	FILE * f2p;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    f2p = fopen("items6.csv", "r");
    if (f2p == NULL)
        exit(EXIT_FAILURE);

	printf("\n");

    while ((read = getline(&line, &len, f2p)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s IS A LINE", line);
		// double moneyToSpend = budget;
		char *cn = strtok(line, ",");
		char *bd = strtok(NULL, ",");
		char *nm = strtok(NULL, ",");
		char *pr = strtok(NULL, ",");
		char *qt = strtok(NULL, ",");
		
		int quantity  = atoi(qt);
		double price  = atof(pr);
		double budget = atof(bd);
		//Product name
		char *name = malloc(sizeof(char) * 50);	//new memory location to store n as name
		strcpy(name, nm);
		//Customer name
		char *cname = malloc(sizeof(char) * 100);	//new memory location to store n as name
		strcpy(cname, cn);
		
		struct Product product = { name, price };
		
		struct CustomerList listItem = { product, quantity };
		customer.shoppingList[customer.index++] = listItem;
		//printf("...................\n");
		// printf("Customer %s has €%.2f to spend\n", customer.name, customer.budget);
		printf("ListItem -> %3d | Customer %s wants %3d units of %s \t. ", 
		customer.index, cname, quantity, name);
		printf("%s has €%.2f available to spend...\n", cname, budget);
    }
	
	return customer;
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


/*	Compare order with stock. If Qty ordered is > than stock available, report this otherwise
	go ahead and fulfil it. Extend this to multiple orders later
*/
void compareOrderWithStock(struct Customer c, struct Shop s ){
// Loop through the customers shopping list. Process all items with QTY != 0, for now, just provide appropriate message.
// First, locate the item and its index number in the Shop
	for (int i = 0; i < s.index; i++){
		if (c.shoppingList[i].quantity != 0){
			if (c.shoppingList[i].quantity > s.stock[i].quantity){

				printf("======>> ...FEEDBACK: \n");
				printf("Customer Ordered - %d units of %s\n", c.shoppingList[i].quantity, c.shoppingList[i].product.name);
				printf("There are %d units of %s in stock!\n", s.stock[i].quantity, c.shoppingList[i].product.name);
				printf("Shortfall: %d\n", s.stock[i].quantity - c.shoppingList[i].quantity);
				printf("SORRY, we do not have enough of  (%s) in stock...\n", c.shoppingList[i].product.name);
			}else{
				printf("======>> ...FEEDBACK: \n");
				printf("Customer Ordered - %d units of %s\n", c.shoppingList[i].quantity, c.shoppingList[i].product.name);
				printf("There are %d units of %s in stock!\n", s.stock[i].quantity, c.shoppingList[i].product.name);
				printf("We can fulfil your order on (%s)...\n", c.shoppingList[i].product.name);

// 				Update stock items appropriately...
				s.stock[i].quantity -= c.shoppingList[i].quantity;
			}
// 			Print remaining stock...
// 			printCustomer(c);
			printf("\n\nITEMS remaining is stock... %s is %d\n", c.shoppingList[i].product.name, s.stock[i].quantity );
// 			printShop(s);
		}
	}
	// printf("\n\n....ITEMS remaining is stock...\n");
// 	printShop(s);
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
	// printf(".....................\n");
// 	printf("....Customer List....\n");
// 	printf(".....................\n");
	struct Customer customer = makeCustomer();
//
// 	printf("Difference of Shop cash and customer cash = %.3f\n", (shop.cash - customer.budget));
	
	//Array of items in the shop
	// char* shopItems[200];
//
	// struct shopItems {
	//         char name[20];
	//         // double price;
	//         // int qty;
	// };
	//
	// 	struct shopItems details[200];
	    // int i;
	// for (i = 0; i < shop.index; i++){
	// 	struct shopItems details[i] = &shop.stock[i].product.name;
	// 	//shopItems.append(shop.stock[i].product.name);
	// 	printf("\n%s", shop.stock[i].product.name);
	// }

	
	// Shop items in an array
	char* shopItems[200000] = {};//array pointers storing all shop items
	int i;
	for(i = 0; i < 200; i++)// iterate the number of pointer times in the array
	{
		shopItems[i] = shop.stock[i].product.name;
	// char input[10];// a local array variable
	// char *name = malloc(sizeof(char) * 50);
	//char shopItems[i] = malloc(sizeof(char)*50); //allocate memory for each pointer in the array here
	//scanf("%s",shop.stock[i].product.name);//take the input from stdin
	//strcpy(shopItems[i], shop.stock[i].product.name);//store the value in one of the pointer in the pointer array
	}
	
	int sindx;
	for( sindx = 0; sindx < (sizeof( shopItems ) / sizeof( shopItems[0] )); sindx++){
		if (shopItems[sindx] != NULL){
	       	printf( "%s\n", shopItems[sindx] );
		}
	}
	
	printf( "Francis %lu\n", sizeof( shopItems ));
	printf( "Francis %lu\n", sizeof( shopItems[0] ));
	printf( "Francis\n" );//}
	
	
	
	
	
	
	//Customer items in an array
	char* custItems[100] = {};//array pointers storing all customer list items
	int j;
	for(j = 0; j < 10; j++)// iterate the number of pointer times in the array
	{
		custItems[j] = customer.shoppingList[j].product.name;
	}


	int cindx;
		for( cindx = 0; cindx < (sizeof( custItems ) / sizeof( custItems[0] )); cindx++){
			if (custItems[cindx] != NULL){
	        	printf( "%s\n", custItems[cindx] );
			}
	        // printf( "\n" );
	   }

	printf( "FA %lu\n", sizeof( custItems ));
	printf( "FA %lu\n", sizeof( custItems[0] ));
	printf( "FA\n" );//}

	
	
	
	//printf("%s\n", shopItems);
	
	
	// printf(details);
	/*
	So there is an array of 3 strings, and each string has space for 256 characters 
	(really only 255 characters, because there is always a terminating null character (\0) at the end of a string)
	*/
	// char strings[200][256];
// 	    scanf("%s %s %s", strings[0], strings[1], strings[2]);
// 	    printf("%s\n%s\n%s\n", strings[0], strings[1], strings[2]);
//
	//     int i;
	// 	char strings[200][256];
	// for (i = 0; i < shop.index; i++){
	// 	strings[i][255] = *shop.stock[i].product.name;
	// 	//scanf("%s", shop.stock[i].product.name;
	// 	//shopItems.append(shop.stock[i].product.name);
	// 	printf("%20s\n", &strings[i][255]);
	// 	printf("\n%s", shop.stock[i].product.name);
	// }
	//printf("%s", strings);
// 	compareOrderWithStock(dominic, shop);		//FA 7-October
	
// 	Update the stock remaining in Shop if order was filled
	
	
	printf("\n!!!!!!!!!!!    END of PROCESSING        !!!!!!!!!!!!!!!!!!\n\n");
	
// 	
// 	printCustomer(dominic);
// 	printShop(shop);
	
    return 0;
}












/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product {
	char* name;
	double price;
};

struct ProductStock {
	struct Product product;
	int quantity;
};

struct Shop {
	double cash;
	struct ProductStock stock[20];
	int index;
};

struct Customer {
	char* name;
	double budget;
	struct ProductStock shoppingList[10];
	int index;
};

void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
	printf("-------------\n");
}

void printCustomer(struct Customer c)
{
	printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
	printf("-------------\n");
	for(int i = 0; i < c.index; i++)
	{
		printProduct(c.shoppingList[i].product);
		printf("%s ORDERS %d OF ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);
		double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price; 
		printf("The cost to %s will be €%.2f\n", c.name, cost);
	}
}

struct Shop createAndStockShop()
{
	struct Shop shop = { 200 };
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s IS A LINE", line);
		char *n = strtok(line, ",");
		char *p = strtok(NULL, ",");
		char *q = strtok(NULL, ",");
		int quantity = atoi(q);
		double price = atof(p);
		char *name = malloc(sizeof(char) * 50);
		strcpy(name, n);
		struct Product product = { name, price };
		struct ProductStock stockItem = { product, quantity };
		shop.stock[shop.index++] = stockItem;
		// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
    }
	
	return shop;
}

void printShop(struct Shop s)
{
	printf("Shop has %.2f in cash\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf("The shop has %d of the above\n", s.stock[i].quantity);
	}
}

int main(void) 
{
	// struct Customer dominic = { "Dominic", 100.0 };
	//
	// struct Product coke = { "Can Coke", 1.10 };
	// struct Product bread = { "Bread", 0.7 };
	// // printProduct(coke);
	//
	// struct ProductStock cokeStock = { coke, 20 };
	// struct ProductStock breadStock = { bread, 2 };
	//
	// dominic.shoppingList[dominic.index++] = cokeStock;
	// dominic.shoppingList[dominic.index++] = breadStock;
	//
	// printCustomer(dominic);
	
	struct Shop shop = createAndStockShop();
	printShop(shop);
	
// printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
	
    return 0;
}

*/