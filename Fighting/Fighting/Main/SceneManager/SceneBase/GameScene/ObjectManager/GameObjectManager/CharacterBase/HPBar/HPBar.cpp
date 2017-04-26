/**
 * @file   HPBar.cpp
 * @brief  HPBarクラスの実装
 * @author kotani
 */
#include "HPBar.h"
#include "Texture/TextureManager.h"
#include "Dx11/DX11Manager.h"
#include "Window/Window.h"

const D3DXVECTOR2 HPBar::m_HPBarRect = D3DXVECTOR2(500, 70);

HPBar::HPBar(const D3DXVECTOR2*  _pos) :
m_Pos(*_pos)
{
	SINGLETON_INSTANCE(Lib::TextureManager).
		Load("Resource/Texture/GameScene/HPbarFrame.png", &m_BarFrameTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).
		Load("Resource/Texture/GameScene/HPbar.png", &m_BarTextureIndex);

	m_UV[0] = D3DXVECTOR2(0, 0);
	m_UV[1] = D3DXVECTOR2(1, 0);
	m_UV[2] = D3DXVECTOR2(0, 1);
	m_UV[3] = D3DXVECTOR2(1, 1);

	// Lib::Vertex2D Init
	m_pVertex.reset(new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle()));

	m_pVertex->Init(&m_HPBarRect, m_UV);
	m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).
		GetTexture(m_BarTextureIndex));
	
	m_pBarFrameVertex.reset(new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle()));

	m_pBarFrameVertex->Init(&m_HPBarRect, m_UV);
	m_pBarFrameVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).
		GetTexture(m_BarFrameTextureIndex));
	// Lib::Vertex2D Init end
}

HPBar::~HPBar()
{
	m_pBarFrameVertex->Release();
	m_pVertex->Release();
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_BarTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_BarFrameTextureIndex);
}


//----------------------------------------------------------------------------------------------------
// Public Function
//----------------------------------------------------------------------------------------------------

void HPBar::Update()
{
}

void HPBar::Draw(int _hp)
{
	RECT g_RectBar = { 0, 0, -(500 - (_hp * 5)), 0 };
	m_pVertex->Draw(&m_Pos,&g_RectBar, m_UV);
	m_pBarFrameVertex->Draw(&m_Pos, m_UV);
}
