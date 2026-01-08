#pragma pack_matrix(row_major)

// Global
SamplerState g_globalPointSampler : register(s0, space0);
SamplerState g_globalLinearSampler : register(s1, space0);

// Frame
struct FrameShaderResources
{
	float m_elapsedTimeSeconds;
	float m_deltaTimeSeconds;
};
ConstantBuffer<FrameShaderResources> g_frameShaderResources : register(b0, space1);

// Mesh Instance
struct MeshInstanceShaderResources
{
	float4x4 m_mvp;
};
ConstantBuffer<MeshInstanceShaderResources> g_meshInstanceShaderResources : register(b0, space2);

struct VsInput
{
	[[vk::location(0)]] float3 m_pos : POSITION0;
	[[vk::location(1)]] float2 m_uv : UV0;
	[[vk::location(2)]] float3 m_color : COLOR0;
	[[vk::location(3)]] float3 m_normal : NORMAL0;
};
