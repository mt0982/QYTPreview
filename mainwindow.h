#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHeaderView>
#include <documentparser.h>

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

private:
    Ui::MainWindow *ui;
    DocumentParser parser;
};

#endif // MAINWINDOW_H
