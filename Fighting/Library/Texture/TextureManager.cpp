#include "TextureManager.h"

Lib::TextureManager::~TextureManager()
{
}

void Lib::TextureManager::Init(ID3D11Device* _pDevice)
{
	m_pDevice = _pDevice;
}

bool Lib::TextureManager::Load(LPCTSTR _pFileName, int* _index)
{
	ID3D11ShaderResourceView* pResourceView = NULL;
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice,
		_pFileName,
		NULL,
		NULL,
		&pResourceView,
		NULL)))
	{
		OutputDebugString(TEXT("テクスチャの読み込みに失敗しました\n"));
		return false;
	}

	*_index = m_pTextureResourceView.size();
	m_pTextureResourceView.push_back(pResourceView);	
	return true;
}

void Lib::TextureManager::ReleaseTexture(int _index)
{
	if (m_pTextureResourceView[_index] != NULL)
	{
		m_pTextureResourceView[_index]->Release();
		m_pTextureResourceView[_index] = NULL;
	}
}
