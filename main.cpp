#include "./build/src/protobuf/message.pb.h"
#include <iostream>
int main() {
    TestTask::Messages::FastResponse msg;
    msg.set_current_date_time("12:00:00");
    std::cout << msg.current_date_time() << std::endl;
    return 0;
}