//
// Copyright (c) 2014-2016 THUNDERBEAST GAMES LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include <Urho3D/Container/Str.h>

using namespace Urho3D;

class JSBFunction;
class JSBPackage;
class JSBModule;

namespace ToolCore
{

    class JSBFunctionType;

    class JSBHaxe
    {

    public:

        void Emit(JSBPackage* package, const String& path);

    private:

        String source_;

        void Begin();

        void End();

        void ExportFunction(const JSBFunction* function);

        String GetScriptType(const JSBFunctionType* ftype);
        String GetPrimitiveType(JSBPrimitiveType* ptype);

        bool checkV(JSBClass* clazz, const String name, const String type);
        bool IsOverride(const JSBFunction* function);
        JSBFunction* findFunctionInBase(const JSBFunction* function);

        void ExportEnums(JSBModule* moduleName);
        void ExportModuleConstants(JSBModule*  moduleName);
        void ExportModuleClasses(JSBModule*  moduleName);

        void WriteToFile(const String& path);

        JSBPackage* package_;


    };

}
