#ifndef SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_
#define SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_

template <typename MessageType>
class DelimitedMessagesStreamParser
{
 public:
  typedef std::shared_ptr<const MessageType> PointerToConstValue;

  std::list<PointerToConstValue> parse(const std::string& data);

 private:
  std::vector<char> m_buffer;
};

#endif /* SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_ */
