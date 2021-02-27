#ifndef PROTOSTORE_STATUS_MATCHERS_H_
#define PROTOSTORE_STATUS_MATCHERS_H_

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace protostore {
namespace testing {

namespace {
using ::testing::MakePolymorphicMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

MATCHER_P(IsStatusCode, code, "") { return arg.code() == code; }

class StatusCodeMatcher {
 public:
  StatusCodeMatcher(absl::StatusCode code) : code_(code) {}

  template <class T>
  bool MatchAndExplain(absl::StatusOr<T>* statusor,
                       MatchResultListener *listener) const {
    *listener << absl::StatusCodeToString(statusor->status().code());
    return statusor->status().code() == code_;
  }

  template <class U>
  bool MatchAndExplain(const absl::StatusOr<U>& statusor,
                       MatchResultListener *listener) const {
    *listener << absl::StatusCodeToString(statusor.status().code());
    return statusor.status().code() == code_;
  }

  template <class V>
  bool MatchAndExplain(const V& status,
      MatchResultListener *listener) const {
    *listener << absl::StatusCodeToString(status.code());
    return status.code() == code_;
  }

  void DescribeTo(std::ostream* os) const {
    *os << "is " << absl::StatusCodeToString(code_);
  }

  void DescribeNegationTo(std::ostream* os) const {
    *os << "isn't " << absl::StatusCodeToString(code_);
  }

 private:
  absl::StatusCode code_;
};

}  // namespace

::testing::PolymorphicMatcher<StatusCodeMatcher> IsStatusCode(
    absl::StatusCode code) {
  return MakePolymorphicMatcher(StatusCodeMatcher(code));
}

::testing::PolymorphicMatcher<StatusCodeMatcher> IsOk() {
  return MakePolymorphicMatcher(StatusCodeMatcher(absl::StatusCode::kOk));
}

#define EXPECT_OK(status) \
  EXPECT_THAT((status), testing::IsOk())
#define ASSERT_OK(status) \
  ASSERT_THAT((status), testing::IsOk())

}  // namespace testing
}  // namespace protostore
#endif  // PROTOSTORE_STATUS_MATCHERS_H_
