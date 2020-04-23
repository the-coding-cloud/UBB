#include "UserModel.h"
#include <qcolor.h>
#include <string>

UserModel::UserModel(Controller& controller) : movieController(controller)
{

}

UserModel::~UserModel()
{
}

int UserModel::rowCount(const QModelIndex &parent) const
{
	return this->movieController.getWatchlist().size();
}

int UserModel::columnCount(const QModelIndex &parent) const
{
	return 5;
}

QVariant UserModel::data(const QModelIndex &index, int role) const
{
	int row = index.row();
	int col = index.column();

	Movie currentMovie = this->movieController.getWatchlist()[row];

	if (role == Qt::DisplayRole)
	{
		switch (col)
		{
		case 0:
			return QString::fromStdString(currentMovie.getTitle());
		case 1:
			return QString::fromStdString(currentMovie.getGenre());
		case 2:
			return QString::fromStdString(std::to_string(currentMovie.getReleaseYear()));
		case 3:
			return QString::fromStdString(std::to_string(currentMovie.getLikes()));
		case 4:
			return QString::fromStdString(currentMovie.getTrailer());
		default:
			break;
		}
	}

	return QVariant();
}

QVariant UserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch (section)
		{
		case 0:
			return "Title";
		case 1:
			return "Genre";
		case 2:
			return "Release Year";
		case 3:
			return "Likes";
		case 4:
			return "Trailer";
		}
	}
	return QVariant();
}

bool UserModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role == Qt::EditRole || role == Qt::DisplayRole)
	{
		Movie& currentMovie = this->movieController.getWatchlist()[index.row()];
		int column = index.column();
		switch (column)
		{
		case 0:
		{
			currentMovie.setTitle(value.toString().toStdString());
			break;
		}
		case 1:
		{
			currentMovie.setGenre(value.toString().toStdString());
			break;
		}
		case 2:
		{
			currentMovie.setReleaseYear(atoi(value.toString().toStdString().c_str()));
			break;
		}
		case 3:
		{
			currentMovie.setLikes(atoi(value.toString().toStdString().c_str()));
			break;
		}
		case 4:
		{
			currentMovie.setTrailer(value.toString().toStdString());
			break;
		}
		}
	}

	emit dataChanged(index, index);
	return true;
}

Qt::ItemFlags UserModel::flags(const QModelIndex &index) const
{
	return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}