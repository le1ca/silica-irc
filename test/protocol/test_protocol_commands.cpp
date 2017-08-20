#include <gtest/gtest.h>

#include <fstream>

#include "protocol/commands.h"

using namespace silica::protocol;

TEST(test_protocol, can_construct) {
    command_base *c;
    ASSERT_NO_THROW(c = new command_mode(std::list<std::string>{"#test", "+o", "test"}));
    ASSERT_NO_THROW(delete c);
}

TEST(test_protocol, can_serialize) {
    command_mode c (std::list<std::string>{"#test", "+o", "test"});
    const std::string expected = "MODE #test +o test\n";
    const std::string result = c.serialize();
    ASSERT_EQ(result, expected);
}

TEST(test_protocol, can_serialize_varlen) {
    command_topic c (std::list<std::string>{"#test", "foo bar baz"});
    const std::string expected = "TOPIC #test :foo bar baz\n";
    const std::string result = c.serialize();
    ASSERT_EQ(result, expected);
}
