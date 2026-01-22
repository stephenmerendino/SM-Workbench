#include "StandardData.hlsli"

struct VsOutput
{
    float4 m_pos : SV_POSITION;
    float4 m_color : COLOR0;
};

VsOutput VsMain(VsInput input)
{
    VsOutput output;
    output.m_pos = mul(float4(input.m_pos, 1.0f), g_meshInstanceShaderResources.m_mvp);
    output.m_color = float4(input.m_color, 1.0f);
    return output;
}

struct PsOutput
{
    float4 m_color : SV_TARGET0;
};

PsOutput PsMain(VsOutput input)
{
    PsOutput output;
    output.m_color = input.m_color;
    return output;
}

PsOutput XRayPsMain(VsOutput input)
{
    PsOutput output;
    output.m_color = float4(input.m_color.xyz, 0.5f);
    return output;
}
