#include "libc/assert.h"
#include "libc/str/str.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"

STATIC_YOINK("third_party/dabbajson/sample.json");
#define BUFFERSIZE 128

#define STRINGANDSIZE(x) x,sizeof(x)

int main(int argc, char *argv[]) {
  const char *keys[] = {"hi", "this", "is", "a", "sample", "json", "el", "eo"};
  const size_t keylens[] = {2, 4, 2, 1, 6, 4, 2, 2};
  const DJValue *values[] = {
      DoubleToDJValue(-3.0), StringToDJValue(STRINGANDSIZE("str\\\"ng")),
      NullToDJValue(),        BoolToDJValue(true),
      BoolToDJValue(false),   IntegerToDJValue(-345),
      ArrayToDJValue(NULL, 0), ObjectToDJValue(NULL, NULL, NULL, 0),
  };

  char buf[BUFFERSIZE] = {0};
  char buf2[BUFFERSIZE] = {0};

  int64_t sample = 0;
  assert(0 == DJValueToInteger(values[5], &sample));
  assert(sample == -345);
  DJValue *obj = ObjectToDJValue(keys, keylens, values, 8);
  int res = WriteDJValueToBuffer(obj, buf, BUFFERSIZE);
  assert(buf[BUFFERSIZE - 1] == '\0');
  printf("%s\n(%d bytes written into buffer)\n", buf,
         res >= BUFFERSIZE ? BUFFERSIZE : res);
  FreeDJValue(obj);
  for (int i = 0; i < 6; i++) {
    FreeDJValue(values[i]);
  }

  DJValue *obj2 = NULL;
  assert(-1 != ReadDJValueFromBuffer(buf, res, &obj2));
  res = WriteDJValueToBuffer(obj2, buf2, sizeof(buf2));
  assert(buf2[BUFFERSIZE - 1] == '\0');
  assert(!strcmp(buf, buf2));
  printf("%s\n(%d bytes written into buffer)\n", buf2,
         res >= BUFFERSIZE ? BUFFERSIZE : res);

  FILE *fp = fopen("/zip/third_party/dabbajson/sample.json", "r");
  DJValue *x = NULL;
  assert(-1 != ReadDJValueFromFile(fp, &x));
  WriteDJValueToFile(x, stdout);
  printf("\n");
  FreeDJValue(x);
  fclose(fp);

  return 0;
}
