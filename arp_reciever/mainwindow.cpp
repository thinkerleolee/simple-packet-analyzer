#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sys/stat.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    re  = new FilterDataReceiver;
    re->find_all_devs();
    re->get_all_devs(dev_description);
    for(auto i:dev_description)
    {
        ui->comboBox_choose_device->addItem(QString::fromStdString(i));
    }
    ui->comboBox_choose_protocol->addItem("arp");
    ui->comboBox_choose_protocol->addItem("udp");
    ui->pushButton_stop->setDisabled(true);
    newModel();
    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(startThreadListen()));
    connect(ui->pushButton_stop, SIGNAL(clicked()), this, SLOT(stopThreadListen()));
}

void MainWindow::newModel()
{
  ui->tableWidget->setColumnCount(4);
  ui->tableWidget->setRowCount(1024);
  ui->tableWidget->setHorizontalHeaderLabels(
        QStringList() << "时间" << "协议类型" << "数据包长度" << "数据包信息");
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
  ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
  ui->tableWidget->setColumnWidth(0,201);
  ui->tableWidget->setColumnWidth(1,100);
  ui->tableWidget->setColumnWidth(2,100);
  ui->tableWidget->setColumnWidth(3,700);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearTable()
{

}

void MainWindow::anan_packet()
{
     analyzer.setPortocol(ui->comboBox_choose_protocol->currentText().toStdString());
    analyzer.get_packet(this->data_buff);
    int num = 0;
    for(data_pack i : this->data_buff)
    {
      ui->tableWidget->setItem(num,0,new QTableWidgetItem(QString::fromStdString(i.timestr)));
      ui->tableWidget->setItem(num,1,new QTableWidgetItem(QString::fromStdString(i.protocol)));
      ui->tableWidget->setItem(num,2,new QTableWidgetItem(QString::fromStdString(i.length)));
      ui->tableWidget->setItem(num++,3,new QTableWidgetItem(QString::fromStdString(i.info)));
    }
}

unsigned long get_file_size(const char *path)
{
    unsigned long filesize = -1;
    struct stat statbuff;
    if(stat(path, &statbuff) < 0){
        return filesize;
    }else{
        filesize = statbuff.st_size;
    }
    return filesize;
}

void MainWindow::on_pushButton_stop_clicked()
{
  stopThreadListen();
    ui->pushButton_stop->setDisabled(true);
    ui->pushButton_start->setDisabled(false);
    ui->comboBox_choose_protocol->setDisabled(false);
        ui->comboBox_choose_device->setDisabled(false);
    if(get_file_size("temp.dat") == 0)
      {
        QMessageBox::information(this,"提示","未抓取到数据包");
      }
    else
      {
           anan_packet();
      }
}

void MainWindow::on_pushButton_start_clicked()
{
    data_buff.clear();
    ui->tableWidget->clearContents();
    ui->comboBox_choose_protocol->setDisabled(true);
    ui->comboBox_choose_device->setDisabled(true);
    ui->pushButton_start->setDisabled(true);
    ui->pushButton_stop->setDisabled(false);
}

void MainWindow::startThreadListen()
 {
    threadListen.set_dev(ui->comboBox_choose_device->currentIndex()+1);
    threadListen.start();
 }


void MainWindow::stopThreadListen()
 {
    threadListen.quit();
 }
