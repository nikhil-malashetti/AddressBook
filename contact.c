/*
Name: Nikhil Malashetti
Date: 10/10/2025
Description: "Address-Book"
	This program is about an address book system project.
	It can create contacts with validated Name, Phone, and Email.
	It can list all contacts sorted by name, phone or email.
	It can search contacts by any field.
	It can edit selected contact details.
	It can delete contacts which are selected.
	Save all changes to a file before exit.
	The program is implemented using strings, pointers, functions, structures, files and basics of C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

//Function to List all the contacts
void listContacts(struct AddressBook *addressBook)			
{
	printf("+----------+------------------------------+---------------+-----------------------------------+\n");
	printf("|%-10s|%-30s|%-15s|%-35s|\n", "SL.No", "Name", "Phone", "Email");
	printf("+----------+------------------------------+---------------+-----------------------------------+\n");

	//Starting for loop
	for(int i = 0; i < addressBook->contactCount; i++)
	{
		printf("|%-10d|%-30s|%-15s|%-35s|\n", i+1, 
				addressBook->contacts[i].name, 
				addressBook->contacts[i].phone,
				addressBook->contacts[i].email);
	} // end for
	printf("+----------+------------------------------+---------------+-----------------------------------+\n");
	printf("|Total contacts %d %-76s|\n", addressBook->contactCount, "");
	printf("+---------------------------------------------------------------------------------------------+\n");
}

//Function to initialise the structure
void initialize(struct AddressBook *addressBook) 
{
	//Initialising the contactCount to 0
	addressBook->contactCount = 0;

	// Load contacts from file during initialization (After files)
	loadContactsFromFile(addressBook);
}

//Function to Save and Exit 
void saveAndExit(struct AddressBook *addressBook) 
{
	saveContactsToFile(addressBook); // Save contacts to file
	exit(EXIT_SUCCESS); // Exit the program
}

//Funtion to Create the contact
void createContact(struct AddressBook *addressBook)
{
	//Reading name
	printf("Enter the name:");
	scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
	int j;
	char arr[20];
	do
	{
		j = 0;
		//Reading mobile number
		printf("Enter the mobile number:");
		scanf(" %[^\n]",arr);
		int duplicate = 0;
		//Checking for the duplicate mobile number
		for(int i = 0; i < addressBook->contactCount; i++)
		{
			if(strcmp(arr,addressBook->contacts[i].phone) == 0)
			{
				duplicate = 1;
				break;
			}
		}
		if(duplicate == 1)
		{
			j = 1;
			printf("Mobile Number already exists\n");
		}
		else
		{
			//Validating mobile number
			int val1 = validatemobile(arr);
			if(val1 == 1)
			{
				//Copying mobile number to structure
				strcpy(addressBook->contacts[addressBook->contactCount].phone, arr);
			}
			else
			{
				printf("Invalid Mobile Number\n");
				j = 1;
			}
		}
	}
	while(j);

	char arr1[30];
	do
	{
		j = 0;
		//Reading Email_ID
		printf("Enter the email: ");
		scanf(" %[^\n]", arr1);
		int duplicate = 0;
		//Checking for duplicate Email_ID
		for(int i = 0; i < addressBook->contactCount; i++)
		{
			if(strcmp(arr1, addressBook->contacts[i].email) == 0)
			{
				duplicate = 1;
				break;
			}
		}
		if(duplicate == 1)
		{
			j = 1;
			printf("Email_ID already exists\n");
		}
		else
		{
			//Validating Email_ID
			int val2 = validate_email(arr1);
			if(val2 == 1)
			{
				//Copying the Email_ID to structure
				strcpy(addressBook->contacts[addressBook->contactCount].email, arr1);
			}
			else
			{
				printf("Invalid Email_ID\n");
				j = 1;
			}
		}
	}while(j);
	printf("Contact saved successfully!\n");
	//Updating the contactCount
	(addressBook->contactCount)++;
}

//Function to validate Email_ID
int validate_email(char arr[])
{
	int flag = 1;
	int special_character = 0;
	int len = strlen(arr);

	for (int k = 0; arr[k] != '\0'; k++)
	{
		//Checking for Upper_Case
		if (arr[k] >= 'A' && arr[k] <= 'Z')
		{
			flag = 0;
			break;
		}
		//Checking for @ 
		if (arr[k] == '@')
		{
			if (k == 0 || k == len - 6)
			{
				flag = 0;
				break;
			}
			//Checking for the ".com"
			if (strcmp(arr + k + 1, ".com") == 0)
			{
				flag = 0;
				break;
			}
			special_character = 1;
		}
	}
	//Checking for the ".com" at the end of email
	if (strcmp(arr + len - 4, ".com") != 0)
		flag = 0;

	if (flag && special_character)
		return 1;
	else
		return 0;
}

//Function to Validate mobile number
int validatemobile(char arr[])
{
	int flag = 1;
	//Checking for the mobile number length = 10
	int len = strlen(arr);
	if(len != 10)
	{
		flag = 0;
	}
	//Checking for digits
	for(int k = 0;k < 10; k++)
	{
		if(!(arr[k] >= '0' && arr[k] <= '9'))
		{
			flag = 0;
			break;
		}
	}
	if(flag == 0)
		return 0;
	else
		return 1;
}

//Function to Search contact
int searchContact(struct AddressBook *addressBook) 
{
	//Checking if contactClount = 0
	if(addressBook->contactCount == 0)
	{
		printf("No contacts found\n");
		return -1;
	}

	char name[50], phone[20], email[50];
	//Creating integer array to store the indices
	int matchedIndex[addressBook->contactCount];
	int matchCount = 0, search;

	do {
		printf("Enter search by:\n1.Name\n2.Phone\n3.Email\n4.Exit\nChoice: ");
		scanf("%d", &search);

		switch(search) {
			case 1: 
				printf("Enter Name: ");
				scanf(" %[^\n]", name);
				for(int i = 0; i < addressBook->contactCount; i++)
				{
					//Seraching the entered name in structure neglecting case
					if(strcasestr(addressBook->contacts[i].name, name) != NULL)
					{
						//assigning the index of matched contacts to integer array
						matchedIndex[matchCount++] = i;
					}
				}
				break;
			case 2: 
				int flag;
				do{
					flag = 1;
					printf("Enter Phone: ");
					scanf(" %[^\n]", phone);
					int val1 = validatemobile(phone);
					if(val1 == 1)
					{
						flag = 0;
						for(int i = 0; i < addressBook->contactCount; i++) 
						{
							//Seraching the entered mobile number in structure neglecting case
							if(strcmp(addressBook->contacts[i].phone, phone) == 0) 
							{
								//assigning the index of matched contacts to integer array
								matchedIndex[matchCount++] = i;
							}
						}
					}
					else
					{
						printf("Inlvaid Mobile number\nEnter valid mobile number\n");
					}
				}
				while(flag);
				break;
			case 3:
				do{
					flag = 1;	       
					printf("Enter Email: ");
					scanf(" %[^\n]", email);
					int val2 = validate_email(email);
					if(val2 == 1)
					{
						flag = 0;
						for(int i = 0; i < addressBook->contactCount; i++) 
						{
							//Seraching the entered mobile number in structure neglecting case
							if(strcmp(addressBook->contacts[i].email, email) == 0) 
							{
								//assigning the index of matched contacts to integer array
								matchedIndex[matchCount++] = i;
							}
						}
					}
					else
					{
						printf("Inlvaid Mobile number\nEnter valid mobile number\n");
					}
				}while(flag);
				break;
			case 4:
				printf("Exiting search!!\n");
				return 0;
			default:
				printf("Invalid choise\nEnter valid choise between 1 - 4\n");
		}
	} while(search < 1 || search > 3);

	if(matchCount == 0) 
	{
		printf("No contacts found.\n");
		searchContact(addressBook);
	}

	//Printing the contacts found
	printf("+----------+------------------------------+---------------+-----------------------------------+\n");
	printf("|%-10s|%-30s|%-15s|%-35s|\n", "SL.No", "Name", "Phone", "Email");
	printf("+----------+------------------------------+---------------+-----------------------------------+\n");

	for(int i = 0; i < matchCount; i++)
	{
		int index = matchedIndex[i];
		printf("|%-10d|%-30s|%-15s|%-35s|\n",
				index + 1,
				addressBook->contacts[index].name,
				addressBook->contacts[index].phone,
				addressBook->contacts[index].email);
	}
	printf("+----------+------------------------------+---------------+-----------------------------------+\n");

	int finalIndex;
	if(matchCount == 1) 
	{
		finalIndex = matchedIndex[0];
	} 
	else 
	{
		int sl, found = 0;
		while(!found) 
		{
			//Asking for the serial number to search in multiple contacts
			printf("Multiple matches found. Enter Serial No: ");
			scanf("%d", &sl);
			//Checking for the serial number in the integer array
			for(int i = 0; i < matchCount; i++)
			{
				if(sl == matchedIndex[i] + 1) 
				{
					finalIndex = matchedIndex[i];
					found = 1;
					break;
				}
			}
			if(!found)
				printf("Invalid Serial No.\n");
		}
		//Displaying the searched contact
		display(addressBook, finalIndex);
	}
	//Returning the final index
	return finalIndex;
}

//Function to edit the contact
void editContact(struct AddressBook *addressBook)
{
	if(addressBook->contactCount == 0) 
	{
		printf("No contacts to edit\n");
		return;
	}

	int index = searchContact(addressBook);
	if(index == -1)
		return;

	int choice;
	do{
		printf("Which field do you want to edit:\n1.Name\n2.Phone\n3.Email\n4.Exit\nChoice: ");
		scanf("%d", &choice);
		char phone[20], email[50];
		int flag;

		switch(choice)
		{
			case 1: 
				//Reading and Assigning the new name to the structure
				printf("Enter new Name: ");
				scanf(" %[^\n]", addressBook->contacts[index].name);
				//Displaying the edited contact
				display(addressBook, index);
				printf("Contact Edited successfully\n");
				break;

			case 2: 
				do {
					flag = 1;
					//Reading the new mobile number
					printf("Enter new Phone: ");
					scanf("%s", phone);
					//Validating the mobile number
					int val1 = validatemobile(phone);
					if(val1 == 1)
					{
						//Assigning the new mobile number to structure
						strcpy(addressBook->contacts[index].phone, phone);
						flag = 0;
						//Displaying the edited contact
						display(addressBook, index);
						printf("Contact Edited successfully\n");
					}
					else
					{
						printf("Invalid mobile number\nEnter the correct mobile number\n");
					}
				}
				while(flag);
				break;

			case 3: 
				do {
					flag = 1;
					//Reading the new Email_ID
					printf("Enter new Email: ");
					scanf(" %[^\n]", email);
					//Validating the Email_ID
					int val2 = validate_email(email);
					if(val2 == 1)
					{
						//Assigning the new Email_ID to stucture
						strcpy(addressBook->contacts[index].email, email);
						//Dispalying the edited contact
						display(addressBook, index);
						printf("Contact Edited successfully\n");
						flag = 0;
					}
					else
					{
						printf("Invalid Email_ID\nEnter the valid Email_ID\n");
					}		
				} while(flag);
				break;
			case 4:
				printf("Exiting Edit!!\n");
				return;
				break;
			default:
				printf("Invalid Choice\nEnter the choice betweeen 1 - 4\n");

		} 
	}while(choice < 1 || choice > 4);
} 

//Function to Delete contact
void deleteContact(struct AddressBook *addressBook)
{
	//Checking for the emptyness of structure
	if(addressBook->contactCount == 0)
	{
		printf("Address book is empty\n");
		return;
	}

	//Getting index using the searchContact function
	int index = searchContact(addressBook);
	if(index == -1)
		return;

	//Deleting using the Shifting method
	for(int i = index; i < addressBook->contactCount - 1; i++)
	{
		addressBook->contacts[i] = addressBook->contacts[i + 1];
	}
	//Decrementing the contactCount
	(addressBook->contactCount)--;

	printf("Contact deleted successfully.\n");

}

//Function to Display the contact
void display(struct AddressBook *addressBook, int index)
{
	printf("+----------+------------------------------+---------------+-----------------------------------+\n");
	printf("|%-10s|%-30s|%-15s|%-35s|\n", "SL.No", "Name", "Phone", "Email");
	printf("+----------+------------------------------+---------------+-----------------------------------+\n");
	printf("|%-10d|%-30s|%-15s|%-35s|\n",
			index + 1,
			addressBook->contacts[index].name,
			addressBook->contacts[index].phone,
			addressBook->contacts[index].email);
	printf("+----------+------------------------------+---------------+-----------------------------------+\n");
}
