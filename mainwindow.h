#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHeaderView>
#include <QMovie>
#include <QTimer>
#include <documentparser.h>
#include <networkmanager.h>
#include <imagenetworkmanager.h>

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

private slots:
    void on_lineName_textChanged(const QString &arg1);
    void on_btnFavourite_clicked(bool checked);
    void setButtonIcon(int frame);
    void refresh();

private:
    Ui::MainWindow *ui;
    DocumentParser parser;
    NetworkManager networkkManager;
    ImageNetworkManager imageNetworkManager;
    QMovie *movieBtnFavourite;
    QTimer timer;
    int globalFrame;
    bool isBtnFavouritePresssed;
};

#endif // MAINWINDOW_H


















