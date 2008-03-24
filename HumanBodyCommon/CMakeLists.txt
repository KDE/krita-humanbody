
set(kritahumanbodycommon_PART_SRCS
    HumanBodyDecoration.cc
    HumanBody.cc
    HumanBodyFoot.cc
    HumanBodyHand.cc
    HumanBodyHead.cc
    HumanBodyLink.cc
    HumanBodyMuscle.cc
    HumanBodyNode.cc
    HumanBodyParameters.cc
    HumanBodyPelvis.cc
     )


kde4_add_library(KritaHumanBodyCommon SHARED ${kritahumanbodycommon_PART_SRCS})

target_link_libraries(KritaHumanBodyCommon ${KRITA_UI_LIBS})

install(TARGETS KritaHumanBodyCommon DESTINATION ${LIB_INSTALL_DIR})
