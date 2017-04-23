#include "TextureLoader.h"

ID3D11Device* Lib::TextureLoader::m_pDevice = NULL;


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

ID3D11ShaderResourceView* Lib::TextureLoader::Load(LPCTSTR _pFileName)
{
	D3DX11_IMAGE_LOAD_INFO LoadInfo;
	ZeroMemory(&LoadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
	LoadInfo.Width = D3DX11_DEFAULT;
	LoadInfo.Height = D3DX11_DEFAULT;
	LoadInfo.Depth = D3DX11_DEFAULT;
	LoadInfo.FirstMipLevel = D3DX11_DEFAULT;
	LoadInfo.MipLevels = 1;
	LoadInfo.Usage = D3D11_USAGE_DEFAULT;
	LoadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	LoadInfo.CpuAccessFlags = 0;
	LoadInfo.MiscFlags = 0;
	LoadInfo.Format = DXGI_FORMAT_FROM_FILE;
	LoadInfo.Filter = D3DX11_FILTER_POINT;
	LoadInfo.MipFilter = D3DX11_FILTER_POINT;
	LoadInfo.pSrcInfo = NULL;

	ID3D11ShaderResourceView* pResourceView = NULL;
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice,
		_pFileName,
		&LoadInfo,
		NULL,
		&pResourceView,
		NULL)))
	{
		OutputDebugString(TEXT("テクスチャの読み込みに失敗しました\n"));
	}

	return pResourceView;
}