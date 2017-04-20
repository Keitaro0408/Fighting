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
m_isFirstKeyPush(false),
m_VectorNum(0)
{
	for (int i = 0; i < KEY_COMMAND_MAX; i++)
	{
		m_KeyCommand[i] = KEY_NONE;
	}

	m_CheckCommandList.push_back(KEY_DOWN);
	m_CheckCommandList.push_back(KEY_RIGHT_SLANT);
	m_CheckCommandList.push_back(KEY_RIGHT);
	m_CheckCommandList.push_back(KEY_LOW_PUNCH);
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

	//m_PushButtonNum++;
}

void CommandManager::Update()
{
	if (m_isFirstKeyPush)
	{
		m_FrameCount++;
		if (m_FrameCount < 5)
		{
			m_PushButtonNum++;
		}

		int count = 0;
		m_VectorNum = 0;
		if (KeyCheck(count))
		{
			for (int i = 0; i < KEY_COMMAND_MAX; i++)
			{
				m_KeyCommand[i] = KEY_NONE;
			}
		}

		if (m_FrameCount > m_KeyValidTime)
		{
			for (int i = 0; i < KEY_COMMAND_MAX; i++)
			{
				m_KeyCommand[i] = KEY_NONE;
			}
			m_FrameCount = 0;
			m_PushButtonNum = 0;
			m_isFirstKeyPush = false;
		}
	}
}

bool CommandManager::KeyCheck(int _arrayNum)
{
	if (_arrayNum > KEY_COMMAND_MAX) return false;

	int count = _arrayNum;

	for (int i = _arrayNum; i < KEY_COMMAND_MAX; i++)
	{
		if (m_KeyCommand[i] == m_CheckCommandList[m_VectorNum])
		{
			count++;
		}
	}
	if (count == _arrayNum) return false;
	m_VectorNum++;
	if (static_cast<unsigned int>(m_VectorNum) <= m_CheckCommandList.size() - 1)
	{
		return KeyCheck(count);
	}
	return true;
}
