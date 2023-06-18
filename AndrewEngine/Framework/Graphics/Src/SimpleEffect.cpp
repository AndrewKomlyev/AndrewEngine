#include "Precompiled.h"
#include "SimpleEffect.h"

#include "Camera.h"
#include "MeshBuffer.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;

void SimpleEffect::Initialize()
{
	std::filesystem::path filePath = L"../../Assets/Shaders/DoTransform.fx";
	mVertexShader.Initialize<VertexPC>(filePath);
	mPixelShader.Initialize(filePath);
	mConstantBuffer.Initialize(sizeof(AEMath::Matrix4));
	mBlendState.Initialize(BlendState::Mode::AlphaBlend);
}

void SimpleEffect::Terminate()
{
	mBlendState.Terminate();
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void SimpleEffect::Begin()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mConstantBuffer.BindVS(0);
	mBlendState.Set();
}

void SimpleEffect::End()
{
	mBlendState.ClearState();
}

void SimpleEffect::Render(const RenderObject& renderObject)
{
	AEMath::Matrix4 matWorld = renderObject.transform.GetMatrix4();
	AEMath::Matrix4 matView = mCamera->GetViewMatrix();
	AEMath::Matrix4 matProj = mCamera->GetProjectionMatrix();
	AEMath::Matrix4 matFinal = matWorld * matView * matProj;
	AEMath::Matrix4 wvp = Transpose(matFinal);

	mConstantBuffer.Update(&wvp);
	
	renderObject.meshBuffer.Render();
}

void SimpleEffect::SetCamera(const Camera& camera)
{
	mCamera = &camera;
}
