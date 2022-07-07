#include "third_party/dabbajson/test/helper.h"

int main() {
	STATIC_YOINK("third_party/dabbajson/test/test-pass1.json");
	CheckFileReadSuccess("/zip/third_party/dabbajson/test/test-pass1.json");
}
