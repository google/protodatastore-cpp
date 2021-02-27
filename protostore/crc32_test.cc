#include "protostore/crc32.h"

#include <cstdint>

#include "googlemock/include/gmock/gmock.h"
#include "googletest/include/gtest/gtest.h"

namespace protostore {

namespace {

using ::testing::Eq;

TEST(Crc32Test, Get) {
  Crc32 crc32_test{10};
  Crc32 crc32_test_empty{};
  EXPECT_THAT(crc32_test.Get(), Eq(10));
  EXPECT_THAT(crc32_test_empty.Get(), Eq(0));
}

TEST(Crc32Test, Append) {
  // Test the complement logic inside Append()
  const uLong kCrcInitZero = crc32(0L, nullptr, 0);
  uint32_t foo_crc =
      crc32(kCrcInitZero, reinterpret_cast<const Bytef*>("foo"), 3);
  uint32_t foobar_crc =
      crc32(kCrcInitZero, reinterpret_cast<const Bytef*>("foobar"), 6);

  Crc32 crc32_test(~foo_crc);
  ASSERT_THAT(~crc32_test.Append("bar"), Eq(foobar_crc));

  // Test Append() that appending things separately should be the same as
  // appending in one shot
  Crc32 crc32_foobar{};
  crc32_foobar.Append("foobar");
  Crc32 crc32_foo_and_bar{};
  crc32_foo_and_bar.Append("foo");
  crc32_foo_and_bar.Append("bar");

  EXPECT_THAT(crc32_foo_and_bar.Get(), Eq(crc32_foobar.Get()));
}

}  // namespace

}  // namespace mobstore
