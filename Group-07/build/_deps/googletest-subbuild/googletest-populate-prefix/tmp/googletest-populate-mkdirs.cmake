# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/CSE 498 CAPTSTONE/CSE498-Spring2025/Group-07/build/_deps/googletest-src"
  "D:/CSE 498 CAPTSTONE/CSE498-Spring2025/Group-07/build/_deps/googletest-build"
  "D:/CSE 498 CAPTSTONE/CSE498-Spring2025/Group-07/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "D:/CSE 498 CAPTSTONE/CSE498-Spring2025/Group-07/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "D:/CSE 498 CAPTSTONE/CSE498-Spring2025/Group-07/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "D:/CSE 498 CAPTSTONE/CSE498-Spring2025/Group-07/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "D:/CSE 498 CAPTSTONE/CSE498-Spring2025/Group-07/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/CSE 498 CAPTSTONE/CSE498-Spring2025/Group-07/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/CSE 498 CAPTSTONE/CSE498-Spring2025/Group-07/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
