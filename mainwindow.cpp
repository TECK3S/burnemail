//
// mainwindow.cpp for  in /home/benlou_d//proj/bmail
// 
// Made by damien benloukil
// Login   <benlou_d@epitech.net>
// 
// Started on  Sat Jun 25 04:08:41 2011 damien benloukil
// Last update Sun Jun 26 20:06:50 2011 damien benloukil
//

//imx : pass : Sucemabite42@
// login : jtebaisePute@gmx.fr

#include "TCPSocket.hh"
#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, QString  fichierDeConf) :    QMainWindow(parent), ui(new Ui::MainWindow),  conf(fichierDeConf),socket(new Client)
{
    ui->setupUi(this);
    this->ui->content->setReadOnly(true);
    this->timer.setInterval(1);
    this->re = false;
    this->mapi["connection"] = &MainWindow::login;
    this->mapi["login"] = &MainWindow::pass;
    this->mapi["pass"] = &MainWindow::stat;
    this->mapi["stat"] = &MainWindow::list;
    this->mapi["top"] = &MainWindow::showMail;
    this->mapi["list"] = &MainWindow::insertList;
    this->mapi["retr"] = &MainWindow::retr;
    this->mapi["quit"] = &MainWindow::lol;
    this->connect(&this->timer, SIGNAL(timeout()), this, SLOT(hasDataToSend()));
    connect(this->ui->maillist, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(openMail(QListWidgetItem *)));

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::hasDataToSend()
{
  if (!this->socket->recv.isNull())
    {
      std::cout << "receive: " << this->socket->recv.toStdString() << std::endl;
      this->re = true;
       if (!this->actionQueue.empty())
	 {
	   func_ptr ptr = this->mapi[this->actionQueue.front()];
	   this->ins = this->socket->recv;
	   this->actionQueue.pop();
	   this->socket->recv.clear();
	   this->socket->tmp->clear();
	   (this->*ptr)();	   
	 }
    }
}

void MainWindow::lol()
{
  return;
  std::cout << "connection terminated loool" << std::endl;
  exit(EXIT_SUCCESS);
}

void MainWindow::quit()
{
  this->actionQueue.push("quit");
  QString pas = "QUIT\n";
  this->socket->startTransfer(pas.toStdString());
}

void MainWindow::retr()
{
  QStringList list = this->ins.split('\n');
  for (int i = 0; i < list.size(); ++i)
    {
      if (list.at(i).contains("Subject:", Qt::CaseInsensitive))
	this->ui->maillist->addItem(list.at(i));
    }  
}

void MainWindow::openMail(QListWidgetItem *item)
{
  int line = this->ui->maillist->row(item);
  this->top(line);
}

void MainWindow::showMail()
{
  this->ui->content->appendPlainText(this->ins);
}

void MainWindow::top(int line)
{
  this->actionQueue.push("top");
  QString pas = "TOP " + QString::number(line + 1) + " 100\n";
  this->socket->startTransfer(pas.toStdString());
}

void MainWindow::dele(int mail)
{
  this->actionQueue.push("dele");
  QString pas = "DELE " +   QString::number(mail) + "\n";
  this->socket->startTransfer(pas.toStdString());
  this->quit();
}

//culsexe@aol.fr
void MainWindow::list()
{
  this->actionQueue.push("list");
  QString pas = "LIST\n";
  this->socket->startTransfer(pas.toStdString());
}


void MainWindow::stat()
{
  this->actionQueue.push("stat");
  QString pas = "STAT\n";
  this->socket->startTransfer(pas.toStdString());
}

void MainWindow::insertList()
{
  QStringList list = this->ins.split('\n');
  for (int i = 1; i < list.size() - 2; ++i)
    {
      this->re = false;  
      QStringList ndList = list.at(i).split(' ');
      this->mailLength[ndList.at(1).toLocal8Bit().constData()]
	= ndList.at(0).toInt();
      this->actionQueue.push("retr");
      QString pas = "RETR " + ndList.at(0) + "\n";
      this->socket->startTransfer(pas.toStdString());
    }
}

void MainWindow::pass()
{
  this->actionQueue.push("pass");
  QString pas = "PASS " + this->ui->password->text() + "\n";
  this->socket->startTransfer(pas.toStdString());//dindon

   delete this->ui->labelLogin;
   delete this->ui->labelPassword;
   delete this->ui->login;
   delete this->ui->password;
   delete this->ui->connection;
   QLabel *co = new QLabel("connected", this);
   co->move(50, 50);
   co->show();
}

void MainWindow::login()
{  
   this->actionQueue.push("login");
   QString log = "USER " + this->ui->login->text() + "\n";
   this->socket->startTransfer(log.toStdString());//culsexe@aol.fr 
}

void MainWindow::on_connection_clicked()
{
   this->actionQueue.push("connection");
   this->socket->start("pop.aol.com", 110);
   this->timer.start();
}

void MainWindow::sendMail()
{
  /* ici envoyer le mail*/
  std::cout << "to: " << this->to->text().toStdString() << std::endl;
  std::cout << "subject: " << this->subject->text().toStdString() << std::endl;
  std::cout << "content: " << this->p->toPlainText().toStdString() << std::endl;
  delete write;
}

void MainWindow::on_write_clicked()
{
    this->write = new QMainWindow;
    write->setFixedSize(550, 430);

    this->to = new QLineEdit(write);
    to->setFixedSize(530, 20);
    to->move(10,10);

    this->subject = new QLineEdit(write);
    subject->setFixedSize(530, 20);
    subject->move(10,40);

    this->p = new QPlainTextEdit(write);
    p->setFixedSize(530, 300);
    p->move(10,75);

    QPushButton *b = new QPushButton("send", write);
    b->setFixedSize(100, 25);
    b->move(420,390);

    write->show();
    connect(b, SIGNAL(clicked()), this, SLOT(sendMail()));
}

void MainWindow::on_delete_2_clicked()
{
    QList<QListWidgetItem *> item = this->ui->maillist->selectedItems();
    this->dele(this->ui->maillist->currentRow() + 1);
}
