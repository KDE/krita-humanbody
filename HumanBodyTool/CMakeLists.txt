include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../HumanBodyCommon)

set(kritatoolhumanbodytool_PART_SRCS
    tool_humanbodytool.cc
    kis_tool_humanbodytool.cc
    ConstraintSolver.cc
    )

kde4_add_ui_files(kritatoolhumanbodytool_PART_SRCS HumanBodyToolOptions.ui )

kde4_add_plugin(kritatoolhumanbodytool ${kritatoolhumanbodytool_PART_SRCS})



target_link_libraries(kritatoolhumanbodytool ${KRITA_UI_LIBS} ${FLAKE_LIBS} KritaHumanBodyCommon)

install(TARGETS kritatoolhumanbodytool  DESTINATION ${PLUGIN_INSTALL_DIR})


########### install files ###############

# install( FILES  tool_humanbodytool.png  DESTINATION ${DATA_INSTALL_DIR}/krita/pics)
install( FILES  kritatoolhumanbodytool.desktop  DESTINATION ${SERVICES_INSTALL_DIR})


