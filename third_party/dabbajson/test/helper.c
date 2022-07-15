#include "third_party/dabbajson/test/helper.h"

void CheckBufferConversion(DJValue *x) {
  char *buf1 = NULL;
  int res1 = WriteDJValueToBuffer(x, &buf1);
  assert(res1 != -1 && buf1 != NULL);
  printf("%s\n(%d bytes written into buffer)\n", buf1, res1);

  DJValue *x2 = NULL;
  assert(-1 != ReadDJValueFromBuffer(buf1, res1, &x2));

  char *buf2 = NULL;
  int res2 = WriteDJValueToBuffer(x2, &buf2);
  assert(res2 != -1 && buf2 != NULL);
  printf("%s\n(%d bytes written into buffer)\n", buf2, res2);
  assert(!strcmp(buf1, buf2));

  free(buf1);
  free(buf2);
  FreeDJValue(x2);
}

void CheckFileReadSuccess(const char *filename) {
  FILE *fp = fopen(filename, "r");
  assert(fp != NULL);
  DJValue *x = NULL;
  printf("Reading file %s:\n", filename);
  assert(-1 != ReadDJValueFromFile(fp, &x));
  WriteDJValueToFile(x, stdout);
  printf("\n");
  fclose(fp);

  /* if we have read it successfully, we should be
   * able to encode it into a buffer, decode it back,
   * encode it again, and have two equivalent buffers */
  CheckBufferConversion(x);
  FreeDJValue(x);
}

void CheckFileReadFailure(const char *filename) {
  FILE *fp = fopen(filename, "r");
  assert(fp != NULL);
  DJValue *x = NULL;
  printf("Reading file %s:\n", filename);
  assert(-1 == ReadDJValueFromFile(fp, &x));
  printf("failed\n");
  fclose(fp);
}
