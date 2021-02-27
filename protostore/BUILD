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
)
