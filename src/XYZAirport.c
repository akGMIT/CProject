/*
 ============================================================================
 Name        : XYZAirport.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Passenger{
	int passportNumber;
	char firstName[20];
	char secondName[20];
	int DOB;
	char email[30];
	int travelOrigin;
	int travelClass;
	int travelPerYear;
	int durationOfStay;
	struct Passenger * next;
}Passenger;

void addPassengerAtStart(struct Passenger** head);
struct Passenger * createPassenger();
void displayList(struct Passenger* head);

void main() {

	struct Passenger* headPtr = NULL;

	for(int i = 0; i < 3; i++){
		addPassengerAtStart(&headPtr);
	}

	displayList(headPtr);
}

void addPassengerAtStart(Passenger** head){
	Passenger* newPassenger;
	newPassenger = (Passenger*)malloc(sizeof(Passenger));
	newPassenger = createPassenger();
	newPassenger->next = *head;
	*head = newPassenger;
}

struct Passenger * createPassenger(){
	struct Passenger * new_passenger = (Passenger*)malloc(sizeof(Passenger));

	if(new_passenger == NULL){
		puts("Error creating new passenger");
		return 0;
	}else{
		printf("Enter new passengers passport number: ");
		scanf("%d", &new_passenger->passportNumber);
		/*printf("Enter first name: ");
		scanf("%s", new_passenger->firstName);
		printf("Enter second name: ");
		scanf("%s", new_passenger->secondName);
		printf("Enter date of birth in format ddmmyyyy: ");
		scanf("%d", &new_passenger->DOB);
		printf("Enter passengers email: ");
		scanf("%s", new_passenger->email);
		printf("Enter passengers origin of travel: ");
		printf("1. UK\n2. Rest of Europe \n3. Asia \n4. Americas \n5. Australasia");
		scanf("%d", &new_passenger->travelOrigin);
		printf("Enter passengers travel class: ");
		scanf("%d", new_passenger->travelClass);
		printf("Passengers trips per year to Ireland: ");
		scanf("%d", &new_passenger->travelPerYear);
		printf("Enter passengers average duration of stay: ");
		printf("1. One day \n2. Less than 3 days \n 3.Less than 7 days \n4. More than 7 days");
		scanf("%d", &new_passenger->durationOfStay);*/
	}

	return new_passenger;
}

void displayList(Passenger* head)
{
	Passenger* curr;

	curr = head;

	while (curr != NULL)
	{
		printf("The name is %d\n", curr->passportNumber);
		curr = curr->next;
	}


}
