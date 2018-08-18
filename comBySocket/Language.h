#pragma once

#include "common.h"

// 注释后，生成中文版
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
string _lang[] = {"尚未获得串口使用权限",
				  "轮询命令没有响应",
				  "没有数据可以发送",
				  "发送数据最大为512字节",
				  "16进制数据长度不合法",
				  "发送数据可能不是合法16进制数",
				  "已连接\n",
				  "已断开连接\n",
				  "申请抢占鼠标键盘权限失败\n",
				  "抢占使用串口已提交，请等待操作结果",
				  "串口被抢占，已停止使用",
				  "抢占使用串口已成功，可以使用串口",
				  "抢占使用串口失败，已停止使用串口",
				  "WARNING:不能使用串口",
				  "串口已占用，是否抢占？",
				  "设置波特率失败",
				  "未定义的波特率",
				  "串口波特率:",

				  "波特率:",
				  "设置波特率",
				  "获得波特率",
				  "盲打",
				  "输入:",
				  "清空",
				  "十六进制",
				  "字符串",
				  "输出:",

				  "连接中...",
				  "发送"
};
#endif