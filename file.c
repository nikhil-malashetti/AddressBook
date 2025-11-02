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
             The program is implemented using strings, pointers, functions,
             structures, files and basics of C.
*/


#include <stdio.h>      
#include "contact.h"  
#include "file.h"     


void saveContactsToFile(struct AddressBook *addressBook) {

	FILE *fptr = fopen("contacts.csv","w");				//Opening the file in write mode	

	fprintf(fptr,"%d\n",addressBook->contactCount);			//Printing the total number of contacts

	for(int i=0; i < addressBook->contactCount; i++)		//Printing the Contacts from structure to file
	{
	fprintf(fptr,"%s,%s,%s\n",
				addressBook->contacts[i].name,
				addressBook->contacts[i].phone,
				addressBook->contacts[i].email);
	}
	fclose(fptr); 
}

void loadContactsFromFile(struct AddressBook *addressBook)
{
	FILE *fptr = fopen("contacts.csv","r");				//Opening the file in read mode

	if(fptr == NULL)						//Checking for the file existence
	{
		addressBook->contactCount = 0;				
		return;
	}

	fscanf(fptr,"%d\n",&addressBook->contactCount);			//Fetching the total number of contacts

	for(int i = 0; i < addressBook->contactCount; i++)		//Fetching the Contacts details from the file to structure
	{
		fscanf(fptr,"%[^,],%[^,],%[^\n]\n",
				addressBook->contacts[i].name,
				addressBook->contacts[i].phone,
				addressBook->contacts[i].email);
	}
	fclose(fptr);
}
