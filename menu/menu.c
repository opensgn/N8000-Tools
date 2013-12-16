#include <linux/input.h>
#include <fcntl.h>
#include <stdio.h>

void key(char *line) {
  int i = 0;
  while(line[i] != '\0') {
    if(line[i] == '=') {
      break;
    } else {
      putchar(line[i]);
    }
    i++;
  }
  putchar('\n');
}

void draw(int sel, int argc, char **argv) {
  int i;
  printf("\033[2J\033[1;1H");
  printf("Use Vol-Up / Vol-Down to change selection, then press Power:\n");
  for(i = 2; i < argc; i++) {
    if (i == sel) {
      printf("> ");
    } else {
      printf("  ");
    }
    key(argv[i]);
  }
}

int main(int argc, char **argv) {
  if(argc < 3) {
    printf("usage: %s <device> <entry1>...<entryN>\n", argv[0]);
   return 1;
  }

  int fd = open(argv[1], O_RDONLY);
  struct input_event ev;
  int pos = 2;

  draw(pos, argc, argv);

  while(1) {
    read(fd, &ev, sizeof(struct input_event));

    if(ev.type == 1 && ev.value == 0) {
      switch(ev.code) {
        // vol up
        case 115: pos = pos == argc - 1 ? pos : pos + 1; break;
        // vol down
        case 114: pos = pos == 2 ? pos : pos - 1; break;
        // power
        case 116: return --pos;
        default: ;
      }

      draw(pos, argc, argv);
    }
  }
}
