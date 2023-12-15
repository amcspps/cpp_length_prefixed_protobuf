#include <vector>
#include <memory>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#ifndef SRC_PROTOBUF_PARSER_HELPERS_H_
#define SRC_PROTOBUF_PARSER_HELPERS_H_

#if GOOGLE_PROTOBUF_VERSION >= 3012004
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSizeLong())
#else
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSize())
#endif

typedef std::vector<char> Data;
typedef std::shared_ptr<const Data> PointerToConstData;
typedef std::shared_ptr<Data> PointerToData;

template <typename Message>
PointerToConstData serializeDelimited(const Message& msg)  {
    const size_t messageSize = PROTOBUF_MESSAGE_BYTE_SIZE(msg);
    const size_t headerSize = google::protobuf::io::CodedOutputStream::VarintSize32(messageSize);

    const PointerToData& result = std::make_shared<Data>(headerSize + messageSize);

    google::protobuf::uint8* buffer = reinterpret_cast<google::protobuf::uint8*>(&*result->begin());
    google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(messageSize, buffer);
    msg.SerializeWithCachedSizesToArray(buffer + headerSize);
    return result;
};


template <typename Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed = 0) {

    google::protobuf::io::ArrayInputStream input(reinterpret_cast <const char*> (data), size);
    google::protobuf::io::CodedInputStream coded_input(&input);

    uint32_t message_size;
    if (!coded_input.ReadVarint32(&message_size))
    {
      // Incomplete message, return nullptr
      *bytesConsumed = 0;
      return nullptr;
    }

    // Ensure we have enough data to read the entire message
    if (coded_input.CurrentPosition() + message_size > size)
    {
      // Incomplete message, return nullptr
      *bytesConsumed = 0;
      return nullptr;
    }

    // Move the stream to the beginning of the message data
    coded_input.Skip(message_size);

    *bytesConsumed = coded_input.CurrentPosition();
    return std::make_shared<Message>();
}

#endif /* SRC_PROTOBUF_PARSER_HELPERS_H_ */
