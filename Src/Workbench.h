#pragma once

struct CommandLineArgs
{
    static const size_t kMaxNumArgs = 10;
    const char* m_keys[kMaxNumArgs];
    const char* m_values[kMaxNumArgs];
    size_t m_numArgs = 0;

    bool HasKey(const char* key, int* pOutIndexOptional = nullptr) const;
    bool GetArgAsInt(const char* key, int* pOutInt) const;
    bool GetArgAsFloat(const char* key, float* pOutFloat) const;
    bool GetArgAsString(const char* key, const char** pOutString) const;
};

void WorkbenchRun(const CommandLineArgs& args);
