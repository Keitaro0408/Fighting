/**
 * @file   HPBar.cpp
 * @brief  HPBarクラスの実装
 * @author kotani
 */
#include "HPBar.h"
#include "TextureManager.h"
#include "DX11Manager.h"
#include "Window.h"

namespace
{
	RECT g_RectBar = {0,0,0,0};
}

HPBar::HPBar(D3DXVECTOR2*  _pos) :
m_Pos(*_pos)
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/GameScene/Character.png", &m_TextureIndex);
	m_UV[0] = D3DXVECTOR2(0, 0);
	m_UV[1] = D3DXVECTOR2(1, 0);
	m_UV[2] = D3DXVECTOR2(0, 1);
	m_UV[3] = D3DXVECTOR2(1, 1);

	// Lib::Vertex2D Init
	m_pVertex.reset(new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle()));

	m_pVertex->Init(&D3DXVECTOR2(524,125), m_UV);

	m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).
		GetTexture(m_TextureIndex));
	// Lib::Vertex2D Init end


}

HPBar::~HPBar()
{
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
	m_pVertex->Release();

}


//----------------------------------------------------------------------------------------------------
// Public Function
//----------------------------------------------------------------------------------------------------

void HPBar::Update()
{
}

void HPBar::Draw()
{
	m_pVertex->Draw(&m_Pos,&g_RectBar, m_UV);
}
