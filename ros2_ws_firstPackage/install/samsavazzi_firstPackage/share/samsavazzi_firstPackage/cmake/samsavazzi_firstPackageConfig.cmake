# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_samsavazzi_firstPackage_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED samsavazzi_firstPackage_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(samsavazzi_firstPackage_FOUND FALSE)
  elseif(NOT samsavazzi_firstPackage_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(samsavazzi_firstPackage_FOUND FALSE)
  endif()
  return()
endif()
set(_samsavazzi_firstPackage_CONFIG_INCLUDED TRUE)

# output package information
if(NOT samsavazzi_firstPackage_FIND_QUIETLY)
  message(STATUS "Found samsavazzi_firstPackage: 0.0.0 (${samsavazzi_firstPackage_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'samsavazzi_firstPackage' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${samsavazzi_firstPackage_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(samsavazzi_firstPackage_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${samsavazzi_firstPackage_DIR}/${_extra}")
endforeach()
