#pragma once

// Resolve the executable directory before the original relative file I/O runs.
bool initializeRuntime(const char* executableArgument);
