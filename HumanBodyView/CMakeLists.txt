
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../HumanBodyCommon)

set(kritahumanbodyview_PART_SRCS humanbodyview.cc )


# kde4_add_ui_files(kritahumanbodyview_PART_SRCS myuifile.ui )

kde4_add_plugin(kritahumanbodyview ${kritahumanbodyview_PART_SRCS})

target_link_libraries(kritahumanbodyview ${KRITA_UI_LIBS} KritaHumanBodyCommon)

install(TARGETS kritahumanbodyview  DESTINATION ${PLUGIN_INSTALL_DIR})


########### install files ###############

install( FILES  humanbodyview.rc  DESTINATION ${DATA_INSTALL_DIR}/kritaplugins)
install( FILES  kritahumanbodyview.desktop  DESTINATION ${SERVICES_INSTALL_DIR})

