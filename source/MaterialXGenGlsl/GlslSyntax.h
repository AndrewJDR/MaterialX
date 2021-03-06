#ifndef MATERIALX_GLSL_SYNTAX_H
#define MATERIALX_GLSL_SYNTAX_H

#include <MaterialXGenShader/Syntax.h>

namespace MaterialX
{

/// Syntax class for GLSL (OpenGL Shading Language)
class GlslSyntax : public Syntax
{
    using ParentClass = Syntax;

public:
    GlslSyntax();

    static SyntaxPtr create() { return std::make_shared<GlslSyntax>(); }

    const string& getOutputQualifier() const override;
    const string& getConstantQualifier() const override { return CONSTANT_QUALIFIER; };
    const string& getUniformQualifier() const override { return UNIFORM_QUALIFIER; };
    bool typeSupported(const TypeDesc* type) const override;

    static const string OUTPUT_QUALIFIER;
    static const string UNIFORM_QUALIFIER;
    static const string CONSTANT_QUALIFIER;

    static const vector<string> VEC2_MEMBERS;
    static const vector<string> VEC3_MEMBERS;
    static const vector<string> VEC4_MEMBERS;
};

} // namespace MaterialX

#endif
