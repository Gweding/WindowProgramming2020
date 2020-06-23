#pragma once

class CSoundManager
{
	DECLARE_SINGLETON(CSoundManager)

public:
	explicit CSoundManager(void);
	~CSoundManager(void);

public:
	enum CHANNELID { BGM, PLAYER, EFFECT, UI, MAXCHANNEL };
	// �Ҹ��� ���� �����°� �����ϱ� ���ؼ� ä�η� ������ ��

public:
	void Ready_SoundManager();
	void Update_SoundManager();

public:
	bool Play_Sound(const wstring& strSoundKey, CHANNELID eID);						// ȿ���� ó�� �ѹ��� ����Ǵ°�
	void Play_BGM(const wstring& strSoundKey);															// �ݺ���� �ɷ��ִ°� (������ ���)
	void Stop_Sound(CHANNELID eID);																			// �ش� ä�� �Ҹ� ���߰� �ϴ°�
	void Stop_All();																													// ��� ä�� ���°�

public:
	void	Load_SoundFile(const char* pFilePath);

public:
	double Get_Position();
	void Set_Position(unsigned int iPosition);
	UINT Get_Length(const wstring& strSoundKey);

private:
	void Free();

private:
	// ���� ���ҽ� ���� ���� �ִ� ��ü 
	map<wstring, FMOD_SOUND*> m_mapSound;
	// ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannel[MAXCHANNEL];
	//���� ä�� ��ü�� ��ġ�� ������ ��ü 
	FMOD_SYSTEM* m_pSystem;
};
