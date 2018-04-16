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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define UK 1
#define RESTOFEUROPE 2
#define ASIA 3
#define AMERICAS 4
#define AUSTRALASIA 5
#define ECONOMY 1
#define PREMIUM 2
#define BUSSINES 3
#define FIRST 4
#define THREE_TIMES 1
#define FIVE_TIMES 2
#define MORE_THAN_FIVE 3
#define ONE_DAY 1
#define THREE_DAYS 2
#define SEVEN_DAYS 3
#define MORE_THAN_SEVEN 4

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

int login();
void addPassengerAtStart(struct Passenger** head);
struct Passenger * createPassenger(Passenger * head, int passportNum);
void displayList(struct Passenger* head);
int searchPassengerList(Passenger * head, int passportNum, char fullName[]);
void passportUnique(int passportNum, Passenger * head);
void sortList(Passenger ** head);
Passenger * swapNodeData(Passenger * temp1, Passenger * temp2);
void updatePassenger(Passenger ** head, int position);
void loadPassengerListFile(Passenger ** head);
void displayPassenger(Passenger ** head, int update);
void printPassengerDetails(Passenger * head, int position);
void deletePassenger(Passenger ** head);
int listLength(Passenger * head);
int validateEmail(char email[]);
int * statisticsMenu(int statisticsOptions[]);
int statisticsSecondMenu();
void generateStatisticsProcess(Passenger * head, int statOptions[]);
float generateStatsByTravelClassAndTravelOrigin(Passenger ** head, int travelClass, int option);

void main() {

    struct Passenger* headPtr = NULL;
    int choice;
    int loggedIn = 0;
    int statisticsOptions[3];

    do
    {
    	loggedIn = login();
    }
    while(loggedIn == 0);

    loadPassengerListFile(&headPtr);
    sortList(&headPtr);

    printf("1. Add new passenger.\n");
    printf("2. Display all passengers to screen.\n");
    printf("3. Display a passengers details.\n");
    printf("4. Update a passenger.\n");
    printf("5. Delete a passenger.\n");
    printf("6. Generate statistics.\n");
    printf("7. Print all passengers details to report file.\n");

    scanf("%d", &choice);

    while(choice != -1)
    {
        switch(choice)
        {
        case 1:
            addPassengerAtStart(&headPtr);
            break;
        case 2:
        	displayList(headPtr);
            break;
        case 3:
        	displayPassenger(&headPtr, 0);
            break;
        case 4:
        	displayPassenger(&headPtr, 1);
        	break;
        case 5:
        	deletePassenger(&headPtr);
        	break;
        case 6:
        	statisticsMenu(statisticsOptions);
        	generateStatisticsProcess(headPtr, statisticsOptions);
        	//printf("%d %d %d\n", statisticsOptions[0], statisticsOptions[1], statisticsOptions[2]);
        	break;
        }
        printf("1. Add new passenger.\n");
        printf("2. Display all passengers to screen.\n");
        printf("3. Display a passengers details.\n");
        printf("4. Update a passenger.\n");
        printf("5. Delete a passenger.\n");
        printf("6. Generate statistics.\n");
        printf("7. Print all passengers details to report file.\n");

        scanf("%d", &choice);
    }
}

float generateStatsByTravelClassAndTravelOrigin(Passenger ** head, int travelClass, int option)
{
	Passenger * curr = *head;
	int count = 0;
	float percentage;
	int len = listLength(*head);

	while(curr != NULL)
	{
		if(curr->travelClass == travelClass && curr->travelOrigin == option)
		{
			count++;
			printf("%d\n", count);
		}
		curr = curr->next;
	}
	printf("Count: %d\n", count);
	printf("LEngth %d\n", listLength(*head));
	percentage = (count / len) * 100;
	return percentage;
}

void generateStatisticsProcess(Passenger * head, int statOptions[])
{
	//Passenger * curr;
	//curr = head;


	switch(statOptions[1])
	{
	case ECONOMY:
	case PREMIUM:
	case BUSSINES:
	case FIRST:
		if(statOptions[2] <= 5)
			printf("---- %f ---", generateStatsByTravelClassAndTravelOrigin(&head, statOptions[1], statOptions[2]));
		//if(statOptions[2] >= 6)
			//generateStatsByTravelClassAndDurationOfStay(head, statOptions[1], statOptions[2]);
		break;
	case 0:
		if(statOptions[2] <= 5)
			//generateStatsByYearBornAndTravelOrigin(head, statOptions[1], statOptions[2]);
		if(statOptions[2] >= 6)
			//generateStatsByYearBornAndDurationOfStay(head, statOptions[1], statOptions[2]);
		break;
	}
}

int * statisticsMenu(int options[])
{
	int choice;
	int correctInput = 1;

	do
	{
		correctInput = 1;
		choice = 0;

		printf("Choose criteria for statistics: \n");
		printf("1. Travel class. \n2. Born before 1980.\n");

		scanf("%d", &choice);

		if(choice == 1)
		{
			options[0] = 1;
			printf("Choose travel class: \n");
			printf("1. Economy.\n2. Premium economy.\n3. Business.\n 4. First.\n");

			scanf("%d", &choice);

			if(choice == 1)
			{
				options[1] = ECONOMY;
			}
			else if(choice == 2)
			{
				options[1] = PREMIUM;
			}
			else if(choice == 3)
			{
				options[1] = BUSSINES;
			}
			else if(choice == 4)
			{
				options[1] = FIRST;
			}
			else
			{
				printf("Incorrect input, try again.\n");
				correctInput = 0;
				continue;
			}
			options[2] = statisticsSecondMenu();
		}
		else if(choice == 2)
		{
			options[0] = 2;
			options[1] = 0;
			options[2] = statisticsSecondMenu();
		}
		else
		{
			printf("Incorrect input.\n");
			correctInput = 0;
			continue;
		}
	}
	while(correctInput != 1);

	return options;
}

int statisticsSecondMenu()
{
	int choice;

	printf("Choose one of the available statistics: \n");
	printf("1. %% of passengers who travel from the UK\n");
	printf("2. %% of passengers who travel from the Rest of Europe");
	printf("3. %% of players who travel from the Asia\n");
	printf("4. %% of passengers who travel from the Americas\n");
	printf("5. %% of passengers who travel from the Australasia\n");
	printf("6. %% of passengers who spent on average one day in Ireland\n");
	printf("7. %% of passengers who spent on average less than 3 days in Ireland\n");
	printf("8. %% of passengers who spent on average less than 7 days in Ireland\n");
	printf("9. %% of passengers who spent on average more than 7 days in Ireland\n");

	scanf("%d", &choice);

	return choice;
}

int validateEmail(char email[])
{
	const char s[2] = "@.";
	const char com[3] = "com";
	char *tok[3];
	char *token;
	int tokenCount;

	token = strtok(email, s);
	tokenCount = 0;

	while( token != NULL)
	{
		tok[tokenCount] = token;

		token = strtok(NULL, s);

		if(token != NULL)tokenCount++;
	}

	if(tokenCount != 2 || strcmp(tok[2], com) != 0)
	{
		printf("Email format is incorrect, try again.\n");
		return 0;
	}
	return 1;
}

int login()
{
	char loginName[10];
	char password[6];

	FILE * fptr;
	fptr = fopen("auth.dat", "r");

	if(fptr == NULL)
	{
		printf("Authentification file could not be opened;");
		exit(0);
	}
	else
	{
		printf("Login: ");
		scanf("%s", loginName);
		printf("Password: ");
		scanf("%s", password);

		while(!feof(fptr))
		{
			char loginFromFile[10];
			char passwordFromFile[6];

			fscanf(fptr, "%s %s", loginFromFile, passwordFromFile);

			if(strcmp(loginName, loginFromFile) == 0 && strcmp(password, passwordFromFile) == 0)
			{
				printf("Login successful.\n\n");
				return 1;
			}
		}
		printf("Login or password incorrect. Try again.\n\n");
		return 0;
	}
}

void loadPassengerListFile(Passenger ** head)
{
	FILE *fptr;
	fptr = fopen("passengerList.dat", "r");

	if (fptr == NULL)
	{
		printf("The file could not be opened\n");
	}
	else
	{
		printf("Loading data file.\n");

		while (!feof(fptr))
		{
			Passenger * readPassenger = (Passenger *)malloc(sizeof(Passenger));
			fscanf(fptr, "%d %s %s %d %s %d %d %d %d",
				&readPassenger->passportNumber, readPassenger->firstName, readPassenger->secondName,
					&readPassenger->DOB, readPassenger->email, &readPassenger->travelOrigin, &readPassenger->travelClass,
						&readPassenger->travelPerYear, &readPassenger->durationOfStay);

			readPassenger->next = *head;
			*head = readPassenger;
		}
		printf("Data loaded successfully.\n\n");
		fclose(fptr);
	}
}

void addPassengerAtStart(Passenger** head)
{
    Passenger* newPassenger;
    int passportNum;
    int passengerIndex;
    int choice;

    newPassenger = (Passenger*)malloc(sizeof(Passenger));

    printf("Enter new passengers passport number: ");
    scanf("%d", &passportNum);

    passengerIndex = searchPassengerList(*head, passportNum, NULL);

    if(passengerIndex > 0)
    {
        printf("\nPassenger with this passport number already exists in database.");
        printf("\nWould you like to update details?");
        printf("\n1. Yes 2. No");

        scanf("%d", &choice);

        if(choice == 1)
        {
            updatePassenger(head, passengerIndex);
        }
        else
        {
            return;
        }
    }
    else
    {
    	newPassenger = createPassenger(*head, passportNum);
        newPassenger->next = *head;
        *head = newPassenger;
    }
    sortList(head);
}

struct Passenger * createPassenger(Passenger * head, int passportNum)
{
    struct Passenger * newPassenger = (Passenger*)malloc(sizeof(Passenger));

    if(newPassenger == NULL)
    {
        puts("Error creating new passenger");
        return 0;
    }
    else
    {
    	newPassenger->passportNumber = passportNum;

        printf("Enter first name: ");
        scanf("%s", newPassenger->firstName);
        printf("Enter second name: ");
        scanf("%s", newPassenger->secondName);
        //printf("Enter date of birth in format ddmmyyyy: ");
        //scanf("%d", &newPassenger->DOB);
        do
        {
        	printf("Enter passengers email: ");
        	scanf("%s", newPassenger->email);
        }
        while(validateEmail(newPassenger->email) != 1);
        /*printf("Enter passengers origin of travel: ");
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
    return newPassenger;
}

void displayList(Passenger* head)
{
    Passenger* curr;

    curr = head;

    if(curr == NULL)
    {
    	printf("\nData file is empty.\n\n");
    	return;
    }

    while (curr != NULL)
    {
        printf("The passport number is %d\n", curr->passportNumber);
        printf("The first name is %s\n", curr->firstName);
        printf("Last name: %s\n\n", curr->secondName);
        curr = curr->next;
    }
}

void passportUnique(int passportNum, Passenger * head)
{
    int result;

    result = searchPassengerList(head, passportNum, "");

    if (result != -1)
    {
        printf("Not a unique ID\n");
        return;
    }
}

int searchPassengerList(Passenger * head, int passportNum, char fullName[])
{
    Passenger * curr = head;
    int position = 0;
    int i;

    if(passportNum != 0)
    {
    	while(curr != NULL)
    	{
    		position++;

    		if(passportNum == curr->passportNumber) return position;

    		curr = curr->next;
    	}
    }
    else
    {
    	for(i = 0; i < strlen(fullName); i++) fullName[i] = toupper(fullName[i]);

    	while(curr != NULL)
    	{
    		char first[20] = "\0";
    		char last[20] = "\0";
    		char full[40] = "\0";

    		strcpy(first,curr->firstName);
    		strcpy(last,curr->secondName);
    		strcpy(full,strcat(first,last));

    		position++;

    		for(i = 0; i < strlen(full); i++) full[i] = toupper(full[i]);

    		if(strcmp(fullName,full) == 0)
    		{
    			return position;
    		}
    		curr = curr->next;
    	}
    }
    return -1;
}

void sortList(Passenger ** head)
{
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

Passenger * swapNodeData(Passenger * temp1, Passenger * temp2)
{
    temp1->passportNumber = temp2->passportNumber;
    strcpy(temp1->firstName, temp2->firstName);
    strcpy(temp1->secondName, temp2->secondName);
    temp1->DOB = temp2->DOB;
    strcpy(temp1->email, temp2->email);
    temp1->travelOrigin = temp2->travelOrigin;
    temp1->travelClass = temp2->travelClass;
    temp1->travelPerYear = temp2->travelPerYear;
    temp1->durationOfStay = temp2->durationOfStay;

    return temp1;
}

void updatePassenger(Passenger ** head, int position)
{
    Passenger * newPassenger = *head;
    int passportNum;

    for (int i = 0;i < position - 1;i++)
    {
        newPassenger = newPassenger->next;
    }
    printf("Enter new passengers passport number: ");
    scanf("%d", &passportNum);
    newPassenger->passportNumber = passportNum;

    printf("Enter passenger first name: ");
    scanf("%s", newPassenger->firstName);
    sortList(head);
}



void displayPassenger(Passenger ** head, int update)
{
	int choice;
	int position;
	int passportNum = 0;
	char firstName[20], secondName[20];

	printf("Find passenger using:\n");
	printf("1. Passport number.\n");
	printf("2. Full name.\n");

	scanf("%d", &choice);

	if(choice == 1)
	{
		printf("Enter passengers passport number: ");
		scanf("%d", &passportNum);

		position = searchPassengerList(*head,passportNum, "");
		printPassengerDetails(*head, position);

		if(update == 1) updatePassenger(head, position);
	}
	else if(choice == 2)
	{
		printf("Enter passengers first name: ");
		scanf("%s", firstName);

		printf("Enter passengers second name: ");
		scanf("%s", secondName);

		position = searchPassengerList(*head, passportNum, strcat(firstName, secondName));
		printPassengerDetails(*head, position);

		if(update == 1) updatePassenger(head, position);
	}
}

void printPassengerDetails(Passenger * head, int position)
{
	Passenger * printPassenger = head;

	for (int i = 0;i < position - 1;i++)
	{
		printPassenger = printPassenger->next;
	}

	printf("Passport number: %d\n", printPassenger->passportNumber);
	printf("First name: %s\n", printPassenger->firstName);
	printf("Last name: %s\n", printPassenger->secondName);
}

void deletePassenger(Passenger ** head)
{
	Passenger* curr;
	Passenger* prev_curr;
	int i;

	int passportNum;
	int position;

	printf("Enter passengers passport number to delete: ");
	scanf("%d", &passportNum);

	position = searchPassengerList(*head, passportNum, NULL);

	curr = *head;

	if(position == 1){

		curr = *head;

		*head = curr->next;

		free(curr);
		return;
	}

	if(position == listLength(*head))
	{
		while (curr->next != NULL)
		{
			prev_curr = curr;
			curr = curr->next;
		}
		prev_curr->next = NULL;
		free(curr);

		return;
	}

	for (i = 0;i < position - 1;i++)
	{
		prev_curr = curr;
		curr = curr->next;
	}
	prev_curr->next = curr->next;
	free(curr);

}

int listLength(Passenger * head)
{
	Passenger * curr = head;
	int len = 0;

	while (curr != NULL)
	{
		len++;
		curr = curr->next;
	}
	return len;
}

