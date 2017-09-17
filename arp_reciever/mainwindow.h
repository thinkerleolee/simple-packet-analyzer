#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data_packet_analyzer/AnalyzerMannger.h"
#include "data_packet_sniffer/FilterDataReceiver.h"
#include "data_packet_sniffer/DataReceiver.h"
#include "threadlisten.h"
#include <QMessageBox>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_stop_clicked();
    void on_pushButton_start_clicked();
    void startThreadListen();
    void stopThreadListen();

private:
    void anan_packet();
    void newModel();
    void clearTable();
    std::vector<std::string> dev_description;
    ThreadListen threadListen;
    Ui::MainWindow *ui;
    DataReceiver *re;
    AnalyzerMannger analyzer;
    std::vector<data_pack> data_buff;
    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
