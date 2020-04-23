#include "MovieGUI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>


MovieGUI::MovieGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void basicGUI::makeLayout()
{
	QHBoxLayout *mainLayout = new QHBoxLayout{ this };

	QVBoxLayout *layoutAdmin = new QVBoxLayout{};
	QVBoxLayout *layoutMiddle = new QVBoxLayout{};
	QVBoxLayout *layoutUser = new QVBoxLayout{};

	QLabel *adminLabel = new QLabel();
	adminLabel->setText("Movie Database");
	QFont adminFont("Helvetica", 12);
	adminLabel->setFont(adminFont);
	layoutAdmin->addWidget(adminLabel);

	QLabel *userLabel = new QLabel();
	userLabel->setText("Watchlist");
	QFont userFont("Helvetica", 12);
	userLabel->setFont(userFont);
	layoutUser->addWidget(userLabel);

	this->movieData = new QListWidget{};
	this->userData = new QListWidget{};

	layoutAdmin->addWidget(this->movieData);
	layoutUser->addWidget(this->userData);

	QVBoxLayout *leftSide = new QVBoxLayout{};
	QVBoxLayout *rightSide = new QVBoxLayout{};

	layoutAdmin->addLayout(leftSide);
	layoutUser->addLayout(rightSide);

	QHBoxLayout *AdminButtonsLayout = new QHBoxLayout{};
	QHBoxLayout *userButtonsLayout = new QHBoxLayout{};

	AdminButtonsLayout->addWidget(new QPushButton{ "Add" });
	AdminButtonsLayout->addWidget(new QPushButton{ "Remove" });
	AdminButtonsLayout->addWidget(new QPushButton{ "Update" });
	userButtonsLayout->addWidget(new QPushButton{ "Next" });
	layoutMiddle->addWidget(new QPushButton{ "Add to Watchlist" });

	QFormLayout *movieData = new QFormLayout{};
	QFormLayout *userData = new QFormLayout{};

	this->movieTitle = new QLineEdit{};
	movieData->addRow("Movie Title", this->movieTitle);
	this->movieGenre = new QLineEdit{};
	movieData->addRow("Movie Genre", this->movieGenre);
	this->releaseYear = new QLineEdit{};
	movieData->addRow("Release Year", this->releaseYear);
	this->likes = new QLineEdit{};
	movieData->addRow("Likes", this->likes);
	this->trailer = new QLineEdit{};
	movieData->addRow("Trailer", this->trailer);

	leftSide->addLayout(movieData);
	leftSide->addLayout(AdminButtonsLayout);
	rightSide->addLayout(userButtonsLayout);

	mainLayout->addLayout(layoutAdmin);
	mainLayout->addLayout(layoutMiddle);
	mainLayout->addLayout(layoutUser);
}

void basicGUI::retrieveAdminData()
{

	this->movieController.loadMovieRepo("testInput.txt");
	for (Movie &movie : this->movieController.getAllMovies())
	{
		this->movieData->addItem(QString::fromStdString(movie.toStringMovie()));

	}
}

basicGUI::basicGUI(Controller & controller) : movieController(controller)
{
	this->makeLayout();
	this->retrieveAdminData();
}

basicGUI::~basicGUI()
{
}
