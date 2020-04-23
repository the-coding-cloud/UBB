/********************************************************************************
** Form generated from reading UI file 'Lab12.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB12_H
#define UI_LAB12_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab12Class
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QTabWidget *mainWidget;
    QWidget *adminTab;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *movieDatabaseWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *adminRightLayout;
    QGridLayout *inputDataLayout;
    QLabel *movieTitleLabel;
    QLineEdit *movieTitleEdit;
    QLabel *movieGenreLabel;
    QLineEdit *movieGenreEdit;
    QLabel *releaseYearLabel;
    QLineEdit *releaseYearEdit;
    QLabel *trailerLabel;
    QLineEdit *trailerEdit;
    QLabel *likesLabel;
    QLineEdit *likesEdit;
    QHBoxLayout *buttonsLayout;
    QPushButton *addButton;
    QPushButton *updateButton;
    QPushButton *removeButton;
    QHBoxLayout *readFileLayout;
    QPushButton *loadFilepathButton;
    QLineEdit *loadFilepathEdit;
    QLabel *faceChestii;
    QHBoxLayout *horizontalLayout;
    QPushButton *undoButton;
    QPushButton *redoButton;
    QWidget *userTab;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *currentMovieLayout;
    QLabel *currentMovieLabel;
    QListWidget *currentMovieData;
    QVBoxLayout *filterReslutLayout;
    QLabel *filterLabel;
    QListWidget *filterResultData;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *userRightLayout;
    QHBoxLayout *saveLayout;
    QLabel *movieIDLabel;
    QLineEdit *movieIDEdit;
    QPushButton *saveIDButton;
    QHBoxLayout *fileLayout;
    QLabel *filePathLabel;
    QLineEdit *filePathEdit;
    QPushButton *saveFilepath;
    QHBoxLayout *userButtonLayout;
    QPushButton *nextButton;
    QPushButton *showWatchlistButton;
    QPushButton *openExternallyButton;
    QVBoxLayout *filterLayout;
    QGridLayout *filterInputDataLayout;
    QLabel *likesFilterLabel;
    QLineEdit *likesFilterEdit;
    QLineEdit *genreFilterEdit;
    QLabel *genreFilterLabel;
    QPushButton *filterByLikesButton;
    QPushButton *filterByLikesGenreButton;

    void setupUi(QMainWindow *Lab12Class)
    {
        if (Lab12Class->objectName().isEmpty())
            Lab12Class->setObjectName(QString::fromUtf8("Lab12Class"));
        Lab12Class->resize(656, 641);
        centralWidget = new QWidget(Lab12Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        mainWidget = new QTabWidget(centralWidget);
        mainWidget->setObjectName(QString::fromUtf8("mainWidget"));
        adminTab = new QWidget();
        adminTab->setObjectName(QString::fromUtf8("adminTab"));
        gridLayout = new QGridLayout(adminTab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        movieDatabaseWidget = new QListWidget(adminTab);
        movieDatabaseWidget->setObjectName(QString::fromUtf8("movieDatabaseWidget"));

        horizontalLayout_2->addWidget(movieDatabaseWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        adminRightLayout = new QVBoxLayout();
        adminRightLayout->setSpacing(6);
        adminRightLayout->setObjectName(QString::fromUtf8("adminRightLayout"));
        inputDataLayout = new QGridLayout();
        inputDataLayout->setSpacing(6);
        inputDataLayout->setObjectName(QString::fromUtf8("inputDataLayout"));
        movieTitleLabel = new QLabel(adminTab);
        movieTitleLabel->setObjectName(QString::fromUtf8("movieTitleLabel"));

        inputDataLayout->addWidget(movieTitleLabel, 0, 0, 1, 1);

        movieTitleEdit = new QLineEdit(adminTab);
        movieTitleEdit->setObjectName(QString::fromUtf8("movieTitleEdit"));

        inputDataLayout->addWidget(movieTitleEdit, 0, 1, 1, 1);

        movieGenreLabel = new QLabel(adminTab);
        movieGenreLabel->setObjectName(QString::fromUtf8("movieGenreLabel"));

        inputDataLayout->addWidget(movieGenreLabel, 1, 0, 1, 1);

        movieGenreEdit = new QLineEdit(adminTab);
        movieGenreEdit->setObjectName(QString::fromUtf8("movieGenreEdit"));

        inputDataLayout->addWidget(movieGenreEdit, 1, 1, 1, 1);

        releaseYearLabel = new QLabel(adminTab);
        releaseYearLabel->setObjectName(QString::fromUtf8("releaseYearLabel"));

        inputDataLayout->addWidget(releaseYearLabel, 2, 0, 1, 1);

        releaseYearEdit = new QLineEdit(adminTab);
        releaseYearEdit->setObjectName(QString::fromUtf8("releaseYearEdit"));

        inputDataLayout->addWidget(releaseYearEdit, 2, 1, 1, 1);

        trailerLabel = new QLabel(adminTab);
        trailerLabel->setObjectName(QString::fromUtf8("trailerLabel"));

        inputDataLayout->addWidget(trailerLabel, 3, 0, 1, 1);

        trailerEdit = new QLineEdit(adminTab);
        trailerEdit->setObjectName(QString::fromUtf8("trailerEdit"));

        inputDataLayout->addWidget(trailerEdit, 3, 1, 1, 1);

        likesLabel = new QLabel(adminTab);
        likesLabel->setObjectName(QString::fromUtf8("likesLabel"));

        inputDataLayout->addWidget(likesLabel, 4, 0, 1, 1);

        likesEdit = new QLineEdit(adminTab);
        likesEdit->setObjectName(QString::fromUtf8("likesEdit"));

        inputDataLayout->addWidget(likesEdit, 4, 1, 1, 1);


        adminRightLayout->addLayout(inputDataLayout);

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setSpacing(6);
        buttonsLayout->setObjectName(QString::fromUtf8("buttonsLayout"));
        addButton = new QPushButton(adminTab);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        buttonsLayout->addWidget(addButton);

        updateButton = new QPushButton(adminTab);
        updateButton->setObjectName(QString::fromUtf8("updateButton"));

        buttonsLayout->addWidget(updateButton);

        removeButton = new QPushButton(adminTab);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        buttonsLayout->addWidget(removeButton);


        adminRightLayout->addLayout(buttonsLayout);


        verticalLayout->addLayout(adminRightLayout);

        readFileLayout = new QHBoxLayout();
        readFileLayout->setSpacing(6);
        readFileLayout->setObjectName(QString::fromUtf8("readFileLayout"));
        loadFilepathButton = new QPushButton(adminTab);
        loadFilepathButton->setObjectName(QString::fromUtf8("loadFilepathButton"));

        readFileLayout->addWidget(loadFilepathButton);

        loadFilepathEdit = new QLineEdit(adminTab);
        loadFilepathEdit->setObjectName(QString::fromUtf8("loadFilepathEdit"));

        readFileLayout->addWidget(loadFilepathEdit);


        verticalLayout->addLayout(readFileLayout);

        faceChestii = new QLabel(adminTab);
        faceChestii->setObjectName(QString::fromUtf8("faceChestii"));
        faceChestii->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(faceChestii);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        undoButton = new QPushButton(adminTab);
        undoButton->setObjectName(QString::fromUtf8("undoButton"));

        horizontalLayout->addWidget(undoButton);

        redoButton = new QPushButton(adminTab);
        redoButton->setObjectName(QString::fromUtf8("redoButton"));

        horizontalLayout->addWidget(redoButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        mainWidget->addTab(adminTab, QString());
        userTab = new QWidget();
        userTab->setObjectName(QString::fromUtf8("userTab"));
        gridLayout_2 = new QGridLayout(userTab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        currentMovieLayout = new QVBoxLayout();
        currentMovieLayout->setSpacing(6);
        currentMovieLayout->setObjectName(QString::fromUtf8("currentMovieLayout"));
        currentMovieLabel = new QLabel(userTab);
        currentMovieLabel->setObjectName(QString::fromUtf8("currentMovieLabel"));
        currentMovieLabel->setAlignment(Qt::AlignCenter);

        currentMovieLayout->addWidget(currentMovieLabel);

        currentMovieData = new QListWidget(userTab);
        currentMovieData->setObjectName(QString::fromUtf8("currentMovieData"));

        currentMovieLayout->addWidget(currentMovieData);


        verticalLayout_3->addLayout(currentMovieLayout);

        filterReslutLayout = new QVBoxLayout();
        filterReslutLayout->setSpacing(6);
        filterReslutLayout->setObjectName(QString::fromUtf8("filterReslutLayout"));
        filterLabel = new QLabel(userTab);
        filterLabel->setObjectName(QString::fromUtf8("filterLabel"));
        filterLabel->setAlignment(Qt::AlignCenter);

        filterReslutLayout->addWidget(filterLabel);

        filterResultData = new QListWidget(userTab);
        filterResultData->setObjectName(QString::fromUtf8("filterResultData"));

        filterReslutLayout->addWidget(filterResultData);


        verticalLayout_3->addLayout(filterReslutLayout);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        userRightLayout = new QVBoxLayout();
        userRightLayout->setSpacing(6);
        userRightLayout->setObjectName(QString::fromUtf8("userRightLayout"));
        saveLayout = new QHBoxLayout();
        saveLayout->setSpacing(6);
        saveLayout->setObjectName(QString::fromUtf8("saveLayout"));
        movieIDLabel = new QLabel(userTab);
        movieIDLabel->setObjectName(QString::fromUtf8("movieIDLabel"));

        saveLayout->addWidget(movieIDLabel);

        movieIDEdit = new QLineEdit(userTab);
        movieIDEdit->setObjectName(QString::fromUtf8("movieIDEdit"));

        saveLayout->addWidget(movieIDEdit);

        saveIDButton = new QPushButton(userTab);
        saveIDButton->setObjectName(QString::fromUtf8("saveIDButton"));

        saveLayout->addWidget(saveIDButton);


        userRightLayout->addLayout(saveLayout);

        fileLayout = new QHBoxLayout();
        fileLayout->setSpacing(6);
        fileLayout->setObjectName(QString::fromUtf8("fileLayout"));
        filePathLabel = new QLabel(userTab);
        filePathLabel->setObjectName(QString::fromUtf8("filePathLabel"));

        fileLayout->addWidget(filePathLabel);

        filePathEdit = new QLineEdit(userTab);
        filePathEdit->setObjectName(QString::fromUtf8("filePathEdit"));

        fileLayout->addWidget(filePathEdit);

        saveFilepath = new QPushButton(userTab);
        saveFilepath->setObjectName(QString::fromUtf8("saveFilepath"));

        fileLayout->addWidget(saveFilepath);


        userRightLayout->addLayout(fileLayout);

        userButtonLayout = new QHBoxLayout();
        userButtonLayout->setSpacing(6);
        userButtonLayout->setObjectName(QString::fromUtf8("userButtonLayout"));
        nextButton = new QPushButton(userTab);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));

        userButtonLayout->addWidget(nextButton);

        showWatchlistButton = new QPushButton(userTab);
        showWatchlistButton->setObjectName(QString::fromUtf8("showWatchlistButton"));

        userButtonLayout->addWidget(showWatchlistButton);

        openExternallyButton = new QPushButton(userTab);
        openExternallyButton->setObjectName(QString::fromUtf8("openExternallyButton"));

        userButtonLayout->addWidget(openExternallyButton);


        userRightLayout->addLayout(userButtonLayout);


        verticalLayout_2->addLayout(userRightLayout);

        filterLayout = new QVBoxLayout();
        filterLayout->setSpacing(6);
        filterLayout->setObjectName(QString::fromUtf8("filterLayout"));
        filterInputDataLayout = new QGridLayout();
        filterInputDataLayout->setSpacing(6);
        filterInputDataLayout->setObjectName(QString::fromUtf8("filterInputDataLayout"));
        likesFilterLabel = new QLabel(userTab);
        likesFilterLabel->setObjectName(QString::fromUtf8("likesFilterLabel"));

        filterInputDataLayout->addWidget(likesFilterLabel, 1, 0, 1, 1);

        likesFilterEdit = new QLineEdit(userTab);
        likesFilterEdit->setObjectName(QString::fromUtf8("likesFilterEdit"));

        filterInputDataLayout->addWidget(likesFilterEdit, 1, 1, 1, 1);

        genreFilterEdit = new QLineEdit(userTab);
        genreFilterEdit->setObjectName(QString::fromUtf8("genreFilterEdit"));

        filterInputDataLayout->addWidget(genreFilterEdit, 0, 1, 1, 1);

        genreFilterLabel = new QLabel(userTab);
        genreFilterLabel->setObjectName(QString::fromUtf8("genreFilterLabel"));

        filterInputDataLayout->addWidget(genreFilterLabel, 0, 0, 1, 1);


        filterLayout->addLayout(filterInputDataLayout);

        filterByLikesButton = new QPushButton(userTab);
        filterByLikesButton->setObjectName(QString::fromUtf8("filterByLikesButton"));

        filterLayout->addWidget(filterByLikesButton);

        filterByLikesGenreButton = new QPushButton(userTab);
        filterByLikesGenreButton->setObjectName(QString::fromUtf8("filterByLikesGenreButton"));

        filterLayout->addWidget(filterByLikesGenreButton);


        verticalLayout_2->addLayout(filterLayout);


        horizontalLayout_3->addLayout(verticalLayout_2);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        mainWidget->addTab(userTab, QString());

        gridLayout_3->addWidget(mainWidget, 0, 0, 1, 1);

        Lab12Class->setCentralWidget(centralWidget);

        retranslateUi(Lab12Class);

        mainWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Lab12Class);
    } // setupUi

    void retranslateUi(QMainWindow *Lab12Class)
    {
        Lab12Class->setWindowTitle(QApplication::translate("Lab12Class", "Lab12", nullptr));
        movieTitleLabel->setText(QApplication::translate("Lab12Class", "Movie Title", nullptr));
        movieGenreLabel->setText(QApplication::translate("Lab12Class", "Movie Genre", nullptr));
        releaseYearLabel->setText(QApplication::translate("Lab12Class", "Release Year", nullptr));
        trailerLabel->setText(QApplication::translate("Lab12Class", "Trailer", nullptr));
        likesLabel->setText(QApplication::translate("Lab12Class", "Likes", nullptr));
        addButton->setText(QApplication::translate("Lab12Class", "Add", nullptr));
        updateButton->setText(QApplication::translate("Lab12Class", "Update", nullptr));
        removeButton->setText(QApplication::translate("Lab12Class", "Remove", nullptr));
        loadFilepathButton->setText(QApplication::translate("Lab12Class", "Read File", nullptr));
        faceChestii->setText(QApplication::translate("Lab12Class", "-", nullptr));
        undoButton->setText(QApplication::translate("Lab12Class", "Undo", nullptr));
        redoButton->setText(QApplication::translate("Lab12Class", "Redo", nullptr));
        mainWidget->setTabText(mainWidget->indexOf(adminTab), QApplication::translate("Lab12Class", "Admin Mode", nullptr));
        currentMovieLabel->setText(QApplication::translate("Lab12Class", "Movie", nullptr));
        filterLabel->setText(QApplication::translate("Lab12Class", "Filter", nullptr));
        movieIDLabel->setText(QApplication::translate("Lab12Class", "Movie Title", nullptr));
        saveIDButton->setText(QApplication::translate("Lab12Class", "Save", nullptr));
        filePathLabel->setText(QApplication::translate("Lab12Class", "Watchlist File Path", nullptr));
        saveFilepath->setText(QApplication::translate("Lab12Class", "Save Path", nullptr));
        nextButton->setText(QApplication::translate("Lab12Class", "Next", nullptr));
        showWatchlistButton->setText(QApplication::translate("Lab12Class", "Show Watchlist", nullptr));
        openExternallyButton->setText(QApplication::translate("Lab12Class", "Open Externally", nullptr));
        likesFilterLabel->setText(QApplication::translate("Lab12Class", "Likes", nullptr));
        genreFilterLabel->setText(QApplication::translate("Lab12Class", "Genre", nullptr));
        filterByLikesButton->setText(QApplication::translate("Lab12Class", "Filter By Likes", nullptr));
        filterByLikesGenreButton->setText(QApplication::translate("Lab12Class", "Filter By Likes And Genre", nullptr));
        mainWidget->setTabText(mainWidget->indexOf(userTab), QApplication::translate("Lab12Class", "User Mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab12Class: public Ui_Lab12Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB12_H
