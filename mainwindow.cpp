#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    /* Clear Table Before */
    ui->table->setRowCount(0);

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

void MainWindow::on_lineName_textChanged(const QString &arg1)
{
    qDebug() << parser.getXmlData().size();
    /* Find User Name */
    if(networkkManager.setURLName(arg1) > 5000) {
        qDebug() << "User was found";

        /* Save To File */
        QFile file(QDir::currentPath() + "/file.xml");

        if(file.open(QIODevice::ReadWrite | QIODevice::Text)){
            QTextStream stream(&file);
            stream << networkkManager.getURLContent();
        } else {
            qDebug() << "File Open Error";
        }

        /* Load Data To Table */
        parser.readFile(QDir::currentPath() + "/file.xml");
        setTableData();
    }
}



















