cc_library(
    name = "aoc",
    hdrs = ["aoc.h"],
    data = [
        ".env",
    ],
)

cc_binary(
    name = "day_01",
    srcs = ["day_01.cc"],
    deps = [":aoc"],
)

cc_binary(
    name = "day_02",
    srcs = ["day_02.cc"],
    deps = [
        ":aoc",
        "@com_google_absl//absl/strings",
    ],
)
