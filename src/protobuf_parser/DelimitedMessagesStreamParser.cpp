#include <DelimitedMessagesStreamParser.hpp>

template <typename MessageType>
std::list<typename DelimitedMessagesStreamParser<MessageType>::PointerToConstValue> DelimitedMessagesStreamParser<MessageType>::parse(const std::string& data) {
    m_buffer.insert(m_buffer.end(), data.begin(), data.end());
    std::list<PointerToConstValue> messageList;
    while (!m_buffer.empty()) {
        size_t bytesRead = 0;
        PointerToConstValue parsedMessage = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size(), &bytesRead);

        if (parsedMessage && bytesRead > 0) {
            messageList.push_back(parsedMessage);
            m_buffer.erase(m_buffer.begin(), m_buffer.begin() + bytesRead);
        } else {

            break;
        }
    }
    return messageList;
}