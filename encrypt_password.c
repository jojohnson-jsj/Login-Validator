#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void hash_and_store(char *password_to_be_encrypted)
{
  int i;
  const char *s = password_to_be_encrypted;

  // Creates a string containing the hexadecimal SHA256 value of the encrypted password
  unsigned char *encrypted_password = SHA256(s, strlen(s), 0);

  // Prints the encrypted password
  printf("\nThe encrypted password (case sensitive) is: ");
  for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    printf("%02x", encrypted_password[i]);
  }
  printf("\n");
}

int main(void)
{
  char password_to_be_encrypted[1000];

  printf("Please Enter The Password You Desire To Encrypt\n");
  scanf("%s", password_to_be_encrypted);

  hash_and_store(password_to_be_encrypted);

  return 0;
}