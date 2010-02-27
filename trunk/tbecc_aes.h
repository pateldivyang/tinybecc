/*****************************************************************************
 *
 *      tbecc_aes.h
 *
 *      This file is part of TinyBECC.
 *
 *      TinyBECC is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      TinyBECC is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with TinyBECC.  If not, see <http://www.gnu.org/licenses/>.
*
 *****************************************************************************/
#ifndef _TBECC_AES_H
#define _TBECC_AES_H

#include "tinyBECC.h"
#include "memory.h"

#define ROTL_32(x,y) (((x) << (y)) | ((x) >> (32-(y))))
#define XTIME(x) ( x & 0x80 ? ((x << 1) ^ 0x1B) : (x << 1))

/**
 * Encrypts a block of 16 bytes using the key found at key.
 * @param block The block to encrypt.
 * @param key The key used to encrypt the block.
 * @param key_len The length of the key in bytes: 16, 24, or 32.
 * @return -1 if an error occurs.
 */
void tbecc_aes_encrypt_block(uchar *block, uchar *key, int key_len);

/**
* Decrypts a block of 16 bytes using the key found at key.
* @param block The block to decrypt.
* @param key The key used to decrypt the block.
* @param key_len The length of the key in bytes: 16, 24, or 32.
* @return -1 if an error occurs.
*/
void tbecc_aes_decrypt_block(uchar *block, uchar *key, int key_len);

#endif
