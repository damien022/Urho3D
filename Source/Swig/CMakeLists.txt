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

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Urho3DNET)
add_custom_target(Urho3DNET
    COMMAND swig -c++ -O -fastdispatch -fvirtual
            -I${Urho3D_SOURCE_DIR}/Source
            -w473                   # Returning a pointer or reference in a director method is not recommended.
            -w516                   # Overloaded method XX ignored, using YY instead. Usually spam about const vs non-const methods, defaults to non-consts.
            -outdir Urho3DNET
            -o Urho3DNET_swig.cxx
            -csharp
            -dllimport Urho3D.so
            -namespace Urho3D
            ${CMAKE_CURRENT_SOURCE_DIR}/Urho3DAll.i
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
