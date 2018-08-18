#include <QVector>
#include "common.h"

/*
QVector<char> vBuf;
qbyte2StrA((const unsigned char*)by.constData(),128,vBuf);
QString str = &vBuf[0];
qDebug()<<"readPendingDatagramsIn: != 0xF0:"<<str;
*/
void qbyte2StrA(const unsigned char* bArr, const unsigned long size, QVector<char>& vstr)
{
	vstr.clear();
	vstr.reserve(500);
	if (!size)
	{
		vstr.push_back('\0');
		return;
	}
	char hexval[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	for (unsigned long j = 0; j < size; j++)
	{
		vstr.push_back(hexval[((bArr[j] >> 4) & 0x0F)]);
		vstr.push_back(hexval[(bArr[j]) & 0x0F]);
		vstr.push_back(' ');
	}
	vstr.push_back('\0');
}

/*
Convert string to byte vector
str: [in] string need convert
byte: [in] byte vector for store
return: false is successful, otherwise is true.
*/
bool str2byte(const TCHAR* pstr, vector<unsigned char>& vByte)
{
	vByte.clear();
	string str = pstr;
	size_t fpos;
	while (string::npos != (fpos = str.find_first_of(_T(" \t\n\r"))))
	{
		str.erase(fpos, 1);
	}
	unsigned char uc = 0;
	int iTmp = 0;
	for (string::const_iterator it = str.begin(); it != str.end(); it += 2)
	{
		if (0 >= _stscanf_s((const TCHAR*)&(*it), _T("%02X"), &iTmp))
		{
			return true;
		}
		vByte.push_back((unsigned char)iTmp);
	}
	return false;
}

bool str2byteA(const char* pstr, vector<unsigned char>& vByte)
{
	vByte.clear();
	string str = pstr;
	size_t fpos;
	while (string::npos != (fpos = str.find_first_of((" \t\n\r"))))
	{
		str.erase(fpos, 1);
	}
	unsigned char uc = 0;
	int iTmp = 0;
	for (string::const_iterator it = str.begin(); it != str.end(); it += 2)
	{
		if (0 >= sscanf_s((const char*)&(*it), ("%02X"), &iTmp))
		{
			return true;
		}
		vByte.push_back((unsigned char)iTmp);
	}
	return false;
}

void strTrim(string& s)
{
	s.erase(0, s.find_first_not_of((" \t\f\v\n\r")));
	s.erase(s.find_last_not_of((" \t\f\v\n\r")) + 1);
}