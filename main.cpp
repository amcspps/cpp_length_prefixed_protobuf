#include "src/protobuf/message.pb.h"
#include "src/protobuf_parser/DelimitedMessagesStreamParser.hpp"
#include "src/protobuf_parser/helpers.hpp"
#include <iostream> 

typedef DelimitedMessagesStreamParser<TestTask::Messages::WrapperMessage> Parser;

int main() {
  TestTask::Messages::WrapperMessage wm;
  TestTask::Messages::FastResponse* fastResponse = wm.mutable_fast_response();
  fastResponse->set_current_date_time("a");
  auto serializedData = serializeDelimited(wm); 
  Parser parser; 
  std::vector<char> messages;
  messages.insert(messages.end(), serializedData->begin(), serializedData->end());
  for(const char byte : messages) {
    auto parsedMessages = parser.parse(std::string(1, byte));
  }
  return 0;
}