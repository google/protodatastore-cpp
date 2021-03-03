#include "protostore/proto-data-store.h"

#include <cstdint>

#include "absl/strings/str_cat.h"
#include "google/protobuf/message.h"
#include "googlemock/include/gmock/gmock.h"
#include "googletest/include/gtest/gtest.h"
#include "protostore/file-storage.h"
#include "protostore/testing-matchers.h"
#include "protostore/testfile-fixture.h"
#include "protostore/test.pb.h"

namespace protostore {
namespace {

using ::testing::Eq;
using ::testing::StartsWith;
using ::testing::Pointee;

using testing::IsOk;
using testing::IsOkAndHolds;
using testing::EqualsProto;

class ProtoDataStoreTest : public testing::TestFileFixture {};

TEST_F(ProtoDataStoreTest, SimpleReadWriteTest) {
  FileStorage storage;
  TestProto document;
  document.set_value("SimpleReadWriteTest");
  ProtoDataStore<TestProto> pds(storage, TestFile("SimpleReadWriteTest"));

  ASSERT_OK(pds.Write(absl::make_unique<TestProto>(document)));
  EXPECT_THAT(pds.Read(), IsOkAndHolds(Pointee(EqualsProto(document))));
  // Multiple reads work.
  EXPECT_THAT(pds.Read(), IsOkAndHolds(Pointee(EqualsProto(document))));
  EXPECT_THAT(pds.Read(), IsOkAndHolds(Pointee(EqualsProto(document))));
}
/*
TEST_F(ProtoDataStoreTest, DataPersistsAcrossMultipleInstancesTest) {
  FileStorage storage;
  TestProto document =
      DocumentBuilder().SetKey("namespace", "google.com").Build();
  {
    FileBackedProto<TestProto> file_proto(storage, filename_);
    EXPECT_THAT(file_proto.Read(), Not(IsOk()));  // Nothing to read.
    ICING_ASSERT_OK(
        file_proto.Write(absl::make_unique<TestProto>(document)));
    EXPECT_THAT(file_proto.Read(),
                IsOkAndHolds(Pointee(EqualsProto(document))));
  }
  {
    // Different instance of FileBackedProto.
    FileBackedProto<TestProto> file_proto(storage, filename_);
    EXPECT_THAT(file_proto.Read(),
                IsOkAndHolds(Pointee(EqualsProto(document))));
  }
}
TEST_F(ProtoDataStoreTest, MultipleUpdatesToProtoTest) {
  FileStorage storage;
  TestProto googleProto =
      DocumentBuilder().SetKey("namespace", "google.com").Build();
  TestProto youtubeProto =
      DocumentBuilder().SetKey("namespace", "youtube.com").Build();
  TestProto wazeProto =
      DocumentBuilder().SetKey("namespace", "waze.com").Build();
  {
    FileBackedProto<TestProto> file_proto(storage, filename_);
    ICING_ASSERT_OK(
        file_proto.Write(absl::make_unique<TestProto>(googleProto)));
    EXPECT_THAT(file_proto.Read(),
                IsOkAndHolds(Pointee(EqualsProto(googleProto))));
    ICING_ASSERT_OK(
        file_proto.Write(absl::make_unique<TestProto>(youtubeProto)));
    EXPECT_THAT(file_proto.Read(),
                IsOkAndHolds(Pointee(EqualsProto(youtubeProto))));
  }
  {
    // Different instance of FileBackedProto.
    FileBackedProto<TestProto> file_proto(storage, filename_);
    EXPECT_THAT(file_proto.Read(),
                IsOkAndHolds(Pointee(EqualsProto(youtubeProto))));
    ICING_ASSERT_OK(
        file_proto.Write(absl::make_unique<TestProto>(wazeProto)));
    EXPECT_THAT(file_proto.Read(),
                IsOkAndHolds(Pointee(EqualsProto(wazeProto))));
    ICING_ASSERT_OK(
        file_proto.Write(absl::make_unique<TestProto>(googleProto)));
    EXPECT_THAT(file_proto.Read(),
                IsOkAndHolds(Pointee(EqualsProto(googleProto))));
  }
}
TEST_F(ProtoDataStoreTest, InvalidFilenameTest) {
  FileStorage storage;
  TestProto document =
      DocumentBuilder().SetKey("namespace", "google.com").Build();
  FileBackedProto<TestProto> file_proto(storage, "");
  EXPECT_THAT(file_proto.Read(), Not(IsOk()));
  EXPECT_THAT(file_proto.Write(absl::make_unique<TestProto>(document)),
              Not(IsOk()));
}
TEST_F(ProtoDataStoreTest, FileCorruptionTest) {
  FileStorage storage;
  TestProto document =
      DocumentBuilder().SetKey("namespace", "google.com").Build();
  {
    FileBackedProto<TestProto> file_proto(storage, filename_);
    ICING_ASSERT_OK(
        file_proto.Write(absl::make_unique<TestProto>(document)));
    EXPECT_THAT(file_proto.Read(),
                IsOkAndHolds(Pointee(EqualsProto(document))));
  }
  document.set_uri("g00gle.com");
  std::string document_str = document.SerializeAsString();
  storage.PWrite(filename_.c_str(),
                     /offset=/sizeof(FileBackedProto<TestProto>::Header),
                     document_str.data(), document_str.size());
  FileBackedProto<TestProto> file_proto(storage, filename_);
  EXPECT_THAT(file_proto.Read(), Not(IsOk()));
}
*/
}  // namespace
}  // namespace protostore
