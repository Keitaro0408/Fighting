#ifndef ENEMY_H
#define ENEMY_H
#include "../../CharactorBase/CharacterBase.h"

class Enemy : public CharacterBase
{
public:
	/**
	 * コンストラクタ
	 */
	Enemy() :
		CharacterBase(D3DXVECTOR2(0, 0), D3DXVECTOR2(256, 256), true){};

	/**
	 * デストラクタ
 	 */
	~Enemy();

	/**
	 * 更新関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

private:


};


#endif
