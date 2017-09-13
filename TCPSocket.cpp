//
// TCPSocket.cpp for  in /home/benlou_d//bmail
// 
// Made by damien benloukil
// Login   <benlou_d@epitech.net>
// 
// Started on  Fri Jun 24 22:00:02 2011 damien benloukil
// Last update Sat Jun 25 18:39:53 2011 damien benloukil
//
#include        <QtGui>
#include	"TCPSocket.hh"

#include <QHostAddress>

Client::Client(QObject* parent): QObject(parent)
{
  this->client  = new QTcpSocket(this);
  this->tmp = new QString;
  connect(this->client, SIGNAL(readyRead()), this, SLOT(receive()));
  connect(this->client, SIGNAL(error(QAbstractSocket::SocketError)),
	  this, SLOT(displayError(QAbstractSocket::SocketError)));
}

Client::~Client()
{
  client->close();
}

void Client::start(QString address, quint16 port)
{
  client->connectToHost(address, port);
}

void Client::startTransfer(std::string const & data)
{
  std::cout << "send " << data << std::endl;
  client->write(data.c_str(), data.size());
}

void Client::receive()
{
  std::cout << "BITE AVAILABLE: "  << this->client->bytesAvailable() << std::endl;
  if (this->client->bytesAvailable() > 0)
    {
      QString s =   this->client->readAll();
      this->client->flush();
      
      int a = s.size() - 3;
      const char * z = s.toStdString().c_str();
      if (z[a] != '.' && a > 100)	
	{
	std::cout << "VA TE FAIRE ENCULER" << std::endl;
	this->tmp->append(s);
	}
      else	
	{
	  if (!this->tmp->isNull())
	    this->recv.append(tmp);
	  else
	    this->recv.append(s);
	}
    }
}

void Client::displayError(QAbstractSocket::SocketError err)
{
  switch (err)
    {
    case QAbstractSocket::ConnectionRefusedError:
      std::cout << "connection refused" << std::endl;
      break;
    case QAbstractSocket::RemoteHostClosedError:
      std::cout << "The remote host closed the connection." << std::endl;
      break;
    case QAbstractSocket::HostNotFoundError:
      std::cout << "host not found" << std::endl;
      break;
    case QAbstractSocket::NetworkError:
      std::cout << "network error" << std::endl;
      break;
    case QAbstractSocket::AddressInUseError:
      std::cout << "The address specified is already in use and was set to be exclusive" << std::endl;
      break;
    case QAbstractSocket::SocketAddressNotAvailableError:
      std::cout << "The address specified to does not belong to the host." << std::endl;
      break;
    default:
      std::cout << "unknown error" << std::endl;
      break;
    }
}
