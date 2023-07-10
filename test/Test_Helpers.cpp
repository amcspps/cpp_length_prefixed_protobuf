#include <protobuf_parser/helpers.hpp>
#include <protobuf/message.pb.h>

#include <gtest/gtest.h>

TEST(ParseDelimited, DefaultTest)
{
  std::shared_ptr<TestTask::Messages::WrapperMessage> delimited;

  TestTask::Messages::WrapperMessage message;
  message.mutable_request_for_fast_response();

  auto buffer = serializeDelimited(message);
  size_t bytesConsumed = 0;

  delimited = parseDelimited<TestTask::Messages::WrapperMessage>(buffer->data(), buffer->size(), &bytesConsumed);

  ASSERT_FALSE(delimited == nullptr);
  EXPECT_TRUE(delimited->has_request_for_fast_response());
  EXPECT_EQ(bytesConsumed, buffer->size());
}

TEST(ParseDelimited, NullDataTest)
{
  std::shared_ptr<TestTask::Messages::WrapperMessage> delimited;

  size_t bytesConsumed = 0;

  delimited = parseDelimited<TestTask::Messages::WrapperMessage>(nullptr, 0, &bytesConsumed);

  ASSERT_TRUE(delimited == nullptr);
  EXPECT_EQ(bytesConsumed, 0);
}

TEST(ParseDelimited, EmptyDataTest)
{
  std::shared_ptr<TestTask::Messages::WrapperMessage> delimited;

  size_t bytesConsumed = 0;

  delimited = parseDelimited<TestTask::Messages::WrapperMessage>("", 0, &bytesConsumed);

  ASSERT_TRUE(delimited == nullptr);
  EXPECT_EQ(bytesConsumed, 0);
}

TEST(ParseDelimited, WrongDataTest)
{
  std::shared_ptr<TestTask::Messages::WrapperMessage> delimited;

  std::string buffer = "\x05parse";
  size_t bytesConsumed = 0;

  delimited = parseDelimited<TestTask::Messages::WrapperMessage>(buffer.data(), buffer.size(), &bytesConsumed);

  ASSERT_TRUE(delimited == nullptr);
  EXPECT_EQ(bytesConsumed, buffer.size());

  buffer = "Hello, World!";
  bytesConsumed = 0;

  delimited = parseDelimited<TestTask::Messages::WrapperMessage>(buffer.data(), buffer.size(), &bytesConsumed);
  ASSERT_TRUE(delimited == nullptr);
  EXPECT_EQ(bytesConsumed, 0);
}

TEST(ParseDelimited, CorruptedDataTest)
{
  std::shared_ptr<TestTask::Messages::WrapperMessage> delimited;

  TestTask::Messages::WrapperMessage message;
  message.mutable_request_for_fast_response();

  auto buffer = serializeDelimited(message);
  size_t bytesConsumed = 0;

  std::string corrupted = std::string(buffer->begin(), buffer->end());

  EXPECT_EQ(corrupted[0], '\x02');
  corrupted[0] -= 1;
  EXPECT_EQ(corrupted[0], '\x01');
  EXPECT_EQ(corrupted.size(), 3);

  delimited = parseDelimited<TestTask::Messages::WrapperMessage>(corrupted.data(), corrupted.size(), &bytesConsumed);

  ASSERT_TRUE(delimited == nullptr);
  EXPECT_EQ(bytesConsumed, corrupted.size() - 1);
}

TEST(ParseDelimited, WrongMessageSizeTest)
{
  std::shared_ptr<TestTask::Messages::WrapperMessage> delimited;

  TestTask::Messages::WrapperMessage message;
  message.mutable_request_for_fast_response();

  auto buffer = serializeDelimited(message);
  size_t bytesConsumed = 0;

  delimited = parseDelimited<TestTask::Messages::WrapperMessage>(buffer->data(), buffer->size() * 2, &bytesConsumed);

  ASSERT_FALSE(delimited == nullptr);
  EXPECT_TRUE(delimited->has_request_for_fast_response());
  EXPECT_EQ(bytesConsumed, buffer->size());

  bytesConsumed = 0;

  delimited = parseDelimited<TestTask::Messages::WrapperMessage>(buffer->data(), buffer->size() / 2, &bytesConsumed);

  ASSERT_TRUE(delimited == nullptr);
  EXPECT_EQ(bytesConsumed, 0);
}
