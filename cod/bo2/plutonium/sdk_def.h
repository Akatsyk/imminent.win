#pragma once
#include <Windows.h>

typedef float vec2_t[2];
typedef float vec3_t[3];
typedef float vec4_t[4];

//DVAR Stuff

enum dvarType_t
{
	DVAR_TYPE_INVALID = 0x0,
	DVAR_TYPE_BOOL = 0x1,
	DVAR_TYPE_FLOAT = 0x2,
	DVAR_TYPE_FLOAT_2 = 0x3,
	DVAR_TYPE_FLOAT_3 = 0x4,
	DVAR_TYPE_FLOAT_4 = 0x5,
	DVAR_TYPE_INT = 0x6,
	DVAR_TYPE_ENUM = 0x7,
	DVAR_TYPE_STRING = 0x8,
	DVAR_TYPE_COLOR = 0x9,
	DVAR_TYPE_INT64 = 0xA,
	DVAR_TYPE_LINEAR_COLOR_RGB = 0xB,
	DVAR_TYPE_COLOR_XYZ = 0xC,
	DVAR_TYPE_COUNT = 0xD,
};
union DvarValue
{
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	__int64 integer64;
	unsigned __int64 unsignedInt64;
	float value;
	vec4_t vector;
	const char *string;
	char color[4];
};
struct $BFBB53559BEAC4289F32B924847E59CB
{
	int stringCount;
	const char **strings;
};
struct $9CA192F9DB66A3CB7E01DE78A0DEA53D
{
	int min;
	int max;
};
struct $5FF817DA2B223410B016B4653DEC4160
{
	__int64 min;
	__int64 max;
};
struct $251C2428A496074035CACA7AAF3D55BD
{
	float min;
	float max;
};
union DvarLimits {
	$BFBB53559BEAC4289F32B924847E59CB enumeration;
	$9CA192F9DB66A3CB7E01DE78A0DEA53D integer;
	$5FF817DA2B223410B016B4653DEC4160 integer64;
	$251C2428A496074035CACA7AAF3D55BD value;
	$251C2428A496074035CACA7AAF3D55BD vector;
};
struct __declspec(align(8)) dvar_t
{
	const char *name;
	const char *description;
	int hash;
	unsigned int flags;
	dvarType_t type;
	bool modified;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarLimits domain;
	dvar_t *hashNext;
};

//DRAWING Stuff

struct Font_s
{

	char uk0[4];
	int Height;

};

//CG Stuff
class entity_t
{
public:
	char _0x0000[44];
	vec3_t vOrigin; //0x002C 
	char _0x0038[296];
	BYTE State; //0x0160  4 = crouch | 8 = prone | 40 = fire
	char _0x0161[1];
	BYTE IsZoomed; //0x0162 
	char _0x0163[17];
	vec3_t vOldOrigin; //0x0174 
	char _0x0180[92];
	__int32 clientNum; //0x01DC 
	char _0x01E0[20];
	vec3_t vNewOrigin; //0x01F4 
	char _0x0200[180];
	BYTE eType; //0x02B4 
	char _0x02B5[11];
	__int32 weaponID; //0x02C0 
	char _0x02C4[180];
	BYTE IsAlive; //0x0378 
	char _0x0379[7];
};

class cgs_t
{
public:
	char _0x0000[8];
	__int32 Width; //0x0008 
	__int32 Height; //0x000C 
	char _0x0010[24];
	__int32 ServerTime; //0x0028 
	char _0x002C[4];
	char GameType[8]; //0x0030 
	char _0x0038[24];
	char Name[32]; //0x0050 
	char _0x0070[224];
	__int32 MaxClients; //0x0150 
	char _0x0154[4];
	char MapNamePath[20]; //0x0158 
	char _0x016C[44];
	char MapName[8]; //0x0198 
	char _0x01A0[32];
};

class refdef_t
{
public:
	__int32 x; //0x0000 
	__int32 y; //0x0004 
	__int32 iWidth; //0x0008 
	__int32 iHeight; //0x000C 
	char _0x0010[16];
	float fovx; //0x0020 
	float fovy; //0x0024 
	float fovz; //0x0028 
	char _0x002C[4];
	float TotalFov; //0x0030 
	vec3_t vOrigin; //0x0034 
	char _0x0040[4];
	vec3_t viewAxis[3]; //0x0044 
	char _0x0068[4];
	__int32 iTime; //0x006C 
	char _0x0070[144];

};

class network_s
{
public:

	char unknown0[100];
	char unknown1[4];
	char unknown2[4];
	int Ping;
	int NewTime;
	int Time;
	int OldTime;
	char unknown3[32];

};

class clientinfo_t
{
public:
	char _0x0000[4];
	__int32 IsValid; //0x0004 
	__int32 clientNum; //0x0008 
	char szName[32]; //0x000C 
	__int32 Team; //0x002C 
	__int32 Team2; //0x0030 
	char _0x0034[88];
	__int32 IsDead; //0x008C 
	char _0x0090[4];
	__int32 Score; //0x0094 
	__int32 Kills; //0x0098 
	char _0x009C[4];
	__int32 Deaths; //0x00A0 
	char _0x00A4[20];
	__int32 Assists; //0x00B8 
	char _0x00BC[1032];
	float ViewAngleY; //0x04C4 
	float ViewAngleX; //0x04C8 
	char _0x04CC[192];
	__int32 IsFiring; //0x058C 
	__int32 IsZoomed; //0x0590 
	char _0x0594[48];
	__int32 weaponID; //0x05C4 
	char _0x05C8[576];
};

class cg_t
{
public:
	__int32 clientnum; //0x0000 
	char _0x0004[20];
	__int32 IsIngame; //0x0018 
	network_s Network;
	//char _0x001C[156];
	vec3_t vOrigin; //0x00B8 
	vec3_t Velocity; //0x00C4 
	char _0x00D0[376];
	BYTE WeaponID; //0x0248 
	char _0x0249[39];
	float ZoomState; //0x0270 
	char _0x0274[84];
	__int32 Health; //0x02C8 
	char _0x02CC[316868];
	refdef_t RefDef; //0x4D890
	char _0x4D8D8[115048];
	clientinfo_t client[18]; //0x69A60
	char _unk[206160];
	entity_t entity[2048];
};//Size=0x02CC

cg_t * cg = (cg_t*)0x2E448C80; //Works every version
float * Viewangles_Write = (float*)0x2CA8C5BC; //Works every version
float * Recoilangles_Write = (float*)0x2CA8C530; //Works every version