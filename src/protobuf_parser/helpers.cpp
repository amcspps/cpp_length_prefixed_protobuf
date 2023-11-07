#include <helpers.hpp>
template <typename Message>
PointerToConstData serializeDelimited(const Message& msg) {
constsize_t messageSize = PROTOBUF_MESSAGE_BYTE_SIZE(msg);
constsize_t headerSize = google::protobuf::io::CodedOutputStream::VarintSize32(messageSize);
const PointerToData& result = std::make_shared<Data>(headerSize + messageSize);
google::protobuf::uint8* buffer = reinterpret_cast<google::protobuf::uint8*>(&*result->begin());
google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(messageSize, buffer);
msg.SerializeWithCachedSizesToArray(buffer + headerSize);
return result;
}


template <typename Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed = 0) {
    std::shared_ptr<Message> parsedMessage = std::make_shared<Message>();
    google::protobuf::io::ArrayInputStream input(data, size);
    google::protobuf::io::CodedInputStream codedInput(&input);

    uint32_t messageSize;
    if (codedInput.ReadVarint32(&messageSize)) {
        google::protobuf::io::CodedInputStream::Limit limit = codedInput.PushLimit(messageSize);
        if (parsedMessage->ParseFromCodedStream(&codedInput)) {
            if (bytesConsumed) {
                *bytesConsumed = size - codedInput.BytesUntilLimit();
            }
            return parsedMessage;
        }
        codedInput.PopLimit(limit);
    }
    return nullptr;
}