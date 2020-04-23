#include "Console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run()
{
	char command[100], offerType[50], offerDestination[50];
	int offerID, offerPrice;
	int loopCondition = 1;
	Offer* newOffer;

	OfferRepo* offerRepo = createRepo();
	UndoRedoList* undoList = createUndoRedoList();
	UndoRedoList* redoList = createUndoRedoList();

	while (loopCondition)
	{
		printf(">>");
		fgets(command, 200, stdin);
		char *commandElement = strtok(&command, ", \n");
		if (strcmp(commandElement, "add") == 0 || strcmp(commandElement, "update") == 0)
		{
			strcpy(command, commandElement);
			
			commandElement = strtok(NULL, ", ");
			offerID = atoi(commandElement);
			
			commandElement = strtok(NULL, ", ");
			strcpy(offerType, commandElement);

			commandElement = strtok(NULL, ", ");
			strcpy(offerDestination, commandElement);

			commandElement = strtok(NULL, ", ");
			offerPrice = atoi(commandElement);

			if (strcmp(command, "add") == 0)
			{
				if (existingID(offerID, offerRepo) == -1)
				{
					destroyOperationList(redoList);
					redoList = createUndoRedoList();

					addOperation(undoList, offerRepo);
					newOffer = createOffer(offerID, offerType, offerDestination, offerPrice);
					addNewOffer(newOffer, offerRepo);
				}
				
				else
					printf("The offer already exists.\n");
			}

			else
			{
				if (existingID(offerID, offerRepo) != -1)
				{
					destroyOperationList(redoList);
					redoList = createUndoRedoList();

					addOperation(undoList, offerRepo);
					newOffer = createOffer(offerID, offerType, offerDestination, offerPrice);
					updateExistingOffer(newOffer, offerRepo);
				}

				else
					printf("The offer doesn't exist.\n");
			}

		}

		else
		{
			if (strcmp(commandElement, "delete") == 0)
			{
				commandElement = strtok(NULL, ", ");
				offerID = atoi(commandElement);

				if (existingID(offerID, offerRepo) != -1)
				{
					destroyOperationList(redoList);
					redoList = createUndoRedoList();

					addOperation(undoList, offerRepo);
					deleteExistingOffer(offerID, offerRepo);
				}

				else
					printf("The offer doesn't exist.\n");
			}

			else
			{
				if (strcmp(commandElement, "list") == 0)
				{
					commandElement = strtok(NULL, "\n");
					if (commandElement == NULL)
					{
						char buffer[15], stringToPrint[200];

						for (int index = 0; index < offerRepo->listLength; index++)
						{
							strcpy(stringToPrint, "");
							strcat(stringToPrint, "Offer ID: ");
							_itoa(offerRepo->offerList[index]->offerID, buffer, 10);
							strcat(stringToPrint, buffer);
							strcat(stringToPrint, ", Holiday Type: ");
							strcat(stringToPrint, offerRepo->offerList[index]->type);
							strcat(stringToPrint, ", Holiday Destination: ");
							strcat(stringToPrint, offerRepo->offerList[index]->destination);
							strcat(stringToPrint, ", Price: ");
							_itoa(offerRepo->offerList[index]->price, buffer, 10);
							strcat(stringToPrint, buffer);
							strcat(stringToPrint, "\n");

							printf("%s", stringToPrint);
						}
					}

					else
					{
						char buffer[15], stringToPrint[200];
						int isNumber = 1;

						for (int index = 0; index < strlen(commandElement); index++)
						{
							if (commandElement[index] < '0' || commandElement[index] > '9')
							{
								isNumber = 0;
								break;
							}

						}

						if (isNumber)
						{
							int maxPrice = atoi(commandElement);
							sortTypeAscending(offerRepo);

							for (int index = 0; index < offerRepo->listLength; index++)
							{
								if (offerRepo->offerList[index]->price <= maxPrice)
								{
									strcpy(stringToPrint, "");
									strcat(stringToPrint, "Offer ID: ");
									_itoa(offerRepo->offerList[index]->offerID, buffer, 10);
									strcat(stringToPrint, buffer);
									strcat(stringToPrint, ", Holiday Type: ");
									strcat(stringToPrint, offerRepo->offerList[index]->type);
									strcat(stringToPrint, ", Holiday Destination: ");
									strcat(stringToPrint, offerRepo->offerList[index]->destination);
									strcat(stringToPrint, ", Price: ");
									_itoa(offerRepo->offerList[index]->price, buffer, 10);
									strcat(stringToPrint, buffer);
									strcat(stringToPrint, "\n");

									printf("%s", stringToPrint);
								}
							}


						}

						else
						{
							for (int index = 0; index < offerRepo->listLength; index++)
							{
								if (strcmp(offerRepo->offerList[index]->destination, commandElement) == 0)
								{
									strcpy(stringToPrint, "");
									strcat(stringToPrint, "Offer ID: ");
									_itoa(offerRepo->offerList[index]->offerID, buffer, 10);
									strcat(stringToPrint, buffer);
									strcat(stringToPrint, ", Holiday Type: ");
									strcat(stringToPrint, offerRepo->offerList[index]->type);
									strcat(stringToPrint, ", Holiday Destination: ");
									strcat(stringToPrint, offerRepo->offerList[index]->destination);
									strcat(stringToPrint, ", Price: ");
									_itoa(offerRepo->offerList[index]->price, buffer, 10);
									strcat(stringToPrint, buffer);
									strcat(stringToPrint, "\n");

									printf("%s", stringToPrint);
								}
							}
						}
					}
				}

				else
				{
					if (strcmp(commandElement, "exit") == 0)
						loopCondition = 0;
					else
					{
						if (strcmp(commandElement, "undo") == 0)
						{
							if (undoList->listLength >= 1)
							{
								
								addOperation(redoList, offerRepo);
								deallocateRepo(offerRepo);
								offerRepo = copyRepo(undoList->operationList[undoList->listLength - 1]);

								deallocateRepo(undoList->operationList[undoList->listLength - 1]);
								undoList->listLength -= 1;
							}
							
							else
								printf("No undo\n");
						}
						else
							if (strcmp(commandElement, "redo") == 0)
							{
								if (redoList->listLength >= 1)
								{
									deallocateRepo(offerRepo);
									offerRepo = copyRepo(redoList->operationList[redoList->listLength - 1]);
									deallocateRepo(redoList->operationList[redoList->listLength - 1]);

									addOperation(undoList, redoList->operationList[redoList->listLength - 1]);
									redoList->listLength -= 1;
								}

								else
									printf("No redo\n");

							}
							else
								printf("The given command is invalid!\n");
					}
				}
			}
		}
	}

	destroyOperationList(undoList);
	destroyOperationList(redoList);
	deallocateRepo(offerRepo);
}