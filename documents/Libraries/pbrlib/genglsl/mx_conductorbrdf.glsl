#include "pbrlib/genglsl/lib/mx_bsdfs.glsl"
#include "pbrlib/genglsl/lib/mx_refractionindex.glsl"

void mx_conductorbrdf_reflection(vec3 L, vec3 V, float weight, vec3 reflectivity, vec3 edgecolor, roughnessinfo roughness, vec3 normal, vec3 tangent, int distribution, out BSDF result)
{
    if (weight < M_FLOAT_EPS)
    {
        result = BSDF(0.0);
        return;
    }

    float NdotL = dot(normal,L);
    float NdotV = dot(normal,V);
    if (NdotL <= 0.0 || NdotV <= 0.0)
    {
        result = BSDF(0.0);
        return;
    }

    vec3 bitangent = normalize(cross(normal, tangent));

    vec3 H = normalize(L + V);
    float NdotH = dot(normal, H);

    float D = mx_microfacet_ggx_NDF(tangent, bitangent, H, NdotH, roughness.alphaX, roughness.alphaY);
    float G = mx_microfacet_ggx_smith_G(NdotL, NdotV, roughness.alpha);

    vec3 ior_n, ior_k;
    mx_artistic_to_complex_ior(reflectivity, edgecolor, ior_n, ior_k);

    float VdotH = dot(V, H);
    vec3 F = mx_fresnel_conductor(VdotH, ior_n, ior_k);
    F *= weight;

    // Note: NdotL is cancelled out
    result = F * D * G / (4 * NdotV);
}

void mx_conductorbrdf_indirect(vec3 V, float weight, vec3 reflectivity, vec3 edgecolor, roughnessinfo roughness, vec3 normal, vec3 tangent, int distribution, out vec3 result)
{
    if (weight < M_FLOAT_EPS)
    {
        result = vec3(0.0);
        return;
    }

    vec3 ior_n, ior_k;
    mx_artistic_to_complex_ior(reflectivity, edgecolor, ior_n, ior_k);

    vec3 Li = mx_environment_specular(normal, V, tangent, roughness);
    vec3 F = mx_fresnel_conductor(dot(normal, V), ior_n, ior_k);
    F *= weight;
    result = Li * F;
}
