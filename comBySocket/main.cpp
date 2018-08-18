#include "combysocket.h"
#include <QtGui/QApplication>
#include <QMessageBox>
#include <qtextcodec.h>

//LV
unsigned char g_desKeyDec[17];
unsigned char g_desKeyEnc[17];
QString g_userName;

extern bool str2byteA(const char* pstr, vector<unsigned char>& vByte);

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QString param = argv[1];

	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	QString strIP, strPort, userID;

	int fpos = param.indexOf("{");
	QString paramClean = param.mid(fpos + 1, param.lastIndexOf("}") - 1 - fpos);
	QStringList strList = paramClean.split(",", QString::SkipEmptyParts);

	QString str;
	string strTmp;
	//QMessageBox::information(NULL, "","", QMessageBox::Ok);
	foreach(str, strList)
	{
		//		qDebug() << str;
		if (str.startsWith("desEncode"))
		{	
			strTmp = str.right(str.length() - str.indexOf(":") - 1).toLatin1();
			g_desKeyDec[0] = 8;
			vector<unsigned char> vBuf;
			str2byteA(strTmp.c_str(), vBuf);
			memcpy(&g_desKeyDec[1], &vBuf[0], 8);
		}
		else if (str.startsWith("desDecode"))
		{
			strTmp = str.right(str.length() - str.indexOf(":") - 1).toLatin1();//.toStdString();
			g_desKeyEnc[0] = 8;
			vector<unsigned char> vBuf;
			str2byteA(strTmp.c_str(), vBuf);
			memcpy(&g_desKeyEnc[1], &vBuf[0], 8);
		}else if (str.startsWith("ip"))
		{
			strIP = str.right(str.length() - str.indexOf(":") - 1);
		}
		else if (str.startsWith("portCOM"))
		{
			strPort = str.right(str.length() - str.indexOf(":") - 1);
		}
		else if (str.startsWith("userID"))
		{
			userID = str.right(str.length() - str.indexOf(":") - 1);
		}
		else if (str.startsWith("userNM"))
		{
			g_userName = str.right(str.length() - str.indexOf(":") - 1);
		}
		
	}

	comBySocket w;
	w.setParam(strIP, strPort,userID);
	w.show();
	return a.exec();
}
