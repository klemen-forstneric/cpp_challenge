cc_binary(
  name = "cpp_challenge",
  srcs = [
    "zmq.hpp",
    "main.cc",
    "network_helper.cc",
    "network_helper.h",
    "utility.cc",
    "utility.h",
    "image_helper.cc",
    "image_helper.h",
    "serialization.cc",
    "serialization.h",
  ],
  copts = [ "-std=c++14", "-Wall" ],
  linkopts = ["-lzmq", "-lopencv_core", "-lopencv_imgcodecs"],
)

cc_test(
  name = "cpp_challenge_tests",
  srcs = [
    "utility.cc",
    "utility.h",
    "utility_test.cc",
    "image_helper.cc",
    "image_helper.h",
    "image_helper_test.cc",
    "serialization.cc",
    "serialization.h",
    "serialization_test.cc",
  ],
  copts = [ "-std=c++14", "-Wall" ],
  linkopts = ["-lopencv_core", "-lopencv_imgcodecs"],
  deps = ["//third_party:gtest"],
)
