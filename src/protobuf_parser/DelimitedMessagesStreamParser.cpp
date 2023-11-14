#include <DelimitedMessagesStreamParser.hpp>

template <typename MessageType>
std::list<typename DelimitedMessagesStreamParser<MessageType>::PointerToConstValue> DelimitedMessagesStreamParser<MessageType>::parse(const std::string& data) {
    std::list<PointerToConstValue> parsedMessages;
    return parsedMessages;
}