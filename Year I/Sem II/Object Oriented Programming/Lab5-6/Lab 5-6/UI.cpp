#include "UI.h"

using namespace std;

bool UI::checkIfNumber(std::string & stringToCheck)
{
	int length = stringToCheck.length();
	for (int index = 0; index < length; index++)
		if (stringToCheck[index] < '0' || stringToCheck[index] > '9')
			return false;

	return true;
}

void UI::UIAddMovieAsAdmin(Movie & movieToAdd)
{
	controller.addMovieAsAdmin(movieToAdd);
}

void UI::UIUpdateMovie(std::string & movieTitle, std::string & movieGenre, int releaseYear, int likes, std::string & trailer)
{
	controller.updateMovie(movieTitle, movieGenre, releaseYear, likes, trailer);
}

void UI::UIDeleteMovie(std::string & movieTitle)
{
	controller.deleteMovie(movieTitle);
}

void UI::UIAddMovieToWatchList(std::string & movieTitle)
{
	controller.addMovieToWatchList(movieTitle);
}

void UI::UIListAll()
{
	DynamicVector<Movie> allMovies = controller.getAllMovies();
	for (int index = 0; index < allMovies.getSize(); index++)
		cout << allMovies[index].toStringMovie() << endl;
}

void UI::UIListGenreLikes(std::string & movieGenre, int likes)
{
	DynamicVector<Movie> allMovies = controller.getAllMovies();
	for (int index = 0; index < allMovies.getSize(); index++)
		if (allMovies[index].getGenre() == movieGenre && allMovies[index].getLikes() >= likes)
			cout << allMovies[index].toStringMovie() << endl;
}

void UI::UIListWatchList()
{
	DynamicVector<Movie> userWatchList = controller.getWatchList();
	for (int index = 0; index < userWatchList.getSize(); index++)
		cout << userWatchList[index].toStringMovie() << endl;
}

void UI::UINext()
{
	controller.nextMovie();
}

void UI::UIPrintAdminMenu()
{
	cout << "Mode A\n" << "Available commands: \n" << "1. mode B\n" << "2. add title, genre, releaseYear, likes, trailer\n" << "3. update title, genre, releaseYear, likes, trailer\n" << "4. delete title\n" << "5. list\n" << "6. exit\n";
}

void UI::UIPrintUserMenu()
{
	cout << "Mode B\n" << "Available commands: \n" << "1. mode A\n" << "2. next\n" << "3. save title\n" << "4. mylist\n" << "5. list x,y\n" << "6. exit\n";
}

void UI::run()
{
	int printMenu = 0;
	char command[256];

		fgets(command, sizeof(command), stdin);
		char* commandParameter;
		commandParameter = strtok(command, " \n");

		if (commandParameter == NULL)
		{
			return;
		}

		else if (strcmp(commandParameter, "mode") == 0)
		{
			commandParameter = strtok(NULL, "\n");
			if (strcmp(commandParameter, "A") == 0)
			{
				mode = 1;
			}

			else
				if (strcmp(commandParameter, "B") == 0)
				{
					mode = 2;
				}
				else
					return;
		}

		else
			return;
	
	while (1)
	{
		if (mode == 1)
		{
			if (printMenu == 0)
			{
				UIPrintAdminMenu();
				printMenu = 1;
			}

			fgets(command, sizeof(command), stdin);
			char* commandParameter;
			commandParameter = strtok(command, " \n");

			if (strcmp(commandParameter, "mode") == 0)
			{
				commandParameter = strtok(NULL, "\n");

				if (strcmp(commandParameter, "A") == 0)
					mode = 1;
				else
					if (strcmp(commandParameter, "B") == 0)
					{
						mode = 2;
						printMenu = 0;
					}
					else
						cout << "Wrong command, try again\n";
			}

			else if (strcmp(commandParameter, "add") == 0)
			{
				commandParameter = strtok(NULL, ",");
				if (commandParameter != NULL)
				{
					std::string movieTitle = commandParameter;

					commandParameter = strtok(NULL, ",");
					if (commandParameter != NULL)
					{
						std::string movieGenre = commandParameter;
						while (movieGenre[0] == ' ')
							movieGenre.erase(movieGenre.begin());

						commandParameter = strtok(NULL, ", ");
						std::string year = commandParameter;
						if (checkIfNumber(year))
						{
							int releaseYear = atoi(commandParameter);

							commandParameter = strtok(NULL, ", ");
							std::string likes = commandParameter;
							if (checkIfNumber(likes))
							{
								int likes = atoi(commandParameter);

								commandParameter = strtok(NULL, "\n ");
								if (commandParameter != NULL)
								{
									std::string trailer = commandParameter;

									Movie movieToAdd = Movie(movieTitle, movieGenre, releaseYear, likes, trailer);

									UIAddMovieAsAdmin(movieToAdd);
								}
							}

							else
								cout << "Nope\n";
						}
						else
							cout << "Nope\n";
					}
					else
						cout << "Nope\n";
				}
				else
					cout << "Nope\n";
			}

			else if (strcmp(commandParameter, "update") == 0)
			{
				commandParameter = strtok(NULL, ",");
				if (commandParameter != NULL)
				{
					std::string movieTitle = commandParameter;

					commandParameter = strtok(NULL, ",");
					if (commandParameter != NULL)
					{
						std::string movieGenre = commandParameter;

						commandParameter = strtok(NULL, ", ");
						std::string year = commandParameter;
						if (checkIfNumber(year))
						{
							int releaseYear = atoi(commandParameter);

							commandParameter = strtok(NULL, ", ");
							std::string likes = commandParameter;
							if (checkIfNumber(likes))
							{
								int likes = atoi(commandParameter);

								commandParameter = strtok(NULL, "\n ");
								if (commandParameter != NULL)
								{
									std::string trailer = commandParameter;
									UIUpdateMovie(movieTitle, movieGenre, releaseYear, likes, trailer);
								}
							}

							else
								cout << "Nope\n";
						}
						else
							cout << "Nope\n";
					}
					else
						cout << "Nope\n";
				}
				else
					cout << "Nope\n";
			}

			else if (strcmp(commandParameter, "delete") == 0)
			{
				commandParameter = strtok(NULL, "\n ");
				std::string movieTitle = commandParameter;

				UIDeleteMovie(movieTitle);
			}

			else if (strcmp(commandParameter, "list") == 0)
			{
					UIListAll();
			}

			else if (strcmp(commandParameter, "exit") == 0)
				return;

			else
				cout << "Wrong command, try again\n";
		}

		if (mode == 2)
		{

			if (printMenu == 0)
			{
				UIPrintUserMenu();
				printMenu = 1;
			}

			fgets(command, sizeof(command), stdin);
			char* commandParameter;
			commandParameter = strtok(command, " \n");

			if (strcmp(commandParameter, "mode") == 0)
			{
				commandParameter = strtok(NULL, "\n");

				if (strcmp(commandParameter, "A") == 0)
				{
					mode = 1;
					printMenu = 0;
				}

				else
					if (strcmp(commandParameter, "B") == 0)
						mode = 2;
					else
						cout << "Wrong command, try again\n";
			}

			else if (strcmp(commandParameter, "next") == 0)
			{
				UINext();
				if (controller.getAllMovies.getSize() > 0)
					cout << controller.getCurrentMovie().toStringMovie() << endl;
			}

			else if (strcmp(commandParameter, "save") == 0)
			{
				commandParameter = strtok(NULL, "\n");
				std::string movieTitle = commandParameter;

				UIAddMovieToWatchList(movieTitle);
			}

			else if (strcmp(commandParameter, "list") == 0)
			{
				commandParameter = strtok(NULL, ",");
				std::string movieGenre = commandParameter;

				commandParameter = strtok(NULL, "\n");
				int likes = atoi(commandParameter);

				UIListGenreLikes(movieGenre, likes);

			}

			else if (strcmp(commandParameter, "mylist") == 0)
				UIListWatchList();

			else if (strcmp(commandParameter, "exit") == 0)
				return;
		}
	}
}
