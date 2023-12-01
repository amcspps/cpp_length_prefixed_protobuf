#include <list>
#include <string>
#include <memory>
#include <vector>
#include "helpers.hpp"
#ifndef SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_
#define SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_

template <typename MessageType>
class DelimitedMessagesStreamParser
{
public:
  typedef std::shared_ptr<const MessageType> PointerToConstValue;
  std::list<PointerToConstValue> parse(const std::string &data) {
    std::list<PointerToConstValue> parsedMessages;
      // Append the incoming symbol to the buffer
      m_buffer.push_back(data.front());
      size_t bytesConsumed = 0;
      while(!m_buffer.empty()) {
        auto parsedMessage = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size(), &bytesConsumed);
        if (parsedMessage) {
          // Successfully parsed, add the message to the result
          parsedMessages.push_back(parsedMessage);
          // Clear the buffer after successful parse
          m_buffer.clear();
        }
        else {
          break;
        }
      }
      // Attempt to parse a one-length-prefixed message
      return parsedMessages;
    }
    
private:
  std::vector<char> m_buffer;
};

#endif /* SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_ */
