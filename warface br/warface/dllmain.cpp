// _                 _         _           _
//| |               | |       | |         | |
//| | _____   ____ _| | __    | |__   __ _| |_ ___ ___      _ __ ___   ___
//| |/ _ \ \ / / _` | |/ /    | '_ \ / _` | __/ _ / __|    | '_ ` _ \ / _ \
//| |  __/\ V | (_| |   <     | | | | (_| | ||  __\__ \    | | | | | |  __/
//|_|\___| \_/ \__,_|_|\_\    |_| |_|\__,_|\__\___|___/    |_| |_| |_|\___|

//made for unknowncheats
//credits:  (onra2)
//credits:  KANKOSHEV
//credits:  SandyWF
//credits:  Dark1027




#include "stdafx.h"
#include "Includes.h"
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS
int ScreenWidth = 0;
int ScreenHeight = 0;
int ScreenCenterX = 0;
int ScreenCenterY = 0;
LPDIRECT3DDEVICE9 pGlobalDevice;
D3DVIEWPORT9 Viewport;
I3DEngine* p3DEngine;
IGame* pIGame;
ICVar* pIcvar;
SSystemGlobalEnvironment* pSSGE = (SSystemGlobalEnvironment*)(*(DWORD*)(SsystemGlobalEnvironmentAdressRU));
IGameFramework* pFrameWork = IGameFramework::GetGameFramework();

typedef HRESULT(WINAPI* EndScene_)(LPDIRECT3DDEVICE9 pDevice);
EndScene_ pEndScene;
HMODULE OhModule;
static bool ADamage = false;
static bool bReset = false;
static bool Ammor = false;
static bool WH = false;//for mod menu later
static bool Silhouettes = true;
static bool ainbot_sinuetas = false;
static bool aimbot = false;
static bool RECOIL = false;
static bool Accuracy = false;
static bool _hora = false;
static bool  sinu_aimbot  = false;
bool damag = false;
int __damage = 0;
bool Gerartexture = true;
int menu_itens = 13;
int V_DAMAGE =1;
std::string name;
std::string entidade_ativa ="aa";







int index = 0;
int Esquerda = 25, Topo = 40;
int Altura = 400, Largura = 150;
int X = (Esquerda + 6), Y = (Topo + 6);
int total_items = 0;
bool bShow = false;
LPD3DXFONT pFont =NULL;

LPDIRECT3DTEXTURE9 Vermelho, amarelo, verde, azul;



#pragma once
#define Red       D3DCOLOR_ARGB(150, 255, 000, 000)
#define Green     D3DCOLOR_ARGB(255, 127, 255, 000)
#define Orange    D3DCOLOR_ARGB(255, 255, 140, 000)
#define Blue      D3DCOLOR_ARGB(150, 000, 000, 255)
#define Yellow    D3DCOLOR_ARGB(255, 255, 255,  51)
#define Black     D3DCOLOR_ARGB(255, 000, 000, 000)
#define cinsa     D3DCOLOR_ARGB(150, 000, 000, 000)
#define Grey      D3DCOLOR_ARGB(255, 112, 112, 112)
#define Gold      D3DCOLOR_ARGB(255, 255, 215, 000)
#define Pink      D3DCOLOR_ARGB(255, 255, 192, 203)
#define Purple    D3DCOLOR_ARGB(255, 128, 000, 128)
#define White     D3DCOLOR_ARGB(255, 255, 255, 249)
#define Cyan      D3DCOLOR_ARGB(255, 000, 255, 255)
#define Magenta   D3DCOLOR_ARGB(255, 255, 000, 255)
#define TBlack    D3DCOLOR_ARGB(128, 000, 000, 000)



struct Items_
{
	bool seleted, on_off, inativo,desativado;


};
Items_ Items[200];





void CreatFont(PDIRECT3DDEVICE9 pD3D9) {
	if (!pFont) {
		D3DXCreateFont(pD3D9, 12, 0, FW_BOLD, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,L"Arial", &pFont);

	}


}



void  Text(int x, int y, LPCSTR text, DWORD color)
{
	RECT rect, rect2;
	SetRect(&rect, x, y, x, y);
	SetRect(&rect2, x - 0.1, y + 0.2, x - 0.1, y + 0.);
	pFont->DrawTextA(NULL, text, -1, &rect2, DT_LEFT | DT_NOCLIP, 0x00000000);
	pFont->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, color);
}





void  DrawBox(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	V[4] = { { x, y + h, 0.0f, 0.0f, Color },{ x, y, 0.0f, 0.01, Color },
	{ x + w, y + h, 0.0f, 0.0f, Color },{ x + w, y, 0.0f, 0.0f, Color } };
	pD3D9->SetTexture(0, NULL);
	pD3D9->SetPixelShader(0);
	pD3D9->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pD3D9->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pD3D9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3D9->SetRenderState(D3DRS_ZENABLE, FALSE);
	pD3D9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pD3D9->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	return;
}


void Resetfont() {
	pFont->OnLostDevice();
	pFont->OnResetDevice();
}

void DrawItem(Items_ its, LPCSTR texto, LPDIRECT3DDEVICE9 pDevice) {





	total_items++;
	if (its.desativado)DrawBox(Esquerda + 3, Y, Largura - 2, 15, cinsa, pDevice);
	else
	{


		if (its.seleted)
			DrawBox(Esquerda + 3, Y, Largura - 2, 15, Red, pDevice);


		else

			DrawBox(Esquerda + 3, Y, Largura - 2, 15, Blue, pDevice);

	}
	if (its.on_off) {
		Text(X + 100, Y + 3, "[on]", Green);
	}
	else {
		Text(X + 100, Y + 3, "[off]", Black);
	}
	Text(X, Y + 3, texto, White);
	Resetfont();
	Y += 15;
}



void Menu(LPDIRECT3DDEVICE9 pDevice) {

	
	

	int i = V_DAMAGE;
	char str[20];
	sprintf_s(str, "%d", i);
	const char *v1 = "- damage + X: ";
	const char *v2 = "def";
	char str1[20];

	strncpy_s(str1, v1, 10);
	str1[11] = '\0';

	strcat_s(str1, str);
	


	//DrawBox(Esquerda, Topo, Largura, Altura, Orange, pDevice);
	//DrawBox(Esquerda + 2, Topo + 2, Largura - 4, Altura - 4, Green, pDevice);



	DrawItem(Items[0], XorString("Acurracy"), pDevice);
	DrawItem(Items[1], "No_Recoin", pDevice);
	DrawItem(Items[2], "ammo", pDevice);
	DrawItem(Items[3], str1, pDevice);
	DrawItem(Items[4], "claymore", pDevice);
	DrawItem(Items[5], "flash", pDevice);
	DrawItem(Items[6], "sinuetas", pDevice);
	DrawItem(Items[7], "aimbot", pDevice);
	DrawItem(Items[8], "Hora", pDevice);	
	DrawItem(Items[9], "shoot_spotting", pDevice);
	DrawItem(Items[10], "ClimbHeight", pDevice);
	DrawItem(Items[11], "deslize", pDevice);
	DrawItem(Items[12], "ant kick coop", pDevice);



	


}





#pragma region utilities
float Distance(Vec3 VecA, Vec3 VecB)
{
	return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
		((VecA.z - VecB.z) * (VecA.z - VecB.z)));
}

int GetTeam(IActor* Actor)
{
	IGameFramework* pFrameWork = IGameFramework::GetGameFramework();
	if (Actor)
		return pFrameWork->GetIGameRules()->GetTeam(Actor->getIEntity()->GetID());//pEnt->GetID()
}

bool MyTeam(IActor* MyPlayer, IActor* EnemyPlayer)
{
	int mTeam = GetTeam(MyPlayer);
	int pTeam = GetTeam(EnemyPlayer);

	if ((mTeam != pTeam || pTeam == 0))
		return true;
	else
		return false;
}

bool GetDeadPlayer(IActor* Player)
{
	if (Player->IsDead()) return true;
	else return false;
}

bool WorldToScreen(Vec3 vEntPos, Vec3 *sPos)
{
	IRenderer::w2s_info info;
	info.Posx = vEntPos.x;
	info.Posy = vEntPos.y;
	info.Posz = vEntPos.z;

	info.Scrnx = &sPos->x;
	info.Scrny = &sPos->y;
	info.Scrnz = &sPos->z;

	pSSGE->pRenderer->ProjectToScreen(&info);

	if (sPos->z < 0.0f || sPos->z > 1.0f) {
		return 0;
	}

	sPos->x *= (Viewport.Width / 100.0f);
	sPos->y *= (Viewport.Height / 100.0f);
	sPos->z *= 1.0f;

	return (sPos->z < 1.0f);
}

bool IsEnemy(IEntity* pLclEnt, IEntity* pEnt)
{
	IGameFramework* pFrameWork = IGameFramework::GetGameFramework();
	IGameRules* pGameRules = pFrameWork->GetIGameRules();

	int pTeam = pGameRules->GetTeam(pEnt->GetID());
	int pLclTeam = pGameRules->GetTeam(pLclEnt->GetID());

	return (pLclTeam != 0) ? (pTeam != pLclTeam) : 1;
}

Vec3 GetPlayerPos(IEntity* pEntit)
{
	Vec3 vOffset = Vec3();
	Matrix34 pWorld = pEntit->GetWorldTM();
	vOffset = pWorld.GetTranslation();
	return vOffset;
}

Vec3 GetBonePositionByID(IEntity* pEnt, int BoneID)
{
	char* getBoneName;
	ICharacterInstance *pCharacterInstance = pEnt->GetCharacter(0);
	ISkeletonPose *pSkeletonPose = pCharacterInstance->GetISkeletonPose();
	int sBoneID = BoneID;
	Matrix34 World = pEnt->GetWorldTM();
	Matrix34 SkeletonAbs = Matrix34(pSkeletonPose->GetBoneByID(sBoneID));
	Matrix34 matWorld = World;
	float m03, m13, m23;
	m03 = (World.m00*SkeletonAbs.m03) + (World.m01*SkeletonAbs.m13) + (World.m02*SkeletonAbs.m23) + World.m03;
	matWorld.m03 = m03;
	m13 = (World.m10*SkeletonAbs.m03) + (World.m11*SkeletonAbs.m13) + (World.m12*SkeletonAbs.m23) + World.m13;
	matWorld.m13 = m13;
	m23 = (World.m20*SkeletonAbs.m03) + (World.m21*SkeletonAbs.m13) + (World.m22*SkeletonAbs.m23) + World.m23;
	matWorld.m23 = m23;

	return matWorld.GetTranslation();
}


extern "C" void Damage(IActor* mActor, INT DamageValue, INT Status)
{
	auto m_pItem = mActor->GetCurrentItem();
	if (m_pItem)
	{
		auto m_pWeapon = m_pItem->GetIWeapon();
		auto m_pExtraOne = m_pWeapon->m_pWeaponSpecific()->m_pWeaponExtraOne();
		auto weaponspec = m_pWeapon->m_pWeaponSpecific();
		if (Status)
		{
			m_pExtraOne->Damage(DamageValue);
		}
		else { m_pExtraOne->Damage(1); }
	}
}  


extern "C" void Aim(IActor* MyActor, IEntity* pEnt, Vec3 EnemyBone, float dist)
{
	if (!MyActor)
		return;
	if (!pEnt)
		return;
	Vec3 vDiffer;
	vDiffer = EnemyBone - GetBonePositionByID(MyActor->getIEntity(), 13);//13 is head pvp
	Quat FinalHeadPos = Quat::CreateRotationVDir(vDiffer.normalize());
	if (dist>0) { MyActor->GetPlayer()->SetViewRotation(FinalHeadPos); }
	else if (dist>10) { MyActor->GetPlayer()->SetViewRotation(FinalHeadPos); }
	else if (dist>20) { MyActor->GetPlayer()->SetViewRotation(FinalHeadPos); }
	else if (dist>30) { MyActor->GetPlayer()->SetViewRotation(FinalHeadPos); }
	else if (dist>40) { MyActor->GetPlayer()->SetViewRotation(FinalHeadPos); }
	else if (dist>50) { MyActor->GetPlayer()->SetViewRotation(FinalHeadPos); }
	else if (dist>60) { MyActor->GetPlayer()->SetViewRotation(FinalHeadPos); }
	else if (dist>70) { MyActor->GetPlayer()->SetViewRotation(FinalHeadPos); }
	else if (dist>80) { MyActor->GetPlayer()->SetViewRotation(FinalHeadPos); }
	else if (dist>90) { MyActor->GetPlayer()->SetViewRotation(FinalHeadPos); }
}

INT isVisible(Vec3 EnemyPos, Vec3 MyPos)
{
	Vec3 vTemp;
	ray_hit tmpHit;
	vTemp.x = EnemyPos.x - MyPos.x;
	vTemp.y = EnemyPos.y - MyPos.y;
	vTemp.z = EnemyPos.z - MyPos.z;
	return !pSSGE->pPhysicalWorld->RayWorldIntersection(MyPos, vTemp, 779, (10 & 0x0F), &tmpHit, 1);
}

int iFOV = 360;
#define PI    ((FLOAT)  3.141592654f)
bool InFOV(Vec3 EnemyPos, IActor* MyActor)
{
	SMovementState sState;
	MyActor->GetMovementController()->GetMovementState(sState);

	Vec3 vDir = EnemyPos - sState.pos;
	Vec3 AimDir = sState.aimDirection;
	vDir.Normalize();

	float fVal = acos(vDir.Dot(AimDir) / (AimDir.GetLengthSquared() * vDir.GetLengthSquared())) * (180 / PI);

	return (fVal <= iFOV);
}
#pragma endregion


void Hack()
{



	

	if (GetAsyncKeyState(VK_UP) & 1)
	{
		
		if (index > 0)
		{
			Items[index].seleted = false;



			index--;


		}
		else
		{
			Items[index].seleted = false;


			index = menu_itens - 1;


		}
	}


	if (GetAsyncKeyState(VK_DOWN) & 1) {
	
		if (index < menu_itens - 1) {
			Items[index].seleted = false;


			index++;

		}
		else {
			Items[index].seleted = false;

			index = 0;


		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 1) {
		Items[index].on_off = false;
		Items[index].inativo = false;
		
	}

	if (GetAsyncKeyState(VK_RIGHT) & 1) {
		Items[index].on_off = true;
		Items[index].inativo = false;
	
	}


	if (GetAsyncKeyState(VK_F9) & 1)
	{
		
		bShow = !bShow;
	}




	Items[index].seleted = true;




	

	IActor * MyPlayer = NULL;
	IActor * EnemyPlayer = NULL;
	IEntitySystem * pEntSys = NULL;
	IEntityIt * pEntIt = NULL;
	IEntity * MyEntity = NULL;
	IEntity * EnemyEntity = NULL;
	IEntityRenderProxy *pEntityRenderProxy = NULL;
	IGameRules* pGameRules = NULL;

	if (!pFrameWork)
		return;

	pGameRules = pFrameWork->GetIGameRules();
	if (!pGameRules)
		return;

	pEntSys = pSSGE->pEntitySystem;
	if (!pEntSys)
		return;

	pEntIt = pEntSys->GetEntityIterator();
	if (!pEntIt)
		return;

	if (!pFrameWork->GetClientActor(&MyPlayer))
		return;

	if (!MyPlayer)
		return;


	p3DEngine = pSSGE->p3DEngine;
	if (!p3DEngine)
		return;

	pIGame = pSSGE->pIGame;
	if (!pIGame)
		return;
	pIcvar = pIGame->GetICvar();
	if (!pIcvar)
		return;
	float OFF = 0;
	pIcvar->ACMemLog(OFF);
	pIcvar->ACMemScan(OFF);
	pIcvar->ACPatternScan(OFF);



	if (Items[0].on_off)
	{

		if (!Items[0].inativo)
		{
			
				pIcvar->SetIPelletsDisp(200);
				pIcvar->CrosshairSpreadTuning(0);
		
			Items[0].inativo = true;
		}
	}
	else
	{

		if (!Items[0].inativo)
		{
			pIcvar->SetIPelletsDisp(0);
			pIcvar->CrosshairSpreadTuning(77);
			Items[0].inativo = true;
		}
	}
	/////////////////////////

	if (Items[1].on_off)
	{

		if (!Items[1].inativo)
		{
			MyPlayer->GetPlayer()->m_ignoreRecoil = true;
			Items[1].inativo = true;
		}
	}
	else
	{

		if (!Items[1].inativo)
		{
			MyPlayer->GetPlayer()->m_ignoreRecoil = false;
			Items[1].inativo = true;
		}
	}


	if (Items[2].on_off)
	{

		if (!Items[2].inativo)
		{
			pIcvar->SetUnlimAmmo(1);
			Items[2].inativo = true;
		}
	}
	else
	{

		if (!Items[2].inativo)
		{
			pIcvar->SetUnlimAmmo(0);
			Items[2].inativo = true;
		}
	}
	


	if (Items[3].on_off)
	{
		if (!Items[3].inativo)
		{
			__damage = __damage + 1;
			Damage(MyPlayer, __damage, 1);
			V_DAMAGE = __damage;
			Items[3].inativo = true;
		}
	}
	else
	{
		if (!Items[3].inativo)
		{
			if (__damage > 1)
				__damage = __damage - 1;
			Damage(MyPlayer, __damage, 1);
			V_DAMAGE = __damage;
			Items[3].inativo = true;
		}

	}


	if (Items[4].on_off)
	{
		
		{
				MyPlayer->GetPlayer();
		float eValue = 100;
		MyPlayer->claymore_detector_radius(eValue);
			Items[4].inativo = true;
		}
	}
	
	
	if (Items[5].on_off)
	{
		
			//remove flashbang
			p3DEngine->SetPostEffectParam("Flashbang_Time", 0);
			p3DEngine->SetPostEffectParam("FlashBang_BlindAmount", 0);
			p3DEngine->SetPostEffectParam("Flashbang_DifractionAmount", 0);
			p3DEngine->SetPostEffectParam("Flashbang_Active", 0);
			//remove flashbang blurring
			p3DEngine->SetPostEffectParam("FilterRadialBlurring_Radius", 0);
			p3DEngine->SetPostEffectParam("FilterRadialBlurring_Amount", 0);
			Items[5].inativo = true;
		
	}
	




	



	if (Items[6].on_off)
	{
		if (!Items[6].inativo)
		{
			Silhouettes = true;
			Items[6].inativo = true;
		}
	}
	else
	{
		if (!Items[6].inativo)
		{
			Silhouettes = false;
			Items[6].inativo = true;
		}

	}



	if (Items[7].on_off)
	{
		if (!Items[7].inativo)
		{
			aimbot = true;
			Items[7].inativo = true;
		}
	}
	else
	{
		if (!Items[7].inativo)
		{
			aimbot = false;
			Items[7].inativo = true;
		}

	}





	if (Items[8].on_off)
	{
		if (!Items[8].inativo)
		{
			_hora = true;
			Items[8].inativo = true;
		}
	}
	else
	{
		if (!Items[8].inativo)
		{
			_hora = false;
			Items[8].inativo = true;
		}

	}


	if (Items[9].on_off)
	{
		if (!Items[9].inativo)
		{
			pIcvar->silencer_shoot_spotting(1);
			Items[9].inativo = true;
		}
	}
	else
	{
		if (!Items[9].inativo)
		{
			pIcvar->silencer_shoot_spotting(0);
			Items[9].inativo = true;
		}

	}

	if (Items[10].on_off)
	{
		
			MyPlayer->GetPlayer();
			float aValue = 3;
			MyPlayer->SetExtraClimbHeight(aValue);		
			Items[10].inativo = true;
		
	}
	else
	{
		
			MyPlayer->GetPlayer();
			MyPlayer->SetExtraClimbHeight(0);
	

	}


	if (Items[11].on_off)
	{
		
			MyPlayer->GetPlayer();
			float bValue = 40;
			MyPlayer->slideDistanceMult(bValue);
			
		
	}
	else
	{
		
			MyPlayer->GetPlayer();
			float bValue = 1;
			MyPlayer->slideDistanceMult(bValue);
			
		

	}



	if (Items[12].on_off)
	{
		if (!Items[12].inativo)
		{
			pIcvar->g_enable_ingame_kickvote_in_zombiemission(1);
			pIcvar->g_kickvote_pve_max_checkpoints(99);
			pIcvar->g_enableIdleCheck(0);
			
			Items[12].inativo = true;
		}
	}
	else
	{
		if (!Items[12].inativo)
		{
			
			Items[12].inativo = true;
		}

	}



	if (GetAsyncKeyState(VK_F7) & 1)
	{




		damag = !damag;
		if (!damag)
		{

			Damage(MyPlayer, 10, 1);
		}
		else
		{

			Damage(MyPlayer, 1, 0);
		}

	}

	









	

		for (; IEntity* pEnt = pEntIt->Next(); )
		{
			if (!pEnt)
				continue;

			
			name =pEnt->GetName();
			

	


			if ((strstr(name.c_str(), XorString ("Turret")) ||
				strstr(name.c_str(), XorString("IronMan")) ||
				strstr(name.c_str(), XorString("Cyborg")) ||
				strstr(name.c_str(), XorString( "Black_Wolf")) ||
				strstr(name.c_str(), XorString( "Mantis")) ||
				strstr(name.c_str(), XorString("SEDSoldier"))||
				strstr(name.c_str(), XorString("Drone") )||
				strstr(name.c_str(), XorString ("Mech") )))
			
				continue;
			


			

		

			if (EnemyPlayer = pFrameWork->GetIActorSystem()->GetActor(pEnt->GetID()))
			{
				if (MyPlayer != EnemyPlayer)
				{
					
					MyEntity = MyPlayer->getIEntity();
					if (!MyEntity)
						continue;
					

					EnemyEntity = EnemyPlayer->getIEntity();
					if (!EnemyEntity)
						continue;

					if (EnemyPlayer->IsDead())
						continue;

					






					Vec3 EnemyPos = GetPlayerPos(pEnt);
					Vec3 Head = GetBonePositionByID(pEnt, 13), Head2;
					Vec3 pHead = GetBonePositionByID(pEnt, 18);
					Vec3 mHead = GetBonePositionByID(MyPlayer->getIEntity(), 18);

					Vec3 Mpos = GetPlayerPos(MyEntity);
					Vec3 EnemyBone{ 0, 0, 0 };
					Vec3 Out;
					EnemyBone = GetBonePositionByID(pEnt, 13);//pvp


					//if (strstr(name.c_str(), XorString("Drone"))) EnemyBone = GetBonePositionByID(pEnt, 12);
					//if (strstr(name.c_str(), XorString("Turret"))) EnemyBone = GetBonePositionByID(pEnt, 1);
					//if (strstr(name.c_str(), XorString("TurretWall"))) EnemyBone = GetBonePositionByID(pEnt, 47);
					//if (strstr(name.c_str(), XorString("TurretCeil"))) EnemyBone = GetBonePositionByID(pEnt, 78);
					//if (strstr(name.c_str(), XorString("TurretFloor_ASR")) || strstr(name.c_str(), XorString("Turret_ASR_Target"))) EnemyBone = GetBonePositionByID(pEnt, 62);
					//if (strstr(name.c_str(), XorString("CQBHeavy"))) EnemyBone = GetBonePositionByID(pEnt, 13);
					//if (strstr(name.c_str(), XorString("SMGHeavy"))) EnemyBone = GetBonePositionByID(pEnt, 13);
					//if (strstr(name.c_str(), XorString("TurretFloor_cqb")) || strstr(name.c_str(), XorString("TurretFloor_CQB")) || strstr(name.c_str(), XorString("TurretHunt_CQB"))) EnemyBone = GetBonePositionByID(pEnt, 58);
					//if (strstr(name.c_str(), XorString("TurretFloor_mg")) || strstr(name.c_str(), XorString("TurretFloor_MG")) || strstr(name.c_str(), XorString("TurretHunt_MG")) || strstr(name.c_str(), XorString("TurretRail_mg")) || strstr(name.c_str(), XorString("Turret_MG"))) EnemyBone = GetBonePositionByID(pEnt, 68);
					//if (strstr(name.c_str(), XorString("HeavyTurretRail"))) EnemyBone = GetBonePositionByID(pEnt, 52);

					//if (strstr(name.c_str(), XorString("Iron"))) EnemyBone = GetBonePositionByID(pEnt, 9);
					//if (strstr(name.c_str(), XorString("SEDAssault"))) EnemyBone = GetBonePositionByID(pEnt, 60);
					//if (strstr(name.c_str(), XorString("SEDSoldier"))) EnemyBone = GetBonePositionByID(pEnt, 58);













					

						if (Silhouettes)
						{
							if (MyTeam(MyPlayer, EnemyPlayer))
							{
								
								if (isVisible(EnemyBone, mHead))
								{
									pEntityRenderProxy = (IEntityRenderProxy*)(pEnt->GetProxy(ENTITY_PROXY_RENDER));
									if (!pEntityRenderProxy)
										continue;
									pEntityRenderProxy->SetRndFlags(eAllMap);
									pEntityRenderProxy->SetHUDSilhouettesParams(0, 255, 0, 0);
								}
								else
								{
									pEntityRenderProxy = (IEntityRenderProxy*)(pEnt->GetProxy(ENTITY_PROXY_RENDER));
									if (!pEntityRenderProxy)
										continue;
									pEntityRenderProxy->SetRndFlags(eAllMap);
									pEntityRenderProxy->SetHUDSilhouettesParams(0, 0, 255, 0);


								}

							}


						}
					




					if (MyTeam(MyPlayer, EnemyPlayer) && (!GetDeadPlayer(EnemyPlayer)))
					{
						if ((WorldToScreen(Head, &Head2)) && (WorldToScreen(EnemyPos, &Out) && (!GetDeadPlayer(EnemyPlayer))) && (MyTeam(MyPlayer, EnemyPlayer)))
						{
							float h = abs(Out.y - Head2.y);
							float w = h / 1.25f;
							float ScaledPosX = Head2.x + w / 2 + 5;
							float ScaledPosY = (Head2.y - (w / 2) + w) - 4;
							EnemyBone = GetBonePositionByID(pEnt, 13);//pvp
							float Distancion;
							Distancion = Distance(GetPlayerPos(MyEntity), GetPlayerPos(pEnt));
							if (!Distancion)
								continue;

							if ((InFOV(pHead, MyPlayer)) && isVisible(EnemyBone, mHead))
							{
								if (aimbot)
									if (GetAsyncKeyState(VK_RBUTTON))
									{
										if (!MyPlayer->IsDead())
										{
											entidade_ativa = pEnt->GetName();
											Aim(MyPlayer, pEnt, EnemyBone, Distancion);
										}
									}
							}
							else
							{
								continue;
							}
						}
						else
						{
							continue;
						}
					}
					else
					{
						continue;
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
}


HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32) {
	if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
		return E_FAIL;
	WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
		| (WORD)(((colour32 >> 20) & 0xF) << 8)
		| (WORD)(((colour32 >> 12) & 0xF) << 4)
		| (WORD)(((colour32 >> 4) & 0xF) << 0);
	D3DLOCKED_RECT d3dlr;
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*)d3dlr.pBits;
	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;
	(*ppD3Dtex)->UnlockRect(0);
	return S_OK;
}








static bool bWasOpen = false;
static bool Create = false;

HRESULT WINAPI EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	
	
	CreatFont(pDevice);
	
	if (bShow)
	{
		Menu(pDevice);
		
	}

	Y = (Topo + 6);
	total_items = 0;
	


	

	if (Gerartexture) {
		GenerateTexture(pDevice, &Vermelho, Red);
		GenerateTexture(pDevice, &amarelo, D3DCOLOR_ARGB(255, 255, 255, 0));
		GenerateTexture(pDevice, &verde, D3DCOLOR_ARGB(255, 0, 255, 0));
		GenerateTexture(pDevice, &azul, D3DCOLOR_ARGB(255, 0, 0, 255));




		Gerartexture = false;
	}


	if (!Create)
	{
		pDevice->GetViewport(&Viewport);
		ScreenWidth = Viewport.Width;
		ScreenHeight = Viewport.Height;
		ScreenCenterX = (ScreenWidth / 2);
		ScreenCenterY = (ScreenHeight / 2);
		Create = true;
	}

	Hack();



	



	
	

	return (*pEndScene)(pDevice);
}

DWORD FindDevice(DWORD Len)
{
	DWORD dwObjBase = 0;

	dwObjBase = (DWORD)LoadLibrary(L"d3d9.dll");
	while (dwObjBase++ < dwObjBase + Len)
	{
		if ((*(WORD*)(dwObjBase + 0x00)) == 0x06C7
			&& (*(WORD*)(dwObjBase + 0x06)) == 0x8689
			&& (*(WORD*)(dwObjBase + 0x0C)) == 0x8689
			) {
			dwObjBase += 2; break;
		}
	}
	return(dwObjBase);
}
DWORD GetDeviceAddress(int VTableIndex)
{
	PDWORD VTable;
	*(DWORD*)&VTable = *(DWORD*)FindDevice(0x128000);
	return VTable[VTableIndex];
}





DWORD WINAPI endhook(LPVOID pThreadParameter)
{

	pEndScene = (EndScene_)GetDeviceAddress(42);


	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)pEndScene, (PVOID)EndScene);
	DetourTransactionCommit();


	
	
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		OhModule = hModule;
		DisableThreadLibraryCalls(hModule);			
		CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)endhook, NULL, NULL, NULL));
	    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

