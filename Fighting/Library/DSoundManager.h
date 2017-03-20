#ifndef DSOUNDMANAGER_H
#define DSOUNDMANAGER_H
#include "Singleton.h"
#include "DSound.h"
#include "DSoundContainer.h"
#include "DSoundLoader.h"

namespace Lib
{
	/**
	* サウンドを操作するためのenum
	*/
	enum SOUND_OPERATION
	{
		SOUND_PLAY,		  //!< サウンドを再生する
		SOUND_STOP,		  //!< サウンドを停止する
		SOUND_LOOP,		  //!< サウンドをループ再生する
		SOUND_START_PLAY, //!< サウンドをリセットして再生する
		SOUND_STOP_RESET  //!< サウンドを停止してリセットする
	};

	class DSoundManager
	{
		friend Singleton<DSoundManager>;
	public:
		/**
		 * DSoundManagerクラスの初期化関数
		 * @param[in] _hWnd ウィンドウハンドル。コンストラクタ内で使う
		 * @return 成功したらtrue
		 */
		bool Init(HWND _hWnd);

		/**
		 * DSoundManagerクラスの解放関数
		 */
		void Release();

		/**
		 * サウンドの操作関数
		 * @param[in] _pSoundBuffer 操作するサウンドのインデックス
		 * @param[in] _operation どのような操作をするか
		 */
		void SoundOperation(int _index, SOUND_OPERATION _operation);

		/**
		 * サウンドの音量調節
		 * @param[in] _index 操作するサウンドのインデックス
		 * @param[in] _volume 音量の数値(0が最大音で-10000が無音)
		 */
		void SetVolume(int _index, int _volume);

		/**
		 * サウンドの読み込み
		 * @param[in] _pFileName 読み込むサウンドのパス
		 * @param[out] _index 読み込んだサウンドへのインデックスが入る
		 * @return 成功すればtrue
		 */
		bool Load(LPCTSTR _pFileName, int* _index);

		/**
		 * サウンドの開放
		 * @param[in] _index 開放するサウンドのインデックス
		 */
		inline void ReleaseSound(int _index)
		{
			SINGLETON_INSTANCE(DSoundContainer).ReleaseSound(_index);
		}

	private:
		DSoundManager() :
			m_pDSound8(NULL),
			m_hWnd(NULL){};
		~DSoundManager(){};

		IDirectSound8*					  m_pDSound8;
		HWND							  m_hWnd;

	};
}

#endif
