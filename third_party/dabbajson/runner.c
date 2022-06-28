#include "libc/assert.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"

#define BUFFERSIZE 80

int main(int argc, char *argv[]) {
  const char *keys[] = {"hi", "this", "is", "a", "sample", "json"};
  const size_t keylens[] = {2, 4, 2, 1, 6, 4};
  const DJValue *values[] = {
      DoubleToDJValue(-3.14), StringToDJValue("string", 6),
      NullToDJValue(),       BoolToDJValue(true),
      BoolToDJValue(false),  IntegerToDJValue(345)};

  char buf[BUFFERSIZE] = {0};

  DJValue *obj = ObjectToDJValue(keys, keylens, values, 6);
  int res = WriteDJValueToBuffer(obj, buf, BUFFERSIZE);
  assert(buf[BUFFERSIZE-1] =='\0');
  printf("%s\n(%d bytes written into buffer)\n", buf, res >= BUFFERSIZE ? BUFFERSIZE : res);
  WriteDJValueToFile(obj, stdout);
  FreeDJValue(obj);
  for (int i = 0; i < 6; i++) {
    FreeDJValue(values[i]);
  }
  printf("\n");
  return 0;
}
