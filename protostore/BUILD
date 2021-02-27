load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "crc32",
    srcs = ["crc32.cc"],
    hdrs = ["crc32.h"],
    visibility = ["//visibility:private"],
    deps = [
      "@com_google_absl//absl/strings",
    ]
)

cc_test(
    name = "crc32_test",
    srcs = ["crc32_test.cc"],
    visibility = ["//visibility:private"],
    deps = [
        ":crc32",
        "@googletest//:gtest_main",
    ],
    linkopts = ["-lz"]
)

cc_library(
    name = "file-storage",
    srcs = ["file-storage.cc"],
    hdrs = ["file-storage.h"],
    visibility = ["//visibility:private"],
    deps = [
      "@com_google_absl//absl/status",
      "@com_google_absl//absl/status:statusor",
    ]
)

cc_test(
    name = "file-storage_test",
    srcs = [
      "file-storage_test.cc",
      "status-matchers.h",
      "testfile-fixture.h"
    ],
    visibility = ["//visibility:private"],
    deps = [
        ":file-storage",
        "@googletest//:gtest_main",
    ],
)

cc_library(
  name = "proto-data-store",
  hdrs = ["proto-data-store.h"],
  deps = [
    ":crc32",
    ":file-storage",
    "@com_google_absl//absl/status",
    "@com_google_absl//absl/status:statusor",
    "@com_google_absl//absl/synchronization",
  ]
)

cc_test(
    name = "proto-data-store_test",
    srcs = [
      "proto-data-store_test.cc",
      "status-matchers.h",
      "testfile-fixture.h"
    ],
    visibility = ["//visibility:private"],
    deps = [
        ":file-storage",
        ":proto-data-store",
        "@googletest//:gtest_main",
    ],
)
