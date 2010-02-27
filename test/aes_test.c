#include "tbecc_aes.h"

#include <stdio.h>

int
main ()
{
  uchar aes_input[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
  uchar tmp[sizeof (aes_input)];

  // AES-128 test vectors
  uchar key_128[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
  uchar encrypt_128[] = { 0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a };

  // AES-192 test vectors
  uchar key_192[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };
  uchar encrypt_192[] = { 0xdd, 0xa9, 0x7c, 0xa4, 0x86, 0x4c, 0xdf, 0xe0, 0x6e, 0xaf, 0x70, 0xa0, 0xec, 0x0d, 0x71, 0x91 };

  // AES-256 test vectors
  uchar key_256[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
  uchar encrypt_256[] = { 0x8e, 0xa2, 0xb7, 0xca, 0x51, 0x67, 0x45, 0xbf, 0xea, 0xfc, 0x49, 0x90, 0x4b, 0x49, 0x60, 0x89 };

  // test 128-bit keys
  memcpy (tmp, aes_input, sizeof (aes_input));
  tbecc_aes_encrypt_block (tmp, key_128, sizeof (key_128));
  if (memcmp (tmp, encrypt_128, sizeof (encrypt_128)) == 0)
    printf ("128 BIT ENCRYPT WORKED\n");
  else
    printf ("128 BIT ENCRYPT FAILED\n");

  memcpy (tmp, encrypt_128, sizeof (encrypt_128));
  tbecc_aes_decrypt_block (tmp, key_128, sizeof (key_128));
  if (memcmp (tmp, aes_input, sizeof (aes_input)) == 0)
    printf ("128 BIT DECRYPT WORKED\n");
  else
    printf ("128 BIT DECRYPT FAILED\n");



  // test 192-bit keys
  memcpy (tmp, aes_input, sizeof (aes_input));
  tbecc_aes_encrypt_block (tmp, key_192, sizeof (key_192));
  if (memcmp (tmp, encrypt_192, sizeof (encrypt_192)) == 0)
    printf ("192 BIT ENCRYPT WORKED\n");
  else
    printf ("192 BIT ENCRYPT FAILED\n");

  memcpy (tmp, encrypt_192, sizeof (encrypt_192));
  tbecc_aes_decrypt_block (tmp, key_192, sizeof (key_192));
  if (memcmp (tmp, aes_input, sizeof (aes_input)) == 0)
    printf ("192 BIT DECRYPT WORKED\n");
  else
    printf ("192 BIT DECRYPT FAILED\n");


  // test 256-bit keys
  memcpy (tmp, aes_input, sizeof (aes_input));
  tbecc_aes_encrypt_block (tmp, key_256, sizeof (key_256));
  if (memcmp (tmp, encrypt_256, sizeof (encrypt_256)) == 0)
    printf ("256 BIT ENCRYPT WORKED\n");
  else
    printf ("256 BIT ENCRYPT FAILED\n");

  memcpy (tmp, encrypt_256, sizeof (encrypt_256));
  tbecc_aes_decrypt_block (tmp, key_256, sizeof (key_256));
  if (memcmp (tmp, aes_input, sizeof (aes_input)) == 0)
    printf ("256 BIT DECRYPT WORKED\n");
  else
    printf ("256 BIT DECRYPT FAILED\n");



  return 0;
}
