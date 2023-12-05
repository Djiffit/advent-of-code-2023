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

cc_binary(
    name = "day_03",
    srcs = ["day_03.cc"],
    deps = [
        ":aoc",
    ],
)

cc_binary(
    name = "day_04",
    srcs = ["day_04.cc"],
    deps = [
        ":aoc",
        "@com_google_absl//absl/strings",
    ],
)

cc_binary(
    name = "day_05",
    srcs = ["day_05.cc"],
    deps = [
        ":aoc",
        "@com_google_absl//absl/strings",
    ],
)
