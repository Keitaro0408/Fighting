/**
 * @file   CommandManager.cpp
 * @brief  CommandManagerクラスの実装
 * @author kotani
 */
#include "CommandManager.h"
const int CommandManager::m_KeyValidTime = 15;


CommandManager::CommandManager() :
m_PushButtonNum(0),
m_FrameCount(0),
m_isFirstKeyPush(false)
{
	for (int i = 0; i < KEY_COMMAND_MAX; i++)
	{
		m_KeyCommand[i] = KEY_NONE;
	}
}

CommandManager::~CommandManager()
{
}

void CommandManager::PushButton(KEY _key)
{
	m_FrameCount = 0;
	if (m_PushButtonNum == 0)
	{
		m_isFirstKeyPush = true;
	}
	else if (m_PushButtonNum > KEY_COMMAND_MAX - 1)
	{
		m_PushButtonNum = 0;
	}
	m_KeyCommand[m_PushButtonNum] = _key;
	m_PushButtonNum++;
}

void CommandManager::Update()
{
	if (m_isFirstKeyPush)
	{
		m_FrameCount++;
		if (m_FrameCount > m_KeyValidTime)
		{
			m_FrameCount = 0;
			m_PushButtonNum = 0;
			m_isFirstKeyPush = false;
			for (int i = 0; i < KEY_COMMAND_MAX; i++)
			{
				m_KeyCommand[i] = KEY_NONE;
			}
		}
	}
}
