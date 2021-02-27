#ifndef PROTOSTORE_FILE_STORAGE_H_
#define PROTOSTORE_FILE_STORAGE_H_

#include <cstdint>

#include "absl/strings/string_view.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace protostore {

class InputStream {
 public:
  InputStream(absl::string_view filename, FILE* file);
  ~InputStream();

  absl::Status Read(size_t n, absl::string_view* result,
      char* scratch);
 private:
  std::string filename_;
  FILE* file_;
};

class OutputStream {
 public:
  OutputStream(absl::string_view filename, FILE* file);
  ~OutputStream();

  absl::Status Append(absl::string_view data);
  absl::Status Close();
 private:
  std::string filename_;
  FILE* file_;
};

class FileStorage {
 public:
  FileStorage() = default;
  ~FileStorage() = default;

  absl::StatusOr<uint64_t> GetFileSize(const std::string& filename) const;
  absl::StatusOr<std::unique_ptr<InputStream>> OpenForRead(
      const std::string& filename) const;
  absl::StatusOr<std::unique_ptr<OutputStream>> OpenForWrite(
      const std::string& filename) const;
};

}  // namespace protostore

#endif  // PROTOSTORE_FILE_STORAGE_H_
