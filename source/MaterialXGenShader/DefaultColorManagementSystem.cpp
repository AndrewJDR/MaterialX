#include <MaterialXGenShader/DefaultColorManagementSystem.h>
#include <MaterialXGenShader/ShaderGenerator.h>

#include <MaterialXCore/Util.h>

namespace MaterialX
{

const string DefaultColorManagementSystem::CMS_NAME = "default_cms";


string DefaultColorManagementSystem::getImplementationName(const ColorSpaceTransform& transform)
{
    return "IM_" + transform.sourceSpace + "_to_" + transform.targetSpace + "_" + transform.type->getName() + "_" + _language;
}

DefaultColorManagementSystemPtr DefaultColorManagementSystem::create(const string& language)
{
    DefaultColorManagementSystemPtr result(new DefaultColorManagementSystem(language));
    return result;
}

DefaultColorManagementSystem::DefaultColorManagementSystem(const string& language)
    : ColorManagementSystem(MaterialX::EMPTY_STRING)
{
    _language = createValidName(language);
}

} // namespace MaterialX
