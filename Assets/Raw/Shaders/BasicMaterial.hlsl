#include "StandardData.hlsli"

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

struct PsOutput
{
    float4 m_color : SV_TARGET0;
};

PsOutput PsMain(VsOutput input)
{
    PsOutput output;
    output.m_color = float4(0.0f, 1.0f, 0.0f, 1.0f);
    return output;
}
