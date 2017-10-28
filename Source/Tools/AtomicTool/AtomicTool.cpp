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

#include "AtomicTool.h"
#include "JSBind/JSBind.h"

URHO3D_DEFINE_APPLICATION_MAIN(AtomicTool::AtomicTool);

using namespace ToolCore;

namespace AtomicTool
{

AtomicTool::AtomicTool(Context* context)
    : Application(context)
{

}

void AtomicTool::Setup()
{
    auto logLevel = LOG_INFO;
    options_.add_option("-l,--loglevel", logLevel, "Set log level");
    bindCommand_ = SharedPtr<BindCommand>(new BindCommand(&options_));

    std::vector<std::string> arguments;
    for (auto& arg: GetArguments())
        arguments.emplace_back(arg.CString());
    std::reverse(arguments.begin(), arguments.end());

    try
    {
        options_.parse(arguments);
    }
    catch (const CLI::CallForHelp& e)
    {
        logLevel = LOG_NONE;
        std::cout << options_.help(80);
        engine_->Exit();
    }
    catch (const CLI::ParseError& e)
    {
        logLevel = LOG_NONE;
        std::cout << e.what();
        engine_->Exit();
    }

    engineParameters_[EP_HEADLESS] = true;
    engineParameters_[EP_FULL_SCREEN] = false;
    engineParameters_[EP_LOG_LEVEL] = logLevel;
    // no default resources, AtomicTool may be run outside of source tree
    engineParameters_[EP_RESOURCE_PATHS] = "";
}

void AtomicTool::Start()
{
    if (bindCommand_->options->parsed())
    {
        SharedPtr<JSBind> jsbind(new JSBind(context_));
        context_->RegisterSubsystem(jsbind);

        URHO3D_LOGINFOF("Loading Package");
        jsbind->LoadPackage(
            AddTrailingSlash(bindCommand_->sourceRoot.c_str()),
            AddTrailingSlash(bindCommand_->packageDirectory.c_str())
        );

        jsbind->GenerateCSharpBindings();

    }

    engine_->Exit();
}

}
