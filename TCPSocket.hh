//
// TCPSocket.hh for  in /home/benlou_d//bmail
// 
// Made by damien benloukil
// Login   <benlou_d@epitech.net>
// 
// Started on  Fri Jun 24 22:00:28 2011 damien benloukil
// Last update Sat Jun 25 18:35:41 2011 damien benloukil
//

#ifndef		TCPSOCKET_HH
#define		TCPSOCKET_HH

#include <QtNetwork>
#include <queue>
#include <QAbstractSocket>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <iostream>

class Client: public QObject
{
  Q_OBJECT
public:
  Client(QObject* parent = 0);
  ~Client();
  void start(QString address, quint16 port);
  QString  recv;
  QString *tmp;

public slots:
  void startTransfer(std::string const &);
  void receive();
  void displayError(QAbstractSocket::SocketError);
public:
  QTcpSocket *client;
};


#endif
