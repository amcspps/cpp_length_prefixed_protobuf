#include "build/src/protobuf/message.pb.h"
#include "src/protobuf_parser/DelimitedMessagesStreamParser.hpp"
#include <helpers.hpp>
#include <iostream>

typedef DelimitedMessagesStreamParser<TestTask::Messages::WrapperMessage> Parser;

int main() {
    std::vector<char> messages;
    Parser parser;
    for(const char byte : messages) {
        const std::list<DelimitedMessagesStreamParser<TestTask::Messages::WrapperMessage>::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte));
        for(auto & value : parsedMessages) {
          // добавляем куда-то все сообщения
        }
    }    

    return 0;
}