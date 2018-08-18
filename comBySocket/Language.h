#pragma once

#include "common.h"

// ע�ͺ��������İ�
#define LANG_ENG

enum LANG_KEY
{
	NO_ACCESS_SERIAL_PORT = 0,
	POLL_CMD_NO_RESP,
	NO_DATA_FOR_SEND,
	MAX_PACKAGE_IS_512,
	HEX_DATA_LEN_INVALID,
	DATA_IS_NOT_VALID_HEX_DATA,
	CONNECTED,
	CONNECTION_BROKEN,
	REQUEST_KM_FAILED,
	REQUEST_KM_SUBMIT,
	SP_WAS_USED_BY_OTHER,
	SP_MAY_USED,
	SP_REQUEST_FAILED,
	SP_CANT_USE,
	CONFIRM_USE_USING_SP,
	SET_BAUD_RATE_FAILED,
	UNKNOWN_BAUD_RATE,
	SE_BAUD_RATE,

	MAIN_BAUD_RATE,
	MAIN_SET_BAUD_RATE,
	MAIN_GET_BAUD_RATE,
	MAIN_SEND,
	MAIN_INPUT,
	MAIN_BTN_CLEAR,
	MAIN_HEX,
	MAIN_STRING,
	MAIN_OUTPUT,

	CONNECTING,
	MAIN_SENDA,
};

#ifdef LANG_ENG
string _lang[] = {"Not yet available for serial using",
				  "The polling command is not responding",
				  "No data can be sent",
				  "Send data up to 512 bytes",
				  "Hexadecimal data length is not legal",
				  "The sending data may not be a legal hexadecimal number",
				  "connected\n",
				  "Has been disconnected",
				  "Apply to grab the mouse and keyboard permissions failed",
				  "To seize the use of the serial port has been submitted, please wait for the results of the operation",
				  "The serial port is preempted and has been discontinued",
				  "To seize the use of serial port has been successful, you can use the serial port",
				  "Fair to seize the use of serial port , has stopped using the serial port",
				  "WARNING: Can not use serial port",
				  "Serial port has occupied, whether to seize",
				  "Set baud rate to fail",
				  "Undefined baud rate",
				  "Serial baud rate:",

				  "Baudrate:",
				  "SetBaudrate",
				  "GetBaudrate",
				  "Blind",
				  "Input:",
				  "Clear",
				  "Hex",
				  "String",
				  "Output:",

				  "Connecting...",
				  "Send"
};
#else
string _lang[] = {"��δ��ô���ʹ��Ȩ��",
				  "��ѯ����û����Ӧ",
				  "û�����ݿ��Է���",
				  "�����������Ϊ512�ֽ�",
				  "16�������ݳ��Ȳ��Ϸ�",
				  "�������ݿ��ܲ��ǺϷ�16������",
				  "������\n",
				  "�ѶϿ�����\n",
				  "������ռ������Ȩ��ʧ��\n",
				  "��ռʹ�ô������ύ����ȴ��������",
				  "���ڱ���ռ����ֹͣʹ��",
				  "��ռʹ�ô����ѳɹ�������ʹ�ô���",
				  "��ռʹ�ô���ʧ�ܣ���ֹͣʹ�ô���",
				  "WARNING:����ʹ�ô���",
				  "������ռ�ã��Ƿ���ռ��",
				  "���ò�����ʧ��",
				  "δ����Ĳ�����",
				  "���ڲ�����:",

				  "������:",
				  "���ò�����",
				  "��ò�����",
				  "ä��",
				  "����:",
				  "���",
				  "ʮ������",
				  "�ַ���",
				  "���:",

				  "������...",
				  "����"
};
#endif