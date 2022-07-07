#include "third_party/dabbajson/test/helper.h"

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
  int64_t sample = 0;
  assert(0 == DJValueToInteger(values[5], &sample));
  assert(sample == -35);
  DJValue *obj = ObjectToDJValue(keys, keylens, values, 8);
  CheckBufferConversion(obj);
  FreeDJValue(obj);
  for (int i = 0; i < 6; i++) {
    FreeDJValue(values[i]);
  }
}

void CheckFileRead() {
  STATIC_YOINK("third_party/dabbajson/test/test-sample.json");
  FILE *fp = fopen("/zip/third_party/dabbajson/test/test-sample.json", "r");
  DJValue *x = NULL;
  assert(-1 != ReadDJValueFromFile(fp, &x));
  WriteDJValueToFile(x, stdout);
  printf("\n");
  fclose(fp);

  CheckBufferConversion(x);
  
  char **keys;
  DJValue **values;
  size_t *keylens;
  size_t len;
  char *ape;
  size_t apelen;
  assert(-1 != DJValueToObject(x, &keys, &keylens, &values, &len));
  assert(-1 != DJValueToString(values[0], &ape, &apelen));
  printf("%s: %s\n", keys[0], ape);
  FreeDJValue(x);
}

int main(int argc, char *argv[]) {
  CheckLocalObject();
  CheckFileRead();
  return 0;
}
