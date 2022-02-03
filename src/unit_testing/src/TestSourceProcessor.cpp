

#include "catch.hpp"
#include "source_processor/SimpleProcessor.hpp"
#include "database/database.hpp"

#include <string>

namespace TestSourceProcessor {
void require(bool b, std::string &desc) {
  REQUIRE(b);
}

// TODO
TEST_CASE("[TestSourceProcessor]") {
}
}



