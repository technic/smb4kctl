project(smb4kctl)
find_package(KDE4 REQUIRED)

include(KDE4Defaults)
include_directories(${KDE4_INCLUDES})

set(smb4kctl_SRCS smb4kctl.cpp main.cpp)

kde4_add_executable(smb4kctl ${smb4kctl_SRCS})
target_link_libraries(smb4kctl ${KDE4_KDEUI_LIBS} smb4kcore)

install(TARGETS smb4kctl  ${INSTALL_TARGETS_DEFAULT_ARGS})
