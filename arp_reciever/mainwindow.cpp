//
// Created by thinkerleo on 17-9-16.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  if(!check_if_root())
    {
      QMessageBox::information(this,"提示","请以root模式运行该程序");
      exit(2);
    }
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
  ui->tableWidget->setColumnCount(5);
  ui->tableWidget->setHorizontalHeaderLabels(
        QStringList() << "NO" << "时间" << "协议类型" << "数据包长度" << "数据包信息");
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
  ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
  ui->tableWidget->setColumnWidth(0,50);
  ui->tableWidget->setColumnWidth(1,201);
  ui->tableWidget->setColumnWidth(2,100);
  ui->tableWidget->setColumnWidth(3,100);
  ui->tableWidget->setColumnWidth(4,700);
}

void MainWindow::anan_packet()
{
  analyzer.setPortocol("arp");
  analyzer.get_packet(this->data_buff_arp);
  analyzer.setPortocol("udp");
  analyzer.get_packet(this->data_buff_udp);
}

void MainWindow::show_table()
{
  int num = 0;
  if(ui->comboBox_choose_protocol->currentText() == "arp")
    {
      for(data_pack i : this->data_buff_arp)
        {
          ui->tableWidget->setRowCount(num + 1);
          ui->tableWidget->setItem(num,0,new QTableWidgetItem(QString::number(num, 10)));
          ui->tableWidget->setItem(num,1,new QTableWidgetItem(QString::fromStdString(i.timestr)));
          ui->tableWidget->setItem(num,2,new QTableWidgetItem(QString::fromStdString(i.protocol)));
          ui->tableWidget->setItem(num,3,new QTableWidgetItem(QString::fromStdString(i.length)));
          ui->tableWidget->setItem(num++,4,new QTableWidgetItem(QString::fromStdString(i.info)));
        }
    }
  if(ui->comboBox_choose_protocol->currentText() == "udp")
    {
      for(data_pack i : this->data_buff_udp)
        {
          ui->tableWidget->setRowCount(num + 1);
          ui->tableWidget->setItem(num,0,new QTableWidgetItem(QString::number(num, 10)));
          ui->tableWidget->setItem(num,1,new QTableWidgetItem(QString::fromStdString(i.timestr)));
          ui->tableWidget->setItem(num,2,new QTableWidgetItem(QString::fromStdString(i.protocol)));
          ui->tableWidget->setItem(num,3,new QTableWidgetItem(QString::fromStdString(i.length)));
          ui->tableWidget->setItem(num++,4,new QTableWidgetItem(QString::fromStdString(i.info)));
        }
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
      show_table();
    }
}

void MainWindow::on_pushButton_start_clicked()
{
  data_buff_arp.clear();
  data_buff_udp.clear();
  ui->tableWidget->clearContents();
  ui->tableWidget->setRowCount(0);
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
  qDebug() << "Stop Thread";
  threadListen.exit();
}

bool MainWindow::check_if_root()
{
  struct passwd *pwd;
  pwd = getpwuid(getuid());
  QString now_user;
  now_user = QString::fromStdString(pwd->pw_name);
  qDebug() << "now user" << now_user;
  if(now_user == "root")
    {
      return true;
    }
  else
    {
      return false;
    }
}

MainWindow::~MainWindow()
{
  delete ui;
  delete re;
}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
}

void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
  QByteArray *qb;
    if(ui->comboBox_choose_protocol->currentText() == "arp")
      {
        qb = new QByteArray((char*)data_buff_arp[ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt()].data);
        ui->textBrowser_ascii_data->setText((char*)data_buff_arp[index.column()].data);
      }
    else if(ui->comboBox_choose_protocol->currentText() == "udp")
      {
        qb = new QByteArray((char*)data_buff_udp[ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt()].data);
        ui->textBrowser_ascii_data->setText((char*)data_buff_udp[index.column()].data);
      }
    ui->textBrowser_hex_data->setText(qb->toHex());

}

void MainWindow::on_comboBox_choose_protocol_currentIndexChanged(const QString &arg1)
{

  if(!get_file_size("temp.dat") == 0)
    {
      ui->tableWidget->clearContents();
      ui->tableWidget->setRowCount(0);
      show_table();
    }
}
