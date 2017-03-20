/**
 * @file   DSoundLoader.h
 * @brief  DSoundLoaderクラスのヘッダファイル
 * @author kotani
 */
#ifndef DSOUNDLOADER_H
#define DSOUNDLOADER_H
#include <dsound.h>
#include "Singleton.h"

namespace Lib
{
	/**
	 * サウンドの読み込みをするクラス
	 */
	class DSoundLoader
	{
	public:
		/**
		 * 初期化処理
		 * @param[in] _pDSound8 IDirectSound8へのポインタ
		 */
		static void Init(IDirectSound8* _pDSound8)
		{
			m_pDSound8 = _pDSound8;
		}

		/**
		 * waveサウンド読み込み
		 * @param[in] _pFileName 読み込むサウンドのパス
		 */
		static LPDIRECTSOUNDBUFFER8 LoadWave(LPSTR _pFileName);

	private:
		DSoundLoader(){};
		~DSoundLoader(){};
		/**
		 * waveファイル内のデータを読み出す関数
		 * @param[in] _pFileName 開くファイルの名前
		 * @param[out] _pWaveFormat 読み込んだwaveファイルのフォーマット
		 * @param[out] _pWaveData 読み込んだwaveファイルのデータ
		 * @param[out] _pWaveSize 読み込んだwaveファイルのサイズ
		 */
		static bool ReadWave(LPSTR _pFileName, WAVEFORMATEX* _pWaveFormat, BYTE** _pWaveData, DWORD* _pWaveSize);

		static IDirectSound8* m_pDSound8;

	};
}



#endif
