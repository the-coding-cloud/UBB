#include "Lab12.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Controller controller{};
	Lab12 w{ controller };
	w.show();
	return a.exec();
}
