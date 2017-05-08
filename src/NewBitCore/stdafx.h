#pragma once

#define NOMINMAX // disable minwindef.h macros

#include <iostream>
#include <string>
#include <unordered_map>
#include <array>
#include <memory>
#include <filesystem>
#include <algorithm>
#include <functional>
#include <utility>
#include <typeinfo>
#include <typeindex>
#include <mutex>
#include <queue>

#ifdef _WIN32
#include <windows.h>
#endif

#include <NewBitSignals\Signal.h>

#define DLL_EXPORT __declspec(dllexport)
