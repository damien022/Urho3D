add_definitions(-DCPLUSPLUS_WITHOUT_QT)

file (GLOB_RECURSE SOURCE_FILES *.cpp *.h)

if (APPLE)
    file (GLOB_RECURSE OBJC_FILES *.mm )
    set (SOURCE_FILES ${SOURCE_FILES} ${OBJC_FILES})
endif()

add_executable(AtomicTool ${SOURCE_FILES})

target_link_libraries(AtomicTool Assimp poco Urho3D)

if (URHO3D_XCODE)
    target_compile_definitions(AtomicTool PRIVATE -DURHO3D_XCODE)
endif ()

group_sources("Assets")
group_sources("Build")
group_sources("Command")
group_sources("Import")
group_sources("JSBind")
group_sources("License")
group_sources("Net")
group_sources("Platform")
group_sources("Project")
group_sources("Subprocess")
group_sources("NETTools")
