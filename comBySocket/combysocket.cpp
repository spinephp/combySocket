#include "combysocket.h"
#include <tchar.h>
#include <QTextCodec>
#include <QDebug>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QtEndian>
#include <vector>
#include <QKeyEvent>
#include <QTextBlock>
using namespace std;
#include "Encrypt.h"
#include "Language.h"

extern void qbyte2StrA(const unsigned char* bArr, const unsigned long size, QVector<char>& vstr);
extern bool str2byte(const TCHAR* pstr, vector<unsigned char>& vByte);
extern bool str2byteA(const char* pstr, vector<unsigned char>& vByte);
extern void strTrim(string& s);
extern unsigned char g_desKeyEnc[17];
extern unsigned char g_desKeyDec[17];

int g_baudrateArray[] =
{
	2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200
};

comBySocket::comBySocket(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.textEditIn->installEventFilter(this);
	ui.label_2->setText(_lang[MAIN_BAUD_RATE].c_str());
	ui.pb_set->setText(_lang[MAIN_SET_BAUD_RATE].c_str());
	ui.pb_get->setText(_lang[MAIN_GET_BAUD_RATE].c_str());
	ui.pb_send->setText(_lang[MAIN_SEND].c_str());
	ui.pb_senda->setText(_lang[MAIN_SENDA].c_str());
	ui.label_9->setText(_lang[MAIN_INPUT].c_str());
	ui.pb_InputClear->setText(_lang[MAIN_BTN_CLEAR].c_str());
	ui.radio_in_hex->setText(_lang[MAIN_HEX].c_str());
	ui.radio_in_string->setText(_lang[MAIN_STRING].c_str());
	//ui.label_10->setText(_lang[MAIN_OUTPUT].c_str());
	//ui.pb_outClear->setText(_lang[MAIN_BTN_CLEAR].c_str());
	ui.textEditIn->document()->setMaximumBlockCount(1000);
	m_socket = new QTcpSocket(this);

	connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(m_socket, SIGNAL(readyRead()), this, SLOT(readFromServer()));
//	connect(m_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
	connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
		this, SLOT(displayTcpError(QAbstractSocket::SocketError)));

	m_curState.flag = 0;
	keycount = 0;
	strTail = "";
	curCmd = "";
	textColor = Qt::black;
	textBackColor = Qt::white;
	ctrlKeyMode = false;
// 	ui.lineEdit_srvIp->setText("127.0.0.1");
// 	ui.lineEdit_srvPort->setText("5168");

//	QStringList strList;
// 	for (int i = 1; i < 5; ++i)
// 	{
// 		 strList.append(QString("COM%1").arg(i));
// 	}
// 	ui.cmb_port->addItems(strList);
// 	ui.cmb_port->setCurrentIndex(0);

	for each (int var in g_baudrateArray)
	{
		ui.cmb_baudrate->addItem(QString::number(var));
	}
	ui.cmb_baudrate->setCurrentIndex(2);

// 	ui.cmb_databits->addItem("5");
// 	ui.cmb_databits->addItem("6");
// 	ui.cmb_databits->addItem("7");
// 	ui.cmb_databits->addItem("8");
// 	ui.cmb_databits->setCurrentIndex(3);

// 	ui.cmb_stopbits->addItem("1");
// 	ui.cmb_stopbits->addItem("1.5");
// 	ui.cmb_stopbits->addItem("2");
// 	ui.cmb_stopbits->setCurrentIndex(0);

// 	ui.cmb_parity->addItem("None");
// 	ui.cmb_parity->addItem("Odd");
// 	ui.cmb_parity->addItem("Even");
// 	ui.cmb_parity->addItem("Mark");
// 	ui.cmb_parity->addItem("Space");
// 	ui.cmb_parity->setCurrentIndex(0);

// 	ui.cmb_flowControl->addItem("Custom");
// 	ui.cmb_flowControl->addItem("Hardware");
// 	ui.cmb_flowControl->addItem("Software");
// 	ui.cmb_flowControl->addItem("None");
// 	ui.cmb_flowControl->setCurrentIndex(0);

	ui.radio_in_string->setChecked(true);
//	ui.radio_out_string->setChecked(true);

//	setUiState(0);
}

comBySocket::~comBySocket()
{
	disconnected();
}

void comBySocket::setParam(QString strIp, QString strPort, QString userID)
{
	//QMessageBox::information(NULL, "","", QMessageBox::Ok);

	ui.textEditIn->append(_lang[CONNECTING].c_str());
	m_socket->abort();
	m_socket->connectToHost(strIp,strPort.toInt());
	m_userID = userID;
}

void comBySocket::inClear()
{
	ui.textEditIn->setText(_T(""));
	ui.textEditIn->setFocus();
}

//盲打选择框点击事件
void comBySocket::blain()
{
	memset(textEditKeys,0,512);
	keycount = 0;
	ui.textEditIn->setFocus();
}

void comBySocket::outClear()
{
	ui.textEditIn->setText(_T(""));
}

void comBySocket::setCom()
{
	doProcess(TYPE_SETBAUDRATE);
}

void comBySocket::getCom()
{
	doProcess(TYPE_GETBAUDRATE);
}

void comBySocket::sendCom()
{
	doProcess(TYPE_SENDDATA);
}

void comBySocket::grabCom()
{
	doProcess(TYPE_GRABCOM);
}

void comBySocket::sendOutClear()
{
	//ui.textEditSendOut->setText("");
}

// textEditIn 键盘事件
bool comBySocket::eventFilter(QObject *target, QEvent *event)
{
	if (target == ui.textEditIn){ 
		if(event->type() == QEvent::KeyPress) 
		{ 
			QByteArray ctrlChars;
			ctrlChars.resize(6);
			ctrlChars[0] = Qt::Key_2;
			ctrlChars[1] = Qt::Key_A;
			ctrlChars[2] = Qt::Key_B;
			ctrlChars[3] = Qt::Key_C;
			ctrlChars[4] = Qt::Key_D;
			ctrlChars[5] = Qt::Key_E;
			QTextCursor tc = ui.textEditIn->textCursor();
			int  row=tc.blockNumber();
			QKeyEvent *ke;
			ke = reinterpret_cast<QKeyEvent*>(event); 
			if (ke->key() == Qt::Key_Enter || ke->key() == Qt::Key_Return) 
			{ 
				// 回车发送数据
				if(ui.pb_send->isChecked()==false){
						if(row!=curInputRow){
							curInputStartCol = tc.columnNumber();
							keycount = 0;
						}
				}
				curInputEndCol = tc.columnNumber();
				doProcess(TYPE_SENDDATA);
				keycount = 0;
				return true;
			}else if((ke->modifiers() & Qt::ControlModifier) && ctrlChars.indexOf(ke->key())>=0){// 发送控制键
				ctrlKeyMode =  true;
				ctrlKeyChar = ctrlChars.indexOf(ke->key());
				doProcess(TYPE_SENDDATA);
				ctrlKeyMode =  false;
				return true;
			}else{
				if(ui.pb_send->isChecked()==true){// 盲打时保存按键值
					textEditKeys[keycount++] = ke->text().toLatin1().data()[0];
					return true;
				}
				else{
					if(!keycount++){
						curInputStartCol = tc.columnNumber();
						curInputRow=tc.blockNumber();
					}else {
						if(row!=curInputRow){
							curInputRow = row;
							curInputStartCol = tc.columnNumber();
							keycount = 1;
						}
					}
				}
			}
		}
	}
	return QWidget::eventFilter(target, event);
}

std::wstring StringToWstring(const string str)
{// string转wstring
    unsigned len = str.size() * 2;// 预留字节数
    setlocale(LC_CTYPE, _T(""));     //必须调用此函数
    wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
    mbstowcs(p,str.c_str(),len);// 转换
    std::wstring str1(p);
    delete[] p;// 释放申请的内存
    return str1;
}

// 发送数据
bool comBySocket::sendData(vector<unsigned char>& vbuf){

	QString strSend,strSendEx;
	int dataLength = 0;
	vector<unsigned char> tmp;

	QTextDocument* textDocument;
	int lineno;
	QTextBlock textBlock;

	if(ctrlKeyMode)
		strSend = ctrlKeyChar;
	else if(ui.pb_send->isChecked()){// 从键盘缓存取字符
		strSend = textEditKeys;
		memset(textEditKeys,0,512);
	}else{// 从 textEditIn 中取字符
		QTextCursor tc;
		tc = ui.textEditIn->textCursor();
		strSend = tc.block().text().right(curInputEndCol-curInputStartCol);
	}
		//QMessageBox::information(NULL, QString::number(keycount,10),ctrlKeyChar, QMessageBox::Ok);

	//QMessageBox::information(NULL,strSend, "keycount="+QString::number(keycount,10)+"cursor="+QString::number(curInputEndCol-curInputStartCol,10), QMessageBox::Ok);
	keycount = 0;
	while(!strSend.isEmpty() && (strSend[0]=='#' || strSend[0]==' ')){
		strSend = strSend.right(strSend.length()-1);
	}
	//if (strSend.isEmpty())
//	{
	//	ui.textEditIn->append(QString(_lang[NO_DATA_FOR_SEND].data()));//Out
		//return false;
	//}
	strSendEx = strSend + "\r";
	curCmd = strSend;
	if (strSendEx.size() > 512)
	{
		ui.textEditIn->append(QString(_lang[MAX_PACKAGE_IS_512].c_str()));//Out
		return false;
	}
	if (ui.radio_in_hex->isChecked())
	{
		strSendEx.remove(_T(" "));
		strSendEx.remove(_T("\t"));
		//strSend.remove(_T("\r"));
		strSend.remove(_T("\n"));
		if (strSendEx.size() % 2)
		{
			ui.textEditIn->append(QString(_lang[HEX_DATA_LEN_INVALID].c_str()));//Out
			return false;
		}
		string str = strSendEx.toStdString();
		if (str2byte(str.c_str(), tmp))
		{
			ui.textEditIn->append(QString(_lang[DATA_IS_NOT_VALID_HEX_DATA].c_str()));//Out
			return false;
		}
		dataLength = tmp.size();
	}
	else
	{
		dataLength = strSendEx.size();
		tmp.resize(dataLength);
		memcpy(&tmp[0], strSendEx.toLatin1().data(), dataLength);
	}
		
	//QMessageBox::information(NULL, QString::number(keycount,10),strSend.left(1).toAscii().toHex(), QMessageBox::Ok);
	if(ctrlKeyMode)
		tmp[0] = ctrlKeyChar;
	m_protocol.sendData(tmp, vbuf);
	return true;
}

void comBySocket::doProcess(int type)
{
	if (m_socket->state() != QAbstractSocket::ConnectedState)
	{
		ui.textEditIn->append(_T("Server not connected."));
		return;
	}
	if ((type != TYPE_SENDUSERID) && (type != TYPE_CONFIRMGRABCOM) && (TYPE_GETKEYBOARDSTATE != type) && (TYPE_GRABCOM != type) && FLAG_HASPRIVILEGE != (m_curState.flag & FLAG_HASPRIVILEGE))
	{
		ui.textEditIn->append( QString(_lang[NO_ACCESS_SERIAL_PORT].c_str()));
		killTimer(m_timerQueryInterval);
		return;
	}
	//不是轮询命令的时候需要停止并等待轮询返回
	if (type != TYPE_QUERYCOMDATA)
	{
		killTimer(m_timerQueryInterval);

		int iCount = 0;
		while (FLAG_INQUERYTIME == (m_curState.flag & FLAG_INQUERYTIME))
		{
			QElapsedTimer t;
			t.start();
			while (t.elapsed() < 200)
			{
				QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
			}
			++iCount;
			if (iCount > 5)
			{
				//ui.textEditIn->append(QString(_lang[POLL_CMD_NO_RESP].c_str()));
	//QMessageBox::information(NULL, "SP",QString::number(type), QMessageBox::Ok);
				return;
			}
		}
	}
	//QMessageBox::information(NULL, "NOSP",QString::number(type), QMessageBox::Ok);

	vector<unsigned char> vbuf;
	int iRet = 0;
	switch (type)
	{
	case TYPE_AUTH:
	{
		//QString ip = ui.lineEdit_srvIp->text();

		m_protocol.sendAuthData(vbuf);
	}
		break;
	case TYPE_SENDKEY:
		break;
	case TYPE_SETBAUDRATE:
		m_protocol.setBaudrate(((char)(ui.cmb_baudrate->currentIndex() + 1)), vbuf);
		break; 
	case TYPE_GETBAUDRATE:
		m_protocol.getBaudrate(vbuf);
		break;
	case TYPE_SENDDATA: // 发送串口命令
	//QMessageBox::information(NULL, "AAA0",(const char*)&vbuf[0], QMessageBox::Ok);
		if(!sendData(vbuf)) return;
	//QMessageBox::information(NULL, "AAA",(const char*)&vbuf[0], QMessageBox::Ok);
		break;
	case TYPE_GRABCOM:
		m_protocol.grabCom(vbuf);
		break;
	case TYPE_ANSWERGRABCOM:
		m_protocol.answerGrabCom(vbuf);
		break;
	case TYPE_GETKEYBOARDSTATE:
		m_protocol.getKeyboardState(vbuf);
		break;
	case TYPE_QUERYCOMDATA:
		m_curState.flag |= (FLAG_INQUERYTIME);
		m_protocol.queryComData(vbuf);
		break;
	case TYPE_CONFIRMGRABCOM:
		m_protocol.confirmGrabCom(vbuf);
		break;
	case TYPE_SENDUSERID:
	{
		vector<unsigned char> tmp;
		tmp.resize(4);
		int uid = qToBigEndian(m_userID.toInt());
		memcpy(&tmp[0], &uid, sizeof(int));
		m_protocol.sendUserID(tmp, vbuf);
	}
		break;
	default:
		break;
	}
    //most command need encrypt here
    /*
    A5 01 97 00 00 00 05 00 00 00 05 32 00 00 00 65
    A5019700000005000000053200
    */
	if (vbuf[COMMAND_LENGTH] != 0x32)
	{
		unsigned int len = vbuf.size() - COMMAND_LENGTH;
		for (int i = 0; i < 8 - (len % 8); ++i)
		{
			vbuf.push_back(0x00);
		}
		Encrypt::DesEncrypt(&g_desKeyEnc[1], &vbuf[COMMAND_LENGTH], &vbuf[COMMAND_LENGTH], len);
		len = qToBigEndian(len);
		memcpy(&vbuf[3+4], &len, 4);

		vbuf[2] = m_protocol.get_crc((unsigned char*)(&vbuf[COMMAND_LENGTH]), vbuf.size() - COMMAND_LENGTH);
	}
	m_socket->write((const char*)&vbuf[0], vbuf.size());

	if (type == TYPE_QUERYCOMDATA)
	{
		return;
	}
// 	QVector<char> buf;
// 	qbyte2StrA((unsigned char*)vbuf.data(), vbuf.size(), buf);
// 	ui.textEditSendOut->append("Sending:" + QString(buf.data()));

}

void comBySocket::connectServer()
{
	ui.textEditIn->append(_lang[CONNECTING].c_str());
	m_socket->abort();
	m_socket->connectToHost(m_curState.strIp,
		m_curState.strPort.toInt());
}

void comBySocket::disconnectServer()
{
	m_curState.flag &= (~FLAG_HASPRIVILEGE);
	killTimer(m_timerQueryInterval);
	if (m_socket->state() != QAbstractSocket::ConnectedState)
	{
		ui.textEditIn->append(_T("Server not connected."));
		return;
	}
	m_socket->disconnectFromHost();
}

void comBySocket::connected()
{
	ui.textEditIn->append(QString(_lang[CONNECTED].c_str()));

// 	doProcess(TYPE_AUTH);
	doProcess(TYPE_SENDUSERID);
}

void comBySocket::disconnected()
{
	m_curState.flag = 0;
	killTimer(m_timerQueryInterval);
//	setUiState(0);
	ui.textEditIn->append(QString(_lang[CONNECTION_BROKEN].c_str()));
}

void comBySocket::bytesWritten(qint64 bytes)
{
// 	qDebug() << "bytesWritten:" << bytes;
// 	ui.textEditIn->append(QString("bytesWritten:%1").arg(bytes));
}

// 设置 textEditIn 文本及其背景色
void comBySocket::setForntColor(int color)
{
	const QColor colors[] = {Qt::black,Qt::red,Qt::green,Qt::yellow,Qt::blue,Qt::magenta,Qt::cyan,Qt::white,Qt::black,Qt::black};
	if(color>=30 && color<=39){
		textColor = colors[color-30];
		ui.textEditIn->setTextColor(textColor);
	}
	else  if(color>=40 && color<=49){
		textBackColor = colors[color-40];
		ui.textEditIn->setTextBackgroundColor(textBackColor);
	}
}

// VT100 解析
QString comBySocket::backDataConvent(QString read)
{
	const QTextCursor::MoveOperation moCursor[] = {QTextCursor::Up,QTextCursor::Down,QTextCursor::Right,QTextCursor::Left};
	QString subRead = read;
	bool hasTail = false;
	int index = subRead.indexOf("\033[");
	int vtLen = 1;
	int x,y;
	int n;
	QTextCursor tc;
    tc = ui.textEditIn->textCursor();
	while(index>-1 && hasTail==false){
		QString tem;
		if(index>=0){
			ui.textEditIn->insertPlainText(subRead.left(index));
			ui.textEditIn->moveCursor(QTextCursor::EndOfLine);
			subRead = subRead.right(subRead.length()-index-2);
		}
		if(subRead.length()<1){
			hasTail = true;
			break;
		}
		switch(subRead[0].toAscii()){
		case 'K'://清除从光标到行尾的内容
			tc.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
			tc.removeSelectedText();
			vtLen = 1;
			break;
		case 's'://保存光标位置
			vtLen = 1;
			break;
		case'a'://恢复光标位置
			vtLen = 1;
			break;
		case'?':
			if(subRead.length()<4)
				hasTail = true;
			else{
				tem = subRead.mid(1,3);
				if(tem=="25l"){//隐藏光标
					ui.textEditIn->setCursor(Qt::BlankCursor);
				}else if(tem=="25h"){//显示光标
					ui.textEditIn->setCursor(Qt::ArrowCursor);
				}
				vtLen = 4;
			}
			break;
		default:
			n=1;
			while(subRead.length()>n && subRead[n]>='0' && subRead[n]<='9'){
				n++;
			}
			if(n>=subRead.length()){
				hasTail = true;
			}else{
				y = subRead.mid(0,n).toInt();
				switch(subRead[n].toAscii()){
				case 'm':
					switch(y){
					case 0://关闭所有属性
						ui.textEditIn->setFontUnderline(false);
						ui.textEditIn->setTextColor(Qt::black);
						ui.textEditIn->setTextBackgroundColor(Qt::white);
						ui.textEditIn->setCursor(Qt::ArrowCursor);
						vtLen = 2;
						break;
					case 1://设置为高亮
						ui.textEditIn->setTextBackgroundColor(textBackColor.lighter(150));
						vtLen = 2;
						break;
					case 4://下划线
						ui.textEditIn->setFontUnderline(true);
						vtLen = 2;
						break;
					case 5://闪烁
						//tc.set
						vtLen = 2;
						break;
					case 7://反显
						ui.textEditIn->setTextColor(textBackColor);
						ui.textEditIn->setTextBackgroundColor(textColor);
						vtLen = 2;
						break;
					case 8://消隐
						vtLen = 2;
						break;
					case 30://设置前景色 黑色
					case 31://设置前景色 红色
					case 32://设置前景色 绿色
					case 33://设置前景色 黄色
					case 34://设置前景色 蓝色
					case 35://设置前景色 紫色
					case 36://设置前景色 青色
					case 37://设置前景色 白色
					case 38://设置前景色 白色
					case 39://设置前景色 白色
					case 40://设置背景色 黑色
					case 41://设置背景色 红色
					case 42://设置背景色 绿色
					case 43://设置背景色 黄色
					case 44://设置背景色 蓝色
					case 45://设置背景色 紫色
					case 46://设置背景色 青色
					case 47://设置背景色 白色
					case 48://设置背景色 白色
					case 49://设置背景色 白色
						setForntColor(y);
						vtLen = 3;
						break;
					}
					break;
				case 'J':
					if(y==2 && n==1){//清屏
						inClear();
						vtLen = 2;
					}
					break;
				case 'A'://光标上移 n 行
				case 'B'://光标下移 n 行
				case 'C'://光标右移 n 行
				case 'D'://光标左移 n 行
					tc.movePosition(moCursor[subRead[0].toAscii()-'A'],QTextCursor::MoveAnchor,y);
					vtLen = n+1;
					break;
				case ';':
					x = n++;
					while(subRead.length()>n && subRead[n]>='0' && subRead[n]<='9'){
						n++;
					}
					if(n>=subRead.length()){
						hasTail = true;
					}else{
						//QString tem = subRead.mid(x+1,n-x-1);
						x = subRead.mid(x+1,n-x-1).toInt();
						vtLen = n+1;
						//QMessageBox::information(NULL,QString::number(y, 10)+","+QString::number(x, 10)+"("+tem+")",subRead, QMessageBox::Ok);
						if(subRead[n]=='H'){//设置光标位置
							ui.textEditIn->moveCursor(QTextCursor::Start);
							tc.movePosition(QTextCursor::Down,QTextCursor::MoveAnchor,y);
							tc.movePosition(QTextCursor::Right,QTextCursor::MoveAnchor,x);
						}else if(subRead[n]=='m'){
							setForntColor(x);
							setForntColor(y);
						}
					}
					break;
				}
			}
		}
		if(hasTail) break;
		int strlen = subRead.length()-vtLen;
		if(strlen>=0)
			subRead = subRead.right(strlen);
		index = subRead.indexOf("\033[");
	}
	if(hasTail)
		return "\033["+subRead;
	else{
		if(subRead.length()>0){
			if(subRead[subRead.length()-1] == '\033'){
				ui.textEditIn->insertPlainText(subRead.left(subRead.length()-1));
				return "\033";
			}
			ui.textEditIn->insertPlainText(subRead);
			//ui.textEditIn->append(subRead);
		}
	}
	ui.textEditIn->moveCursor(QTextCursor::End);
	return "";
	//if(subRead.length()<5)
		//QMessageBox::information(NULL,NULL,subRead, QMessageBox::Ok);
	//return saveRead;
}

/*
	鼠标键盘权限状态 返回允许
	a5031700000002000000021701
	返回不允许
	a5031700000002000000021700
	轮询返回
	a5032b00000002000000022b00
	抢占权限返回成功
	a5031400000002000000021400
	抢占结果通知 成功
	a5031600000002000000021600
*/
void comBySocket::readFromServer()
{
	QByteArray arr = m_socket->readAll();
	//arr = "\0xa5\0x03\0x89\0x00\0x00\0x00\0x70\0x00\0x00\0x00\0x70\0x46\0xed\0x00\0x5e\0x24\0xe7\0x5c\0xd5\0x8f\0xed\0xf8\0x9d\0xda\0x64\0x38\0xe7\0x52\0x98\0x99\0xc5\0xa9\0xad\0xdc\0xae\0x41\0xd6\0x06\0xd5\0x7a\0x48\0x84\0x66\0xd0\0x5b\0x39\0x19\0x36\0xca\0x1d\0x46\0x4b\0x7a\0xb5\0xc9\0xd6\0x93\0x79";
    char* p = (char*)arr.data();
    vector<unsigned char> vbuf;
    //TODO most command need decrypt here
	//if (((PCOMMAND)p)->encryptCount != ((PCOMMAND)p)->dataLength)
	//{
		uint32_t len = qToBigEndian(((PCOMMAND)p)->dataLength);
		Encrypt::DesDecrypt(&g_desKeyDec[1], (uint8_t*)(p + COMMAND_LENGTH), (uint8_t*)(p + COMMAND_LENGTH), len);
	//}
   
	QVector<char> buf;
	QString strRead;
		//	qbyte2StrA((unsigned char*)arr.data() + 12, arr.length() - 12, buf);
		//	strRead = QString(&buf[0]);
		//QMessageBox::information(NULL,"Back00",strRead, QMessageBox::Ok);
#define pos_command 11
	switch (arr[pos_command])
	{
	case 0x01://发送认证数据
		doProcess(TYPE_SENDKEY);
		return;
	case 0x02://发送密钥
		doProcess(TYPE_GETKEYBOARDSTATE);
		return;
	case 0x14://申请抢占鼠标键盘权限 回复
		if (arr[pos_command + 1] == (char)0x0001)
		{
			QMessageBox::warning(NULL, _T("warning"), QString(_lang[REQUEST_KM_FAILED].c_str()), QMessageBox::Ok);
		}
		else
		{
			ui.textEditIn->append(QString(_lang[REQUEST_KM_SUBMIT].c_str()));
		}
		return;
	case 0x15://鼠标键盘权限被抢占通知 21
		doProcess(TYPE_ANSWERGRABCOM);
		QMessageBox::warning(NULL, _T("warning"), QString(_lang[SP_WAS_USED_BY_OTHER].c_str()), QMessageBox::Ok);
		disconnectServer();
		return;
	case 0x16://申请鼠标键盘权限通过通知
		doProcess(TYPE_CONFIRMGRABCOM);
		if (arr[pos_command + 1] == (char)0x0000)
		{
			ui.textEditIn->append(QString(_lang[SP_MAY_USED].c_str()));
			m_curState.flag |= (FLAG_HASPRIVILEGE);
		}
		else
		{
			ui.textEditIn->append(QString(_lang[SP_REQUEST_FAILED].c_str()));
			disconnectServer();
		}
		return;
	case 23://鼠标键盘权限状态,用来表示串口使用权限
		if (arr[pos_command + 1] == (char)0x0000)
		{
			ui.textEditIn->append(QString(_lang[SP_CANT_USE].c_str()));
			m_curState.flag &= (~FLAG_HASPRIVILEGE);
			QMessageBox::StandardButton rb = QMessageBox::information(NULL, _T("ComBySocket"), QString(_lang[CONFIRM_USE_USING_SP].c_str()), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			if (rb == QMessageBox::Yes)
			{
				doProcess(TYPE_GRABCOM);
				return;
			}
			else
			{
				disconnectServer();
				return;
			}
		}
		else
		{
			m_curState.flag |= FLAG_HASPRIVILEGE;
//			setUiState(1);
		}
		break;
	case 40: //设置dongle的波特率
		if (arr[pos_command + 1] != (char)0)
		{
			ui.textEditIn->append(QString(_lang[SET_BAUD_RATE_FAILED].c_str()));
		}
		break;
	case 41://查询dongle的波特率
		if ((arr[pos_command + 1] & 0x0F) < (char)1 || (arr[pos_command + 1] & 0x0F) > (char)9)
		{
			ui.textEditIn->append(QString(_lang[UNKNOWN_BAUD_RATE].c_str()));
		}
		else
		{
			//g_baudrateArray 从0开始，所以要-1
			ui.textEditIn->append(QString(_lang[SE_BAUD_RATE].c_str()) + QString::number(g_baudrateArray[(arr[pos_command + 1] & 0x0F) - 1])+"\n");
		}
		break;
	case 42: // 发送串口数据
		//strRead = QString(&buf[pos_command + 1]);
		//ui.textEditIn->append("data:" + strRead);
		break;
	case 43:// 接收串口数据
		m_curState.flag &= ~(FLAG_INQUERYTIME);
		//没有数据
		if (arr[pos_command + 1] == (char)0)
		{
			return;
		}
		if (ui.radio_in_hex->isChecked())
		{
			qbyte2StrA((unsigned char*)arr.data() + 12, arr.length() - 12, buf);
			strRead = QString(&buf[0]);
		}
		else
		{
			//106 utf-8
			strRead = QTextCodec::codecForMib(106)->toUnicode(arr.data() + 12);
		}

		//QMessageBox::information(NULL,"Back00","Back0="+strRead, QMessageBox::Ok);
		// 不是盲打时，返回的命令不显现
		if(!curCmd.isEmpty() && !ui.pb_send->isChecked() && strRead.indexOf(curCmd)==0){
			strRead = strRead.right(strRead.length()-curCmd.length());
			curCmd = "";
		}

		strTail = backDataConvent(strTail+strRead);

		if(strTail.isEmpty()){// 保存输入行号和列号
			QTextCursor tc = ui.textEditIn->textCursor();
			curInputRow = tc.blockNumber();
			curInputStartCol = tc.columnNumber();
		}
		//ui.textEditIn->setText(ui.textEditIn->toPlainText() + strRead);
		break;
	case TYPE_SENDUSERID:
		doProcess(TYPE_GETKEYBOARDSTATE);
		break;
	default:
		break;
	}
#undef pos_command
	//收到命令回复后需要轮询
	m_timerQueryInterval = startTimer(400);
}

// void comBySocket::setUiState(int isEnable, int controlId)
// {
// 	return;
// // 	if (controlId)
// // 	{
// // 		switch (controlId)
// // 		{
// // 		case :
// // 			break;
// // 		default:
// //			break;
// // 		}
// // 	}
// // 	else
// 	{
// 		ui.pb_set->setEnabled(isEnable);
// 		ui.pb_get->setEnabled(isEnable);
// 		ui.pb_send->setEnabled(isEnable);
// 		ui.btn_grabCom->setEnabled(isEnable);
// 	}
// }

void comBySocket::timerEvent(QTimerEvent *event)
{
// 	if (event->timerId() == m_timerComInterval)
// 	{
// 		
// 	}
	if (event->timerId() == m_timerQueryInterval)
	{
		m_curState.flag |= FLAG_INQUERYTIME;
		doProcess(TYPE_QUERYCOMDATA);
	}
	//qDebug( "timer event, id %d",event->timerId() );
}


void comBySocket::displayTcpError(QAbstractSocket::SocketError socketErr)
{
	switch (socketErr)
	{
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		ui.textEditIn->setText(tr("The host was not found. Please check the "
			"host name and port settings."));
// 		QMessageBox::information(this, tr("ComBySocket"),
// 			tr("The host was not found. Please check the "
// 			"host name and port settings."));
		break;
	case QAbstractSocket::ConnectionRefusedError:
		ui.textEditIn->setText(tr("The connection was refused by the peer. "
			"Make sure the server is running, "
			"and check that the host name and port "
			"settings are correct."));

// 		QMessageBox::information(this, tr("ComBySocket"),
// 			tr("The connection was refused by the peer. "
// 			"Make sure the server is running, "
// 			"and check that the host name and port "
// 			"settings are correct."));
		break;
	default:
		ui.textEditIn->setText(tr("The following error occurred: %1.")
			.arg(m_socket->errorString()));

// 		QMessageBox::information(this, tr("ComBySocket"),
// 			tr("The following error occurred: %1.")
// 			.arg(m_socket->errorString()));
	}

}

