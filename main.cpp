#include "src/protobuf/message.pb.h"
#include "src/protobuf_parser/DelimitedMessagesStreamParser.hpp"
#include "src/protobuf_parser/helpers.hpp"

#include <iostream>
#include <iterator>
#include <ostream>
#include <string>

typedef DelimitedMessagesStreamParser<TestTask::Messages::WrapperMessage> Parser;

int main() {
	return 0;
}