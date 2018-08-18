#pragma once
#include <vector>
using namespace std;

#pragma pack(push,1)
typedef struct typeCommand
{
	unsigned char	head;
	unsigned char	flag;
	unsigned char	crc;
	int				encryptCount;
	int				dataLength;
}COMMAND, *PCOMMAND;
#pragma pack(pop)

#define COMMAND_LENGTH	11

#define CMD_GRABCOM					0x14
#define CMD_ANSWERGRABCOM			0x15

class CLanbeProtocol
{
public:
	CLanbeProtocol();
	~CLanbeProtocol();
private:
	COMMAND	m_command;

public:
	unsigned char get_crc(unsigned char* buf, const unsigned int len);
	int prepareCmd(unsigned char cmd, vector<unsigned char>& param, vector<unsigned char>& cmdBuf);
	// keyboard/mouse state
	int getKeyboardState(vector<unsigned char>& cmd);

	// com port command
	int setBaudrate(unsigned char baudrate, vector<unsigned char>& cmdBuf);
	int getBaudrate(vector<unsigned char>& cmdBuf);
	int sendData(vector<unsigned char>& data, vector<unsigned char>& cmdBuf);
	int grabCom(vector<unsigned char>& cmdBuf);
	int answerGrabCom(vector<unsigned char>& cmdBuf);
	int confirmGrabCom(vector<unsigned char>& cmdBuf);
	int sendAuthData(vector<unsigned char>& cmdBuf);
	int queryComData(vector<unsigned char>& cmdBuf);
	int sendUserID(vector<unsigned char>& data, vector<unsigned char>& cmdBuf);
};

