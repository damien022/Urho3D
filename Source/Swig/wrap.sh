#!/usr/bin/env sh
swig -c++ -I.. -outdir Urho3DNET -o Urho3DNET_swig.cxx -csharp -dllimport Urho3D.so -namespace Urho3D Urho3DAll.i
