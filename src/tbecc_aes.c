/*****************************************************************************
*
*      tbecc_aes.c
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
#include "tbecc_aes.h"
#include <stdio.h>

static const uchar sbox[] = {
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
  0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
  0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
  0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
  0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
  0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
  0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
  0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
  0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
  0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
  0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
  0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
  0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
  0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
  0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
  0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
  0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

static const uchar inv_sbox[] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
  0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
  0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
  0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
  0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
  0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
  0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
  0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
  0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
  0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
  0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
  0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
  0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
  0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
  0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
  0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
  0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

uint ByteSwap_32 (uint arg)
{
  uint ret = arg;
  uchar *tmp = (uchar *) & ret, t;

  t = tmp[0];
  tmp[0] = tmp[3];
  tmp[3] = t;

  t = tmp[1];
  tmp[1] = tmp[2];
  tmp[2] = t;

  return ret;
}

static void tbecc_sub_bytes (uchar * state_array)
{
  int i;

  for (i = 0; i < 16; ++i)
    state_array[i] = sbox[(state_array[i] >> 4) * 16 + (state_array[i] & 0x0F)];
}

static void tbecc_inv_sub_bytes (uchar * state_array)
{
  int i;

  for (i = 0; i < 16; ++i)
    state_array[i] = inv_sbox[(state_array[i] >> 4) * 16 + (state_array[i] & 0x0F)];
}

static void tbecc_shift_rows (uchar * state_array)
{
  uchar tmp[4];
  int i, j;

  for (i = 1; i < 4; ++i)
    {
      memcpy (tmp, &state_array[i * 4], 4);  // copy over to the temp

      for (j = 0; j < 4; ++j)
        state_array[i * 4 + j] = tmp[(j + i) % 4];
    }
}

static void tbecc_inv_shift_rows (uchar * state_array)
{
  uchar tmp[4];
  int i, j;

  for (i = 1; i < 4; ++i)
    {
      memcpy (tmp, &state_array[i * 4], 4);  // copy over to the temp

      for (j = 0; j < 4; ++j)
        state_array[i * 4 + j] = tmp[(j + (4 - i)) % 4];
    }
}

static void tbecc_mix_columns (uchar state[4][4])
{
  int i;
  uchar t[3];

  for (i = 0; i < 4; ++i)
    {
      t[0] = XTIME (state[0][i]) ^ XTIME (state[1][i]) ^ state[1][i] ^ state[2][i] ^ state[3][i];
      t[1] = XTIME (state[1][i]) ^ XTIME (state[2][i]) ^ state[2][i] ^ state[3][i] ^ state[0][i];
      t[2] = XTIME (state[2][i]) ^ XTIME (state[3][i]) ^ state[3][i] ^ state[0][i] ^ state[1][i];
      state[3][i] =
        XTIME (state[3][i]) ^ XTIME (state[0][i]) ^ state[0][i] ^ state[1][i] ^ state[2][i];

      state[0][i] = t[0];
      state[1][i] = t[1];
      state[2][i] = t[2];
    }
}

static uchar gmul (uchar a, uchar b)         // multiply a * b in the AES Galois field
{
  uchar res = 0;
  int i;

  for (i = 0; i < 8; ++i)
    {
      if (b & 0x01)
        res ^= a;
      a = XTIME (a);
      b >>= 1;
    }

  return res;
}

static void tbecc_inv_mix_columns (uchar state[4][4])
{
  int i;
  uchar t[3];

  for (i = 0; i < 4; ++i)
    {
      t[0] = gmul (state[0][i], 0x0E) ^ gmul (state[1][i], 0x0B) ^
	     gmul (state[2][i], 0x0D) ^ gmul (state[3][i], 0x09);
      t[1] = gmul (state[1][i], 0x0E) ^ gmul (state[2][i], 0x0B) ^
	     gmul (state[3][i], 0x0D) ^ gmul (state[0][i], 0x09);
      t[2] = gmul (state[2][i], 0x0E) ^ gmul (state[3][i], 0x0B) ^
	     gmul (state[0][i], 0x0D) ^ gmul (state[1][i], 0x09);
      state[3][i] = gmul (state[3][i], 0x0E) ^ gmul (state[0][i], 0x0B) ^
	      	    gmul (state[1][i], 0x0D) ^ gmul (state[2][i], 0x09);

      state[0][i] = t[0];
      state[1][i] = t[1];
      state[2][i] = t[2];
    }
}

static void tbecc_add_round_key (uint * w, int round, uchar state[4][4])
{
  uchar *p = (uchar *) & w[round * 4];
  int i, j;

  for (i = 0; i < 4; ++i)
    {
      for (j = 0; j < 4; ++j)
        state[j][i] ^= p[i * 4 + (4 - j - 1)];
    }
}

static uint tbecc_sub_word (uint arg)
{
  uchar *t1 = (uchar *) & arg;
  uint ret;
  uchar *t2 = (uchar *) & ret;

  t2[0] = sbox[(t1[0] >> 4) * 16 + (t1[0] & 0x0F)];
  t2[1] = sbox[(t1[1] >> 4) * 16 + (t1[1] & 0x0F)];
  t2[2] = sbox[(t1[2] >> 4) * 16 + (t1[2] & 0x0F)];
  t2[3] = sbox[(t1[3] >> 4) * 16 + (t1[3] & 0x0F)];

  return ret;
}

static void tbecc_aes_set_key (uchar * key, int key_len, uint * w)
{
  uint tmp;
  int i;
  int Nk = key_len / 4;         // key size in words
  int Nr = Nk + 6;              // number of rounds
  uint rcon[] = {
	0x01000000, 0x02000000,
	0x04000000, 0x08000000,
	0x10000000, 0x20000000,
	0x40000000, 0x80000000,
	0x1b000000, 0x36000000
  };

  // copy over the key directly to the expanded key
  memcpy (w, key, key_len);

  for (i = 0; i < Nk; ++i)
    w[i] = ByteSwap_32 (w[i]);

  for (i = Nk; i < 4 * (Nr + 1); ++i)
    {
      tmp = w[i - 1];

      if (i % Nk == 0)
        tmp = tbecc_sub_word (ROTL_32 (tmp, 8)) ^ rcon[(i / Nk) - 1];

      else if (Nk > 6 && i % Nk == 4)
        tmp = tbecc_sub_word (tmp);

      w[i] = w[i - Nk] ^ tmp;
    }
}

void tbecc_aes_encrypt_block (uchar * block, uchar * key, int key_len)
{
  int i, j;
  int Nr = key_len / 4 + 6;
  uint w[72];                   // max expanded key
  uchar state[4][4];            // state as a 2D array

  // expand the key
  tbecc_aes_set_key (key, key_len, w);

  // copy the block over to the state
  for (i = 0; i < 4; ++i)
    {
      for (j = 0; j < 4; ++j)
        state[j][i] = block[i * 4 + j];
    }

  // add round key
  tbecc_add_round_key (w, 0, state);    // Section 5.1.4 FIPS-197

  // perform round function 10 - 14 times
  for (i = 0; i < Nr - 1; ++i)
    {
      tbecc_sub_bytes ((uchar *) state);     // Section 5.1.1 FIPS-197
      tbecc_shift_rows ((uchar *) state);    // Section 5.1.2 FIPS-197
      tbecc_mix_columns (state);   // Section 5.1.3 FIPS-197
      tbecc_add_round_key (w, i + 1, state);
    }

  // perform final round
  tbecc_sub_bytes ((uchar *) state);    // Section 5.1.1 FIPS-197
  tbecc_shift_rows ((uchar *) state);   // Section 5.1.2 FIPS-197
  tbecc_add_round_key (w, i + 1, state);

  // copy the result out
  for (i = 0; i < 4; ++i)
    {
      for (j = 0; j < 4; ++j)
        block[i * 4 + j] = state[j][i];
    }
}

void tbecc_aes_decrypt_block (uchar * block, uchar * key, int key_len)
{
  int i, j;
  int Nr = key_len / 4 + 6;
  uint w[72];                   // max expanded key
  uchar state[4][4];            // state as a 2D array

  // expand the key
  tbecc_aes_set_key (key, key_len, w);

  // copy the block in the state
  for (i = 0; i < 4; ++i)
    {
      for (j = 0; j < 4; ++j)
        state[j][i] = block[i * 4 + j];
    }

  tbecc_add_round_key (w, Nr, state);   // Section 5.1.4 FIPS-197

  // perform round function 10 - 14 times
  for (i = Nr; i > 1; --i)
    {
      tbecc_inv_shift_rows ((uchar *) state);     // Section 5.3.1 FIPS-197
      tbecc_inv_sub_bytes ((uchar *) state); // Section 5.3.2 FIPS-197
      tbecc_add_round_key (w, i - 1, state);
      tbecc_inv_mix_columns (state);    // Section 5.3.3 FIPS-197
    }

  // perform final round
  tbecc_inv_shift_rows ((uchar *) state);    // Section 5.1.2 FIPS-197
  tbecc_inv_sub_bytes ((uchar *) state);     // Section 5.1.1 FIPS-197
  tbecc_add_round_key (w, 0, state);

  // copy the result out
  for (i = 0; i < 4; ++i)
    {
      for (j = 0; j < 4; ++j)
        block[i * 4 + j] = state[j][i];
    }
}
