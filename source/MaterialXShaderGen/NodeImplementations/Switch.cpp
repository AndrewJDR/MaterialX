#include <MaterialXShaderGen/NodeImplementations/Switch.h>
#include <MaterialXShaderGen/Shader.h>
#include <MaterialXShaderGen/ShaderGenerator.h>

namespace MaterialX
{

DEFINE_NODE_IMPLEMENTATION(Switch, "switch", "", "")

const vector<string> Switch::kInputNames = { "in1", "in2", "in3", "in4", "in5" };

void Switch::emitFunctionCall(const SgNode& sgnode, ShaderGenerator& shadergen, Shader& shader)
{
    const Node& node = sgnode.getNode();

    // Declare the output variable
    shader.beginLine();
    shadergen.emitOutput(node, true, shader);
    shader.endLine();

    static const vector<string> inputNames = { "in1", "in2", "in3", "in4", "in5" };
    const ParameterPtr which = node.getParameter("which");

    // Process the five branches of the switch node
    for (int branch = 0; branch < 5; ++branch)
    {
        const InputPtr input = node.getInput(inputNames[branch]);

        shader.beginLine();
        if (branch > 0)
        {
            shader.addStr("else ");
        }
        if (branch < 5)
        {
            shader.addStr("if ("); shadergen.emitInput(*which, shader); shader.addStr(" < "); shader.addValue(float(branch+1));  shader.addStr(")");
        }
        shader.endLine(false);

        shader.beginScope();

        // Emit nodes that are ONLY needed in this scope
        // TODO: Performance warning, iterating all nodes in the graph!
        for (const SgNode& sg : shader.getNodes())
        {
            const SgNode::ScopeInfo& scope = sg.getScopeInfo();
            if (scope.conditionalNode == sgnode.getNodePtr() && scope.usedByBranch(branch))
            {
                shadergen.emitFunctionCall(sg, shader);
            }
        }

        shader.beginLine();
        shadergen.emitOutput(node, false, shader);
        shader.addStr(" = ");
        shadergen.emitInput(*input, shader);
        shader.endLine();

        shader.endScope();
    }
}

} // namespace MaterialX
