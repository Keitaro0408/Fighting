/**
 * @file   DSoundContainer.h
 * @brief  DSoundContainerクラスのヘッダファイル
 * @author kotani
 */
#ifndef SOUNDCONTAINER_H
#define SOUNDCONTAINER_H
#include <dsound.h>
#include <vector>
#include "Singleton.h"

namespace Lib
{
	/**
	 * サウンドデータを入れておくクラス
	 */
	class DSoundContainer
	{
		friend Singleton<DSoundContainer>;
	public:
		/**
		 * サウンドのリソースを追加
		 * @param[in] _pSound 読み込んだサウンド(NULLだと追加されない)
		 * @param[out] _index 読み込んだサウンドのインデックス
		 */
		void Add(LPDIRECTSOUNDBUFFER8 _pSound, int* _index);

		/**
		 * 音声の開放
		 * @param[in] _index 開放先のインデックス
		 */
		void ReleaseSound(int _index);
		
		/**
		 * 音声の取得
		 * @param[in] _index 格納先のインデックス
		 * @return 読み込んだサウンドバッファー
		 */
		inline LPDIRECTSOUNDBUFFER8& GetSound(int _index)
		{
			return m_pSound[_index];
		}

		inline int GetSoundMaxNum()
		{
			return m_pSound.size();
		}

		/**
		 * サウンドのバッファーを開放する
		 */
		inline void ClearBuffer()
		{
			m_pSound.clear();
		}

	private:
		DSoundContainer() :
			m_hWnd(NULL){}
		~DSoundContainer(){};

		HWND m_hWnd;
		std::vector<LPDIRECTSOUNDBUFFER8> m_pSound;

	};
}

#endif
