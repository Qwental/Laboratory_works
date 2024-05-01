cc_library(
    name = "tree_lib",
    srcs = ["tree_lib.c"],
    hdrs = ["tree_lib.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "tree_bin",
    srcs = ["tree.c"],
    # copts = [
    #     "-g",
    #     "-fsanitize=address",
    #     "-fsanitize=undefined",
    #     "-static-libasan"
    #     "-fno-sanitize-recover=all",
    #     "-fsanitize=float-divide-by-zero",
    #     "-fsanitize=float-cast-overflow",
    #     "-fno-sanitize=null",
    #     "-fno-sanitize=alignment",
    # ],
    deps = [":tree_lib"],
)
