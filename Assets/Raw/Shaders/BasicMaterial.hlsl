#include "StandardData.hlsli"

struct VsOutput
{
    float4 m_pos : SV_POSITION;
    float3 m_normal : NORMAL0;
};

VsOutput VsMain(VsInput input)
{
    VsOutput output;
    output.m_pos = mul(float4(input.m_pos, 1.0f), g_meshInstanceShaderResources.m_mvp);
    output.m_normal = input.m_normal;
    return output;
}

struct PsOutput
{
    float4 m_color : SV_TARGET0;
};

PsOutput PsMain(VsOutput input)
{
    PsOutput output;

    //float3 lightDir = normalize(float3(1.0f, -1.0f, 1.0f));
    //float3 lightColor = float3(1.0f, 1.0f, 1.0f);
    //float lightIntensity = 3.0f;
    //float3 ambientLight = float3(0.25f, 0.25f, 0.25f);

    //float3 albedo = float3(0.5f, 0.0f, 0.0f);

    float3 normal = normalize(input.m_normal);
    //float3 light = saturate(dot(lightDir, normal) * lightColor * lightIntensity) + ambientLight;

    //output.m_color.xyz = albedo * light;
    //output.m_color.w = 1.0f;

    float3 remappedNormal = (normal + 1.0f) * 0.5f;
    output.m_color = float4(remappedNormal, 1.0f);

    return output;
}
