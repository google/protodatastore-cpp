#include "protostore/proto-data-store.h"

#include <cstdint>

#include "absl/strings/str_cat.h"
#include "googlemock/include/gmock/gmock.h"
#include "googletest/include/gtest/gtest.h"
#include "protostore/file-storage.h"
#include "protostore/status-matchers.h"
#include "protostore/testfile-fixture.h"
#include "protostore/test.pb.h"

namespace protostore {
namespace {

using ::testing::Eq;
using ::testing::StartsWith;

class ProtoDataStoreTest : public testing::TestFileFixture {};


}  // namespace
}  // namespace protostore
