#include "stdafx.h"
#include "F_loadingScene.h"


HRESULT F_loadingScene::init(void)
{
	//로딩클래스 생성 및 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	_sceneChange = false;
	_alpha = 0;

	return S_OK;
}

void F_loadingScene::release(void)
{
	//로딩화면 해제
	SAFE_DELETE(_loading);
}

void F_loadingScene::update(void)
{
	//cout << "로딩 시작 됬냐?" << endl;
	//로딩클래스 업데이트
	_loading->update();

	if (_loading->loadingDone())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//로딩이 완료 됐으니 씬변경하자
			_sceneChange = true;
		}
	}

	if (_sceneChange)
	{
		_alpha += 5;
	}

	if (_alpha == 255)
	{
		SCENEMANAGER->changeScene("메인");
	}
}

void F_loadingScene::render(void)
{
	_loading->render();

}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void F_loadingScene::loadingImage(void)
{
	//백그라운드
	//========================================================================================================
	_loading->loadImage("배경1", "image/시스템/배경1.bmp", 640, 480);
	_loading->loadImage("배경2", "image/시스템/배경2.bmp", 640, 480);
	_loading->loadImage("배경3", "image/시스템/배경3.bmp", 640, 480);

	_loading->loadImage("마을", "image/시스템/town00.bmp", WINSIZEX, WINSIZEY);

	_loading->loadImage("게임오버", "image/시스템/게임오버.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("엔딩", "image/시스템/엔딩.bmp", WINSIZEX, 345);

	_loading->loadImage("검은화면", WINSIZEX, WINSIZEY);

	//시스템 UI
	//========================================================================================================
	_loading->loadImage("상태창", "image/시스템/상태창.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("상태창_이동", "image/시스템/이동선택.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("상태창_스킬", "image/시스템/스킬선택.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("상태창_도구", "image/시스템/아이템 선택.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("상태창_턴", "image/시스템/턴종료 선택.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("상태창_저장", "image/시스템/세이브 선택.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("상태창_로드", "image/시스템/로드 선택.bmp", 452, 102, true, RGB(255, 0, 255));

	_loading->loadImage("세이브창", "image/시스템/세이브창.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("로드창", "image/시스템/로드창.bmp", 452, 102, true, RGB(255, 0, 255));

	_loading->loadImage("세이브 선택2", "image/시스템/세이브 선택2.bmp", 70, 70, true, RGB(255, 0, 255));
	_loading->loadImage("로드 선택2", "image/시스템/로드 선택2.bmp", 70, 70, true, RGB(255, 0, 255));

	_loading->loadImage("경험치창", "image/시스템/경험치창.bmp", 360, 100, true, RGB(255, 0, 255));

	_loading->loadImage("UI배경", "image/시스템/UI백그라운드.bmp", 200, 480);
	_loading->loadImage("세이브", "image/시스템/세이브.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadImage("로드", "image/시스템/로드.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadFrameImage("화살표", "image/시스템/화살표.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("화살표2", "image/시스템/화살표2.bmp", 64, 128, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("표지판", "image/시스템/표지판.bmp", 128, 256, 1, 4, true, RGB(255, 0, 255));
	_loading->loadImage("테두리", "image/시스템/테두리2.bmp", 240, 480, true, RGB(255, 0, 255));
	_loading->loadImage("승리", "image/시스템/승리.bmp", 500, 148, true, RGB(255, 0, 255));

	//시스템
	//========================================================================================================
	_loading->loadFrameImage("기절", "image/시스템/기절.bmp", 96, 384, 1, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("방향", "image/시스템/방향.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("숫자폰트1", "image/시스템/숫자폰트1.bmp", 128, 320, 8, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("숫자폰트2", "image/시스템/숫자폰트2.bmp", 128, 320, 8, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("숫자폰트3", "image/시스템/숫자폰트3.bmp", 32, 640, 1, 10, true, RGB(255, 0, 255));
	_loading->loadImage("체력바_앞", "image/시스템/체력바_앞1.bmp", 150, 12);
	_loading->loadImage("체력바_뒤", "image/시스템/체력바_뒤1.bmp", 150, 12);
	_loading->loadImage("마나바_앞", "image/시스템/마나바_앞.bmp", 150, 12);
	_loading->loadImage("마나바_뒤", "image/시스템/마나바_뒤.bmp", 150, 12);
	_loading->loadImage("진행바_앞", "image/시스템/진행바_앞.bmp", 800, 24);
	_loading->loadImage("진행바_뒤", "image/시스템/진행바_뒤.bmp", 800, 24);
	_loading->loadImage("경험치바_뒤", "image/시스템/경험치바_뒤.bmp", 300, 12);
	_loading->loadImage("경험치바_앞", "image/시스템/경험치바_앞.bmp", 300, 12);
	_loading->loadImage("그림자", "image/시스템/그림자.bmp", 96, 96, true, RGB(255, 0, 255));
	_loading->loadImage("캐릭터_상태창", "image/시스템/캐릭터 상태창.bmp", 300, 100, true, RGB(255, 0, 255));
	_loading->loadImage("알림_창", "image/시스템/알림 창.bmp", 100, 100, true, RGB(255, 0, 255));


	//스킬
	//========================================================================================================
	_loading->loadFrameImage("플레임버스트", "image/스킬/플레임버스트.bmp", 2380, 192, 17, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("힐1", "image/스킬/힐_낙하.bmp", 192, 384, 2, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("힐2", "image/스킬/힐_산란.bmp", 192, 768, 2, 8, true, RGB(255, 0, 255));



	//몬스터 이미지
	//========================================================================================================
	//두목
	_loading->loadFrameImage("두목_사망", "image/몬스터/두목/두목 사망.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("두목_피격", "image/몬스터/두목/두목 피격.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("두목_대기", "image/몬스터/두목/두목 대기.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("두목_준비", "image/몬스터/두목/두목 대기.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("두목_이동", "image/몬스터/두목/두목 이동.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("두목_점프", "image/몬스터/두목/두목 점프.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("두목_공격", "image/몬스터/두목/두목 공격.bmp", 384, 1152, 4, 12, true, RGB(255, 0, 255));
	//히드라
	//========================================================================================================

	_loading->loadFrameImage("히드라_사망", "image/몬스터/히드라/히드라 사망.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("히드라_피격", "image/몬스터/히드라/히드라 피격.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("히드라_대기", "image/몬스터/히드라/히드라 대기.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("히드라_준비", "image/몬스터/히드라/히드라 대기.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("히드라_이동", "image/몬스터/히드라/히드라 이동.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("히드라_점프", "image/몬스터/히드라/히드라 점프.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("히드라_공격", "image/몬스터/히드라/히드라 공격.bmp", 384, 960, 4, 10, true, RGB(255, 0, 255));


	//캐릭터 이미지
	//=======================================================================================================
	//카린
	_loading->loadFrameImage("카린_피격", "image/캐릭터/카린/카린 피격.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("카린_대기", "image/캐릭터/카린/카린 대기.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("카린_가드", "image/캐릭터/카린/카린 가드.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("카린_회피", "image/캐릭터/카린/카린 회피.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("카린_기절", "image/캐릭터/카린/카린 기절.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("카린_빙결", "image/캐릭터/카린/카린 빙결.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("카린_석화", "image/캐릭터/카린/카린 석화.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("카린_이동", "image/캐릭터/카린/카린 이동.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("카린_점프", "image/캐릭터/카린/카린 점프.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("카린_준비", "image/캐릭터/카린/카린 준비.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("카린_스킬1", "image/캐릭터/카린/카린 스킬1.bmp", 384, 288, 4, 3, true, RGB(255, 0, 255));

	_loading->loadFrameImage("카린_스킬2", "image/캐릭터/카린/카린 스킬2.bmp", 384, 288, 4, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("카린_스킬3", "image/캐릭터/카린/카린 스킬3.bmp", 384, 480, 4, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("카린_공격", "image/캐릭터/카린/카린 공격.bmp", 384, 576, 4, 6, true, RGB(255, 0, 255));

	//아리스				  
	_loading->loadFrameImage("아리스_대기", "image/캐릭터/아리스/아리스 대기.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("아리스_기절", "image/캐릭터/아리스/아리스 기절.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아리스_피격", "image/캐릭터/아리스/아리스 피격.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("아리스_이동", "image/캐릭터/아리스/아리스 이동.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아리스_점프", "image/캐릭터/아리스/아리스 점프.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아리스_준비", "image/캐릭터/아리스/아리스 준비.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아리스_스킬1", "image/캐릭터/아리스/아리스 스킬1.bmp", 384, 1056, 4, 11, true, RGB(255, 0, 255));

	_loading->loadFrameImage("아리스_공격", "image/캐릭터/아리스/아리스 공격.bmp", 384, 576, 4, 6, true, RGB(255, 0, 255));

	//알
	_loading->loadFrameImage("알_대기", "image/캐릭터/알/알 대기.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("알_기절", "image/캐릭터/알/알 기절.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("알_피격", "image/캐릭터/알/알 피격.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("알_기절", "image/캐릭터/알/알 기절.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("알_준비", "image/캐릭터/알/알 준비.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("알_이동", "image/캐릭터/알/알 이동.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("알_점프", "image/캐릭터/알/알 점프.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("알_스킬1", "image/캐릭터/알/알 스킬1.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("알_공격", "image/캐릭터/알/알 공격.bmp", 384, 576, 4, 6, true, RGB(255, 0, 255));

	//맵이미지
	//=======================================================================================================
	_loading->loadImage("블록", "image/블록.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("블록2", "image/블록2.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("블록3", "image/블록3.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("블록4", "image/블록4.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("선택", "image/TileSelectTrue2.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("선택2", "image/TileSelectFalse2.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("선택3", "image/TileSelectTrue.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("선택4", "image/TileSelectFalse.bmp", 64, 32, true, RGB(255, 0, 255));

	_loading->loadFrameImage("타일1", "image/GrassTile.bmp", 320, 192, 5, 6, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일2", "image/SnowTile.bmp", 1120, 48, 16, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("오브젝트", "image/오브젝트.bmp", 640, 128, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("오브젝트2", "image/오브젝트2.bmp", 448, 140, 7, 1, true, RGB(255, 0, 255));

}

void F_loadingScene::loadingSound(void)
{

}
