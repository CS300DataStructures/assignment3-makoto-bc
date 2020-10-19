#include <gtest/gtest.h>
#include "../Response.h"

using namespace network;

TEST(Response, output) {
	{
		std::stringstream ss;
		Response::newDropped().output(ss);
		EXPECT_EQ(ss.str(), "-1");
	}
	{
		std::stringstream ss;
		Response::newCompletedResponse(1).output(ss);
		EXPECT_EQ(ss.str(), "1");
	}
}