#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHeaderView>
#include <QMovie>
#include <QTimer>
#include <documentparser.h>
#include <networkmanager.h>
#include <imagenetworkmanager.h>
#include <storage.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void configureTable();
    void setTableData();
    void checkRepeat(const QString &channel);
    void saveDataFromTable();
    void loadDataToTable();

private slots:
    void on_lineName_textChanged(const QString &arg1);
    void on_btnFavourite_clicked(bool checked);
    void setButtonIcon(int frame);
    void setButton2Icon(int frame);
    void refresh();
    void on_btnAdd_clicked();
    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    DocumentParser parser;
    NetworkManager networkkManager;
    ImageNetworkManager imageNetworkManager;
    QMovie *movieBtnFavourite;
    QMovie *movieLabelLoad;
    QMovie *movieBtnAdd;
    QTimer timer;
    Storage storage;
    int globalFrame;
    bool isBtnFavouritePresssed;
};

#endif // MAINWINDOW_H


















