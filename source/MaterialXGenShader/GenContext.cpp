#include <MaterialXGenShader/GenContext.h>

namespace MaterialX
{

void GenContext::addInputSuffix(const ShaderInput* input, const string& suffix)
{
    _inputSuffix[input] = suffix;
}

void GenContext::removeInputSuffix(const ShaderInput* input)
{
    _inputSuffix.erase(input);
}

void GenContext::getInputSuffix(const ShaderInput* input, string& suffix) const
{
    suffix.clear();
    std::unordered_map<const ShaderInput*, string>::const_iterator iter = _inputSuffix.find(input);
    if (iter != _inputSuffix.end())
    {
        suffix = iter->second;
    }
}

void GenContext::addOutputSuffix(const ShaderOutput* output, const string& suffix)
{
    _outputSuffix[output] = suffix;
}

void GenContext::removeOutputSuffix(const ShaderOutput* output)
{
    _outputSuffix.erase(output);
}

void GenContext::getOutputSuffix(const ShaderOutput* output, string& suffix) const
{
    suffix.clear();
    std::unordered_map<const ShaderOutput*, string>::const_iterator iter = _outputSuffix.find(output);
    if (iter != _outputSuffix.end())
    {
        suffix = iter->second;
    }
}

} // namespace MaterialX
