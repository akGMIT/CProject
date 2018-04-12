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
#include <string.h>

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
struct Passenger * createPassenger(Passenger * head, int passportNum);
void displayList(struct Passenger* head);
int searchPassengerList(Passenger * head, int passportNum);
void passportUnique(int passportNum, Passenger * head);
void sortList(Passenger ** head);
Passenger * swapNodeData(Passenger * temp1, Passenger * temp2);
//void updatePassenger(Passenger ** head, int position);

void main() {

	struct Passenger* headPtr = NULL;
	int choice;

	printf("Please enter 1 to add passenger\n");
	printf("Please enter 2 sort list\n");
	printf("Please enter 3 to display the list\n");
	printf("Please enter 4 to display the list in reverse\n");
	printf("Please enter -1 to exit\n");
	scanf("%d", &choice);


	while(choice != -1){
		switch(choice){
		case 1:
			addPassengerAtStart(&headPtr);
			break;
		case 2:
			sortList(&headPtr);
			break;
		case 3:
			displayList(headPtr);
			break;
		}
		printf("Please enter 1 to add passenger\n");
		printf("Please enter 2 sort list\n");
		printf("Please enter 3 to display the list\n");
		printf("Please enter 4 to display the list in reverse\n");
		printf("Please enter -1 to exit\n");
		scanf("%d", &choice);
	}
}

void addPassengerAtStart(Passenger** head){
	Passenger* newPassenger;
	int passportNum;
	int passengerIndex;
	int choice;

	newPassenger = (Passenger*)malloc(sizeof(Passenger));
	//Passenger * tempPas = *head;

	printf("Enter new passengers passport number: ");
	scanf("%d", &passportNum);
	passengerIndex = searchPassengerList(*head, passportNum);
	printf("%d", passengerIndex);
	if(passengerIndex > 0){
		printf("\nPassenger with this passport number already exists in database.");
		printf("\nWould you like to update details?");
		printf("\n1. Yes 2. No");
		scanf("%d", &choice);
		if(choice == 1){
			//updatePassenger(&tempPas, passengerIndex);
		}else{
			return;
		}
	}else{
		newPassenger = createPassenger(*head, passportNum);
		newPassenger->next = *head;
		*head = newPassenger;
	}


}

struct Passenger * createPassenger(Passenger * head, int passportNum){
	struct Passenger * new_passenger = (Passenger*)malloc(sizeof(Passenger));

	if(new_passenger == NULL){
		puts("Error creating new passenger");
		return 0;
	}else{
		new_passenger->passportNumber = passportNum;

		printf("Enter first name: ");
		scanf("%s", new_passenger->firstName);
		/*printf("Enter second name: ");
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

void passportUnique(int passportNum, Passenger * head){
	int result;

	result = searchPassengerList(head, passportNum);

	if (result != -1)
	{
		printf("Not a unique ID\n");
		return;
	}
}

int searchPassengerList(Passenger * head, int passportNum){
	Passenger * curr = head;
	int position = 0;

	while(curr != NULL){
		position++;
		printf("%d ", curr->passportNumber);
		if(passportNum == curr->passportNumber){
			printf("---%d", position);
			return position;
		}
		curr = curr->next;
	}
	return -1;
}

void sortList(Passenger ** head){
	Passenger *temp3 = (Passenger*)malloc(sizeof(Passenger));
	Passenger *temp1;
	Passenger *temp2;

	for(temp1=*head;temp1!=NULL;temp1=temp1->next)
	{
		for(temp2=temp1->next;temp2!=NULL;temp2=temp2->next)
		{
			if(temp2->passportNumber < temp1->passportNumber)
			{
				temp3 = swapNodeData(temp3,temp1);
				temp1 = swapNodeData(temp1, temp2);
				temp2 = swapNodeData(temp2, temp3);
			}
		}
	}
}

Passenger * swapNodeData(Passenger * temp1, Passenger * temp2){
	temp1->passportNumber = temp2->passportNumber;
	strcpy(temp1->firstName, temp2->firstName);

	return temp1;
}

/*void updatePassenger(Passenger ** head, int position){
	Passenger * temp;

	Passenger * newPassenger = (Passenger*)malloc(sizeof(Passenger));
	int passportNum;
	newPassenger = *head;

	for (int i = 0;i < position - 2;i++)
	{
		newPassenger = newPassenger->next;
	}
	printf("Enter new passengers passport number: ");
	scanf("%d", &passportNum);
	newPassenger = createPassenger(newPassenger, passportNum);

}*/
