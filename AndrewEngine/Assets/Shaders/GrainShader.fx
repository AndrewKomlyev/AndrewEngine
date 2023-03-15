cbuffer GrainEffectData : register(b0)
{
    float param0;
    float param1;
    float param2;
    float param3;
}

Texture2D textureMap0 : register(t0);
Texture2D textureMapImage : register(t1);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position, 1.0f);
    output.texCoord = input.texCoord;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 finalColor;
    
    
    
    float4 color0 = textureMapImage.Sample(textureSampler, input.texCoord) * param0;
    float4 color1 = textureMap0.Sample(textureSampler, input.texCoord) * param1;
    finalColor = color0 + color1;
    
    
    return finalColor;

}