#include "third_party/dabbajson/test/helper.h"

int main(int argc, char **argv) {
    if(argc != 2) {
      fprintf(stderr, "no file provided\n");
      return -1;
    }
	CheckFileReadFailure(argv[1]);
    return 0;
}
