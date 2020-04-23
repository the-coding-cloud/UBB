#include "UserView.h"
#include "Domain.h"
#include "UserModel.h"



UserView::UserView(QAbstractItemModel* model, QWidget *parent)
	: QWidget(parent), model{ model }
{
	ui.setupUi(this);
	this->ui.watchlistData->setModel(this->model);
}

UserView::~UserView()
{
}
