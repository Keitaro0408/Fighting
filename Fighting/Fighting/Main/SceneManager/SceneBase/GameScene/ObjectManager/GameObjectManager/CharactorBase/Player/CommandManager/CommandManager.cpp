/**
 * @file   CommandManager.cpp
 * @brief  CommandManagerクラスの実装
 * @author kotani
 */
#include "CommandManager.h"
const int CommandManager::m_KeyValidTime = 15;
#include <Windows.h>


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

	/* ファイルで管理予定 */
	m_CheckCommandList.push_back(KEY_DOWN);
	m_CheckCommandList.push_back(KEY_RIGHT_SLANT);
	m_CheckCommandList.push_back(KEY_RIGHT);
	m_CheckCommandList.push_back(KEY_LOW_PUNCH);
	m_CommandListNum = m_CheckCommandList.size();
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

CommandManager::COMMAND_ARTS CommandManager::Update()
{
	if (!m_isFirstKeyPush) return ARTS_NONE;

	m_FrameCount++;

	if (m_FrameCount > m_KeyValidTime)
	{
		for (int i = 0; i < KEY_COMMAND_MAX; i++)
		{
			m_KeyCommand[i] = KEY_NONE;
		}
		m_FrameCount = 0;
		m_PushButtonNum = 0;
		m_isFirstKeyPush = false;
		m_VectorNum = 0;
	}

	if ((KEY_COMMAND_MAX / 2 ) > m_PushButtonNum) return ARTS_NONE;
	m_CommandListNum = m_CheckCommandList.size();
	m_VectorNum = 0;
	if (KeyCheck())
	{
		return HADOUKEN;
	}

	return ARTS_NONE;
}

bool CommandManager::KeyCheck(int _arrayNum)
{
	if (_arrayNum > KEY_COMMAND_MAX) return false;

	int count = _arrayNum;

	int matchKeyCount = 0;
	for (int i = _arrayNum; i < KEY_COMMAND_MAX; i++)
	{
		if (m_KeyCommand[i] == m_CheckCommandList[m_VectorNum])
		{
			count++;
			matchKeyCount++;

			if (matchKeyCount > 5) return false;
		}
		else
		{
			matchKeyCount = 0;
		}
	}
	if (count == _arrayNum)
	{
		return false;
	}
	else
	{
		m_CommandListNum--;
		m_VectorNum++;
	}

	if (static_cast<unsigned int>(m_VectorNum) <= m_CheckCommandList.size() - 1)
	{
		return KeyCheck(count);
	}

	return (m_CommandListNum == 0);
}
