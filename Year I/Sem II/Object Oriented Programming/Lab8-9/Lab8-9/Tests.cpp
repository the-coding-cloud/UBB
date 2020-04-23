#include "Tests.h"
#include <assert.h>
#include <iostream>

using namespace std;

void Tests::testDomain()
{
	std::string movieTitle, movieGenre, trailer;
	int releaseYear, likes;

	movieTitle = "The Breakfast Club";
	movieGenre = "Comedy-Drama";
	trailer = "https://youtu.be/BSXBvor47Zs";
	releaseYear = 1985;
	likes = 3200;

	Movie movie_TestFirstConstructor = Movie(movieTitle, movieGenre, releaseYear, likes, trailer);
	
	// Test getters
	assert(movie_TestFirstConstructor.getTitle() == "The Breakfast Club");
	assert(movie_TestFirstConstructor.getGenre() == "Comedy-Drama");
	assert(movie_TestFirstConstructor.getReleaseYear() == 1985);
	assert(movie_TestFirstConstructor.getLikes() == 3200);
	assert(movie_TestFirstConstructor.getTrailer() == "https://youtu.be/BSXBvor47Zs");

	// Test setters
	movieGenre = "Comedy";
	trailer = "link";
	releaseYear = 1990;
	likes = 3300;

	movie_TestFirstConstructor.setGenre(movieGenre);
	movie_TestFirstConstructor.setReleaseYear(releaseYear);
	movie_TestFirstConstructor.setLikes(likes);
	movie_TestFirstConstructor.setTrailer(trailer);

	assert(movie_TestFirstConstructor.getGenre() == "Comedy");
	assert(movie_TestFirstConstructor.getReleaseYear() == 1990);
	assert(movie_TestFirstConstructor.getLikes() == 3300);
	assert(movie_TestFirstConstructor.getTrailer() == "link");

	// Test operators
	Movie movie_TestOperators = movie_TestFirstConstructor;
	assert(movie_TestOperators == movie_TestFirstConstructor);

	// Test toStringMovie()
	assert(movie_TestFirstConstructor.toStringMovie() == "The Breakfast Club; Comedy; 1990; 3300; link");

	cout << "Domain tested successfully" << endl;
}

void Tests::testRepo()
{
	MovieRepository baseRepository = MovieRepository();

	std::string movieTitle, movieGenre, trailer;
	int releaseYear, likes;

	movieTitle = "The Breakfast Club";
	movieGenre = "Comedy-Drama";
	trailer = "https://youtu.be/BSXBvor47Zs";
	releaseYear = 1985;
	likes = 3200;
	Movie movie_TestAdd = Movie(movieTitle, movieGenre, releaseYear, likes, trailer);

	movieTitle = "Movie1";
	movieGenre = "Genre1";
	trailer = "Link1";
	releaseYear = 1;
	likes = 1;
	Movie movie1 = Movie(movieTitle, movieGenre, releaseYear, likes, trailer);

	movieTitle = "Movie2";
	movieGenre = "Genre2";
	trailer = "Link2";
	releaseYear = 2;
	likes = 2;
	Movie movie2 = Movie(movieTitle, movieGenre, releaseYear, likes, trailer);

	movieTitle = "Movie3";
	movieGenre = "Genre3";
	trailer = "Link3";
	releaseYear = 3;
	likes = 3;
	Movie movie3 = Movie(movieTitle, movieGenre, releaseYear, likes, trailer);

	movieTitle = "Movie4";
	movieGenre = "Genre1";
	trailer = "Link4";
	releaseYear = 4;
	likes = 4;
	Movie movie4 = Movie(movieTitle, movieGenre, releaseYear, likes, trailer);

	// Test addMovie(), getNumberOfMovies(), getMovieByPosition()
	baseRepository.addMovie(movie_TestAdd);
	assert(baseRepository.getNumberOfMovies() == 1);
	assert(baseRepository.getMovieByPosition(0).getTitle() == "The Breakfast Club");

	// Test updateMovie()
	Movie movie_TestUpdate = Movie(movie_TestAdd);
	trailer = "link";
	movie_TestUpdate.setTrailer(trailer);
	baseRepository.updateMovie(movie_TestUpdate);
	assert(baseRepository.getMovieByPosition(0).getTrailer() == "link");

	// Test deleteMovie()
	baseRepository.deleteMovie(movie_TestAdd);
	assert(baseRepository.getNumberOfMovies() == 0);

	// Test filterMovies()
	baseRepository.addMovie(movie1);
	baseRepository.addMovie(movie2);
	baseRepository.addMovie(movie3);
	baseRepository.addMovie(movie4);

	std::string genreForFilter = "Genre1";
	std::vector<Movie> filteredMovies = baseRepository.filterMoviesByGenreLikes(genreForFilter, 1);
	assert(filteredMovies.size() == 2);
	for (auto element : filteredMovies)
	{
		assert(element.getLikes() >= 1);
	}

	cout << "Base repo tested successfully" << endl;

	FileRepository* textRepository = new TXTRepository();
	
	// Test readFromFile()
	textRepository->readFromFile("testInput.txt");
	assert(textRepository->getNumberOfMovies() == 3);
	
	// Test writeToFile()
	//textRepository->addMovie(movie1);
	textRepository->addMovie(movie1);
	textRepository->addMovie(movie2);
	textRepository->addMovie(movie3);
	textRepository->writeToFile();

	textRepository->deleteMovie(movie1);
	textRepository->deleteMovie(movie2);
	textRepository->deleteMovie(movie3);
	textRepository->writeToFile();

	cout << "File repo tested successfully" << endl;

	// Test writeToFile() for HTML
	FileRepository* HTMLRepo = new HTMLRepository();
	HTMLRepo->addMovie(movie1);
	HTMLRepo->addMovie(movie2);
	HTMLRepo->addMovie(movie3);
	HTMLRepo->addMovie(movie4);
	HTMLRepo->setPath("testInput.html");
	HTMLRepo->writeToFile();
	HTMLRepo->openFile();

	cout << "HTML repo tested successfully" << endl;
}

void Tests::testController()
{
	Controller controller = Controller();

	// Test loadMovieRepo()
	controller.loadMovieRepo("testInput.txt");
	assert(controller.getAllMovies().size() >= 3);

	// Test addMovie()
	std::string movieTitle, movieGenre, trailer;
	int releaseYear, likes;

	movieTitle = "Madagascar";
	movieGenre = "Animated comedy";
	trailer = "https://youtu.be/fq5zU9T_Hl4";
	releaseYear = 2005;
	likes = 3600;
	Movie movie_TestAdd = Movie(movieTitle, movieGenre, releaseYear, likes, trailer);

	try 
	{
		controller.addMovie(movie_TestAdd);
		assert(true);
	}
	catch (MovieException& exception) 
	{
		assert(false);
	}

	try
	{
		controller.addMovie(movie_TestAdd);
		assert(false);
	}
	catch (MovieException& exception)
	{
		assert(true);
	}

	assert(controller.getAllMovies().size() == 4);

	// Test updateMovie()
	Movie movie_TestUpdate = Movie(movie_TestAdd);
	movie_TestUpdate.setLikes(3700);
	try
	{
		controller.updateMovie(movie_TestUpdate);
		assert(true);
	}
	catch (MovieException& exception)
	{
		assert(false);
	}

	assert(controller.getAllMovies()[3].getLikes() == 3700);

	// Test deleteMovie()
	try
	{
		controller.deleteMovie("Madagascar");
		assert(true);
	}
	catch (MovieException& exception)
	{
		assert(false);
	}

	// Test saveMovie()
	controller.saveMovie("The Breakfast Club");
	assert(controller.getWatchlist().size() == 1);
	assert(controller.getWatchlist()[0].getTitle() == "The Breakfast Club");

	// Test nextMovie()
	controller.saveMovie("Avengers: Endgame");
	assert(controller.nextMovie().getTitle() == "Avengers: Endgame");

	cout << "Controller tested successfully" << endl;
}

void Tests::testValidator()
{
}

void Tests::testIsolated()
{
}
