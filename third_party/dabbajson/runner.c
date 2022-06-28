#include "libc/assert.h"
#include "libc/str/str.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"

STATIC_YOINK("third_party/dabbajson/sample.json");
#define BUFFERSIZE 128

int main(int argc, char *argv[]) {
  const char *keys[] = {"hi", "this", "is", "a", "sample", "json"};
  const size_t keylens[] = {2, 4, 2, 1, 6, 4};
  const DJValue *values[] = {
      DoubleToDJValue(-3.14), StringToDJValue("string", 6),
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
  char buf3[] = "[4, 2.1, true, false, null, \"abc\", {\"a\":null}]";
  ReadDJValueFromBuffer(buf3, strlen(buf3), &obj2);
  res = WriteDJValueToBuffer(obj2, buf2, sizeof(buf2));
  assert(buf2[BUFFERSIZE - 1] == '\0');
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
