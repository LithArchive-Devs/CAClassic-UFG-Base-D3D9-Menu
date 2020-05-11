#ifndef _ENGINE_CLASS_
#define _ENGINE_CLASS_

//SFX ID's								
#define SFX_NADE				0x13
#define SFX_PICKUP				0x17
#define SFX_CHARACTER			0x18
#define SFX_MAX					0x3B

//Send To Server ID's
#define ID_Weapon_Spawn         50//402
#define ID_Anti_Kick            206
#define ID_God_Mode             135
#define ID_Spammer              104
#define ID_Respawn              113
#define ID_Server_Crash         153//404//200
#define ID_Suicide              161
#define ID_Leave_Game           174
#define ID_IP_Ban               406//150

//cShell
#define ADDR_LTCLIENT           0x377E0C88
#define ADDR_GAMESTATUS         0x377F0E9C
#define ADDR_WEAPONMGR	        0x37821D14
#define ADDR_LOCALPLAYER        0x371560C0
#define ADDR_CLIENTINFOMGR      0x377DA934
#define ADDR_PLAYERBYINDEX      0x37155240

//Engine.Exe
#define ADDR_W2S		        0x4915C0
#define ADDR_DRAWPRIM		    0x805774
#define ADDR_SENDTOSERVER       0x474350

//ClientFx.fxd
#define ADDR_CLIENTFX           0x66F34

//Weapon ID's
#define M107CQ 1
#define M107CQ_SE 2
#define M107CQ_Air_Force 3; 
#define M107CQ_SE_Ghillie 4; 
#define UMP45 5; 
#define M60E4 6; 
#define M60E4_Steel 7; 
#define Airstrike_Napalm 8;
#define AirStrike_1 9; 
#define MP5_MOD_LE 10;
#define MTAR_21_LE 11;
#define M4A1_DW_LE 12;
#define MP7_MOD_LE 13;
#define Turkey_Leg 14;
#define M6A2 15;
#define M6A2_SRT 16;
#define FAMAS_SE 17;
#define FAMAS_G2_SE_1 18;
#define L115A2 19;
#define L115A3 20;
#define K5SD 21;
#define K5_CAMO 22;
#define K5SD_CAMO 23;
#define Frist_Aid_Kit 24;
#define AK_74M_LE 25;
#define FAMAS_G2_SE_2 26;
#define LifeTaker_1 27;
#define Zombie_Frag 28;
#define Zombie_Gas 29;
#define LifeTaker_2 30;
#define LifeTaker_3 31;
#define LifeTaker_4 32;
#define L96A1_Black_Magnum 33;
#define M32_Droppable 34;
#define Minigun_Droppable 35;
#define Golden_Punisher 36;
#define Airstrike_Napalm_Droppable 37;
#define AirStrike_2 38;
#define M3_Super_90 39;
#define Do_Not_Use_1 40;
#define REC7 41;
#define M39_EMR 42;
#define M39_EM_Desert 43;
#define M417_Combat_LE 44;
#define M107CQ_SE_LE 45;
#define M6A2_SRT_LE 46;
#define G36E_LE 47;
#define UMP45_LE 48;
#define M417_SB 49;
#define M110_SASS 50;
#define AA_12 51;
#define M93_HORNET 52;
#define M16A3_Champion 53;
#define M16A3_Elite 54;
#define M16A3_Veteran 55;
#define M16A3_Professional 56;
#define ACR_Blacksnake 57;
#define AN_94 58;
#define MG36 59;
#define M92FS_Champion 60;
#define M92FS_Elite 61;
#define M92FS_Veteran 62;
#define M92FS_Professional 63;
#define M9_Champion 64;
#define M9_Elite 65;
#define M9_Veteran 66;
#define M9_Professional 67;
#define UMP_LE 68;
#define ACR 69;
#define ACR_Sandfire 70;
#define CX4_Storm 71;
#define M960 72;
#define Mels_MP7_MOD 73;
#define Auto_Turret 74;
#define Do_Not_Use_2 75;
#define REC7_Rangers 76;
#define G3 77;
#define M_200 78;
#define M_200_Ghillie 79;
#define SPR 80;
#define Kriss 81;
#define Kriss_SpecOps 82;
#define TMP 83;
#define M21E 84;
#define DSR_1_Tactical 85;
#define M32_Stun 86;
#define American_Eagle 87;
#define Qurantine_Hands 88;
#define Guillotine 89;
#define Barons_M416_CQB 90;
#define DSR_1 91;
#define DSR_1_Subsonic 92;
#define Ulitmax_100 93;
#define Negev 94;
#define FS2000 95;
#define F2000 96;
#define F2000_Tactical 97;
#define Tracker_Knife 98;
#define TPG_1 99;
#define TPG_1_Pro 100;
#define M14EBR 101;
#define Survival_Machete 102;
#define MG2E 103;
#define M1866 104;
#define Dom_Pedro_Sword 105;
#define Pumkin_Grenade 106;
#define Dynamite_1 107;
#define Dynamite_HE 108;
#define Dynamite_2 109;
#define LifeTaker_5 110;
#define Dynamite_Pack 111;
#define XK_8 112;
#define XK_8_Tactical 113;
#define Autumn_G36E_Valkyrie 114;
#define Vipers_P90TR 115;
#define Autumn_LAW 116;
#define M417_CQB 117;
#define XM8 118;
#define L96A1_Holiday_Wolf 119;
#define Scorpions_PP_19_MOD 120;
#define Anaconda_Gold 121;
#define P99 122;
#define Tiger_Strider 123;
#define Candy_Cane_Club 124;
#define TRG_21 125;
#define TRG_41 126;
#define TGR_SE 127;
#define Caltrops 128;
#define MG21E_Steel 129;
#define MG42 130;
#define TPG_1_Master 131;
#define S_58_Musket 132;
#define A44RemRev 133;
#define HR1860 134;
#define M1849_pocket_Revolver 135;
#define C1851N 136;
#define E_57_Musket 137;
#define Confederate_Double_Barrel 138;
#define A32SW2 139;
#define Dragoon 140;
#define C1860N 141;
#define T_2 142;
#define WA2000 143;
#define WA2000_Classic 144;
#define Box_Gun 145;
#define Guitar_Gun 146;
#define M79 147;
#define PSG_1_MARK_II 148;
#define AA_12_MARK_II 149;
#define TAR_CAMO_MARK_II 150;
#define Toy_Gun 151;
#define Squirt_Gun_1 152;
#define Azazel 153;
#define P90TR_CBS 154;
#define Saiga_20K_CQB_CAMO_MARK_II 155;
#define Skorpion_MARK_II 156;
#define SG556_MARK_II 157;
#define MZP_1 158;
#define Alien_Gun 159;
#define MP5A4_Unlimited_Ammo 160;
#define M4A1_Unlimited_Ammo 161;
#define P90_Unlimited_Ammo 162;
#define M416_Unlimited_Ammo 163;
#define MG21E_Unlimited_Ammo 164;


class cWeaponInfo;
class cWeaponMgr;
class cClientWeaponMgr;
class cCharacterFX;
class cClientInfo;
class cPlayerInfo;
class WepInfo;
class Info;
class Something;
class _Object;
class cPlayerMgr;
class LocalInfo;
class c_player;
class cLTModel;
class cGameClientShell;
class cSFXList;
class cSFXMgr;
struct Transform;


struct Transform
{
	D3DXVECTOR3 Pos;
	unsigned char Space [0x100];
};

class cSFXList
{
public:
			unsigned long	unk0;
	unsigned long*	List;
			unsigned long	unk1;
	int				Num;
};

class cSFXMgr
{
public:
	cSFXList		SFXList[0x3D];
};

class cPlayerInfo
{
public:
	__int32 Unknown0;
	__int32 index;
	__int32 Unknown1;
	__int32 Unknown2;
	CHAR Name[12];
	CHAR unknown3[12];
	int *obj;
	CHAR unknown4[68];
	__int32 Team; 
	__int32 unknown5;
	__int8 IsDead;
	BYTE pIsDead; //0x0078 
	char _0x0079[319];
};

class c_player
{
public:
			char unknown0[4];
	__int32 ClientID;			 
			char unknown1[4]; 
	//std::string Name;			
	int* Object;
	__int32 Kills;				 
	__int32 Deaths;				 
			char unknown52[44];  
	__int32 HeadShots;			
			char unknown100[12];
	__int32 TeamID;				 
			char unknown47[4];
	bool isDead;				
			char unknown4[491];
	c_player* Next;				
};


class LocalInfo
{
public:
	Info* goToInfoClass; //0000
};


class _Object
{
public:
   CHAR Pad[4];
   D3DXVECTOR3 origin;
};

class Something
{
public:
	bool bIsAlive; //0000
};

class WepInfo
{
public:
	__int32 iBackPackABulletsLeft;  //0000
	__int32 i2ndaryBulletsLeft;		//0004
			__int32 Unknown0;	    
	__int32 iGrenadesLeft;			//000C
	__int32 iBackPackBBulletsLeft;  //0010
};

class Info
{
public:
			char unknown0[12];		//0x0000
	__int32 iHP;					//0x000C  
	__int32 iAP;					//0x0010  
	__int32 iMaxHP;					//0x0014  
	__int32 iMaxAP;					//0x0018  
	WepInfo* gotoWepInfo;			//0x001C  
	Something* goToSomething;		//0x0020  
			char unknown36[352];	
	float fStamina;					//0x0184  
	__int32 iIsRunning;				//0x0188  
	__int32 iIsJumping;				//0x018C  
	__int32 iWeaponSlotInUse;		//0x0190  
			char unknown404[44];	//0x0194
	cPlayerInfo* goToPlayers;			//0x01C0  		
};

class PlayerInfo
{
public:
	__int32 Unknown0;
	__int32 index;
	__int32 Unknown1;
	__int32 Unknown2;
	CHAR Name[12];
	CHAR unknown3[12];
	_Object *obj;
	CHAR unknown4[68];
	__int32 Team; 
	__int32 unknown5;
	__int8 IsDead;
};

class cWeaponInfo
{
public:

char unknown0[12]; //0x0000
DWORD dwClientWeaponType; //0x000C  
char unknown16[16]; //0x0010
DWORD dwAlt_InstDamage; //0x0020  
DWORD dwInstDamage; //0x0024  
DWORD UNK; //0x0028  
char unknown44[104]; //0x002C
DWORD dwFireSnd; //0x0094  
char unknown152[108]; //0x0098
float fFireDelay1; //0x0104  
float ffiredelay1; //0x0108  
DWORD dwMaxAmmo3; //0x010C  
DWORD dwMaxAmmo2; //0x0110  
char unknown276[276]; //0x0114
DWORD dwCrossHairA; //0x0228  
DWORD dwCrossHairR; //0x022C  
DWORD dwCrossHairG; //0x0230  
DWORD dwCrossHairB; //0x0234  
BYTE TripleShotMode; //0x0238  
char unknown569[3]; //0x0239
DWORD dwTripleShotRoundNum; //0x023C  
float fDamageRFacter; //0x0240  
char unknown580[28]; //0x0244
DWORD dwInfiAmmo2;
DWORD dwInfiniteAmmo; //0x0264  
DWORD dwHideWhenEmpty; //0x0268  
DWORD dwIsAmmo; //0x026C  
char unknown624[4]; //0x0270
DWORD dwShotsPerClip; //0x0274  
char unknown632[52]; //0x0278
float fZoomTime; //0x02AC  
DWORD dwMinPerturb; //0x02B0  
DWORD dwMaxPerturb; //0x02B4  
float fDuckPerturb; //0x02B8  
float fMoveDuckPerturb; //0x02BC  
DWORD dwZoomedMinPerturb; //0x02C0  
DWORD dwZoomedMaxPerturb; //0x02C4  
DWORD dwRange; //0x02C8  
char unknown716[12]; //0x02CC
DWORD VectorsPerRound; //0x02D8  
char unknown732[40]; //0x02DC
float fPerturbIncSpeed; //0x0304  
float fPerturbDecSpeed; //0x0308  
char unknown780[4]; //0x030C
float fZoomedPerturbIncSpeed; //0x0310  
float fZoomedPerturbDecSpeed; //0x0314  
char unknown792[4]; //0x0318
float fBaseCamRecoilPitch; //0x031C  
float fBaseCamRecoilAccelPitch; //0x0320  
char unknown804[36]; //0x0324
float fTripleShotMaxCamRecoilPitch; //0x0348  
float fTripleShotBaseCamRecoilPitch; //0x034C  
char unknown848[8]; //0x0350
DWORD dwTripleShotMinPerturb; //0x0358  
DWORD dwTripleShotMaxPerturb; //0x035C  
float fTripleShotPerturbIncSpeed; //0x0360  
float fTripleShotPerturbDecSpeed; //0x0364  
char unknown872[112]; //0x0368
DWORD dwFireRate; //0x03D8  
DWORD dwMoveSpeed; //0x03DC  
DWORD ID03B39CC0; //0x03E0  
char unknown996[32]; //0x03E4
BYTE DisableCrosshair; //0x0404  
char unknown1029[27]; //0x0405
float fCameraSwayXFreq; //0x0420  
float fCameraSwayYFreq; //0x0424  
char unknown1064[12]; //0x0428
DWORD dwTargetCrosshairFlag; //0x0434  
DWORD dwEffectRange; //0x0438  
char unknown1084[192]; //0x043C
DWORD dwFireDelay; //0x04FC 

};

class cWeaponMgr
{
public:

char unknown0[5564];
cWeaponInfo** Weapons; //15BC
__int32 WeaponCount; //15C0

};

class cClientWeaponMgr{
public:

	cWeaponInfo** WeaponList;   //0000
	__int32 MaxWeapons;			  //0004
	__int32 WeapIndex;			  //0008
	cWeaponInfo* CurrentWeapon; //000C
	BYTE WeaponsEnabled;		  //0010
	BYTE WeaponsVisible;		  //0011	
			char unknown16[20];				
	__int32 nCurrentWeaponID;	 //0x0024
};

class cCharacterFX
{
public:
			char	unk1[16];
	int*	Object;			//0x10
			char	unk2[44];
	int		IsPlayer;		//0x40
			char	unk3[40];
	unsigned char	Index;	//0x6C
			char unknown112[8]; //0x0070
	float fStartPitch; //0x0078  
	float fStartYaw; //0x007C  
			char unknown128[1224]; //0x0080
			BYTE unk1287; //0x0548  
	bool bIsDead; //0x0549  
	bool bSpawnSheild; //0x054A  
			BYTE unk5563; //0x054B  
			char unknown1356[12]; //0x054C
	int* hHitbox; //0x0558  
			char unknown1372[96]; //0x055C
			WORD wUnk; //0x05BC  
	WORD wHealth; //0x05BE  
	WORD wArmor; //0x05C0  
};

class cClientInfo
{
public:
	__int32 pPing; //0x0000 
	__int32 Index; //0x0004 
char _0x0008[8];
	char pName[12]; //0x0010 
char _0x001C[12];
	int* Object; //0x0028 
	__int32 pKills; //0x002C 
	__int32 pDeaths; //0x0030 
char _0x0034[52];
	__int32 pFTMission; //0x0068 
char _0x006C[4];
	__int32 pTeam; //0x0070 
char _0x0074[4];
	BYTE pIsDead; //0x0078 
char _0x0079[319];
	__int32 pRank; //0x01B8 
char _0x01BC[80];
	__int32 pFTScore; //0x020C 
	BYTE pFTSpawn; //0x0210 
char _0x0211[3];
	__int32 pFTLongestLife; //0x0214 
	__int32 pFTKill; //0x0218 
char _0x021C[84];
	cClientInfo* PlayerNext; //0x0270 
};//Size=0x0274

class cPlayerMgr
{
public:
			char pad[24];
	cClientWeaponMgr* WeaponMgr; //0018
			char unknown0[48];
	float Pitch; //0048
	float Yaw; //004C
	float Roll;
			char unknown3[220];
	int* CameraObject; //012C

	__inline cWeaponInfo* GetCurrentWeapon()
	{
		if( WeaponMgr && WeaponMgr->CurrentWeapon )
			return WeaponMgr->CurrentWeapon;

		return NULL;
	}
};

class cLTModel
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual unsigned int GetBoneNode( int* Obj, char* nodeName, unsigned int &Node ); 
	virtual unsigned int GetNodeName( int* Obj, unsigned int Node, char* name, int maxlen ); 
	virtual unsigned int GetNodeTransform( int* Obj, unsigned int hNode, Transform* trans, char bWorldSpace );
	virtual unsigned int GetModelNextNode( int* Obj, unsigned int Node, unsigned int &Next );
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual unsigned int GetNumNodes( int* Obj, unsigned int &num ); 
};

class cGameClientShell
{
public:
			virtual void Function0();
			virtual void Function1();
			virtual void Function2();
			virtual void Function3();
			virtual void Function4();
			virtual void Function5();
			virtual void Function6();
			virtual void Function7();
			virtual void Function8();
			virtual void Function9();
			virtual void Function10();
			virtual void Function11();
			virtual void Function12();
			virtual void Function13();
			virtual void Function14();
			virtual void Function15();
			virtual void Function16();
			virtual void Function17();
			virtual void Function18();
			virtual void Function19();
			virtual void Function20();
			virtual void Function21();
			virtual void Function22();
			virtual void Function23();
			virtual void Function24();
			virtual void Function25();
			virtual void Function26();
			virtual void Function27();
			virtual void Function28();
			virtual void Function29();
			virtual void Function30();
			virtual void Function31();
			virtual void Function32();
			virtual void Function33();
			virtual void Function34();
			virtual void Function35();
			virtual void Function36();
			virtual void Function37();
			virtual void Function38();
			virtual void Function39();
			virtual void Function40();
			virtual void Function41();
			virtual void Function42();
			virtual void Function43();
			virtual void Function44();
			virtual void Function45();
	virtual DWORD GetClientInfoMgr();
	virtual DWORD GetInterfaceManager();
    virtual DWORD GetPlayerManager();
			virtual void Function49();
			virtual void Function50();
			virtual void Function51();
			virtual void Function52();
			virtual void Function53();
			virtual void Function54();
			virtual void Function55();
			virtual void Function56();
	virtual cSFXMgr* GetSFXMgr();
};


#endif