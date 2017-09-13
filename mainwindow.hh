#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <queue>
#include <string>
#include <iostream>
#include <map>
#include <QMainWindow>
#include "TCPSocket.hh"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
      Q_OBJECT

private:
  Ui::MainWindow *ui;
  QString conf;
  QMainWindow *write;
  QTimer      timer;
  std::map<std::string,void (MainWindow::*)()> mapi;
  QLineEdit *to;
  QLineEdit *subject;
  QPlainTextEdit *p;

public:
  explicit MainWindow(QWidget *parent = 0, QString fichierDeConf = "conf.conf");
  virtual ~MainWindow();
  void login();
  void pass();
  void stat();
  void list();
  void top(int);
  void retr();
  void quit();
  void lol();
  void dele(int);
  void insertList();
  void showMail();
  QString ins;
  Client *socket;
  std::queue<std::string> actionQueue;		
  std::map<std::string, int> mailLength;
  bool re;    
		     
public slots:
  void on_connection_clicked();
  void on_write_clicked();
  void sendMail();
  void on_delete_2_clicked();
  void hasDataToSend();
  void openMail(QListWidgetItem *);
  
};

typedef void(MainWindow::*func_ptr)();

#endif // MAINWINDOW_H
