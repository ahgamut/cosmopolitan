#include "third_party/dabbajson/test/helper.h"

int main() {
	STATIC_YOINK("third_party/dabbajson/test/test-fail4.json");
	CheckFileReadFailure("/zip/third_party/dabbajson/test/test-fail4.json");
}
