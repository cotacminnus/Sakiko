find_path(DPP_INCLUDE_DIR NAMES /usr/include/dpp/dpp.h HINTS ${DPP_ROOT_DIR})
 
find_library(DPP_LIBRARIES NAMES dpp "libdpp.so" HINTS ${DPP_ROOT_DIR})
 
include(FindPackageHandleStandardArgs)
 
find_package_handle_standard_args(DPP DEFAULT_MSG DPP_LIBRARIES DPP_INCLUDE_DIR)
