#ifndef TEXTUREANIM_H
#define TEXTUREANIM_H
#include <Windows.h>


namespace Lib
{
	class AnimFileParser;
	struct Anim
	{
		float LeftUp;
		float Width;
		float Height;
		int	  AnimNum;
	};

	/**
	 * テクスチャアニメーションを管理するクラス
	 */
	class TextureAnim
	{
	public:
		TextureAnim();
		~TextureAnim();

		/**
		 * アニメーション
		 */
		void LoadAnimation(LPCTSTR _pFileName, LPCTSTR _pAnimName);

	private:
		AnimFileParser* m_pAnimFileParser;
		Anim			m_AnimData;

	};

}


#endif
