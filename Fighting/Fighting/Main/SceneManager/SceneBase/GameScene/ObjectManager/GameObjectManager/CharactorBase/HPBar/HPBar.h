/**
 * @file   HPBar.h
 * @brief  HPBar�N���X�̃w�b�_�t�@�C��
 * @author kotani
 */
#ifndef HPBAR_H
#define HPBAR_H
#include "../../../ObjectBase/ObjecBase.h"
#include "Vertex2D.h"
#include <memory>

class HPBar : public ObjecBase
{
public:
	/**
	 * �R���X�g���N�^
	 */
	HPBar(D3DXVECTOR2* _pos);

	/**
	 * �f�X�g���N�^
	 */
	~HPBar();

	/**
	 * ����֐�
	 */
	void Update() override;

	/**
	 * �`��֐�
	 */
	void Draw() override;

private:
	D3DXVECTOR2 m_Pos;
	int			m_TextureIndex;
	int			m_HPBar;
	D3DXVECTOR2	m_UV[4];


};


#endif
