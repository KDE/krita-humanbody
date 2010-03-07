FIND_LIBRARY(KRITAIMAGE_LIBRARY NAMES kritaimage
  PATHS
  $ENV{KDEDIR}/lib
  ${KDE4REFIX}/lib
  ${CMAKE_INSTAL_PREFIX}/lib
  /opt/kde4/lib
  /opt/kde/lib
  NO_DEFAULT_PATH
)

FIND_LIBRARY(KRITAUI_LIBRARY NAMES kritaui
  PATHS
  $ENV{KDEDIR}/lib
  ${KDE4PREFIX}/lib
  ${CMAKE_INSTAL_PREFIX}/lib
  /opt/kde4/lib
  /opt/kde/lib
  NO_DEFAULT_PATH
)

FIND_LIBRARY(KRITAPAINTOP_LIBRARY NAMES kritalibpaintop
  PATHS
  $ENV{KDEDIR}/lib
  ${KDE4PREFIX}/lib
  ${CMAKE_INSTAL_PREFIX}/lib
  /opt/kde4/lib
  /opt/kde/lib
  NO_DEFAULT_PATH
)

# if (KRITA_EXTRA_INCLUDE_DIR)
#    # in cache already
#    set(KRITA_EXTRA_FOUND TRUE)
# else (KRITA_EXTRA_INCLUDE_DIR)
# 
#    # Make sure we can find the place where kis_transform_worker is installed.
#    find_path(KRITA_EXTRA_INCLUDE_DIR NAMES image/kis_transform_worker.h
#              PATHS
#              ${KRITA_EXTRA_INCLUDE_PATH}
#              ${INCLUDE_INSTALL_DIR}
#              /usr/include
#              /usr/local/include
#                 )
# 
#    if(KRITA_EXTRA_INCLUDE_DIR)
#       set(KRITA_EXTRA_FOUND TRUE)
#    endif(KRITA_EXTRA_INCLUDE_DIR)
# 
# mark_as_advanced( KRITA_EXTRA_INCLUDE_DIR )
#     message(status "Found Krita extra include dir in ${KRITA_EXTRA_INCLUDE_DIR}")
# endif(KRITA_EXTRA_INCLUDE_DIR)
# 
# if(KRITA_EXTRA_FOUND)
#    # Include the paths to the different include files.
#    # XXX: IMHO only ${KRITA_EXTRA_INCLUDE_DIR} should be in the include path and 
#    # the include statements should be written <core/kis_filter_strategy.h>
#    include_directories( ${KRITA_EXTRA_INCLUDE_DIR} 
#        ${KRITA_EXTRA_INCLUDE_DIR}/image
#        ${KRITA_EXTRA_INCLUDE_DIR}/image/brushengine
#        ${KRITA_EXTRA_INCLUDE_DIR}/image/metadata
#       ${KRITA_EXTRA_INCLUDE_DIR}/ui
#       ${KRITA_EXTRA_INCLUDE_DIR}/sdk
#       ${KRITA_EXTRA_INCLUDE_DIR}/plugins/paintops/libpaintop
#    )
# endif(KRITA_EXTRA_FOUND)
# 
# mark_as_advanced( KRITA_EXTRA_INCLUDE_DIR  )
