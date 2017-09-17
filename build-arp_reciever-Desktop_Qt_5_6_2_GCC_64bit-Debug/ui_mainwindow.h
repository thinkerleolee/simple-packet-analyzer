/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_device_chooser;
    QComboBox *comboBox_choose_device;
    QTextBrowser *textBrowser_ascii_data;
    QLabel *label_2;
    QLabel *label_3;
    QTextBrowser *textBrowser_hex_data;
    QPushButton *pushButton_start;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_save_hex;
    QPushButton *pushButton_save_ascii;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QLabel *label_protocol_chooser;
    QComboBox *comboBox_choose_protocol;
    QTableWidget *tableWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1093, 681);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_device_chooser = new QLabel(centralWidget);
        label_device_chooser->setObjectName(QStringLiteral("label_device_chooser"));
        label_device_chooser->setGeometry(QRect(20, 60, 71, 61));
        QFont font;
        font.setPointSize(14);
        label_device_chooser->setFont(font);
        comboBox_choose_device = new QComboBox(centralWidget);
        comboBox_choose_device->setObjectName(QStringLiteral("comboBox_choose_device"));
        comboBox_choose_device->setGeometry(QRect(100, 80, 551, 26));
        textBrowser_ascii_data = new QTextBrowser(centralWidget);
        textBrowser_ascii_data->setObjectName(QStringLiteral("textBrowser_ascii_data"));
        textBrowser_ascii_data->setGeometry(QRect(610, 360, 461, 291));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(790, 330, 91, 31));
        QFont font1;
        font1.setPointSize(20);
        label_2->setFont(font1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(230, 330, 91, 31));
        label_3->setFont(font1);
        textBrowser_hex_data = new QTextBrowser(centralWidget);
        textBrowser_hex_data->setObjectName(QStringLiteral("textBrowser_hex_data"));
        textBrowser_hex_data->setGeometry(QRect(30, 360, 461, 291));
        pushButton_start = new QPushButton(centralWidget);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        pushButton_start->setGeometry(QRect(120, 10, 91, 41));
        pushButton_stop = new QPushButton(centralWidget);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        pushButton_stop->setGeometry(QRect(280, 10, 91, 41));
        pushButton_save_hex = new QPushButton(centralWidget);
        pushButton_save_hex->setObjectName(QStringLiteral("pushButton_save_hex"));
        pushButton_save_hex->setGeometry(QRect(450, 10, 91, 41));
        pushButton_save_ascii = new QPushButton(centralWidget);
        pushButton_save_ascii->setObjectName(QStringLiteral("pushButton_save_ascii"));
        pushButton_save_ascii->setGeometry(QRect(620, 10, 91, 41));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 60, 1081, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(540, 330, 20, 321));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 320, 1091, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_protocol_chooser = new QLabel(centralWidget);
        label_protocol_chooser->setObjectName(QStringLiteral("label_protocol_chooser"));
        label_protocol_chooser->setGeometry(QRect(690, 60, 141, 61));
        label_protocol_chooser->setFont(font);
        comboBox_choose_protocol = new QComboBox(centralWidget);
        comboBox_choose_protocol->setObjectName(QStringLiteral("comboBox_choose_protocol"));
        comboBox_choose_protocol->setGeometry(QRect(790, 80, 161, 26));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(40, 120, 991, 201));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_device_chooser->setText(QApplication::translate("MainWindow", "Device:", 0));
        label_2->setText(QApplication::translate("MainWindow", "ACSII", 0));
        label_3->setText(QApplication::translate("MainWindow", "HEX", 0));
        textBrowser_hex_data->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        pushButton_start->setText(QApplication::translate("MainWindow", "Start", 0));
        pushButton_stop->setText(QApplication::translate("MainWindow", "Stop", 0));
        pushButton_save_hex->setText(QApplication::translate("MainWindow", "Save_HEX", 0));
        pushButton_save_ascii->setText(QApplication::translate("MainWindow", "Save_ASCII", 0));
        label_protocol_chooser->setText(QApplication::translate("MainWindow", "Protocol:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
