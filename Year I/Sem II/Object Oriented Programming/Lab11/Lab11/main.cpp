#include "MovieGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Controller controller{};
	basicGUI widget{ controller };
	widget.show();

	return a.exec();
}
