#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHeaderView>
#include <documentparser.h>
#include <networkmanager.h>
#include <imagenetworkmanager.h>
#include <QThread>

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

private:
    Ui::MainWindow *ui;
    DocumentParser parser;
    NetworkManager networkkManager;
    ImageNetworkManager imageNetworkManager;
};

#endif // MAINWINDOW_H


















