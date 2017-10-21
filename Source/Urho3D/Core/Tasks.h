//
// Copyright (c) 2008-2017 the Urho3D project.
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

#include "../Container/List.h"
#include "../Core/Object.h"
#include "../Core/Thread.h"
#include "../Core/Timer.h"

namespace Urho3D
{
class TaskScheduler;
class Tasks;

enum TaskState
{
    /// Task was created, but not executed yet.
    TSTATE_CREATED,
    /// Task was switched to at least once.
    TSTATE_EXECUTING,
    /// Task finished execution and should not be rescheduled.
    TSTATE_FINISHED,
    /// Task termination was requested.
    TSTATE_TERMINATE,
};

/// Default task size.
static const unsigned DEFAULT_TASK_SIZE = 1024 * 5;

/// Object representing a single cooperative t
class URHO3D_API Task : public RefCounted
{
public:
    /// Construct empty task. It can not be scheduled.
    Task() = default;
    /// Construct a task. It has to be manually scheduled by calling Task::SwitchTo(). Caller is responsible for freeing
    /// returned object after task finishes execution.
    Task(const std::function<void()>& taskFunction, unsigned stackSize = DEFAULT_TASK_SIZE);
    /// Destruct.
    ~Task();
    /// Return true if task is still executing.
    bool IsAlive() const { return state_ != TSTATE_FINISHED; };
    /// Return true if task is supposed to terminate shortly.
    bool IsTerminating() const { return state_ == TSTATE_TERMINATE; };
    /// Return true if task is ready, false if task is still sleeping.
    bool IsReady();
    /// Suspend execution of current task. Must be called from within function invoked by callback passed to
    /// TaskScheduler::Create() or Tasks::Create().
    void Suspend(float time = 0.f);
    /// Explicitly switch execution to specified task. Task must be created on the same thread where this function is
    /// called. Task can be switched to at any time.
    bool SwitchTo();
    /// Request task termination. If exception support is disabled then user must return from the task manually when
    /// IsTerminating() returns true. If exception support is enabled then task will be terminated next time Suspend()
    /// method is called. Suspend() will throw an exception that will be caught out-most layer of the task.
    void Terminate() { state_ = TSTATE_TERMINATE; }
    /// Get current thread task. Other tasks should switch into returned task periodically. This function must be called
    /// at least once before creating tasks. Do not store return value in a shared pointer.
    static Task* GetThreadTask();

protected:
    /// Handles task execution. Should not be called by user.
    void ExecuteTask();
    /// Starts execution of a task using fiber API.
    static void ExecuteTaskWrapper(void* parameter);

    /// Fiber context.
    void* fiber_ = nullptr;
    /// Timer which keeps track of how long task should sleep.
    Timer sleepTimer_{};
    /// Number of milliseconds task should sleep for.
    unsigned sleepMSec_ = 0;
    /// Procedure that executes the task.
    std::function<void()> taskProc_;
    /// Current state of the task.
    TaskState state_ = TSTATE_CREATED;
    /// Thread id on which task was created.
    ThreadID threadID_ = Thread::GetCurrentThreadID();

    friend class TaskScheduler;
    friend class Tasks;
};

/// Task scheduler used for scheduling concurrent tasks.
class URHO3D_API TaskScheduler : public Object
{
    URHO3D_OBJECT(TaskScheduler, Object);

public:
    /// Construct.
    explicit TaskScheduler(Context* context);
    /// Destruct.
    ~TaskScheduler() override;

    /// Create a task and schedule it for execution.
    Task* Create(const std::function<void()>& taskFunction, unsigned stackSize = DEFAULT_TASK_SIZE);
    /// Return number of active tasks.
    unsigned GetActiveTaskCount() const;
    /// Schedule tasks created by Create() method. This has to be called periodically, otherwise tasks will not run.
    void ExecuteTasks();
    /// Schedule tasks continuously until all of them exit.
    void ExecuteAllTasks();

private:
    /// List of tasks for every event tasks are executed on.
    List<SharedPtr<Task>> tasks_;
};

/// Suspend execution of current task. Must be called from within function invoked by callback passed to
/// TaskScheduler::Create() or Tasks::Create().
URHO3D_API void SuspendTask(float time = 0.f);

/// Tasks subsystem. Handles execution of tasks on the main thread.
class URHO3D_API Tasks : public Object
{
    URHO3D_OBJECT(Tasks, Object);

public:
    /// Construct.
    explicit Tasks(Context* context);
    /// Create a task and schedule it for execution.
    Task* Create(StringHash eventType, const std::function<void()>& taskFunction,
                 unsigned stackSize = DEFAULT_TASK_SIZE);
    /// Return number of active tasks.
    unsigned GetActiveTaskCount() const;

private:
    /// Schedule tasks created by Create() method.
    void ExecuteTasks(StringHash eventType);

    /// Task schedulers for each scene event.
    HashMap<StringHash, SharedPtr<TaskScheduler>> taskSchedulers_;
};
};
