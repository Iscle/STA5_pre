/*
 *  Copyright (C) 2014 STMicroelectronics
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/**
 * @file    CSE_AES_HW_Modes.h
 * @brief   CSE HW natively supported AES modes.
 * @details Set of functions used to encrypt and decrypt data with AES modes
 *          supported natively by CSE AES Engine (ECB and CBC)
 *          As well as functions to compute and verify a MAC using CMAC.
 *
 *
 * @addtogroup CSE_driver
 * @{
 * @addtogroup API Functions
 * @{
 */

#ifndef _CSE_AES_HW_MODES_H_
#define _CSE_AES_HW_MODES_H_

#include "cse_typedefs.h"

/*============================================================================*/
/**
 * @brief	   Performs AES encryption in ECB mode
 * @details        Encrypts the specified number of AES blocs from source to
 *                 destination
 *
 * @param[in]      key_idx	key index value
 * @param[in]      *psrc        pointer to the buffer to encrypt (plaintext)
 * @param[in]      block_nb     number of AES blocks to encrypt (one block is
 *                              16 bytes)
 *
 * @param[out]     *pdst        pointer to the destination buffer where to store
 *				result (cyphertext)
 *
 * @param[in]      ext_key_set	1 to use extended key set, 0 for normal key set
 *
 * @return         Error code
 * @retval 0       When encryption was performed properly
 * @retval 1..21   In case of error - the error code values are the CSE returned
 *                 ones
 *
 * @pre		   The specified key security flags must allow a encryption use
 *                 for the operation to succeed
 *
 * @note           The function is blocking and waits for operation completion
 */
extern uint32_t cse_aes_encrypt_ecb(vuint32_t key_idx, vuint32_t *psrc,
				    vuint32_t *pdst, vuint32_t block_nb,
				    uint32_t ext_key_set);

/*============================================================================*/
/**
 * @brief	Performs AES decryption in ECB mode
 * @details	Decrypts the specified number of AES blocs from source to
 *		destination
 *
 * @param[in]   key_idx		key index value
 * @param[in]   *psrc		pointer to the buffer to decrypt (cyphertext)
 * @param[in]	block_nb	number of AES blocks to encrypt (one block is
 *				16 bytes)
 *
 * @param[out]	*pdst           pointer to the destination buffer where to store
 *				result (plaintext)
 *
 * @param[in]	ext_key_set	1 to use extended key set, 0 for normal key set
 *
 * @return	Error code
 * @retval	0	When decryption was performed properly
 * @retval	1..21	In case of error - the error code values are the CSE
 *			returned ones
 *
 * @pre		The specified key security flags must allow a encryption
 *		use for the operation to succeed
 *
 * @implements	cf. CSE decryption function
 *
 * @note	The function is blocking and waits for operation completion
 */
extern uint32_t cse_aes_decrypt_ecb(vuint32_t key_idx, vuint32_t *psrc,
				    vuint32_t *pdst, vuint32_t block_nb,
				    uint32_t ext_key_set);

/*============================================================================*/
/**
 * @brief	Performs AES encryption in CBC mode
 * @details	Encrypts the specified number of AES blocs from source to
 *		destination
 *
 * @param[in]	key_idx		key index value
 * @param[in]	*psrc		pointer to the buffer to encrypt (plaintext)
 * @param[in]	*piv		pointer to the initialization vector to use
 * @param[in]	block_nb	number of AES blocks to encrypt (one block is
 *				16 bytes)
 *
 * @param[out]	*pdst		pointer of the destination buffer where to store
 *				result (cyphertext)
 *
 * @param[in]	ext_key_set	1 to use extended key set, 0 for normal key set
 *
 * @return	Error code
 * @retval	0	When encryption was performed properly
 * @retval	1..21   In case of error - the error code values are the CSE
 *			returned ones
 *
 * @pre		The specified key security flags must allow a encryption use
 *		for the operation to succeed
 *
 * @implements	cf. CSE encryption function
 *
 * @note	The function is blocking and waits for operation completion
 */
extern uint32_t cse_aes_encrypt_cbc(vuint32_t key_idx, vuint32_t *psrc,
				    vuint32_t *pdst, vuint32_t *piv,
				    vuint32_t block_nb, uint32_t ext_key_set);

/*============================================================================*/
/**
 * @brief	Performs AES decryption in CBC mode
 * @details	Decrypts the specified number of AES blocks from source to
 *		destination
 *
 * @param[in]	key_idx		key index value
 * @param[in]	*psrc		pointer to the buffer to decrypt (cyphertext)
 * @param[in]	*piv		pointer to the initialization vector to use
 * @param[in]	block_nb	number of AES blocks to encrypt (one block is
 *				16 bytes)
 *
 * @param[out]	*pdst		pointer to the destination buffer where to store
 *				result (plaintext)
 *
 * @param[in]	ext_key_set	1 to use extended key set, 0 for normal key set
 *
 * @return	Error code
 * @retval	0       When decryption was performed properly
 * @retval	1..21   In case of error - the error code values are the CSE
 *			returned ones
 *
 * @pre		The specified key security flags must allow a encryption use
 *		for the operation to succeed
 *
 * @implements	cf. CSE decryption function
 *
 * @note	The function is blocking and waits for operation completion
 */
extern uint32_t cse_aes_decrypt_cbc(uint32_t key_idx, vuint32_t *psrc,
				    vuint32_t *pdst, uint32_t *piv,
				    uint32_t block_nb, uint32_t ext_key_set);

/*============================================================================*/
/**
 * @brief	Performs AES based CMAC computation
 * @details	Computes the MAC of message of xxx bits using the specified
 *		Key
 *
 * @param[in]	key_idx		key index value
 * @param[in]	*pbitlength	pointer to 64bit length of message in bits
 *				( !!! address of the location of the length
 *				variable, not the value )
 * @param[in]	*pmessage	pointer to the message
 *
 * @param[out]	output_mac      pointer to the buffer location to store computed
 *		MAC
 *
 * @param[in]	ext_key_set	1 to use extended key set, 0 for normal key set
 *
 * @return	Error code
 * @retval	0	   When MAC was computed properly
 * @retval	1..21   In case of error - the error code values are the CSE
 *			returned ones
 *
 * @pre		The specified key security flags must allow a MAC use for
 *		the operation to succeed
 *
 * @note	The function is blocking and waits for operation completion
 */
extern uint32_t cse_aes_generate_mac(vuint32_t key_idx, vuint64_t *pbitlength,
				     vuint32_t *pmessage, vuint32_t *output_mac,
				     uint32_t ext_key_set);

/*============================================================================*/
/**
 * @brief	Performs AES based CMAC verification
 * @details	Computes the MAC of message of xxx bits using the specified
 *		Key and compares it with the provided reference
 *
 * @param[in]	key_idx		key index value
 * @param[in]	*plength	pointer to 64bit length of message in bits
 *				( !!! address of the location of the length
 *				variable, not the value )
 * @param[in]	*pmessage	pointer to the message
 * @param[in]	input_mac	pointer to the reference MAC to compare with
 * @param[in]	mac_length	length of message in bits (value, not pointer)
 *
 * @param[out]	status		pointer to a variable where the MAC
 *				verification status will be stored
 *
 * @param[in]	ext_key_set	1 to use extended key set, 0 for normal key set
 *
 * @return	Error code
 * @retval	0	When MAC was computed & checked properly - DOES NOT
 *			TELL IF reference MAC is matching the computed one
 * @retval	1..21   In case of error - the error code values are the CSE
 *			returned ones
 *
 * @pre		The specified key security flags must allow a MAC use for the
 *		operation to succeed
 *
 * @note	The function is blocking and waits for operation completion
 */
extern uint32_t cse_aes_verify_mac(vuint32_t key_idx, vuint64_t *plength,
				   vuint32_t *pmessage, vuint32_t *input_mac,
				   vuint32_t mac_length, vuint32_t *status,
				   uint32_t ext_key_set);

#endif //_CSE_AES_HW_MODES_H_

/**
 * @}
 * @}
 */