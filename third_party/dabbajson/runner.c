#include "libc/assert.h"
#include "libc/str/str.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"

STATIC_YOINK("third_party/dabbajson/sample.json");
#define BUFFERSIZE 128

#define STRINGANDSIZE(x) x,sizeof(x)

void CheckLocalObject() {
  const char *keys[] = {"hi", "this", "is", "a", "sample", "json", "el", "eo"};
  const size_t keylens[] = {2, 4, 2, 1, 6, 4, 2, 2};
  const DJValue *values[] = {
      DoubleToDJValue(-3.0),   StringToDJValue(STRINGANDSIZE("str\u03b1\\\"\n\r\t\b\fng")),
      NullToDJValue(),         BoolToDJValue(true),
      BoolToDJValue(false),    IntegerToDJValue(-35),
      ArrayToDJValue(NULL, 0), ObjectToDJValue(NULL, NULL, NULL, 0),
  };
  char *buf = NULL;
  char *buf2 = NULL;
  int64_t sample = 0;
  ssize_t res = 0;

  assert(0 == DJValueToInteger(values[5], &sample));
  assert(sample == -35);
  DJValue *obj = ObjectToDJValue(keys, keylens, values, 8);
  res = WriteDJValueToBuffer(obj, &buf);
  assert(res != -1 && buf != NULL);
  printf("%s\n(%d bytes written into buffer)\n", buf, res);
  FreeDJValue(obj);
  for (int i = 0; i < 6; i++) {
    FreeDJValue(values[i]);
  }

  DJValue *obj2 = NULL;
  assert(-1 != ReadDJValueFromBuffer(buf, res, &obj2));
  res = WriteDJValueToBuffer(obj2, &buf2);
  assert(res != -1 && buf2 != NULL);
  printf("%s\n(%d bytes written into buffer)\n", buf2, res);
  assert(!strcmp(buf, buf2));
  if (buf) free(buf);
  if (buf2) free(buf2);
}

void CheckFileRead() {
  FILE *fp = fopen("/zip/third_party/dabbajson/sample.json", "r");
  DJValue *x = NULL;
  assert(-1 != ReadDJValueFromFile(fp, &x));
  WriteDJValueToFile(x, stdout);
  printf("\n");
  fclose(fp);

  char **keys;
  DJValue **values;
  size_t *keylens;
  size_t len;

  char *ape;
  size_t apelen;
  assert(-1 != DJValueToObject(x, &keys, &keylens, &values, &len));
  assert(-1 != DJValueToString(values[0], &ape, &apelen));
  printf("%s: %s\n", keys[0], ape);

  char *buf3 = NULL;
  int res = WriteDJValueToBuffer(x, &buf3);
  assert(res != -1 && buf3 != NULL);
  printf("%s\n(%d bytes written into buffer)\n", buf3, res);
  FreeDJValue(x);
}

int main(int argc, char *argv[]) {
  CheckLocalObject();
  CheckFileRead();
  return 0;
}
