#include "libc/assert.h"
#include "libc/str/str.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"

STATIC_YOINK("third_party/dabbajson/sample.json");
#define BUFFERSIZE 128

#define STRINGANDSIZE(x) x,sizeof(x)

int main(int argc, char *argv[]) {
  const char *keys[] = {"hi", "this", "is", "a", "sample", "json"};
  const size_t keylens[] = {2, 4, 2, 1, 6, 4};
  const DJValue *values[] = {
      DoubleToDJValue(-3.0), StringToDJValue(STRINGANDSIZE("str\\\"ng")),
      NullToDJValue(),        BoolToDJValue(true),
      BoolToDJValue(false),   IntegerToDJValue(345)};

  char buf[BUFFERSIZE] = {0};
  char buf2[BUFFERSIZE] = {0};

  DJValue *obj = ObjectToDJValue(keys, keylens, values, 6);
  int res = WriteDJValueToBuffer(obj, buf, BUFFERSIZE);
  assert(buf[BUFFERSIZE - 1] == '\0');
  printf("%s\n(%d bytes written into buffer)\n", buf,
         res >= BUFFERSIZE ? BUFFERSIZE : res);
  FreeDJValue(obj);
  for (int i = 0; i < 6; i++) {
    FreeDJValue(values[i]);
  }

  DJValue *obj2 = NULL;
  ReadDJValueFromBuffer(buf, res, &obj2);
  res = WriteDJValueToBuffer(obj2, buf2, sizeof(buf2));
  assert(buf2[BUFFERSIZE - 1] == '\0');
  assert(!strcmp(buf, buf2));
  printf("%s\n(%d bytes written into buffer)\n", buf2,
         res >= BUFFERSIZE ? BUFFERSIZE : res);

  FILE *fp = fopen("/zip/third_party/dabbajson/sample.json", "r");
  DJValue *x = NULL;
  ReadDJValueFromFile(fp, &x);
  WriteDJValueToFile(x, stdout);
  printf("\n");
  FreeDJValue(x);
  fclose(fp);

  return 0;
}
