#
# Copyright (c) 2008-2017 the Urho3D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

add_subdirectory(FreeType)
add_subdirectory(JO)
add_subdirectory(LZ4)
add_subdirectory(PugiXml)
add_subdirectory(rapidjson)
add_subdirectory(SDL)
add_subdirectory(StanHull)
add_subdirectory(STB)
add_subdirectory(Mustache)
add_subdirectory(IconFontCppHeaders)

if (URHO3D_SYSTEMUI)
    add_subdirectory(imgui)
    add_subdirectory(ImGuizmo)
endif ()

if (URHO3D_NETWORK)
    add_subdirectory (Civetweb)
    add_subdirectory (kNet)
endif ()

if (URHO3D_IK)
    add_subdirectory (ik)
endif ()

if (URHO3D_NAVIGATION)
    add_subdirectory (Detour)
    add_subdirectory (DetourCrowd)
    add_subdirectory (DetourTileCache)
    add_subdirectory (Recast)
endif ()

if (URHO3D_URHO2D)
    add_subdirectory (Box2D)
endif ()

if (URHO3D_WEBP)
    add_subdirectory (WebP)
endif ()

if (URHO3D_PHYSICS)
    add_subdirectory (Bullet)
endif ()

if (URHO3D_PROFILING)
    set (EASY_PROFILER_NO_SAMPLES ON)
    add_subdirectory (easy_profiler)
endif ()

if (NOT ANDROID AND NOT ARM AND NOT WEB)
    if (URHO3D_OPENGL)
        add_subdirectory (GLEW)
    elseif (URHO3D_D3D9)
        add_subdirectory (MojoShader)
    endif ()
    if (WIN32 OR APPLE)
        add_subdirectory (LibCpuId)
    endif ()
endif ()

if (URHO3D_TOOLS)
    add_subdirectory(poco)
    add_subdirectory(Assimp)
endif ()
if (URHO3D_SYSTEMUI)
    add_subdirectory(tinyfiledialogs)
endif ()

# Group third party dependencies into ThirdParty subfolder in VS solution.
file(GLOB third_party_dirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach (lib ${third_party_dirs})
    if (TARGET ${lib})
        set_target_properties(${lib} PROPERTIES FOLDER ThirdParty)
    endif ()
endforeach ()
if (TARGET profiler_gui)
    set_target_properties(profiler_gui PROPERTIES FOLDER Tools)
endif ()
