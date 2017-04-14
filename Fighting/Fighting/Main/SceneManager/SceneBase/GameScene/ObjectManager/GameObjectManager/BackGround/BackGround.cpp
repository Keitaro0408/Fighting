/**
 * @file   BackGround.cpp
 * @brief  BackGroundクラスの実装
 * @author kotani
 */
#include "BackGround.h"
#include "TextureManager.h"
#include "DX11Manager.h"
#include "Window.h"

const D3DXVECTOR2 BackGround::m_Pos = D3DXVECTOR2(640,360);
const D3DXVECTOR2 BackGround::m_RectSize = D3DXVECTOR2(1280, 720);


BackGround::BackGround()
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/Texture/GameScene/stage.png",&m_TextureIndex);

	m_pVertex.reset(new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle()));
	
	m_UV[0] = D3DXVECTOR2(0, 0);
	m_UV[1] = D3DXVECTOR2(1, 0);
	m_UV[2] = D3DXVECTOR2(0, 1);
	m_UV[3] = D3DXVECTOR2(1, 1);

	m_pVertex->Init(&m_RectSize, m_UV);
	m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
}


BackGround::~BackGround()
{
	if (m_pVertex != NULL)
	{
		m_pVertex->Release();
	}

	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void BackGround::Update()
{

}

void BackGround::Draw()
{
	m_pVertex->Draw(&m_Pos, m_UV);
}
