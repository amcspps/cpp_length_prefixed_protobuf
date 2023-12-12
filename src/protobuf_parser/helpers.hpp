#include <vector>
#include <memory>

#include <google/protobuf/io/coded_stream.h>


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
    if (size < sizeof(uint32_t)) {
            // Not enough data to parse the length prefix
            return nullptr;
        }

    // Extract the length prefix from the data
    google::protobuf::uint32 messageLength;
    size_t bytesRead = google::protobuf::io::CodedInputStream::ReadVarint32FromArray(
        reinterpret_cast<const google::protobuf::uint8*>(data), &messageLength);

    if (bytesRead == 0) {
        // Failed to read varint (possibly incomplete data)
        return nullptr;
    }

    // Check if the remaining data is sufficient for the complete message
    size_t expectedSize = sizeof(uint32_t) + messageLength;
    if (size < expectedSize) {
        // Not enough data for the complete message
        return nullptr;
    }

    // Extract the message data
    const char* messageData = reinterpret_cast<const char*>(data) + sizeof(uint32_t);

    // Deserialize the protobuf message
    Message parsedMessage;
    if (parsedMessage.ParseFromArray(messageData, messageLength)) {
        // Set the number of consumed bytes
        *bytesConsumed = expectedSize;

        // Create a shared pointer to the parsed message
        return std::make_shared<Message>(parsedMessage);
    } else {
        // Protobuf parsing failed
        return nullptr;
    }
};

#endif /* SRC_PROTOBUF_PARSER_HELPERS_H_ */
