#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    parser.readFile("/home/asus/Pulpit/file.xml");

    /* Configure Table */
    configureTable();
    setTableData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureTable()
{
    QStringList headerList;
    headerList << "Title" << "Video ID" << "Video Link";
    ui->table->setColumnCount(3);
    ui->table->setHorizontalHeaderLabels(headerList);

    /* Stretch */
    for (int nr = 0; nr < ui->table->horizontalHeader()->count(); ++nr) {
        ui->table->horizontalHeader()->setSectionResizeMode(nr, QHeaderView::Stretch);
    }
}

void MainWindow::setTableData()
{
    /* Get Loaded Data */
    QVector<XMLData> xmlData = parser.getXmlData();

    /* Convert To Table Widget Item */
    QTableWidgetItem *title;
    QTableWidgetItem *videoID;
    QTableWidgetItem *link;

    /* Add Items To Table */
    for(int i = 0; i < xmlData.size(); i++) {
        title = new QTableWidgetItem(xmlData[i].title);
        videoID = new QTableWidgetItem(xmlData[i].videoID);
        link = new QTableWidgetItem(xmlData[i].link);

        ui->table->insertRow(i);
        ui->table->setItem(i, 0, title);
        ui->table->setItem(i, 1, videoID);
        ui->table->setItem(i, 2, link);
    }
}


















