/**
 * @file   CommandManager.cpp
 * @brief  CommandManagerクラスの実装
 * @author kotani
 */
#include "CommandManager.h"

const int CommandManager::m_KeyValidTime = 20;


CommandManager::CommandManager() :
m_PushButtonNum(0)
{
}


CommandManager::~CommandManager()
{
}

void CommandManager::PushButton(KEY _key)
{
	m_KeyCommand[m_PushButtonNum] = _key;
	m_PushButtonNum++;
	if (m_PushButtonNum > KEY_COMMAND_MAX)
	{
		m_PushButtonNum = 0;
	}
}
