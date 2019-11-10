  This repository contains "credentials.c". That program asks for a username and password. It then hashes the given password with SHA256 and  compares that username and encrypted password to the usernames and passwords given in the config file specified in main.

  The string "config" in main holds the address of a JSON file containing two arrays, one for usernames and one for passwords. The first username corresponds to the first password, the second username to the second password, and so forth. The passwords are already hashed with SHA256 and so are not easily compromised.

  Also in this github repository is a c file named "encrypt_password.c" that can be executed in order to obtain the SHA256 hash for the password you enter. That way, if a different password is desired than the preset ones in config, it can be run through that c file and the output can be entered into the config for use with credentials.c.  These .c files should be compiled with

  "-lssl -ljson-c -lcrypto"