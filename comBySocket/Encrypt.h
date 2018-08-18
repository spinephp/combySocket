/*****************************************************************
 * COPYRIGHT (C) 2009 - 2014, Beijing LANBE Technologies Co,. Ltd.
 * File Name    : Encypt.h
 *
 * Description  : Declaration of  Encrypt function.
 *
 *
 * History:
 * Date           Author       Notes
 * 2014-10-29     Eddie Zhu    The first version.
     
 ****************************************************************/

 #ifndef _ENCRYPT_H_
 #define _ENCRYPT_H_

#include <inttypes.h>
//#define DO_ENCRYPT

namespace Encrypt
{
/**
	@param pKey		[in]	: des key 8bytes length
	@param pText	[in]	: plain data
	@param pCypher	[out]	: encrypted data, buffer should be large enough for output.
					if pText is multiple of 8, then pCypher should be pText length + 8
	@param len		[in/out]: plain data length when in, crypted data length when out
	@return 
		true :success
		false:failure
*/
bool DesEncrypt(uint8_t *pKey, uint8_t *pText, uint8_t *pCypher, uint32_t& len);

bool DesDecrypt(uint8_t *pKey, uint8_t *pCypher, uint8_t *pText, uint32_t& len);

bool AesEncrypt(uint8_t *pKey, uint8_t *pText, uint8_t *pCypher, uint32_t len);

bool AesDecrypt(uint8_t *pKey, uint8_t *pCypher, uint8_t *pText, uint32_t len);
}

 #endif
