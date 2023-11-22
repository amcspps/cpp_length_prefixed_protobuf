#include "src/protobuf/message.pb.h"
#include "src/protobuf_parser/DelimitedMessagesStreamParser.hpp"
#include "src/protobuf_parser/helpers.hpp"
#include <iostream> 

typedef DelimitedMessagesStreamParser<TestTask::Messages::WrapperMessage> Parser;

int main() {
  TestTask::Messages::WrapperMessage wm;
  TestTask::Messages::FastResponse* fastResponse = wm.mutable_fast_response();
  fastResponse->set_current_date_time("2023-01-01 12:00:00");
  auto serializedData = serializeDelimited(wm); 
  Parser parser; 
  std::vector<char> messages;
  for(const char byte : messages) {
    auto parsedMessages = parser.parse(std::string(1, byte));
    // for(const auto& value : parsedMessages) {
      
    // }
  }
  return 0;
}