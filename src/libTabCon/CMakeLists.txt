add_library(SHA1 "sha1/sha1.c")
add_library(TabCon "tabCon.c")

target_link_libraries(TabCon SHA1)