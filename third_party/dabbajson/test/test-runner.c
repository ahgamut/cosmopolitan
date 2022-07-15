#include "third_party/dabbajson/test/helper.h"

int CheckFileRead(const char *filename) {
  FILE *fp = fopen(filename, "r");
  if(!fp) {
    return 1;
  }
  int res = 0;
  DJValue *x = NULL;
  printf("Reading file %s:\n", filename);
  res = ReadDJValueFromFile(fp, &x);
  fclose(fp);
  /* passing or failing is ok, as long as no segfault */
  if (res != -1) {
    WriteDJValueToFile(x, stdout);
    printf("\n");
    FreeDJValue(x);
    return 0;
  }
  return 1;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "no file provided\n");
    return 1;
  }
  return CheckFileRead(argv[1]);
}
