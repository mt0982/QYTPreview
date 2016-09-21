#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Configure Table */
    configureTable();
    setWindowTitle("YT Preview");

    /* Animation */
    movieBtnFavourite = new QMovie(":/icon/rounded.gif");
    movieLabelLoad = new QMovie(":/icon/wait24x24.gif");
    movieBtnAdd = new QMovie(":/icon/save.gif");
    connect(movieBtnFavourite, SIGNAL(frameChanged(int)), this, SLOT(setButtonIcon(int)));
    connect(movieBtnAdd, SIGNAL(frameChanged(int)), this, SLOT(setButton2Icon(int)));
    movieLabelLoad->start();
    movieBtnAdd->start();

    /* Initial State */
    ui->listWidget->hide();
    ui->label_2->hide();
    globalFrame = 0;
    isBtnFavouritePresssed = false;
    ui->btnAdd->setDisabled(true);
    ui->labelWait->setMovie(movieLabelLoad);
    ui->btnAdd->hide();
    ui->labelSearch->hide();
    ui->btnRemove->hide();
    ui->btnRemove->setIcon(QIcon(":/icon/remove.png"));
    ui->btnRemove->setIconSize(QSize(24,24));
    ui->btnRemove->setDisabled(true);

    /* Timer */
    connect(&timer, SIGNAL(timeout()), this, SLOT(refresh()));
    timer.start();

    /* Initialize Table Data */
    loadDataToTable();
}

MainWindow::~MainWindow()
{
    saveDataFromTable();
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

void MainWindow::checkRepeat(const QString &channel)
{
    /* Check Repeat */
    int itemCount = ui->listWidget->count();

    for(int i = 0; i < itemCount; i++) {
        if(ui->listWidget->item(i)->text() == channel) {
            ui->btnAdd->setDisabled(true);
            break;
        }
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

        /* Enable Add Button */
        ui->btnAdd->setDisabled(false);
        ui->btnAdd->show();
        ui->labelWait->hide();
    } else {

        /* Disable Add Button */
        ui->btnAdd->hide();
        ui->labelWait->show();
        ui->btnAdd->setDisabled(true);
    }

    checkRepeat(arg1);
}

void MainWindow::on_btnFavourite_clicked(bool checked)
{
    /* Hide Favourite Menu */
    if(checked) {
        ui->listWidget->hide();
        ui->label_2->hide();
        movieBtnFavourite->start();
        isBtnFavouritePresssed = false;
        ui->btnRemove->hide();
        ui->labelSearch->hide();
    } else {
        ui->listWidget->show();
        ui->label_2->show();
        movieBtnFavourite->start();
        isBtnFavouritePresssed = true;
        ui->btnRemove->show();
        ui->labelSearch->show();
    }
}

void MainWindow::setButtonIcon(int frame)
{
    globalFrame = frame;
    ui->btnFavourite->setIcon(QIcon(movieBtnFavourite->currentPixmap()));
    ui->btnFavourite->setIconSize(QSize(32,32));
}

void MainWindow::setButton2Icon(int frame)
{
    /* Button Add Movie */
    ui->btnAdd->setIcon(QIcon(movieBtnAdd->currentPixmap()));
    ui->btnAdd->setIconSize(QSize(24,24));
}

void MainWindow::refresh()
{
    if(globalFrame == 30 && isBtnFavouritePresssed)  movieBtnFavourite->setPaused(true);
    else if(globalFrame == 0 && !isBtnFavouritePresssed) movieBtnFavourite->setPaused(true);
}

void MainWindow::on_btnAdd_clicked()
{
    /* Add Favourite Channel To List */
    QString channel = ui->lineName->text();

    if(!channel.isEmpty()){
        qDebug() << channel;
        ui->listWidget->addItem(channel);
    }

    /* Disable Multiple Insert */
    ui->btnAdd->setDisabled(true);
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    /* Select Channel */
    int row = index.row();
    const QString channel = ui->listWidget->item(row)->text();
    ui->lineName->setText(channel);
}

void MainWindow::saveDataFromTable()
{
    int size = ui->listWidget->count();
    QVector<QString> channel;

    /* Read All Elements */
    for(int i = 0; i < size; i++) {
        QString name = ui->listWidget->item(i)->text();
        channel.push_back(name);
    }

    /* Save Data */
    storage.save(channel);
}

void MainWindow::loadDataToTable()
{
    /* Load Data To Table */
    QVector<QString> channel = storage.load();

    for(int i = 0; i < channel.size(); i++) {
        ui->listWidget->addItem(channel[i]);
    }
}

void MainWindow::on_table_cellDoubleClicked(int row, int column)
{
    if(column == 3) {
        const QString link = ui->table->item(row, column)->text();
        qDebug() << link;
        QDesktopServices::openUrl(link);
    }
}

void MainWindow::on_btnRemove_clicked()
{
    /* Remove Item From List */
    int row = ui->listWidget->currentRow();
    QListWidgetItem *item = ui->listWidget->takeItem(row);
    const QString text = item->text();
    ui->listWidget->removeItemWidget(item);
    ui->listWidget->repaint();
    qDebug() << "Removed" << text << row;
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    if(!ui->btnRemove->isEnabled()) {
        ui->btnRemove->setEnabled(true);
    }
}

void MainWindow::on_labelSearch_textChanged(const QString &arg1)
{
    /* Show Only Founded Channel */
    int size = ui->listWidget->count();

    /* Show | Hide */
    for(int row = 0; row < size; ++row) {
        QString text = ui->listWidget->item(row)->text();
        if(text.contains(arg1)) {
            ui->listWidget->setRowHidden(row, false);
        } else {
            ui->listWidget->setRowHidden(row, true);
        }
    }
}





















