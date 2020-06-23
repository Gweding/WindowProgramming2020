#include "stdafx.h"
#include "CSoundManager.h"

IMPLEMENT_SINGLETON(CSoundManager)

CSoundManager::CSoundManager(void)
{
}

CSoundManager::~CSoundManager(void)
{
	Free();
}

void CSoundManager::Ready_SoundManager()
{
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
}

void CSoundManager::Update_SoundManager()
{
}

bool CSoundManager::Play_Sound(const wstring& strSoundKey, CHANNELID eID)
{
	auto iter_find = m_mapSound.find(strSoundKey);

	if (m_mapSound.end() == iter_find)
		return false;

	FMOD_BOOL isPlay;
	bool temp = true;
	if (FMOD_Channel_IsPlaying(m_pChannel[eID], &isPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter_find->second, FALSE, &m_pChannel[eID]);
		temp = false;
	}

	FMOD_System_Update(m_pSystem);

	return temp;
}

void CSoundManager::Play_BGM(const wstring& strSoundKey)
{
	auto iter_find = m_mapSound.find(strSoundKey);

	if (m_mapSound.end() == iter_find)
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter_find->second, FALSE, &(m_pChannel[BGM]));

	FMOD_Channel_SetMode(m_pChannel[BGM], FMOD_LOOP_NORMAL);
}

void CSoundManager::Stop_Sound(CHANNELID eID)
{
	FMOD_Channel_Stop(m_pChannel[eID]);
}

void CSoundManager::Stop_All()
{
	for (int i = 0; i < MAXCHANNEL; ++i)
	{
		FMOD_Channel_Stop(m_pChannel[i]);
	}
}

HRESULT CSoundManager::Load_SoundFile(const char* pFilePath)
{
	_finddata_t fd;
	
	char pFindFirstPath[128];
	ZeroMemory(pFindFirstPath, sizeof(char) * 128);
	strcpy_s(pFindFirstPath, pFilePath);
	strcat_s(pFindFirstPath, "*.*");
	intptr_t Handle = _findfirst(pFindFirstPath, &fd);

	if (0 == Handle)
		return E_FAIL;

	int iResult = 0;

	char szCurPath[128];
	ZeroMemory(&szCurPath, sizeof(char) * 128);
	strcpy_s(szCurPath, pFilePath);
	char szFullPath[128] = "";

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath);
		strcat_s(szFullPath, fd.name);

		FMOD_SOUND* pSound = nullptr;
		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);
		if (eRes == FMOD_OK)
		{
			int iLen = (int)strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLen];
			ZeroMemory(pSoundKey, iLen);

			MultiByteToWideChar(CP_ACP, 0, fd.name, iLen, pSoundKey, iLen);

			m_mapSound.emplace(pSoundKey, pSound);

			if (pSoundKey)
			{
				delete[] pSoundKey;
				pSoundKey = nullptr;
			}
		}
		iResult = _findnext(Handle, &fd);
	}
	FMOD_System_Update(m_pSystem);

	return NOERROR;
}

double CSoundManager::Get_Position()
{
	unsigned int iPos = 0;
	FMOD_BOOL isPlay;
	FMOD_Channel_IsPlaying(m_pChannel[BGM], &isPlay);
	if (isPlay == TRUE)
		FMOD_Channel_GetPosition(m_pChannel[BGM], &iPos, (FMOD_TIMEUNIT)FMOD_TIMEUNIT_MS);

	return double(iPos);
}

void CSoundManager::Set_Position(unsigned int iPosition)
{
	FMOD_BOOL isPlay;
	FMOD_Channel_IsPlaying(m_pChannel[BGM], &isPlay);
	if (isPlay == TRUE)
		FMOD_Channel_SetPosition(m_pChannel[BGM], iPosition, (FMOD_TIMEUNIT)FMOD_TIMEUNIT_MS);
}

UINT CSoundManager::Get_Length(const wstring& strSoundKey)
{
	unsigned int iLength = 0;
	FMOD_BOOL isPlay;
	FMOD_Channel_IsPlaying(m_pChannel[BGM], &isPlay);
	if (isPlay == TRUE)
		FMOD_Sound_GetLength(m_mapSound[strSoundKey], &iLength, (FMOD_TIMEUNIT)FMOD_TIMEUNIT_MS);

	return iLength;
}

void CSoundManager::Free()
{
	for (auto& MyPair : m_mapSound)
		FMOD_Sound_Release(MyPair.second);

	m_mapSound.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}
