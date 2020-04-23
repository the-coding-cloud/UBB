#include "Tests.h"

using namespace std;

void testDomain()
{
	std::string title = "Equilibrium";
	std::string genre = "Sci Fi";
	std::string trailer = "trailer";
	Movie movie = Movie(title, genre, 2000, 3000, trailer);

	assert(movie.getLikes() == 3000);
	assert(movie.getReleaseYear() == 2000);

	movie.setLikes(4000);
	assert(movie.getLikes() == 4000);

	Movie movieCopy = Movie(movie);
	assert(movie.getTitle() == title);
	assert(movie.getGenre() == genre);
	assert(movie.getLikes() == 4000);

	assert(movie == movieCopy);

}

void testRepository()
{
	std::string title = "Equilibrium";
	std::string genre = "Sci Fi";
	std::string trailer = "trailer";
	Movie movie = Movie(title, genre, 2000, 3000, trailer);

	MovieRepository movieRepo = MovieRepository();

	movieRepo.addMovieAsAdmin(movie);
	assert(movieRepo.getMovieByTitle(title) == movie);
	assert(movieRepo.getCurrentMovie() == movie);

	movieRepo.nextMovie();
	assert(movieRepo.getCurrentMovie() == movie);

	movieRepo.addMovieToWatchList(title);

}

void runTests()
{
	testDomain();
	testRepository();
}