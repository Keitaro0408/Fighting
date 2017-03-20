/**
 * @file   DirectShowSound.h
 * @brief  DirectShowSoundクラスのヘッダファイル
 * @author kotani
 */
#ifndef DirectShowSound_H
#define DirectShowSound_H
#include <atlstr.h>
#include <dshow.h>
#include <vector>
#include "Singleton.h"
#include "DSoundManager.h"

namespace Lib
{
	/**
	 * サウンドの再生と管理を行うクラス
	 * mp3等の音声も再生出来るが、ウィンドウが有効化されていない時も音声が再生される
	 */
	class DirectShowSound
	{
		friend Singleton<DirectShowSound>;
	public:
		/**
		 * メディアファイルを読み込む
		 * @param[in] _fileName 読み込むファイルのパス
		 * @param[out] _index 読み込んだサウンドのインデックス
		 * @return 読み込みに成功すればtrue
		 */
		bool LoadMediaSound(CString _fileName, int* _index);

		/**
		 * サウンドの操作関数 
		 * @param[in] _index 操作するサウンドのインデックス
		 * @param[in] _operation どのような操作をするか
		 */
		void SoundOperation(int _index, SOUND_OPERATION _operation);

		/**
		 * 音が終了していたら再生し直す(SOUND_LOOPなら)。
		 * DirectShowは標準でループ再生をサポートしてないので毎フレーム自分でチェックしないと行けない
		 * @param[in] _index チェックするサウンドのインデックス
		 */
		void CheckLoop(int _index);

		/**
		 * サウンドの開放
		 * @param[in] _index 開放するサウンドのインデックス
		 */
		void ReleaseMediaSound(int _index);

	private:
		DirectShowSound(){};
		~DirectShowSound(){};

		struct Sound
		{
			IGraphBuilder*  pGraphBuilder;
			IMediaControl*  pMediaControl;	// ファイルの読み込み、再生停止などを行う。
			IMediaPosition* pMediaPosition;	// 再生位置を指定するのに使う。
			bool			isLoop;			// ループさせるか？
		};

		std::vector<Sound*> m_pSound;

	};
}


#endif
