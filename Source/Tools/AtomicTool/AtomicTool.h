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

#include <Urho3D/Urho3DAll.h>
#include <ThirdParty/CLI11/CLI11.hpp>

using namespace Urho3D;

namespace AtomicTool
{


struct BindCommand : public RefCounted
{
    explicit BindCommand(CLI::App* parentOptions)
    {
        options = parentOptions->add_subcommand("bind", "Generate .NET bindings");
        options->add_option("root", sourceRoot, "Root source directory")->required();
        options->add_option("package", packageDirectory, "Package directory")->required();
    }

    CLI::App* options = nullptr;
    std::string sourceRoot;
    std::string packageDirectory;
};

class AtomicTool : public Application
{
    URHO3D_OBJECT(AtomicTool, Application)

public:

    explicit AtomicTool(Context* context);
    ~AtomicTool() override = default;

    void Setup() override;
    void Start() override;

protected:
    CLI::App options_{"Tool that manages atoms."};
    SharedPtr<BindCommand> bindCommand_;
};

}
