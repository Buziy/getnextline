#include "get_next_line.h"
//#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>


int main()
{
  int fd = open("tx.txt",O_RDONLY);
  char *line;
  while((line = get_next_line(fd)) != NULL)
  {
    write(1, line, gn_strlen(line));
    free(line);
  }
  printf("%s", get_next_line(fd));
  printf("%s", get_next_line(fd));
  close(fd);
  return(0);
}
