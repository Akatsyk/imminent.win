#include "framework.h"

void Offsets::InitializeOffsets() {
	typedef dvar_t* (*Dvar_FindVar_d)(char*);
	Dvar_FindVar_d Dvar_FindVar_f = (Dvar_FindVar_d)Memory::Scan("\x8B\x44\x24\x04\x85\xC0\x74\x0A\x80\x38\x00\x74\x05\xE9\x00\x00\x00\x00\x33\xC0", "xxxxxxxxxxxxxx????xx");

	typedef int(__cdecl* tStrWidth)(int a1, char* szString, int iMaxLen, Font_s* pFont);
	tStrWidth StrWidth = (tStrWidth)Memory::Scan("\x83\xEC\x0C\x55\x57\x33\xED\x33\xFF\x39\x6C\x24\x20", "xxxxxxxxxxxxx");

	typedef Font_s* (*RegisterFont_)(char* FontName, int Unknown1);
	RegisterFont_ RegisterFont = (RegisterFont_)Memory::Scan("\x8B\x44\x24\x04\x6A\xFF\x6A\x01\x50\x6A\x14\xE8\x00\x00\x00\x00\x83\xC4\x10", "xxxxxxxxxxxx????xxx");

	typedef int(*DrawUberText_)(char* Text, int uk1, Font_s* Font, float x, float y, float width, float height, float rotation, float* color, int style);
	DrawUberText_ DrawUberText = (DrawUberText_)Memory::Scan("\x8B\x44\x24\x04\x80\x38\x00\x55\x56\x57\x0F\x84\x00\x00\x00\x00\x8D\x50\x01\x8A\x08\x40\x84\xC9\x75\xF9\x2B\xC2\x8B\xE8\x8D\x7D\x68\x83\xE7\xFC", "xxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxx");

	typedef void(__cdecl* R_DrawStretchPic_t)(float x, float y, float arg_1f, float w, float h, float is0, float is0_1, float is1, float is1_1, float* color, void* shader);
	R_DrawStretchPic_t R_DrawStretchPic = (R_DrawStretchPic_t)Memory::Scan("\x8B\x44\x24\x2C\x8B\x4C\x24\x28\xF3\x0F\x10\x44\x24\x24\x50\x51\x83\xEC\x24\xF3\x0F\x11\x44\x24\x20\xF3\x0F\x10\x44\x24\x4C\xF3\x0F\x11\x44\x24\x1C\xF3\x0F\x10\x44\x24\x48\xF3\x0F\x11\x44\x24\x18\xF3\x0F\x10\x44\x24\x44\xF3\x0F\x11\x44\x24\x14\xF3\x0F\x10\x44\x24\x40\xF3\x0F\x11\x44\x24\x10\xF3\x0F\x10\x44\x24\x3C\xF3\x0F\x11\x44\x24\x0C\xF3\x0F\x10\x44\x24\x38", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

	typedef void* (__cdecl* R_RegisterShader_t)(char* name, int, int, int);
	R_RegisterShader_t R_RegisterShader = (R_RegisterShader_t)Memory::Scan("\x8B\x44\x24\x04\x80\x38\x00\x75\x06\xA1\x00\x00\x00\x00\xC3\x89\x44\x24\x04\xE9\x00\x00\x00\x00", "xxxxxxxxxx????xxxxxx????");

	typedef int(__cdecl* tDrawRotatedPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float angle, float* color, void* material);
	tDrawRotatedPic DrawRotatedPic = (tDrawRotatedPic)Memory::Scan("\x56\x57\xBF\x00\x00\x00\x00\x8D\x57\xD9\xE8\x00\x00\x00\x00\x8B\xF0\x85\xF6\x0F\x84\x00\x00\x00\x00\x8B\x44\x24\x34\x85\xC0\x75\x05", "xxx????xxxx????xxxxxx????xxxxxxxx");

	typedef PVOID(__cdecl* Com_GetClientDObj_t)(UINT ClientNum, UINT a2);
	Com_GetClientDObj_t Com_GetClientDObj = (Com_GetClientDObj_t)Memory::Scan("\x8B\x4C\x24\x08\x8B\x44\x24\x04\x69\xC9\x00\x00\x00\x00\x03\xC1\x0F\xB7\x04\x45\xC0\xD1\x62\x02\x66\x85\xC0\x74\x0A\x98\x6B\xC0\x7C", "xxxxxxxxxx????xxxxxxxxxxxxxxxxxxx");

	typedef BOOL(__cdecl* CG_DObjGetWorldTagPos_t)(entity_t* pEnt, PVOID DObj, UINT Tag, PFLOAT vOut);
	CG_DObjGetWorldTagPos_t CG_DObjGetWorldTagPos = (CG_DObjGetWorldTagPos_t)Memory::Scan("\x51\x8B\x4C\x24\x10\x56\x57\x8B\x7C\x24\x14\x6A\xFF\x8D\x44\x24\x0F", "xxxxxxxxxxxxxxxxx");

	typedef WORD(__cdecl* tRegisterTag)(char* name, int etype, int strl, int uk6);
	tRegisterTag RegisterTag = (tRegisterTag)Memory::ScanPattern("\x83\xEC\x0C\x8B\x54\x24\x10\x53\x8B\x5C\x24\x1C\x55\x56\x57\x8B\xC3\xE8\x00\x00\x00\x00\x8B\xE8\x6A\x1B\x89\x6C\x24\x18\xE8\x00\x00\x00\x00\x8B\x3D\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxx????xxxxxxxxx????xx????");

	typedef void(*tEndFrame)(void);
	tEndFrame pEndFrame;

	DWORD HookingOffset = Memory::Scan("\x53\x8B\x5C\x24\x08\x8B\x83\x00\x00\x00\x00\x55\x8B\x6C\x24\x10\x89\x45\x00\xD9\x83\x00\x00\x00\x00\xD9\x5D\x04\xF3\x0F\x7E\x83\x00\x00\x00\x00\x66\x0F\xD6\x45", "xxxxxxx????xxxxxxxxxx????xxxxxxx????xxxx");
}