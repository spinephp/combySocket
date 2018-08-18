#include "LanbeProtocol.h"
#include <QtEndian>

CLanbeProtocol::CLanbeProtocol()
{
	m_command.head = 0xA5;
	m_command.flag = 0x01;
}

CLanbeProtocol::~CLanbeProtocol()
{
}

int CLanbeProtocol::prepareCmd(unsigned char cmd, vector<unsigned char>& param, vector<unsigned char>& cmdBuf)
{
	cmdBuf.resize(COMMAND_LENGTH + 1 + param.size());
	memset(&cmdBuf[0], 0, cmdBuf.size());
	cmdBuf[0] = 0xA5;
	cmdBuf[1] = 0x01;
	cmdBuf[2] = 0x00;
	int pos = 3;
	int paramLength = qToBigEndian(1 + param.size());
	memcpy(&cmdBuf[pos], &paramLength, 4);
	pos += 4;
	memcpy(&cmdBuf[pos], &paramLength, 4);
	pos += 4;
	cmdBuf[pos++] = cmd;
	memcpy(&cmdBuf[pos], &param[0], param.size());
	cmdBuf[2] = get_crc((unsigned char*)(cmdBuf.data() + COMMAND_LENGTH), cmdBuf.size() - COMMAND_LENGTH);

	return 0;
}

int CLanbeProtocol::sendAuthData(vector<unsigned char>& cmdBuf)
{
	vector<unsigned char> param;
	param.push_back(0);
	return prepareCmd(1, param, cmdBuf);
}

int CLanbeProtocol::getKeyboardState(vector<unsigned char>& cmdBuf)
{
	vector<unsigned char> param;
	param.push_back(0);
	return prepareCmd(0x17, param, cmdBuf);
}

int CLanbeProtocol::setBaudrate(unsigned char baudrate,vector<unsigned char>& cmdBuf)
{
	vector<unsigned char> param;
	param.push_back(0xe0 | baudrate);
	return prepareCmd(0x28, param, cmdBuf);
}

int CLanbeProtocol::getBaudrate(vector<unsigned char>& cmdBuf)
{
	vector<unsigned char> param;
	param.push_back(0);
	return prepareCmd(0x29, param, cmdBuf);
}

int CLanbeProtocol::grabCom(vector<unsigned char>& cmdBuf)
{
	vector<unsigned char> param;
	param.push_back(0);
	return prepareCmd(0x14, param, cmdBuf);
}

int CLanbeProtocol::answerGrabCom(vector<unsigned char>& cmdBuf)
{
	vector<unsigned char> param;
	param.push_back(0);
	return prepareCmd(0x15, param, cmdBuf);
}

int CLanbeProtocol::confirmGrabCom(vector<unsigned char>& cmdBuf)
{
	vector<unsigned char> param;
	param.push_back(0);
	return prepareCmd(0x16, param, cmdBuf);
}

int CLanbeProtocol::sendData(vector<unsigned char>& data, vector<unsigned char>& cmdBuf)
{
	vector<unsigned char> param(data);
	return prepareCmd(0x2A, param, cmdBuf);
}

int CLanbeProtocol::queryComData(vector<unsigned char>& cmdBuf)
{
	vector<unsigned char> param;
	param.push_back(0);
	return prepareCmd(0x2B, param, cmdBuf);
}

int CLanbeProtocol::sendUserID(vector<unsigned char>& data, vector<unsigned char>& cmdBuf)
{
	vector<unsigned char> param(data);
	return prepareCmd(0x32, param, cmdBuf);
}


unsigned char CLanbeProtocol::get_crc(unsigned char* buf, const unsigned int len)
{
	if (buf == nullptr)
	{
		return 0;
	}
	unsigned char crc = 0;
	for (int i = 0; i < len; ++i)
	{
		crc += buf[i];
	}
	return crc;
}