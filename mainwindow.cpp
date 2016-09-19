#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    parser.readFile("/home/asus/Pulpit/file.xml");

    /* Configure Table */
    configureTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureTable()
{
    QStringList headerList;
    headerList << "A" << "B" << "C";
    ui->table->setColumnCount(3);
    ui->table->setHorizontalHeaderLabels(headerList);

    /* Stretch */
    for (int nr = 0; nr < ui->table->horizontalHeader()->count(); ++nr) {
         ui->table->horizontalHeader()->setSectionResizeMode(nr, QHeaderView::Stretch);
    }
}


















