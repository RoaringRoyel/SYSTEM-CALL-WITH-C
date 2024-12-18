#include<stdio.h>

struct property{

	int quantity, unit_price;
	
	};
	
int main(){
	
	struct property paratha, vegetable, water;
	
	printf("Quantity Of Paratha: ");
	scanf("%d", &paratha.quantity);
	printf("Unit price of Paratha: ");
	scanf("%d", &paratha.unit_price);
	
	printf("Quantity Of Vegetables: ");
	scanf("%d", &vegetable.quantity);
	printf("Unit price of Vegetables: ");
	scanf("%d", &vegetable.unit_price);
	
	printf("Quantity Of Mineral Water: ");
	scanf("%d", &water.quantity);
	printf("Unit price of Mineral Water: ");
	scanf("%d", &water.unit_price);
	
	int people;
	printf("Number of People: ");
	scanf("%d", &people);
	
	float total_bill = (paratha.quantity * paratha.unit_price) + (vegetable.quantity * vegetable.unit_price) + (water.quantity * water.unit_price);
	
	float individual_bill = total_bill / people;	
	
	printf("Individual people will pay: %.2f tk\n", individual_bill);
	
	return 0;
	
	}
