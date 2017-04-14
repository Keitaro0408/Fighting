/**
 * @file   CombatManager.cpp
 * @brief  CombatManagerクラスの実装
 * @author kotani
 */
#include "CombatManager.h"


CombatManager::RESULT CombatManager::BattleJudge()
{
	if (m_PlayerHP == 0)
	{
		return RESULT_LOSE;
	}
	else if (m_EnemyHP == 0)
	{
		return RESULT_WIN;
	}
	return IN_COMBAT;
}
