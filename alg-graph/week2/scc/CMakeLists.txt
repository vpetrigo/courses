add_executable(scc_recursive scc_2.cpp)
set_property(TARGET scc_recursive PROPERTY CXX_STANDARD 14)
set_property(TARGET scc_recursive PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(scc_it scc.cpp)
set_property(TARGET scc_it PROPERTY CXX_STANDARD 14)
set_property(TARGET scc_it PROPERTY CXX_STANDARD_REQUIRED ON)
