#include "third_party/dabbajson/test/helper.h"

int main() {
	STATIC_YOINK("third_party/dabbajson/test/test-fail19.json");
	CheckFileReadFailure("/zip/third_party/dabbajson/test/test-fail19.json");
}
