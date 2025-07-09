INCLUDE(ExternalProject)

# for the CMAKE_ARGS, the author recommends -DCPACK_PACKAGING_INSTALL_PREFIX=xxx
# but seems on windows this doesn't work

ExternalProject_Add(
    g3log

    GIT_REPOSITORY "https://github.com/KjellKod/g3log"
    GIT_TAG        "2.4"
  
    SOURCE_DIR "${MIR2X_3RD_PARTY_DIR}/g3log"
    INSTALL_DIR "${MIR2X_3RD_PARTY_DIR}/g3log/build"

    UPDATE_COMMAND ""
    PATCH_COMMAND ""

    # seems G3_SHARED_RUNTIME gives me link error on windows
    # CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${MIR2X_3RD_PARTY_DIR}/g3log/build/install -DCMAKE_BUILD_TYPE=Release -DG3_SHARED_LIB=OFF -DG3_SHARED_RUNTIME=OFF
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${MIR2X_3RD_PARTY_DIR}/g3log/build/install -DCMAKE_BUILD_TYPE=Release -DG3_SHARED_LIB=OFF

    LOG_BUILD 1
    LOG_CONFIGURE 1
    LOG_INSTALL 1
)

SET(G3LOG_INCLUDE_DIRS "${MIR2X_3RD_PARTY_DIR}/g3log/build/install/include")
SET(G3LOG_LIBRARIES    "${CMAKE_STATIC_LIBRARY_PREFIX}g3log${CMAKE_STATIC_LIBRARY_SUFFIX}")

INCLUDE_DIRECTORIES(SYSTEM ${G3LOG_INCLUDE_DIRS})
LINK_DIRECTORIES(${MIR2X_3RD_PARTY_DIR}/g3log/build/install/lib)
ADD_DEPENDENCIES(mir2x_3rds g3log)
