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
		char *name = malloc(sizeof(char) * 50);	//new memory location to store n as name
		strcpy(name, n);
		struct Product product = { name, price };
		//struct Product product = { &n, price };...this does'nt work
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
		printf("-------------\n");
	}
}


/*	Compare order with stock. If Qty ordered is > than stock available, report this otherwise
	go ahead and fulfil it. Extend this to multiple orders later
*/
void compareOrderWithStock(struct Customer c, struct Shop s ){
// Loop through the customers shopping list. Process all items with QTY != 0, for now, just provide appropriate message.
// First, locate the item and its index number in the Shop
	int i; 
	int j;
	for (j = 0; j < s.index; j++){
		for (i = 0; i < c.index; i++){
			if (c.shoppingList[i].product.name == s.stock[j].product.name){
				if (c.shoppingList[i].quantity != 0){
					printf("======>> ...FEEDBACK: \n");
					printf("Customer Ordered - %d units of %s\n", c.shoppingList[i].quantity, c.shoppingList[i].product.name);
					printf("There are %d units of %s in stock!\n", s.stock[j].quantity, c.shoppingList[i].product.name);
					printf("We can fulfil your order on (%s)...\n", c.shoppingList[i].product.name);
// 					Update stock items appropriately...
					s.stock[j].quantity -= c.shoppingList[i].quantity;
					printf("\n\nITEMS remaining is stock... %s is %d\n", c.shoppingList[i].product.name, s.stock[j].quantity );
				}
				else {
					//Print remaining stock...
 					printCustomer(c);
 					//printf("\n\nITEMS remaining is stock... %s is %d\n", c.shoppingList[i].product.name, s.stock[j].quantity );
 					printShop(s);
				}
			} // whileiloop
		}
	}

	printf("\n\nITEMS remaining is stock... %s is %d\n", c.shoppingList[i].product.name, s.stock[j].quantity );
}// compareWithStock Loop



// Compare order with stock. If Qty ordered is > than stock available, report this otherwise
// 	go ahead and fulfil it. Extend this to multiple orders later
// */
// void compareOrderWithStock(struct Customer c, struct Shop s ){
// // Loop through the customers shopping list. Process all items with QTY != 0, for now, just provide appropriate message.
// // First, locate the item and its index number in the Shop
// 	int i, j;
// 	for (j = 0; j < s.index; j++){
// 		for (i = 0; i < c.index; i++){
// 			do while ((c.shoppingList[i].product.name == s.stock[j].product.name) && (c.shoppingList[i].quantity != 0)){
// 				// if (c.shoppingList[i].quantity > s.stock[j].quantity){
// // 
// // 					printf("======>> ...FEEDBACK: \n");
// // 					printf("Customer Ordered - %d units of %s\n", c.shoppingList[i].quantity, c.shoppingList[i].product.name);
// // 					printf("There are %d units of %s in stock!\n", s.stock[j].quantity, c.shoppingList[i].product.name);
// // 					printf("Shortfall: %d\n", s.stock[j].quantity - c.shoppingList[i].quantity);
// // 					printf("SORRY, we do not have enough of  (%s) in stock...\n", c.shoppingList[i].product.name);
// // 				}else{
// 					printf("======>> ...FEEDBACK: \n");
// 					printf("Customer Ordered - %d units of %s\n", c.shoppingList[i].quantity, c.shoppingList[i].product.name);
// 					printf("There are %d units of %s in stock!\n", s.stock[j].quantity, c.shoppingList[i].product.name);
// 					printf("We can fulfil your order on (%s)...\n", c.shoppingList[i].product.name);
// 
// // 				Update stock items appropriately...
// 					s.stock[j].quantity -= c.shoppingList[i].quantity;
// // 				}
// // 			Print remaining stock...
// // 			printCustomer(c);
// // 			printf("\n\nITEMS remaining is stock... %s is %d\n", c.shoppingList[i].product.name, s.stock[j].quantity );
// // 			printShop(s);
// 			}
// 		} // iloop
// 	// printf("\n\n....ITEMS remaining is stocks...\n");
// // 	printShop(s);
// 
// 	} ///j loop
// 	printf("\n\nITEMS remaining is stock... %s is %d\n", c.shoppingList[i].product.name, s.stock[j].quantity );
// }// compareWithStock Loop

int main(void) 
{
	// Create a Customer and his items to buy
	struct Customer dominic = { "Dominic", 500.0 };
	
	// WHY can't I just read this from the stock file?
 	struct Product coke = { "Can Coke", 1.10 };
 	struct Product bread = { "Bread", 0.7 };
 	struct Product tomato = { "Tomato Sauce", 0.8 };
 	struct Product binbag = { "Bin Bag", 2.50  };
// 	printProduct(coke);

// 	Customers Shopping List
 	struct ProductStock cokeStock = { coke, 120 };
 	struct ProductStock breadStock = { bread, 2 };
 	struct ProductStock tomatoStock = { tomato, 50 };
 	struct ProductStock binbagStock = { binbag, 5 };

// 	Customers Items stored inside Shopping Cart
 	dominic.shoppingList[dominic.index++] = cokeStock;
 	dominic.shoppingList[dominic.index++] = breadStock;
 	dominic.shoppingList[dominic.index++] = tomatoStock;
 	dominic.shoppingList[dominic.index++] = binbagStock;
	
	struct Shop shop = createAndStockShop();
	compareOrderWithStock(dominic, shop);		//FA 7-October
	
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