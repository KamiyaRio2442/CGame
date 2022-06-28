#include <time.h>
#include "CardManeger.h"
#include "Input.h"
#include "Scene.h"
#include "Texture.h"
#include "DebugProc.h"

//（　拡縮×回転×移動　）

// 全カードの画像情報
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

// 動的配列
ID3D11ShaderResourceView* CCardManeger::m_pCardInfo[CARD_MAX];

// コンストラクタ
CCardManeger::CCardManeger(CScene* pScene) : CGameObj(pScene), m_pattern(0)
{
}
// デストラクタ
CCardManeger::~CCardManeger()
{
}

// 初期化関数
HRESULT CCardManeger::Init()
{
	HRESULT hr = S_OK;

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	switch (GetID())
	{
		case SCENE_GAME1:
		{
			// 現在の配布カード枚数
			m_currentCardNo = 0;
			// 現在のプレイヤー番号
			m_PlayerNo = 0;

			// カード情報の初期化
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

			// カードのシャッフルsrand( (int)time(NULL) );
			srand((int)time(NULL));
			for (int i = 0; i < 5000; i++)
			{
				int s1 = rand() % CARD_MAX;
				int s2 = rand() % CARD_MAX;

				CCard *wait = m_pCardList[s1];
				m_pCardList[s1] = m_pCardList[s2];
				m_pCardList[s2] = wait;
			}

			// プレイヤーマネージャーの初期化
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

			// カード情報の初期化
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

			// カードのシャッフルsrand( (int)time(NULL) );
			srand((int)time(NULL));
			for (int i = 0; i < 5000; i++)
			{
				int s1 = rand() % CARD_MAX;
				int s2 = rand() % CARD_MAX;

				CCard *wait = m_pCardList[s1];
				m_pCardList[s1] = m_pCardList[s2];
				m_pCardList[s2] = wait;
			}

			// 手札のセット
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
// 終了関数
void CCardManeger::Fin()
{
}
// 更新関数
void CCardManeger::Update()
{
	switch (GetID())
	{
		case SCENE_GAME1:
			// デバッグ情報表示
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

			// ゲームが始まった時にのみ実行されるauto処理のフラグ設定
			if (CInput::GetKeyTrigger(VK_SPACE) && m_autocnt == 0)
			{
				// ゲーム開始フラグの有効化
				m_StartFlag = true;
				// オート開始フラグの有効化
				m_autoflag = true;
			}

			// ゲーム開始フラグが有効の時
			if (m_StartFlag == true)
			{
				// 現在の回転情報の取得
				m_EachCardAngle[m_currentCardNo] = m_pCardList[m_currentCardNo]->GetAngle();
				// 現在の位置情報の取得
				m_EachCardPos[m_currentCardNo] = m_pCardList[m_currentCardNo]->GetPos();
				m_pCardList[m_currentCardNo]->SetPos(m_CradBasePos);

				// 【 Stayの処理 】
				if (m_FinFlag[m_PlayerNo] == true)
				{
					// プレイヤー番号の変更
					m_PlayerNo++;
					m_PlayerNo %= PLAYER_MAX;
				}

				if (m_autoflag == false && m_PlayerNo == PLAYER_MAX - 1)
				{
					// プレイヤー番号の変更
					m_PlayerNo++;
					m_PlayerNo %= PLAYER_MAX;
					break;
				}

				if (CInput::GetKeyTrigger(VK_W) && m_FinFlag[m_PlayerNo] == false)
				{
					// 状態を【ステイ】に設定
					m_NowState[m_PlayerNo] = Stay;
					// プレイヤー行動終了フラグの有効化
					m_FinFlag[m_PlayerNo] = true;
					// プレイヤー番号の変更
					m_PlayerNo++;
					m_PlayerNo %= PLAYER_MAX;
					break;
				}
				// 【 Hitの処理 】
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

								// 合計値の保存
								m_totalkeep[m_PlayerNo] = m_pDealer->GetTotalNo();

								if (m_autocnt < 2 && m_totalkeep[m_PlayerNo] >= 17)
								{
									// 状態を【ディーラーストップ】に設定
									m_NowState[m_PlayerNo] = DealerStop;

									m_ThisGameFin = true;
								}
								else if (m_totalkeep[PLAYER_MAX - 1] == 21)
								{
									// 状態を【ブラックジャック】に設定
									m_NowState[m_PlayerNo] = BlackJack;

									m_ThisGameFin = true;
								}

								// auto処理の回数
								if (m_autocnt < 2)
								{
									m_autocnt++;
								}
								else
								{
									// プレイヤー行動終了フラグの有効化
									m_FinFlag[m_PlayerNo] = true;
									// auto処理終了フラグ
									m_autoflag = false;
								}

								m_currentCardNo++;
								m_gap[m_PlayerNo]++;
								// プレイヤー番号の変更
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

							// 各合計値の保存
							m_totalkeep[m_PlayerNo] = m_pPlayerManager->GetEachNoKeep(m_PlayerNo);

							if (m_totalkeep[m_PlayerNo] < 21)
							{
								// 状態を【ヒット】に設定
								m_NowState[m_PlayerNo] = Hit;
							}
							else if (m_totalkeep[m_PlayerNo] == 21)
							{
								// 状態を【ブラックジャック】に設定
								m_NowState[m_PlayerNo] = BlackJack;
								// プレイヤー行動終了フラグの有効化
								m_FinFlag[m_PlayerNo] = true;
							}
							else if (m_totalkeep[m_PlayerNo] > 21)
							{
								// 状態を【バースト】に設定
								m_NowState[m_PlayerNo] = Bust;
								// プレイヤー行動終了フラグの有効化
								m_FinFlag[m_PlayerNo] = true;

								m_FirstPBust[m_PlayerNo] = true;
							}

							m_currentCardNo++;
							m_gap[m_PlayerNo]++;
							// プレイヤー番号の変更
							m_PlayerNo++;
							m_PlayerNo %= PLAYER_MAX;
							break;
						}
					}
				}

				// １ゲーム終わってなかったら
				if (m_oneGameFin == false)
				{
					// 全プレイヤーがStayになっているかの確認
					for (int i = 0; i < PLAYER_MAX - 1; i++)
					{
						m_nAllFinCnt += m_FinFlag[i];
					}
				}
				// デバッグ情報表示
				CDebugProc::Print("%2d Fin\n\n\n\n", m_nAllFinCnt);

				// １ゲーム終了したかの判定
				// 【 終了していた時 】
				if (m_nAllFinCnt >= PLAYER_MAX - 1)
				{
					// １ゲーム終了フラグの有効化
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

						// 回転情報の設定
						m_pCardList[m_currentCardNo]->SetDestination({ m_EachPlayerPos[PLAYER_MAX - 1].x + (m_gap[PLAYER_MAX - 1] * 5.0f), m_EachPlayerPos[PLAYER_MAX - 1].y + (m_gap[PLAYER_MAX - 1] * 0.1f), m_EachPlayerPos[PLAYER_MAX - 1].z + (m_gap[PLAYER_MAX - 1] * 0.5f) });
						m_pCardList[m_currentCardNo]->SetPos(m_EachCardPos[m_currentCardNo]);

						m_pDealer->SetAttachFlag(true);
						m_pDealer->SetAttachCardInfo(m_pCardList[m_currentCardNo]->mode[1]);
						m_pDealer->Update();

						// 合計値の保存
						m_totalkeep[PLAYER_MAX - 1] = m_pDealer->GetTotalNo();

						if (m_totalkeep[PLAYER_MAX - 1] == 21)
						{
							// 状態を【ブラックジャック】に設定
							m_NowState[PLAYER_MAX - 1] = BlackJack;

							m_ThisGameFin = true;
						}
						else if (m_totalkeep[PLAYER_MAX - 1] > 21)
						{
							// 状態を【バースト】に設定
							m_NowState[PLAYER_MAX - 1] = Bust;

							m_ThisGameFin = true;
						}
						else if (m_totalkeep[PLAYER_MAX - 1] >= 17)
						{
							// 状態を【ディーラーストップ】に設定
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

					// 各プレイヤーの勝敗情報の設定
					for (int i = 0; i < PLAYER_MAX - 1; i++)
					{
						// 【 プレイヤーの負け 】
						if (m_FirstPBust[i] == true)
						{
							m_PlayerWinLose[i] = LOSE;
							m_DealerWinLose[i] = WIN;
						}
						else
						{
							// 【 プレイヤーの負け 】
							if (m_NowState[PLAYER_MAX] == (DealerStop || BlackJack) && m_totalkeep[PLAYER_MAX - 1] > m_totalkeep[i])
							{
								m_PlayerWinLose[i] = LOSE;
								m_DealerWinLose[i] = WIN;
							}
							// 【 ディーラーの負け 】
							else
							{
								m_PlayerWinLose[i] = WIN;
								m_DealerWinLose[i] = LOSE;
							}
						}
					}

					// デバッグ情報表示
					CDebugProc::Print("GameFin\n\n\n\n");
				}
				// 【 終了していなかった時 】
				else
				{
					m_nAllFinCnt = 0;
				}
			}

			// デバッグ情報表示
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
			// デバッグ情報表示
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
							// 回転情報の設定
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

// 全モデル読込
HRESULT CCardManeger::LoadAll()
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	HRESULT hr = S_OK;

	// 全てのカード読込
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

// 全モデル解放
void CCardManeger::ReleaseAll()
{
	// 全モデル解放
	for (int i = 0; i < CARD_MAX; ++i)
	{
		if (m_pCardInfo[i])
		{
			SAFE_RELEASE(m_pCardInfo[i]);
		}
	}
}

// カードのテクスチャの取得
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
//		// デバッグ情報表示
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
//		// ゲーム終了の有無
//		switch (m_ThisGameFin)
//		{
//			// ゲーム終了
//			case true:
//				// カード自動回収フラグの有効化
//				if (CInput::GetKeyTrigger(VK_A))
//				{
//					m_autocollect = true;
//				}
//
//				// カード自動回収処理フラグが有効の時
//				if (m_autocollect == true)
//				{
//					// 回収未完了の間
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
//			// ゲーム未終了
//			case false:
//				// ゲーム開始フラグ・オート開始フラグの有効化
//				if (CInput::GetKeyTrigger(VK_SPACE) && m_autoflag == false)
//				{
//					m_autoflag = true;
//					m_gamestart = true;
//				}
//
//				// ゲーム開始フラグが有効の時
//				if (m_gamestart == true)
//				{
//					// プレイヤーの状態が【 ディーラーストップ・ストップ・ブラックジャック・バースト 】の時に順番を飛ばす
//					if (m_Stop[m_PlayerNo] == true)
//					{
//						m_PlayerNo++;
//						m_PlayerNo = m_PlayerNo % PLAYER_MAX;
//					}
//					else
//					{
//						// 待ち
//						if (CInput::GetKeyTrigger(VK_W))
//						{
//							// 状態を【ストップ】に設定
//							m_NowState[m_PlayerNo] = Stay;
//							// ストップフラグの有効化
//							m_Stop[m_PlayerNo] = true;
//							// プレイヤー番号の変更
//							m_PlayerNo++;
//							m_PlayerNo %= PLAYER_MAX;
//							// 終了フラグの有効化
//							m_FinCnt[m_PlayerNo] = true;
//						}
//						// 配り
//						else if (CInput::GetKeyTrigger(VK_Q) || m_autoflag == true)
//						{
//							// 現在の回転情報の取得
//							m_EachCardAngle[m_currentCardNo] = m_pCardList[m_currentCardNo]->GetAngle();
//							// 現在の位置情報の取得
//							m_pCardList[m_currentCardNo]->SetPos(m_CradBasePos);
//							m_EachCardPos[m_currentCardNo] = m_pCardList[m_currentCardNo]->GetPos();
//
//							// カードクラス移動有効化フラグの有効化
//							m_pCardList[m_currentCardNo]->SetUseFlag(true);
//							// ズラしたい値の入力
//							m_pCardList[m_currentCardNo]->SetGap(m_gap[m_PlayerNo]);
//							// ディーラーの二枚目をダウンカードに設定
//							if (m_currentCardNo == 11)
//							{
//								m_pCardList[m_currentCardNo]->SetAngle({ 90.0f, 90.0f, 0.0f });
//							}
//							// それ以外はアップカード
//							else
//							{
//								m_pCardList[m_currentCardNo]->SetAngle({ 270.0f, 90.0f, 0.0f });
//							}
//							// カードクラスの更新
//							m_pCardList[m_currentCardNo]->Update();
//
//							// 回転情報の設定
//							m_pCardList[m_currentCardNo]->SetDestination({ m_EachPlayerPos[m_PlayerNo].x + (m_gap[m_PlayerNo] * 5.0f), m_EachPlayerPos[m_PlayerNo].y + (m_gap[m_PlayerNo] * 0.1f), m_EachPlayerPos[m_PlayerNo].z + (m_gap[m_PlayerNo] * 0.5f) });
//							m_pCardList[m_currentCardNo]->SetPos(m_EachCardPos[m_currentCardNo]);
//
//							if (m_PlayerNo <= PLAYER_MAX - 1)
//							{
//								// プレイヤー番号の設定
//								m_pPlayerManager->SetAttachPlayerNo(m_PlayerNo);
//								// 配られたカードの値を設定
//								m_pPlayerManager->SetAttachCardNo(m_pCardList[m_currentCardNo]->mode[1]);
//								// プレイヤークラスの更新
//								m_pPlayerManager->Update();
//
//								// 各合計値の保存
//								m_totalkeep[m_PlayerNo] = m_pPlayerManager->GetEachNoKeep(m_PlayerNo);
//
//								// ブラックジャックの時
//								if (m_totalkeep[m_PlayerNo] == 21)
//								{
//									// 状態を【ブラックジャック】に設定
//									m_NowState[m_PlayerNo] = BlackJack;
//									// ストップフラグの有効化
//									m_Stop[m_PlayerNo] = true;
//									// 終了フラグの有効化
//									m_FinCnt[m_PlayerNo] = true;
//								}
//								// バーストの時
//								else if (m_totalkeep[m_PlayerNo] > 21)
//								{
//									// 状態を【バースト】に設定
//									m_NowState[m_PlayerNo] = Bust;
//									// ストップフラグの有効化
//									m_Stop[m_PlayerNo] = true;
//									// 終了フラグの有効化
//									m_FinCnt[m_PlayerNo] = true;
//
//									m_FirstPBust[m_PlayerNo] = true;
//								}
//								// ヒットの時
//								else if (m_totalkeep[m_PlayerNo] < 21)
//								{
//									// 状態を【ヒット】に設定
//									m_NowState[m_PlayerNo] = Hit;
//								}
//							}
//							else
//							{
//								m_pDealer->SetAttachFlag(true);
//								// 配られたカードの値を設定
//								m_pDealer->SetAttachCardInfo(m_pCardList[m_currentCardNo]->mode[1]);
//								// ディーラークラスの更新
//								m_pDealer->Update();
//
//								// 合計値の保存
//								m_totalkeep[m_PlayerNo] = m_pDealer->GetTotalNo();
//
//								if (m_totalkeep[m_PlayerNo] == 21)
//								{
//									// 状態を【ブラックジャック】に設定
//									m_NowState[m_PlayerNo] = BlackJack;
//									// ストップフラグの有効化
//									m_Stop[m_PlayerNo] = true;
//									// 終了フラグの有効化
//									m_FinCnt[m_PlayerNo] = true;
//								}
//								else if (m_autocnt < 2 && m_totalkeep[PLAYER_MAX - 1] >= 17)
//								{
//									// 状態を【ディーラーストップ】に設定
//									m_NowState[m_PlayerNo] = DealerStop;
//									// ストップフラグの有効化
//									m_Stop[m_PlayerNo] = true;
//									// 終了フラグの有効化
//									m_FinCnt[m_PlayerNo] = true;
//								}
//							}
//
//							// 配るカードを変更
//							m_currentCardNo++;
//							// ズレの位置の変更
//							m_gap[m_PlayerNo]++;
//							// プレイヤー番号の変更
//							m_PlayerNo++;
//							m_PlayerNo %= PLAYER_MAX;
//
//							// auto処理の回数
//							if (true)
//							{
//
//							}
//							if (m_autocnt < 2 && m_PlayerNo == PLAYER_MAX - 1)
//							{
//								// オート回数の変更
//								m_autocnt++;
//							}
//							else if
//							{
//								if (m_PlayerNo == PLAYER_MAX - 1)
//								{
//									// 終了フラグの有効化
//									m_FinCnt[m_PlayerNo] = true;
//								}
//								// auto処理終了フラグ
//								m_autoflag = false;
//							}
//
//						}
//					}
//
//					// １ゲーム終わってなかったら
//					if (m_oneGameFin == false)
//					{
//						// 全プレイヤーがStayになっているかの確認
//						for (int i = 0; i < PLAYER_MAX; i++)
//						{
//							m_nFinAllCnt += m_FinCnt[i];
//						}
//
//						// １ゲーム終了していた時
//						if (m_nFinAllCnt >= PLAYER_MAX)
//						{
//							m_oneGameFin = true;
//						}
//						else
//						{
//							m_nFinAllCnt = 0;
//						}
//					}
//					// デバッグ情報表示
//					CDebugProc::Print("%2d Fin\n\n\n\n", m_nFinAllCnt);
//
//					if (m_oneGameFin == true)
//					{
//						// １ゲーム終了フラグの有効化
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
//							// 回転情報の設定
//							m_pCardList[m_currentCardNo]->SetDestination({ m_EachPlayerPos[m_PlayerNo].x + (m_gap[PLAYER_MAX - 1] * 5.0f), m_EachPlayerPos[m_PlayerNo].y + (m_gap[PLAYER_MAX - 1] * 0.1f), m_EachPlayerPos[m_PlayerNo].z + (m_gap[PLAYER_MAX - 1] * 0.5f) });
//							m_pCardList[m_currentCardNo]->SetPos(m_EachCardPos[m_currentCardNo]);
//
//							m_pDealer->SetAttachFlag(true);
//							m_pDealer->SetAttachCardInfo(m_pCardList[m_currentCardNo]->mode[1]);
//							m_pDealer->Update();
//
//							// 合計値の保存
//							m_totalkeep[PLAYER_MAX - 1] = m_pDealer->GetTotalNo();
//
//							if (m_totalkeep[PLAYER_MAX - 1] >= 17)
//							{
//								// 状態を【ディーラーストップ】に設定
//								m_NowState[PLAYER_MAX - 1] = DealerStop;
//								m_ThisGameFin = true;
//							}
//							else if (m_totalkeep[PLAYER_MAX - 1] == 21)
//							{
//								// 状態を【ブラックジャック】に設定
//								m_NowState[PLAYER_MAX - 1] = BlackJack;
//								m_ThisGameFin = true;
//							}
//							else if (m_totalkeep[PLAYER_MAX - 1] > 21)
//							{
//								// 状態を【バースト】に設定
//								m_NowState[PLAYER_MAX - 1] = Bust;
//								m_ThisGameFin = true;
//							}
//
//							m_currentCardNo++;
//							m_gap[PLAYER_MAX - 1]++;
//						}
//
//						// 各プレイヤーの勝敗情報の設定
//						for (int i = 0; i < PLAYER_MAX - 1; i++)
//						{
//							// 【 プレイヤーの負け 】
//							switch (m_FirstPBust[i])
//							{
//							case true:
//								m_WinLose[i] = { LOSE, WIN };
//								break;
//
//							case false:
//								// 【 プレイヤーの負け 】
//								if (m_NowState[PLAYER_MAX] == (DealerStop || BlackJack) && m_totalkeep[PLAYER_MAX - 1] > m_totalkeep[i])
//								{
//									m_WinLose[i] = { LOSE, WIN };
//								}
//								// 【 ディーラーの負け 】
//								else
//								{
//									m_WinLose[i] = { WIN, LOSE };
//								}
//								break;
//							}
//						}
//
//						// デバッグ情報表示
//						CDebugProc::Print("GameFin\n\n\n\n");
//					}
//
//
//
//
//
//					// デバッグ情報表示
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
//		// デバッグ情報表示
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
//						// 回転情報の設定
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