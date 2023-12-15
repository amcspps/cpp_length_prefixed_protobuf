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
      m_buffer.push_back(data.front());
      size_t bytesConsumed = 0;
      while(!m_buffer.empty()) {
        std::shared_ptr<MessageType> parsedMessage = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size(), &bytesConsumed);
        if (parsedMessage) {
          // for (auto byte:m_buffer) {
          //   std::cout << byte << "X";
          // } 
          std::cout << parsedMessage->fast_response().current_date_time();
          parsedMessages.push_back(parsedMessage);
          m_buffer.erase(m_buffer.begin(), m_buffer.begin() + bytesConsumed);
        }
        else {
          break;
        }
      }
      return parsedMessages;
    }
    
private:
  std::vector<char> m_buffer;
};

#endif /* SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_ */
