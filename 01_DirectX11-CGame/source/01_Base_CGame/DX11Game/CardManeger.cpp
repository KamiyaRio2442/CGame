#include <time.h>
#include "CardManeger.h"
#include "Input.h"
#include "Scene.h"
#include "Texture.h"
#include "DebugProc.h"

//�i�@�g�k�~��]�~�ړ��@�j

// �S�J�[�h�̉摜���
namespace {
	LPCSTR g_pszCardPath[CARD_MAX]
	{
		"data/model/card/CardH1.tif", "data/model/card/CardH2.tif", "data/model/card/CardH3.tif" , "data/model/card/CardH4.tif" , "data/model/card/CardH5.tif" , "data/model/card/CardH6.tif" , "data/model/card/CardH7.tif" ,
		"data/model/card/CardH8.tif", "data/model/card/CardH9.tif", "data/model/card/CardH10.tif", "data/model/card/CardH11.tif", "data/model/card/CardH12.tif", "data/model/card/CardH13.tif",
		"data/model/card/CardS1.tif", "data/model/card/CardS2.tif", "data/model/card/CardS3.tif" , "data/model/card/CardS4.tif" , "data/model/card/CardS5.tif" , "data/model/card/CardS6.tif" , "data/model/card/CardS7.tif" ,
		"data/model/card/CardS8.tif", "data/model/card/CardS9.tif", "data/model/card/CardS10.tif", "data/model/card/CardS11.tif", "data/model/card/CardS12.tif", "data/model/card/CardS13.tif",
		"data/model/card/CardC1.tif", "data/model/card/CardC2.tif", "data/model/card/CardC3.tif" , "data/model/card/CardC4.tif" , "data/model/card/CardC5.tif" , "data/model/card/CardC6.tif" , "data/model/card/CardC7.tif" ,
		"data/model/card/CardC8.tif", "data/model/card/CardC9.tif", "data/model/card/CardC10.tif", "data/model/card/CardC11.tif", "data/model/card/CardC12.tif", "data/model/card/CardC13.tif",
		"data/model/card/CardD1.tif", "data/model/card/CardD2.tif", "data/model/card/CardD3.tif" , "data/model/card/CardD4.tif" , "data/model/card/CardD5.tif" , "data/model/card/CardD6.tif" , "data/model/card/CardD7.tif" ,
		"data/model/card/CardD8.tif", "data/model/card/CardD9.tif", "data/model/card/CardD10.tif", "data/model/card/CardD11.tif", "data/model/card/CardD12.tif", "data/model/card/CardD13.tif",
	};
}

// ���I�z��
ID3D11ShaderResourceView* CCardManeger::m_pCardInfo[CARD_MAX];

// �R���X�g���N�^
CCardManeger::CCardManeger(CScene* pScene) : CGameObj(pScene), m_pattern(0)
{
}
// �f�X�g���N�^
CCardManeger::~CCardManeger()
{
}

// �������֐�
HRESULT CCardManeger::Init()
{
	HRESULT hr = S_OK;

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	switch (GetID())
	{
		case SCENE_GAME1:
		{
			// ���݂̔z�z�J�[�h����
			m_currentCardNo = 0;
			// ���݂̃v���C���[�ԍ�
			m_PlayerNo = 0;

			// �J�[�h���̏�����
			for (int i = 0; i < CARD_MAX; i++)
			{
				CCard* pCard = new CCard(m_pScene);
				pCard->Init();
				pCard->SetAngle({ 90.0f, 90.0f, 0.0f });
				pCard->SetPos(m_CradBasePos);
				m_pattern = i;
				pCard->mark = m_pattern / 13;
				pCard->number = (m_pattern % 13) + 1;
				if (pCard->number == 1)
				{
					pCard->mode[0] = 1;
					pCard->mode[1] = 11;
				}
				else if (pCard->number >= 10)
				{
					pCard->mode[0] = 10;
					pCard->mode[1] = 10;
				}
				else if (pCard->number < 10)
				{
					pCard->mode[0] = pCard->number;
					pCard->mode[1] = pCard->number;
				}
				pCard->SetUseFlag(false);
				pCard->SetPat(m_pattern);
				m_pCardList[i] = pCard;

				m_EachCardAngle[i] = m_pCardList[i]->GetAngle();
				m_EachCardPos[i] = m_pCardList[i]->GetPos();
			}

			// �J�[�h�̃V���b�t��srand( (int)time(NULL) );
			srand((int)time(NULL));
			for (int i = 0; i < 5000; i++)
			{
				int s1 = rand() % CARD_MAX;
				int s2 = rand() % CARD_MAX;

				CCard *wait = m_pCardList[s1];
				m_pCardList[s1] = m_pCardList[s2];
				m_pCardList[s2] = wait;
			}

			// �v���C���[�}�l�[�W���[�̏�����
			for (int i = 0; i < PLAYER_MAX; i++)
			{
				CPlayerManager* pPlayerM = new CPlayerManager(m_pScene);
				pPlayerM->Init();
				pPlayerM->SetAngle({ 90.0f, 90.0f, 0.0f });
				pPlayerM->SetPos({ 100.0f, 5.0f, 0.0f });
				m_pattern = i;
				m_pPlayerManager = pPlayerM;
			}

			CDealer *pDealer = new CDealer(m_pScene);
			pDealer->Init();
			m_pDealer = pDealer;

			for (int i = 0; i < PLAYER_MAX; i++)
			{
				m_totalkeep[i] = 0;
				m_gap[i] = 0;
				m_NowState[i] = NoState;
				m_FinFlag[i] = false;
			}

			for (int i = 0; i < PLAYER_MAX - 1; i++)
			{
				m_PlayerWinLose[i] = NONE;
				m_DealerWinLose[i] = NONE;
				m_FirstPBust[i] = false;
			}

			m_autocnt = 0;
			m_autoflag = false;
			m_Dealerturnflag = false;
			m_NoPlay = false;
			m_oneGameFin = false;
			m_Wait = false;
			m_tobecontinue = false;
			m_ThisGameFin = false;
			m_StartFlag = false;
			m_nAllFinCnt = 0;
		}
		break;

		// -------------------------------------------------------------------------------------------------------------------------------------------

		case SCENE_GAME2:
		{
			m_currentCardNo = 0;
			m_PlayerNo = 0;
			m_nSetNum = 0;

			// �J�[�h���̏�����
			for (int i = 0; i < CARD_MAX; i++)
			{
				CCard* pCard = new CCard(m_pScene);
				pCard->Init();
				pCard->SetAngle({ 90.0f, 90.0f, 0.0f });
				pCard->SetPos(m_CradBasePos);
				m_pattern = i;
				pCard->mark = m_pattern / 13;
				pCard->number = (m_pattern % 13) + 1;
				if (pCard->number == 1)
				{
					pCard->mode[0] = 1;
					pCard->mode[1] = 11;
				}
				else if (pCard->number >= 10)
				{
					pCard->mode[0] = 10;
					pCard->mode[1] = 10;
				}
				else
				{
					pCard->mode[0] = pCard->number;
					pCard->mode[1] = pCard->number;
				}
				pCard->SetUseFlag(false);
				pCard->SetPat(m_pattern);
				m_pCardList[i] = pCard;

				m_EachCardAngle[i] = m_pCardList[i]->GetAngle();
				m_EachCardPos[i] = m_pCardList[i]->GetPos();

			}

			// �J�[�h�̃V���b�t��srand( (int)time(NULL) );
			srand((int)time(NULL));
			for (int i = 0; i < 5000; i++)
			{
				int s1 = rand() % CARD_MAX;
				int s2 = rand() % CARD_MAX;

				CCard *wait = m_pCardList[s1];
				m_pCardList[s1] = m_pCardList[s2];
				m_pCardList[s2] = wait;
			}

			// ��D�̃Z�b�g
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 13; j++)
				{
					CCard* pPlaca = new CCard(m_pScene);
					pPlaca->Init();
					pPlaca->SetAngle({ 90.0f, 90.0f, 0.0f });
					pPlaca->SetPos(m_CradBasePos);
					m_pattern = i;
					pPlaca->mark = -1;
					pPlaca->number = -1;
					pPlaca->mode[0] = -1;
					pPlaca->mode[1] = -1;
					pPlaca->SetUseFlag(false);
					pPlaca->SetPat(m_pattern);
					m_pPlaceCards[i][j] = pPlaca;

					m_EachCardAngle[i] = m_pPlaceCards[i][j]->GetAngle();
					m_EachCardPos[i] = m_pPlaceCards[i][j]->GetPos();

					if (j <= i)
					{
						m_pPlaceCards[i][j] = m_pCardList[m_nSetNum];
						m_nSetNum++;
					}
				}
			}

			for (int i = 0; i < PLAYER_MAX; i++)
			{
				m_gap[i] = 0;
			}

		}
		break;
		default:
			break;
	}

	return hr;
}
// �I���֐�
void CCardManeger::Fin()
{
}
// �X�V�֐�
void CCardManeger::Update()
{
	switch (GetID())
	{
		case SCENE_GAME1:
			// �f�o�b�O���\��
			CDebugProc::Print("%2d\n\n", GetID());

			for (int i = 0; i < CARD_MAX; i++)
			{
				CDebugProc::Print("%2d ", m_pCardList[i]->number);
				if (i % 13 == 12)
				{
					CDebugProc::Print("\n");
				}
			}
			CDebugProc::Print("\n");

			m_pCardList[m_currentCardNo]->SetNowGameSceneNo(SCENE_GAME1);

			// �Q�[�����n�܂������ɂ̂ݎ��s�����auto�����̃t���O�ݒ�
			if (CInput::GetKeyTrigger(VK_SPACE) && m_autocnt == 0)
			{
				// �Q�[���J�n�t���O�̗L����
				m_StartFlag = true;
				// �I�[�g�J�n�t���O�̗L����
				m_autoflag = true;
			}

			// �Q�[���J�n�t���O���L���̎�
			if (m_StartFlag == true)
			{
				// ���݂̉�]���̎擾
				m_EachCardAngle[m_currentCardNo] = m_pCardList[m_currentCardNo]->GetAngle();
				// ���݂̈ʒu���̎擾
				m_EachCardPos[m_currentCardNo] = m_pCardList[m_currentCardNo]->GetPos();
				m_pCardList[m_currentCardNo]->SetPos(m_CradBasePos);

				// �y Stay�̏��� �z
				if (m_FinFlag[m_PlayerNo] == true)
				{
					// �v���C���[�ԍ��̕ύX
					m_PlayerNo++;
					m_PlayerNo %= PLAYER_MAX;
				}

				if (m_autoflag == false && m_PlayerNo == PLAYER_MAX - 1)
				{
					// �v���C���[�ԍ��̕ύX
					m_PlayerNo++;
					m_PlayerNo %= PLAYER_MAX;
					break;
				}

				if (CInput::GetKeyTrigger(VK_W) && m_FinFlag[m_PlayerNo] == false)
				{
					// ��Ԃ��y�X�e�C�z�ɐݒ�
					m_NowState[m_PlayerNo] = Stay;
					// �v���C���[�s���I���t���O�̗L����
					m_FinFlag[m_PlayerNo] = true;
					// �v���C���[�ԍ��̕ύX
					m_PlayerNo++;
					m_PlayerNo %= PLAYER_MAX;
					break;
				}
				// �y Hit�̏��� �z
				if (CInput::GetKeyTrigger(VK_Q) || (m_autoflag == true && m_autocnt < 2))
				{
					if (m_FinFlag[m_PlayerNo] == false)
					{
						m_pCardList[m_currentCardNo]->SetUseFlag(true);
						m_pCardList[m_currentCardNo]->SetGap(m_gap[m_PlayerNo]);
						if (m_currentCardNo == PLAYER_MAX * 2 -1)
						{
							m_pCardList[m_currentCardNo]->SetAngle({ 90.0f, 90.0f, 0.0f });
						}
						else
						{
							m_pCardList[m_currentCardNo]->SetAngle({ 270.0f, 90.0f, 0.0f });
						}
						m_pCardList[m_currentCardNo]->Update();

						switch (m_PlayerNo >= PLAYER_MAX - 1)
						{
						case true:
							if (m_autoflag == true && m_autocnt < 2)
							{
								m_pCardList[m_currentCardNo]->SetDestination({ m_EachPlayerPos[m_PlayerNo].x + (m_gap[m_PlayerNo] * 5.0f), m_EachPlayerPos[m_PlayerNo].y + (m_gap[m_PlayerNo] * 0.1f), m_EachPlayerPos[m_PlayerNo].z + (m_gap[m_PlayerNo] * 0.5f) });
								m_pCardList[m_currentCardNo]->SetPos(m_EachCardPos[m_currentCardNo]);

								m_pDealer->SetAttachFlag(true);
								m_pDealer->SetAttachCardInfo(m_pCardList[m_currentCardNo]->mode[1]);
								m_pDealer->Update();

								// ���v�l�̕ۑ�
								m_totalkeep[m_PlayerNo] = m_pDealer->GetTotalNo();

								if (m_autocnt < 2 && m_totalkeep[m_PlayerNo] >= 17)
								{
									// ��Ԃ��y�f�B�[���[�X�g�b�v�z�ɐݒ�
									m_NowState[m_PlayerNo] = DealerStop;

									m_ThisGameFin = true;
								}
								else if (m_totalkeep[PLAYER_MAX - 1] == 21)
								{
									// ��Ԃ��y�u���b�N�W���b�N�z�ɐݒ�
									m_NowState[m_PlayerNo] = BlackJack;

									m_ThisGameFin = true;
								}

								// auto�����̉�
								if (m_autocnt < 2)
								{
									m_autocnt++;
								}
								else
								{
									// �v���C���[�s���I���t���O�̗L����
									m_FinFlag[m_PlayerNo] = true;
									// auto�����I���t���O
									m_autoflag = false;
								}

								m_currentCardNo++;
								m_gap[m_PlayerNo]++;
								// �v���C���[�ԍ��̕ύX
								m_PlayerNo++;
								m_PlayerNo %= PLAYER_MAX;
							}
							break;
						case false:
							m_pCardList[m_currentCardNo]->SetDestination({ m_EachPlayerPos[m_PlayerNo].x + (m_gap[m_PlayerNo] * 5.0f), m_EachPlayerPos[m_PlayerNo].y + (m_gap[m_PlayerNo] * 0.1f), m_EachPlayerPos[m_PlayerNo].z + (m_gap[m_PlayerNo] * 0.5f) });
							m_pCardList[m_currentCardNo]->SetPos(m_EachCardPos[m_currentCardNo]);

							m_pPlayerManager->SetAttachPlayerNo(m_PlayerNo);
							m_pPlayerManager->SetAttachCardNo(m_pCardList[m_currentCardNo]->mode[1]);
							m_pPlayerManager->Update();

							// �e���v�l�̕ۑ�
							m_totalkeep[m_PlayerNo] = m_pPlayerManager->GetEachNoKeep(m_PlayerNo);

							if (m_totalkeep[m_PlayerNo] < 21)
							{
								// ��Ԃ��y�q�b�g�z�ɐݒ�
								m_NowState[m_PlayerNo] = Hit;
							}
							else if (m_totalkeep[m_PlayerNo] == 21)
							{
								// ��Ԃ��y�u���b�N�W���b�N�z�ɐݒ�
								m_NowState[m_PlayerNo] = BlackJack;
								// �v���C���[�s���I���t���O�̗L����
								m_FinFlag[m_PlayerNo] = true;
							}
							else if (m_totalkeep[m_PlayerNo] > 21)
							{
								// ��Ԃ��y�o�[�X�g�z�ɐݒ�
								m_NowState[m_PlayerNo] = Bust;
								// �v���C���[�s���I���t���O�̗L����
								m_FinFlag[m_PlayerNo] = true;

								m_FirstPBust[m_PlayerNo] = true;
							}

							m_currentCardNo++;
							m_gap[m_PlayerNo]++;
							// �v���C���[�ԍ��̕ύX
							m_PlayerNo++;
							m_PlayerNo %= PLAYER_MAX;
							break;
						}
					}
				}

				// �P�Q�[���I����ĂȂ�������
				if (m_oneGameFin == false)
				{
					// �S�v���C���[��Stay�ɂȂ��Ă��邩�̊m�F
					for (int i = 0; i < PLAYER_MAX - 1; i++)
					{
						m_nAllFinCnt += m_FinFlag[i];
					}
				}
				// �f�o�b�O���\��
				CDebugProc::Print("%2d Fin\n\n\n\n", m_nAllFinCnt);

				// �P�Q�[���I���������̔���
				// �y �I�����Ă����� �z
				if (m_nAllFinCnt >= PLAYER_MAX - 1)
				{
					// �P�Q�[���I���t���O�̗L����
					m_oneGameFin = true;

					m_pCardList[PLAYER_MAX * 2 -1]->SetUseFlag(true);
					m_pCardList[PLAYER_MAX * 2 -1]->SetGap(m_gap[m_PlayerNo]);
					m_pCardList[PLAYER_MAX * 2 -1]->SetAngle({ 270.0f, 90.0f, 0.0f });
					m_pCardList[PLAYER_MAX * 2 -1]->Update();

					while (m_NowState[PLAYER_MAX - 1] == NoState)
					{
						m_pCardList[m_currentCardNo]->SetUseFlag(true);
						m_pCardList[m_currentCardNo]->SetGap(m_gap[PLAYER_MAX - 1]);
						m_pCardList[m_currentCardNo]->SetAngle({ 270.0f, 90.0f, 0.0f });
						m_pCardList[m_currentCardNo]->Update();

						// ��]���̐ݒ�
						m_pCardList[m_currentCardNo]->SetDestination({ m_EachPlayerPos[PLAYER_MAX - 1].x + (m_gap[PLAYER_MAX - 1] * 5.0f), m_EachPlayerPos[PLAYER_MAX - 1].y + (m_gap[PLAYER_MAX - 1] * 0.1f), m_EachPlayerPos[PLAYER_MAX - 1].z + (m_gap[PLAYER_MAX - 1] * 0.5f) });
						m_pCardList[m_currentCardNo]->SetPos(m_EachCardPos[m_currentCardNo]);

						m_pDealer->SetAttachFlag(true);
						m_pDealer->SetAttachCardInfo(m_pCardList[m_currentCardNo]->mode[1]);
						m_pDealer->Update();

						// ���v�l�̕ۑ�
						m_totalkeep[PLAYER_MAX - 1] = m_pDealer->GetTotalNo();

						if (m_totalkeep[PLAYER_MAX - 1] == 21)
						{
							// ��Ԃ��y�u���b�N�W���b�N�z�ɐݒ�
							m_NowState[PLAYER_MAX - 1] = BlackJack;

							m_ThisGameFin = true;
						}
						else if (m_totalkeep[PLAYER_MAX - 1] > 21)
						{
							// ��Ԃ��y�o�[�X�g�z�ɐݒ�
							m_NowState[PLAYER_MAX - 1] = Bust;

							m_ThisGameFin = true;
						}
						else if (m_totalkeep[PLAYER_MAX - 1] >= 17)
						{
							// ��Ԃ��y�f�B�[���[�X�g�b�v�z�ɐݒ�
							m_NowState[PLAYER_MAX - 1] = DealerStop;

							m_ThisGameFin = true;
						}

						m_currentCardNo++;
						m_gap[PLAYER_MAX - 1]++;
					}

					if (m_ThisGameFin == true)
					{
						if (CInput::GetKeyTrigger(VK_A))
						{
							for (int i = 0; i <= m_currentCardNo; i++)
							{
								m_pCardList[i]->SetUseFlag(true);
								m_pCardList[i]->SetGap(m_gap[m_PlayerNo]);
								m_pCardList[i]->SetDestination({ m_CradBasePos.x * -1.0f, m_CradBasePos.y, m_CradBasePos.z });
								m_pCardList[i]->SetPos({ m_CradBasePos.x * -1.0f, m_CradBasePos.y, m_CradBasePos.z });
								m_pCardList[i]->SetAngle({ 270.0f, 90.0f, 0.0f });
								m_pCardList[i]->Update();

								if (i == m_currentCardNo)
								{
									m_ThisGameFin = false;
									CCardManeger::Init();
								}
							}
						}

						SetContinueFlag(true);
					}

					// �e�v���C���[�̏��s���̐ݒ�
					for (int i = 0; i < PLAYER_MAX - 1; i++)
					{
						// �y �v���C���[�̕��� �z
						if (m_FirstPBust[i] == true)
						{
							m_PlayerWinLose[i] = LOSE;
							m_DealerWinLose[i] = WIN;
						}
						else
						{
							// �y �v���C���[�̕��� �z
							if (m_NowState[PLAYER_MAX] == (DealerStop || BlackJack) && m_totalkeep[PLAYER_MAX - 1] > m_totalkeep[i])
							{
								m_PlayerWinLose[i] = LOSE;
								m_DealerWinLose[i] = WIN;
							}
							// �y �f�B�[���[�̕��� �z
							else
							{
								m_PlayerWinLose[i] = WIN;
								m_DealerWinLose[i] = LOSE;
							}
						}
					}

					// �f�o�b�O���\��
					CDebugProc::Print("GameFin\n\n\n\n");
				}
				// �y �I�����Ă��Ȃ������� �z
				else
				{
					m_nAllFinCnt = 0;
				}
			}

			// �f�o�b�O���\��
			for (int i = 0; i < PLAYER_MAX - 1; i++)
			{
				CDebugProc::Print("Player%d (%2d) : ", i + 1, m_totalkeep[i]);

				switch (m_NowState[i])
				{
				case 0:
					// NoState
					CDebugProc::Print("NS   ");
					break;
				case 1:
					// Hit
					CDebugProc::Print(" H   ");
					break;
				case 2:
					// Stay
					CDebugProc::Print(" S   ");
					break;
				case 3:
					// Bust
					CDebugProc::Print(" B   ");
					break;
				case 4:
					// BlackJack
					CDebugProc::Print("BJ   ");
					break;
				case 5:
					// DealerStop
					CDebugProc::Print("DS   ");
					break;
				}

				switch (m_PlayerWinLose[i])
				{
				case 0:
					CDebugProc::Print("NONE\n");
					break;
				case 1:
					CDebugProc::Print("WIN \n");
					break;
				case 2:
					CDebugProc::Print("LOSE\n");
					break;
				case 3:
					CDebugProc::Print("DRAW\n");
					break;
				}
			}
			CDebugProc::Print("Dealer  (%2d) : ", m_totalkeep[PLAYER_MAX - 1]);

			switch (m_NowState[PLAYER_MAX - 1])
			{
			case NoState:
				// NoState
				CDebugProc::Print("NS\n");
				break;
			case Hit:
				// Hit
				CDebugProc::Print(" H\n");
				break;
			case Stay:
				// Stay
				CDebugProc::Print(" S\n");
				break;
			case Bust:
				// Bust
				CDebugProc::Print(" B\n");
				break;
			case BlackJack:
				// BlackJack
				CDebugProc::Print("BJ\n");
				break;
			case DealerStop:
				// DealerStop
				CDebugProc::Print("DS\n");
				break;
			}
			CDebugProc::Print("\n");

			for (int i = 0; i < PLAYER_MAX; i++)
			{
				CDebugProc::Print("stop <%2d> ", m_FinFlag[i]);
			}
			break;

		// ---------------------------------------------------------------------------------------------------------------------------------------

		case SCENE_GAME2:
			// �f�o�b�O���\��
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 13; j++)
				{
					CDebugProc::Print("%2d ", m_pPlaceCards[i][j]->number);
					if (j % 13 == 12)
					{
						CDebugProc::Print("\n");
					}
				}
			}
			CDebugProc::Print("\n");

			if (CInput::GetKeyTrigger(VK_SPACE))
			{
				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 13; j++)
					{
						if (m_pPlaceCards[i][j]->number != -1)
						{
							// ��]���̐ݒ�
							m_pPlaceCards[i][j]->SetAngle(m_EachCardAngle[m_currentCardNo]);
							m_pPlaceCards[i][j]->SetDestination({ -180.0f + ((i + 1) * 20.0f), 5.0f + ((j + 1) * 0.1f), -20.0f - ((j + 1) * 10.0f) });
							m_pPlaceCards[i][j]->SetPos(m_EachCardPos[m_currentCardNo]);

							m_pPlaceCards[i][j]->SetUseFlag(true);
							m_pPlaceCards[i][j]->SetGap(m_gap[m_PlayerNo]);
							m_pPlaceCards[i][j]->SetNowGameSceneNo(SCENE_GAME2);

							if (m_pPlaceCards[i][j + 1]->number == -1)
							{
								m_pPlaceCards[i][j]->SetAngle({ 270.0f, 90.0f, 0.0f });
							}
							m_pPlaceCards[i][j]->Update();
						}
					}
				}
			}

			m_gap[m_PlayerNo]++;
			break;

		// ---------------------------------------------------------------------------------------------------------------------------------------

		default:
			break;
	}
}

// �S���f���Ǎ�
HRESULT CCardManeger::LoadAll()
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	HRESULT hr = S_OK;

	// �S�ẴJ�[�h�Ǎ�
	for (int i = 0; i < CARD_MAX; ++i)
	{
		hr = CreateTextureFromFile(pDevice, g_pszCardPath[i], &m_pCardInfo[i]);
		if (FAILED(hr))
		{
			return hr;
		}
	}

	return hr;
}

// �S���f�����
void CCardManeger::ReleaseAll()
{
	// �S���f�����
	for (int i = 0; i < CARD_MAX; ++i)
	{
		if (m_pCardInfo[i])
		{
			SAFE_RELEASE(m_pCardInfo[i]);
		}
	}
}

// �J�[�h�̃e�N�X�`���̎擾
ID3D11ShaderResourceView* CCardManeger::GetTexture(int nPat)
{
	if (nPat < 0 || CARD_MAX <= nPat)
	{
		return nullptr;
	}

	return m_pCardInfo[nPat];
}



//	switch (GetID())
//	{
//	case SCENE_GAME1:
//		// �f�o�b�O���\��
//		CDebugProc::Print("%2d\n\n", GetID());
//		for (int i = 0; i < CARD_MAX; i++)
//		{
//			CDebugProc::Print("%2d ", m_pCardList[i]->number);
//			if (i % 13 == 12)
//			{
//				CDebugProc::Print("\n");
//			}
//		}
//		CDebugProc::Print("\n");
//
//		m_pCardList[m_currentCardNo]->SetNowGameSceneNo(SCENE_GAME1);
//		
//		// �Q�[���I���̗L��
//		switch (m_ThisGameFin)
//		{
//			// �Q�[���I��
//			case true:
//				// �J�[�h��������t���O�̗L����
//				if (CInput::GetKeyTrigger(VK_A))
//				{
//					m_autocollect = true;
//				}
//
//				// �J�[�h������������t���O���L���̎�
//				if (m_autocollect == true)
//				{
//					// ����������̊�
//					while(m_nextgame < m_currentCardNo)
//					{
//						m_pCardList[m_nextgame]->SetUseFlag(true);
//						SetContinueFlag(true);
//						m_pCardList[m_nextgame]->SetGap(m_gap[m_PlayerNo]);
//						m_pCardList[m_nextgame]->SetDestination({ (m_CollectBasePos.x * -1.0f), m_CollectBasePos.y, m_CollectBasePos.z });
//						m_pCardList[m_nextgame]->SetPos({ (m_CradBasePos.x * -1.0f), m_CradBasePos.y, m_CradBasePos.z });
//						m_pCardList[m_nextgame]->SetAngle({ 270.0f, 90.0f, 0.0f });
//						m_pCardList[m_nextgame]->Update();
//						m_nextgame++;
//					}
//					CCardManeger::Init();
//				}
//				break;
//
//			// �Q�[�����I��
//			case false:
//				// �Q�[���J�n�t���O�E�I�[�g�J�n�t���O�̗L����
//				if (CInput::GetKeyTrigger(VK_SPACE) && m_autoflag == false)
//				{
//					m_autoflag = true;
//					m_gamestart = true;
//				}
//
//				// �Q�[���J�n�t���O���L���̎�
//				if (m_gamestart == true)
//				{
//					// �v���C���[�̏�Ԃ��y �f�B�[���[�X�g�b�v�E�X�g�b�v�E�u���b�N�W���b�N�E�o�[�X�g �z�̎��ɏ��Ԃ��΂�
//					if (m_Stop[m_PlayerNo] == true)
//					{
//						m_PlayerNo++;
//						m_PlayerNo = m_PlayerNo % PLAYER_MAX;
//					}
//					else
//					{
//						// �҂�
//						if (CInput::GetKeyTrigger(VK_W))
//						{
//							// ��Ԃ��y�X�g�b�v�z�ɐݒ�
//							m_NowState[m_PlayerNo] = Stay;
//							// �X�g�b�v�t���O�̗L����
//							m_Stop[m_PlayerNo] = true;
//							// �v���C���[�ԍ��̕ύX
//							m_PlayerNo++;
//							m_PlayerNo %= PLAYER_MAX;
//							// �I���t���O�̗L����
//							m_FinCnt[m_PlayerNo] = true;
//						}
//						// �z��
//						else if (CInput::GetKeyTrigger(VK_Q) || m_autoflag == true)
//						{
//							// ���݂̉�]���̎擾
//							m_EachCardAngle[m_currentCardNo] = m_pCardList[m_currentCardNo]->GetAngle();
//							// ���݂̈ʒu���̎擾
//							m_pCardList[m_currentCardNo]->SetPos(m_CradBasePos);
//							m_EachCardPos[m_currentCardNo] = m_pCardList[m_currentCardNo]->GetPos();
//
//							// �J�[�h�N���X�ړ��L�����t���O�̗L����
//							m_pCardList[m_currentCardNo]->SetUseFlag(true);
//							// �Y���������l�̓���
//							m_pCardList[m_currentCardNo]->SetGap(m_gap[m_PlayerNo]);
//							// �f�B�[���[�̓񖇖ڂ��_�E���J�[�h�ɐݒ�
//							if (m_currentCardNo == 11)
//							{
//								m_pCardList[m_currentCardNo]->SetAngle({ 90.0f, 90.0f, 0.0f });
//							}
//							// ����ȊO�̓A�b�v�J�[�h
//							else
//							{
//								m_pCardList[m_currentCardNo]->SetAngle({ 270.0f, 90.0f, 0.0f });
//							}
//							// �J�[�h�N���X�̍X�V
//							m_pCardList[m_currentCardNo]->Update();
//
//							// ��]���̐ݒ�
//							m_pCardList[m_currentCardNo]->SetDestination({ m_EachPlayerPos[m_PlayerNo].x + (m_gap[m_PlayerNo] * 5.0f), m_EachPlayerPos[m_PlayerNo].y + (m_gap[m_PlayerNo] * 0.1f), m_EachPlayerPos[m_PlayerNo].z + (m_gap[m_PlayerNo] * 0.5f) });
//							m_pCardList[m_currentCardNo]->SetPos(m_EachCardPos[m_currentCardNo]);
//
//							if (m_PlayerNo <= PLAYER_MAX - 1)
//							{
//								// �v���C���[�ԍ��̐ݒ�
//								m_pPlayerManager->SetAttachPlayerNo(m_PlayerNo);
//								// �z��ꂽ�J�[�h�̒l��ݒ�
//								m_pPlayerManager->SetAttachCardNo(m_pCardList[m_currentCardNo]->mode[1]);
//								// �v���C���[�N���X�̍X�V
//								m_pPlayerManager->Update();
//
//								// �e���v�l�̕ۑ�
//								m_totalkeep[m_PlayerNo] = m_pPlayerManager->GetEachNoKeep(m_PlayerNo);
//
//								// �u���b�N�W���b�N�̎�
//								if (m_totalkeep[m_PlayerNo] == 21)
//								{
//									// ��Ԃ��y�u���b�N�W���b�N�z�ɐݒ�
//									m_NowState[m_PlayerNo] = BlackJack;
//									// �X�g�b�v�t���O�̗L����
//									m_Stop[m_PlayerNo] = true;
//									// �I���t���O�̗L����
//									m_FinCnt[m_PlayerNo] = true;
//								}
//								// �o�[�X�g�̎�
//								else if (m_totalkeep[m_PlayerNo] > 21)
//								{
//									// ��Ԃ��y�o�[�X�g�z�ɐݒ�
//									m_NowState[m_PlayerNo] = Bust;
//									// �X�g�b�v�t���O�̗L����
//									m_Stop[m_PlayerNo] = true;
//									// �I���t���O�̗L����
//									m_FinCnt[m_PlayerNo] = true;
//
//									m_FirstPBust[m_PlayerNo] = true;
//								}
//								// �q�b�g�̎�
//								else if (m_totalkeep[m_PlayerNo] < 21)
//								{
//									// ��Ԃ��y�q�b�g�z�ɐݒ�
//									m_NowState[m_PlayerNo] = Hit;
//								}
//							}
//							else
//							{
//								m_pDealer->SetAttachFlag(true);
//								// �z��ꂽ�J�[�h�̒l��ݒ�
//								m_pDealer->SetAttachCardInfo(m_pCardList[m_currentCardNo]->mode[1]);
//								// �f�B�[���[�N���X�̍X�V
//								m_pDealer->Update();
//
//								// ���v�l�̕ۑ�
//								m_totalkeep[m_PlayerNo] = m_pDealer->GetTotalNo();
//
//								if (m_totalkeep[m_PlayerNo] == 21)
//								{
//									// ��Ԃ��y�u���b�N�W���b�N�z�ɐݒ�
//									m_NowState[m_PlayerNo] = BlackJack;
//									// �X�g�b�v�t���O�̗L����
//									m_Stop[m_PlayerNo] = true;
//									// �I���t���O�̗L����
//									m_FinCnt[m_PlayerNo] = true;
//								}
//								else if (m_autocnt < 2 && m_totalkeep[PLAYER_MAX - 1] >= 17)
//								{
//									// ��Ԃ��y�f�B�[���[�X�g�b�v�z�ɐݒ�
//									m_NowState[m_PlayerNo] = DealerStop;
//									// �X�g�b�v�t���O�̗L����
//									m_Stop[m_PlayerNo] = true;
//									// �I���t���O�̗L����
//									m_FinCnt[m_PlayerNo] = true;
//								}
//							}
//
//							// �z��J�[�h��ύX
//							m_currentCardNo++;
//							// �Y���̈ʒu�̕ύX
//							m_gap[m_PlayerNo]++;
//							// �v���C���[�ԍ��̕ύX
//							m_PlayerNo++;
//							m_PlayerNo %= PLAYER_MAX;
//
//							// auto�����̉�
//							if (true)
//							{
//
//							}
//							if (m_autocnt < 2 && m_PlayerNo == PLAYER_MAX - 1)
//							{
//								// �I�[�g�񐔂̕ύX
//								m_autocnt++;
//							}
//							else if
//							{
//								if (m_PlayerNo == PLAYER_MAX - 1)
//								{
//									// �I���t���O�̗L����
//									m_FinCnt[m_PlayerNo] = true;
//								}
//								// auto�����I���t���O
//								m_autoflag = false;
//							}
//
//						}
//					}
//
//					// �P�Q�[���I����ĂȂ�������
//					if (m_oneGameFin == false)
//					{
//						// �S�v���C���[��Stay�ɂȂ��Ă��邩�̊m�F
//						for (int i = 0; i < PLAYER_MAX; i++)
//						{
//							m_nFinAllCnt += m_FinCnt[i];
//						}
//
//						// �P�Q�[���I�����Ă�����
//						if (m_nFinAllCnt >= PLAYER_MAX)
//						{
//							m_oneGameFin = true;
//						}
//						else
//						{
//							m_nFinAllCnt = 0;
//						}
//					}
//					// �f�o�b�O���\��
//					CDebugProc::Print("%2d Fin\n\n\n\n", m_nFinAllCnt);
//
//					if (m_oneGameFin == true)
//					{
//						// �P�Q�[���I���t���O�̗L����
//						m_oneGameFin = true;
//
//						m_pCardList[11]->SetUseFlag(true);
//						m_pCardList[11]->SetGap(m_gap[PLAYER_MAX - 1]);
//						m_pCardList[11]->SetAngle({ 270.0f, 90.0f, 0.0f });
//						m_pCardList[11]->Update();
//
//						while (m_NowState[PLAYER_MAX - 1] == NoState)
//						{
//							m_pCardList[m_currentCardNo]->SetUseFlag(true);
//							m_pCardList[m_currentCardNo]->SetGap(m_gap[PLAYER_MAX - 1]);
//							m_pCardList[m_currentCardNo]->SetAngle({ 270.0f, 90.0f, 0.0f });
//							m_pCardList[m_currentCardNo]->Update();
//
//							// ��]���̐ݒ�
//							m_pCardList[m_currentCardNo]->SetDestination({ m_EachPlayerPos[m_PlayerNo].x + (m_gap[PLAYER_MAX - 1] * 5.0f), m_EachPlayerPos[m_PlayerNo].y + (m_gap[PLAYER_MAX - 1] * 0.1f), m_EachPlayerPos[m_PlayerNo].z + (m_gap[PLAYER_MAX - 1] * 0.5f) });
//							m_pCardList[m_currentCardNo]->SetPos(m_EachCardPos[m_currentCardNo]);
//
//							m_pDealer->SetAttachFlag(true);
//							m_pDealer->SetAttachCardInfo(m_pCardList[m_currentCardNo]->mode[1]);
//							m_pDealer->Update();
//
//							// ���v�l�̕ۑ�
//							m_totalkeep[PLAYER_MAX - 1] = m_pDealer->GetTotalNo();
//
//							if (m_totalkeep[PLAYER_MAX - 1] >= 17)
//							{
//								// ��Ԃ��y�f�B�[���[�X�g�b�v�z�ɐݒ�
//								m_NowState[PLAYER_MAX - 1] = DealerStop;
//								m_ThisGameFin = true;
//							}
//							else if (m_totalkeep[PLAYER_MAX - 1] == 21)
//							{
//								// ��Ԃ��y�u���b�N�W���b�N�z�ɐݒ�
//								m_NowState[PLAYER_MAX - 1] = BlackJack;
//								m_ThisGameFin = true;
//							}
//							else if (m_totalkeep[PLAYER_MAX - 1] > 21)
//							{
//								// ��Ԃ��y�o�[�X�g�z�ɐݒ�
//								m_NowState[PLAYER_MAX - 1] = Bust;
//								m_ThisGameFin = true;
//							}
//
//							m_currentCardNo++;
//							m_gap[PLAYER_MAX - 1]++;
//						}
//
//						// �e�v���C���[�̏��s���̐ݒ�
//						for (int i = 0; i < PLAYER_MAX - 1; i++)
//						{
//							// �y �v���C���[�̕��� �z
//							switch (m_FirstPBust[i])
//							{
//							case true:
//								m_WinLose[i] = { LOSE, WIN };
//								break;
//
//							case false:
//								// �y �v���C���[�̕��� �z
//								if (m_NowState[PLAYER_MAX] == (DealerStop || BlackJack) && m_totalkeep[PLAYER_MAX - 1] > m_totalkeep[i])
//								{
//									m_WinLose[i] = { LOSE, WIN };
//								}
//								// �y �f�B�[���[�̕��� �z
//								else
//								{
//									m_WinLose[i] = { WIN, LOSE };
//								}
//								break;
//							}
//						}
//
//						// �f�o�b�O���\��
//						CDebugProc::Print("GameFin\n\n\n\n");
//					}
//
//
//
//
//
//					// �f�o�b�O���\��
//					for (int i = 0; i < PLAYER_MAX - 1; i++)
//					{
//						CDebugProc::Print("Player%d (%2d) : ", i + 1, m_totalkeep[i]);
//
//						switch (m_NowState[i])
//						{
//						case 0:
//							// NoState
//							CDebugProc::Print("NS   ");
//							break;
//						case 1:
//							// Hit
//							CDebugProc::Print(" H   ");
//							break;
//						case 2:
//							// Stay
//							CDebugProc::Print(" S   ");
//							break;
//						case 3:
//							// Bust
//							CDebugProc::Print(" B   ");
//							break;
//						case 4:
//							// BlackJack
//							CDebugProc::Print("BJ   ");
//							break;
//						case 5:
//							// DealerStop
//							CDebugProc::Print("DS   ");
//							break;
//						}
//
//						switch (m_WinLose[i].player)
//						{
//						case 0:
//							CDebugProc::Print("NONE\n");
//							break;
//						case 1:
//							CDebugProc::Print("WIN \n");
//							break;
//						case 2:
//							CDebugProc::Print("LOSE\n");
//							break;
//						case 3:
//							CDebugProc::Print("DRAW\n");
//							break;
//						}
//					}
//					CDebugProc::Print("Dealer  (%2d) : ", m_totalkeep[PLAYER_MAX - 1]);
//
//					switch (m_NowState[PLAYER_MAX - 1])
//					{
//					case NoState:
//						// NoState
//						CDebugProc::Print("NS\n");
//						break;
//					case Hit:
//						// Hit
//						CDebugProc::Print(" H\n");
//						break;
//					case Stay:
//						// Stay
//						CDebugProc::Print(" S\n");
//						break;
//					case Bust:
//						// Bust
//						CDebugProc::Print(" B\n");
//						break;
//					case BlackJack:
//						// BlackJack
//						CDebugProc::Print("BJ\n");
//						break;
//					case DealerStop:
//						// DealerStop
//						CDebugProc::Print("DS\n");
//						break;
//					}
//					CDebugProc::Print("\n");
//				}
//		}
//		break;
//
//	case SCENE_GAME2:
//		// �f�o�b�O���\��
//		for (int i = 0; i < 7; i++)
//		{
//			for (int j = 0; j < 13; j++)
//			{
//				CDebugProc::Print("%2d ", m_pPlaceCards[i][j]->number);
//				if (j % 13 == 12)
//				{
//					CDebugProc::Print("\n");
//				}
//			}
//		}
//		CDebugProc::Print("\n");
//
//
//		if (CInput::GetKeyTrigger(VK_SPACE))
//		{
//			for (int i = 0; i < 7; i++)
//			{
//				for (int j = 0; j < 13; j++)
//				{
//					if (m_pPlaceCards[i][j]->number != -1)
//					{
//						// ��]���̐ݒ�
//						m_pPlaceCards[i][j]->SetAngle(m_EachCardAngle[m_currentCardNo]);
//						m_pPlaceCards[i][j]->SetDestination({ -180.0f + ((i + 1) * 20.0f), 5.0f + ((j + 1) * 0.1f), -20.0f - ((j + 1) * 10.0f) });
//						m_pPlaceCards[i][j]->SetPos(m_EachCardPos[m_currentCardNo]);
//
//						m_pPlaceCards[i][j]->SetUseFlag(true);
//						m_pPlaceCards[i][j]->SetGap(m_gap[m_PlayerNo]);
//						m_pPlaceCards[i][j]->SetNowGameSceneNo(SCENE_GAME2);
//						
//						if (m_pPlaceCards[i][j+1]->number==-1)
//						{
//							m_pPlaceCards[i][j]->SetAngle({ 270.0f, 90.0f, 0.0f });
//						}
//						m_pPlaceCards[i][j]->Update();
//					}
//				}
//			}
//		}
//
//		m_gap[m_PlayerNo]++;
//		break;
//
//	default:
//		break;
//	}