#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <json-c/json.h>


int config_parser(char *config, char *username_attempt, char *password_attempt_hash)
{
  FILE *fptr;
  char buffer[1024];
  struct json_object *parsed_json;
  struct json_object *username_object;
  struct json_object *username;
  struct json_object *password_hash_object;
  struct json_object *password_hash;
  size_t n_usernames;
  size_t n_password_hashes;
  int i;

  // Checks to see if config file given in main is NULL
  if ((fptr = fopen(config, "r")) == NULL)
  {
    printf("Invalid config file\n");
    exit(0);
  }

  fread(buffer, 1024, 1, fptr);
  fclose(fptr);

  // Parses config file
  parsed_json = json_tokener_parse(buffer);

  json_object_object_get_ex(parsed_json, "username", &username_object);
  json_object_object_get_ex(parsed_json, "password_hash", &password_hash_object);

  // Gets the array length of the username and password arrays in the config
  n_usernames = json_object_array_length(username_object);
  n_password_hashes = json_object_array_length(password_hash_object);

  // Checks to see if the attempted username & password match the first username & the first
  // password or the second username & and the second password, etc. in order to grant access.
	for (i = 0; i < n_usernames; i++)
  {
		username = json_object_array_get_idx(username_object, i);

		password_hash = json_object_array_get_idx(password_hash_object, i);

    if (strcmp(json_object_get_string(username), username_attempt) == 0 && strcmp(json_object_get_string(password_hash), password_attempt_hash) == 0)
    {
      printf("\nWelcome, %s!\n", json_object_get_string(username));
      return 0;
    }
	}

  printf("\nInvalid Credentials. Please Re-Compile And Try Again.\n");
  return -1;
}

void hash_and_store(char *username_attempt, char *password_attempt, char *config)
{
  int i;
  const char *s = password_attempt;

  // Creates an string containing the "raw" (hexadecimal) SHA256 value of the user's
  // password attempt
  unsigned char *password_attempt_hash_raw = SHA256(s, strlen(s), 0);
  unsigned char password_attempt_hash[1000];

  // Goes through and prints the "raw" string into a regular string that can be used later for
  // comparison
  for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    sprintf(password_attempt_hash + i * 2, "%02x", password_attempt_hash_raw[i]);
  }

  config_parser(config, username_attempt, password_attempt_hash);
}

int main(void)
{
  char username_attempt[1000];
  char password_attempt[1000];
  char config[] = "config.json";

  printf("Please Enter Your Username\n");
  scanf("%s", username_attempt);

  printf("Please Enter Your Password\n");
  scanf("%s", password_attempt);

  hash_and_store(username_attempt, password_attempt, config);

  return 0;
}

