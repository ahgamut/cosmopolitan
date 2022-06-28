#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"

int main(int argc, char *argv[]) {
  const char *keys[] = {"hi", "this", "is", "a", "sample", "json"};
  const size_t keylens[] = {2, 4, 2, 1, 6, 4};
  const DJValue *values[] = {NumberToDJValue(3.14), StringToDJValue("string", 6),
                       NullToDJValue(),       BoolToDJValue(true),
                       BoolToDJValue(false),  NumberToDJValue(23.4)};
  
  DJValue *obj = ObjectToDJValue(keys, keylens, values, 6);
  WriteDJValueToFile(obj, stdout);
  FreeDJValue(obj);
  for (int i = 0; i < 6; i++) {
    FreeDJValue(values[i]);
  }
  printf("\n");
  return 0;
}
