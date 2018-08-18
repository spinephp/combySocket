/*****************************************************************
 * COPYRIGHT (C) 2009 - 2014, Beijing LANBE Technologies Co,. Ltd.
 * File Name    : Encypt.h
 *
 * Description  : Implementation of  Encrypt function.
 *
 *
 * History:
 * Date           Author       Notes
 * 2014-10-29     Eddie Zhu    The first version.
     
 ****************************************************************/
#include <stdint.h>
#include "Encrypt.h"

extern "C" {
#include "aes.h"
#include "d3des.h"

}

bool Encrypt::DesEncrypt(uint8_t* pKey, uint8_t* pText, uint8_t* pCypher, uint32_t& len)
{
	unsigned int i;
	pText[len] = 0x80;
	++len;
	while(len%8)
	{
		pText[len++] = 0x00;
	}
	deskey(pKey, EN0);
	for (i = 0; i < len; i+= 8)
	{
		des(pText + i,  pCypher + i);
	}
	return true;
}

/*****************************************************************
* Description:    Dncrypt cypher with des
* Input:
* @param  :       des key 
* @param  : 	  cypher to dncrypt
* @param  : 	  buffer to store text
* @param  : 	  cypher length

* return:         true :success
			      false:failure
*****************************************************************/
bool Encrypt::DesDecrypt(unsigned char *pKey, unsigned char *pCypher, unsigned char *pText, unsigned int& len)
{
	unsigned int i;

	if ((len & 0x07) != 0)
	{
		return false;
	}
	deskey(pKey, DE1);
	for (i = 0; i < len; i+= 8)
	{
		des(pCypher + i, pText + i);
	}
	for (i = 0; i < 8; ++i)
	{
		if(pText[len - 1 - i] != 0x00 && pText[len - 1 - i] != 0x80)
		{
			break;
		}
	}
	if (i>8)
	{
		return false;
	}
	len -= i;
	return true;
}

/*****************************************************************
* Description:    Encrypt text with aes
* Input:
* @param  :       aes key 
* @param  : 	  text to encrypt
* @param  : 	  buffer to store cypher
* @param  : 	  text length

* return:         true :success
			      false:failure
*****************************************************************/
bool Encrypt::AesEncrypt(uint8_t *pKey, uint8_t *pText, uint8_t *pCypher, uint32_t len)
{
	unsigned int i;

	if ((len & 0x0f) != 0)
	{
		return false;
	}

	for (i = 0; i < len; i += 16)
	{
		AES128_ECB_encrypt(pText + i, pKey, pCypher + i);
	}

	return true;
}

/*****************************************************************
* Description:    Dncrypt cypher with aes
* Input:
* @param  :       aes key 
* @param  : 	  cypher to dncrypt
* @param  : 	  buffer to store text
* @param  : 	  cypher length

* return:         true :success
			      false:failure
*****************************************************************/
bool Encrypt::AesDecrypt(unsigned char *pKey, unsigned char *pCypher, unsigned char *pText, unsigned int len)
{
	unsigned int i;

	if ((len & 0x0f) != 0)
	{
		return false;
	}

	for (i = 0; i < len; i += 16)
	{
		AES128_ECB_decrypt(pCypher + i, pKey, pText + i);
	}

	return true;
}
	

