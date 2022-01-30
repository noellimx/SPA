

#include "catch.hpp"
#include "source_processor/SourceProcessor.hpp"
#include "database/database.hpp"

#include <string>

// Each cpp is a set of test cases for a specific component.
namespace TestSourceProcessor {
void require(bool b, std::string &desc) {
  REQUIRE(b);
}

// The name of a test case should be unique and meaningful.
TEST_CASE("[TestSourceProcessor] 1 naive procedure name", "[Tokenize1Procedure]") {
  // NOTE: SourceProcessor will initialize the database connection.

  std::string procedureName = "some";
  std::string source = "procedure " + procedureName + " { a = 0; }";
  SourceProcessor sp;
  sp.process(source);
  CHECK(database::isProcedureExist(procedureName));

}
}



