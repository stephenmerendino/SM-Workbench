#include "StandardData.hlsli"

struct DebugMaterialPushConstants
{
    float4 m_color;
};
[[vk::push_constant]] DebugMaterialPushConstants g_debugMaterialPushConstants;

struct VsOutput
{
    float4 m_pos : SV_POSITION;
};

VsOutput VsMain(VsInput input)
{
    VsOutput output;
    output.m_pos = mul(float4(input.m_pos, 1.0f), g_meshInstanceShaderResources.m_mvp);
    return output;
}

VsOutput VsLineMain(VsLineInput input)
{
    VsOutput output;
    output.m_pos = mul(float4(input.m_pos, 1.0f), g_meshInstanceShaderResources.m_mvp);
    return output;
}

struct PsOutput
{
    float4 m_color : SV_TARGET0;
};

PsOutput PsMain(VsOutput input)
{
    PsOutput output;
    output.m_color = g_debugMaterialPushConstants.m_color;
    return output;
}

PsOutput DrawBehindGeoPsMain(VsOutput input)
{
    PsOutput output;
    output.m_color = g_debugMaterialPushConstants.m_color;
    return output;
}
