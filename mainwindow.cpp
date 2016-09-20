#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Configure Table */
    configureTable();
    setWindowTitle("YT Preview");

    /* Animation */
    movieBtnFavourite = new QMovie(":/icon/animation.gif");
    connect(movieBtnFavourite, SIGNAL(frameChanged(int)), this, SLOT(setButtonIcon(int)));

    /* Initial State */
    ui->listWidget->hide();
    ui->label_2->hide();
    globalFrame = 0;
    isBtnFavouritePresssed = false;

    /* Timer */
    connect(&timer, SIGNAL(timeout()), this, SLOT(refresh()));
    timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureTable()
{
    QStringList headerList;
    headerList << "Preview" << "Title" << "Video ID" << "Video Link";
    ui->table->setColumnCount(4);
    ui->table->setHorizontalHeaderLabels(headerList);
    ui->table->setColumnWidth(0, 240);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setSelectionMode(QTableWidget::NoSelection);

    /* Stretch */
    for (int nr = 1; nr < ui->table->horizontalHeader()->count(); ++nr) {
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
    QTableWidgetItem *image;

    /* Add Items To Table */
    for(int i = 0; i < xmlData.size(); i++) {
        title = new QTableWidgetItem(xmlData[i].title);
        videoID = new QTableWidgetItem(xmlData[i].videoID);
        link = new QTableWidgetItem(xmlData[i].link);

        ui->table->insertRow(i);
        ui->table->setItem(i, 1, title);
        ui->table->setItem(i, 2, videoID);
        ui->table->setItem(i, 3, link);
    }

    /* Convert URL To Pixmap */
    qDebug() << "Before:" << xmlData[0].image.size();
    imageNetworkManager.setContainer(xmlData);
    qDebug() << "After" << xmlData[0].image.size();

    /* Set Image */
    qDebug() << "Size:" << xmlData.size();
    for(int i = 0; i < xmlData.size(); i++) {
        ui->table->setRowHeight(i, 160);
        image = new QTableWidgetItem;
        image->setData(Qt::DecorationRole, xmlData[i].image.scaled(240, 160));
        ui->table->setItem(i, 0, image);
    }
}

void MainWindow::on_lineName_textChanged(const QString &arg1)
{
    ui->lineName->setStyleSheet("color: red");

    qDebug() << parser.getXmlData().size();
    /* Find User Name */
    if(networkkManager.setURLName(arg1) > 5000) {
        qDebug() << "User was found";
        ui->lineName->setStyleSheet("color: green; font: bold");

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

void MainWindow::on_btnFavourite_clicked(bool checked)
{
    /* Hide Favourite Menu */
    if(checked) {
        ui->listWidget->hide();
        ui->label_2->hide();
        movieBtnFavourite->start();
        isBtnFavouritePresssed = false;
    } else {
        ui->listWidget->show();
        ui->label_2->show();
        movieBtnFavourite->start();
        isBtnFavouritePresssed = true;
    }
}

void MainWindow::setButtonIcon(int frame)
{
    globalFrame = frame;
    ui->btnFavourite->setIcon(QIcon(movieBtnFavourite->currentPixmap()));
    ui->btnFavourite->setIconSize(QSize(32,32));
}

void MainWindow::refresh()
{
    if(globalFrame == 30 && isBtnFavouritePresssed)  movieBtnFavourite->setPaused(true);
    else if(globalFrame == 0 && !isBtnFavouritePresssed) movieBtnFavourite->setPaused(true);
}


















