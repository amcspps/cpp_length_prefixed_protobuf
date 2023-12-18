#include "helpers.hpp"
#include <list>
#include <memory>
#include <string>
#include <vector>

#ifndef SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_
#define SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_

template <typename MessageType>
class DelimitedMessagesStreamParser {
public:
	typedef std::shared_ptr<const MessageType> PointerToConstValue;
	std::list<PointerToConstValue> parse(const std::string &data) {
		std::list<PointerToConstValue> parsedMessages;
		m_buffer.insert(m_buffer.end(), data.begin(), data.end());
		size_t bytesConsumed = 0;

		while (!m_buffer.empty()) {
			std::shared_ptr<MessageType> parsedMessage = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size(), &bytesConsumed);
			if (parsedMessage) {
				parsedMessages.push_back(parsedMessage);
				m_buffer.erase(m_buffer.begin(), m_buffer.begin() + bytesConsumed);
			}
			else if (!m_buffer.empty() && bytesConsumed == -1) {
				break;
			} else {
				throw std::runtime_error("Error parsing data");
			}
		}
		return parsedMessages;
}

private:
	std::vector<char> m_buffer;
};

#endif /* SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_ */
