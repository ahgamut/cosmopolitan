#include "third_party/dabbajson/test/helper.h"

void CheckFileRead(const char *filename) {
  FILE *fp = fopen(filename, "r");
  int res = 0;
  DJValue *x = NULL;
  printf("Reading file %s:\n", filename);
  res = ReadDJValueFromFile(fp, &x);
  /* passing or failing is ok, as long as no segfault */
  if (res != -1) {
    WriteDJValueToFile(x, stdout);
    printf("\n");
    FreeDJValue(x);
  }
  fclose(fp);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "no file provided\n");
    return -1;
  }
  CheckFileRead(argv[1]);
  return 0;
}
