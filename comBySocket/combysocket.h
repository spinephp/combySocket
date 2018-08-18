#ifndef COMBYSOCKET_H
#define COMBYSOCKET_H

#include <QtGui/QWidget>
#include "ui_combysocket.h"
#include <QTcpSocket>
#include "LanbeProtocol.h"

#define FLAG_HASPRIVILEGE		0x00000001
#define FLAG_INQUERYTIME		0x00000002

#define TYPE_SETBAUDRATE		0x01
#define TYPE_GETBAUDRATE		0x02
#define	TYPE_SENDDATA			0x03
#define TYPE_GRABCOM			0x04
#define TYPE_ANSWERGRABCOM		0x05
#define TYPE_GETKEYBOARDSTATE	0x06
#define TYPE_AUTH				0x07
#define TYPE_SENDKEY			0x08
#define	TYPE_QUERYCOMDATA		0x09
#define TYPE_CONFIRMGRABCOM		0x0A
#define TYPE_SENDUSERID			0x32

typedef struct typeCurState
{
	int flag;
	QString strIp;
	QString strPort;
}CURSTATE,*PCURSTATE;

class comBySocket : public QWidget
{
	Q_OBJECT

public:
	comBySocket(QWidget *parent = 0);
	~comBySocket();
protected:
	void timerEvent(QTimerEvent *event);

private:
	Ui::comBySocketClass ui;
	CLanbeProtocol m_protocol;
	QStringList m_param;
	QString m_userID;
	CURSTATE	m_curState;
	//timeout 3 times, maybe com can't use
//	int			m_intervalCount;
	//轮询超时时间
	int m_timerComInterval;
	//串口轮询时间间隔。通过轮询得到串口发出的数据
	int m_timerQueryInterval;
public slots:
	//send com param to socket
	void setCom();
	void getCom();
	void sendCom();
	void connectServer();
	void disconnectServer();
	void doProcess(int type);
	
	void inClear();
	void outClear();
	void blain();
	

	//network relative
	void connected();
	void disconnected();
	void bytesWritten(qint64 bytes);
	void readFromServer();
	void displayTcpError(QAbstractSocket::SocketError socketError);
	bool eventFilter(QObject *target, QEvent *event);
	bool sendData(vector<unsigned char>& vbuf);
	QString backDataConvent(QString subRead);
	void setForntColor(int color);

	//禁止，允许操作UI控件, 默认都禁止
//	void setUiState(int isEnable, int controlId = 0);
public:
	void setParam(QString strIp, QString strPort, QString userID);
	void grabCom();
	void sendOutClear();

private:
	QTcpSocket * m_socket;
	char textEditKeys[512];
	int keycount;
	QString strTail;
	QString curCmd;
	QColor textColor;
	QColor textBackColor;
	int curInputStartCol,curInputEndCol,curInputRow;
	bool ctrlKeyMode;
	char ctrlKeyChar;
};

#endif // COMBYSOCKET_H
