#include "Console.h"
#include <iostream>

using namespace std;

bool Console::checkIfNumber(std::string & stringToCheck)
{
	int length = stringToCheck.length();
	for (int index = 0; index < length; index++)
		if (stringToCheck[index] < '0' || stringToCheck[index] > '9')
			return false;

	return true;
}

void Console::UIAddMovie(char * parameters)
{
	std::string movieTitle, movieGenre, movieTrailer;
	int releaseYear, likes;
	
	parameters = strtok(parameters, ",\n");
	movieTitle = parameters;

	parameters = strtok(NULL, ",\n");
	movieGenre = parameters;

	parameters = strtok(NULL, " ,\n");
	releaseYear = atoi(parameters);

	parameters = strtok(NULL, " ,\n");
	likes = atoi(parameters);

	parameters = strtok(NULL, "\n");
	movieTrailer = parameters;
	
	try
	{
		Movie movieToAdd = Movie(movieTitle, movieGenre, releaseYear, likes, movieTrailer);
		controller.addMovie(movieToAdd);
	}

	catch (MovieException& exception)
	{
		exception.getError();
	}

}

void Console::UIUpdateMovie(char * parameters)
{
	std::string movieTitle, movieGenre, movieTrailer;
	int releaseYear, likes;

	parameters = strtok(parameters, ",\n");
	movieTitle = parameters;
	parameters = strtok(NULL, ",\n");
	movieGenre = parameters;
	parameters = strtok(NULL, " ,\n");
	releaseYear = atoi(parameters);
	parameters = strtok(NULL, " ,\n");
	likes = atoi(parameters);
	parameters = strtok(NULL, ",\n");
	movieTrailer = parameters;

	try
	{
		Movie movieToUpdate = Movie(movieTitle, movieGenre, releaseYear, likes, movieTrailer);
		controller.updateMovie(movieToUpdate);
	}

	catch (MovieException& exception)
	{
		exception.getError();
	}
}

void Console::UIDeleteMovie(char * parameters)
{
	std::string movieTitle;

	parameters = strtok(parameters, ",\n");
	movieTitle = parameters;
	try
	{
		controller.deleteMovie(movieTitle);
	}

	catch (MovieException& exception)
	{
		exception.getError();
	}
}

void Console::UIListAll()
{
	std::vector<Movie> movieList = controller.getAllMovies();

	for (auto movie : movieList)
		cout << movie.toStringMovie().c_str() << endl;
}

void Console::UINext()
{
	Movie nextMovie = controller.nextMovie();
	cout << nextMovie.toStringMovie().c_str() << endl;
}

void Console::UIFilter(char * parameters)
{
	std::string filterParameter1, filterParameter2;

	parameters = strtok(parameters, ",\n");
	filterParameter1 = parameters;
	if (checkIfNumber(filterParameter1))
	{
		int likes = atoi(filterParameter1.c_str());

		std::vector<Movie> filteredMovies = controller.filterMovieByLikes(likes);
		for (auto movie : filteredMovies)
			cout << movie.toStringMovie().c_str() << endl;
	}
	else
	{
		parameters = strtok(NULL, "\n");
		filterParameter2 = parameters;
		int likes = atoi(filterParameter2.c_str());

		std::vector<Movie> filteredMovies = controller.filterMoviesByGenreLikes(filterParameter1, likes);
		for (auto movie : filteredMovies)
			cout << movie.toStringMovie().c_str() << endl;
	}


}

void Console::UIAddToWatchlist(char * parameters)
{
	std::string movieTitle;

	parameters = strtok(parameters, ",\n");
	movieTitle = parameters;
	try
	{
		controller.saveMovie(movieTitle);
	}

	catch (MovieException& exception)
	{
		exception.getError();
	}
}

void Console::UISetFilePath(char * parameters)
{
	controller.loadMovieRepo(parameters);
}

void Console::UIWatchlistLocation(char * parameters)
{
	parameters = strtok(parameters, ".");
	std::string filePath = parameters;

	parameters = strtok(NULL, "\n");
	std::string fileExtension = parameters;

	filePath += ".";
	filePath += fileExtension;

	this->controller.setUserListType(filePath, fileExtension);

}

void Console::UIListWatchlist()
{
	std::vector<Movie> movieList = controller.getWatchlist();

	for (auto movie : movieList)
		cout << movie.toStringMovie().c_str() << endl;

	controller.openWatchlist();
}

void Console::run()
{
	char command[256];
	char* token;
	int mode = 0;

	for (int index = 0; index < 2; index++)
	{
		cin.getline(command, 256);
		token = strtok(command, "\n");

		if (strcmp(token, "mode A") == 0)
			mode = 1;
		else if (strcmp(token, "mode B") == 0)
			mode = 2;
		else
		{
			token = strtok(command, " ");
			if (strcmp(token, "fileLocation") == 0)
			{
				token = strtok(NULL, "\n");
				UISetFilePath(token);
			}

			else if (strcmp(token, "mylistLocation") == 0)
			{
				token = strtok(NULL, "\n");
				this->UIWatchlistLocation(token);
			}
			else return;
		}
	}

	while (true)
	{
		cin.getline(command, 256);
		token = strtok(command, " ,");
		if (strcmp(token, "mode") == 0)
		{
			token = strtok(NULL, " ,");
			if (strcmp(token, "A") == 0)
				mode = 1;
			else if (strcmp(token, "B") == 0)
				mode = 2;
			else return;
		}

		else if (mode == 1)
		{
			if (strcmp(token, "add") == 0)
			{
				token = strtok(NULL, "\n");
				UIAddMovie(token);
			}
			else if (strcmp(token, "update") == 0)
			{
				token = strtok(NULL, "\n");
				UIUpdateMovie(token);
			}
			else if (strcmp(token, "delete") == 0)
			{
				token = strtok(NULL, "\n");
				UIDeleteMovie(token);
			}
			else if (strcmp(token, "list") == 0)
				UIListAll();
			else if (strcmp(token, "exit") == 0)
				return;
			else if (strcmp(token, "fileLocation") == 0)
			{
				token = strtok(NULL, "\n");
				UISetFilePath(token);
			}
			else
				cout << "Invalid input\n";
		}

		else
		{
			if (strcmp(token, "next") == 0)
				UINext();
			else if (strcmp(token, "save") == 0)
			{
				token = strtok(NULL, "\n");
				UIAddToWatchlist(token);
			}

			else if (strcmp(token, "list") == 0)
			{
				token = strtok(NULL, "\n");
				UIFilter(token);
			}

			else if (strcmp(token, "mylist") == 0)
			{
				UIListWatchlist();
			}

			else if (strcmp(token, "exit") == 0)
				return;

			else
				cout << "Invalid input!\n";
		}
	}

}
