#include "QtGUI.h"

QtGUI::QtGUI(Controller &controller, QWidget *parent)
	: QMainWindow(parent), controller(controller)
{
	ui.setupUi(this);
	populateList();

	connect(ui.precipitationButton, SIGNAL(released()), this, SLOT(handleFilter()));
	connect(ui.descriptionButton, SIGNAL(released()), this, SLOT(handleTime()));
	connect(ui.showAllButton, SIGNAL(released()), this, SLOT(handleShowAll()));
}

void QtGUI::populateList()
{
	for (auto weather : this->controller.getAllWeather())
		ui.weatherData->addItem(QString::fromStdString(weather.toString()));
}

void QtGUI::handleFilter()
{
	int precipitation = ui.precipitationEdit->text().toInt();
	std::vector<Weather> weatherList = controller.getFilteredWeather(precipitation);
	ui.weatherData->clear();

	for (auto weather : weatherList)
		ui.weatherData->addItem(QString::fromStdString(weather.toString()));
}

void QtGUI::handleTime()
{
	std::string description = ui.descriptionEdit->text().toStdString();
	int time = controller.getTotalTimeForType(description);

	ui.timeData->setNum(time);
}

void QtGUI::handleShowAll()
{
	ui.weatherData->clear();
	for (auto weather : this->controller.getAllWeather())
		ui.weatherData->addItem(QString::fromStdString(weather.toString()));
}


