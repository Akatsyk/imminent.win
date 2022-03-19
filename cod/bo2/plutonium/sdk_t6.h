#pragma once
#include "sdk_def.h"
#include "sdk_detour.h"

void EndFrame(void);

#pragma region typedef & colors

	vec4_t				colWhite = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4_t				colBlack = { 0.0f, 0.0f, 0.0f, 1.0f };
	vec4_t				colRed = { 0.6f, 0.0f, 0.0f, 1.0f };
	vec4_t				colGreen = { 0.0f, 0.6f, 0.0f, 1.0f };
	vec4_t				colBlue = { 0.0f, 0.0f, 0.6f, 1.0f };
	vec4_t				colYellow = { 0.6f, 0.6f, 0.0f, 1.0f };
	vec4_t				colCyan = { 0.0f, 1.0f, 1.0f, 1.0f };
	vec4_t				colOrange = { 1.0f, 0.6f, 0.0f, 1.0f };
	vec4_t				colPink = { 1.0f, 0.0f, 1.0f, 1.0f };
	vec4_t				colWhite_ = { 1.0f, 1.0f, 1.0f, 0.6f };
	vec4_t				colBlack_ = { 0.0f, 0.0f, 0.0f, 0.8f };
	vec4_t				colRed_ = { 0.6f, 0.0f, 0.0f, 0.8f };
	vec4_t				colGreen_ = { 0.0f, 0.6f, 0.0f, 0.6f };
	vec4_t				colBlue_ = { 0.0f, 0.0f, 0.6f, 0.6f };
	vec4_t				colYellow_ = { 0.6f, 0.6f, 0.0f, 0.8f };
	vec4_t				colCyan_ = { 0.0f, 1.0f, 1.0f, 0.8f };
	vec4_t				colOrange_ = { 1.0f, 0.6f, 0.0f, 0.8f };
	vec4_t				colPink_ = { 1.0f, 0.0f, 1.0f, 0.5f };

#pragma endregion

		/////////////////////////////////////////////////////////////
		////////////////// SDK FUNCTIONS TO USE /////////////////////
		/////////////////////////////////////////////////////////////

	class DVAR
	{
	public:
		static dvar_t * Dvar_FindVar(char * var)
		{
			return (dvar_t*)Dvar_FindVar_f(var);
		}

		static int Dvar_GetInt(dvar_t* var)
		{
			return var->current.integer;
		}

		static float Dvar_GetFloat(dvar_t* var)
		{
			return var->current.value;
		}

		static float Dvar_GetBool(dvar_t* var)
		{
			return var->current.enabled;
		}

		static const char* Dvar_GetString(dvar_t* var)
		{
			return var->current.string;
		}

		static float* Dvar_GetVector(dvar_t* var)
		{
			return var->current.vector;
		}

		static void Dvar_SetInt(dvar_t* var, int i)
		{
			var->current.integer = i;
		}
		static void Dvar_SetFloat(dvar_t* var, float i)
		{
			var->current.value = i;
		}
		static void Dvar_SetBool(dvar_t* var, bool i)
		{
			var->current.enabled = i;
		}
		static void Dvar_SetString(dvar_t* var, char * i)
		{
			var->current.string = i;
		}
	};

	class DRAWING
	{
	public:
		
		static void DrawShader(float x, float y, float w, float h, float * color, char * shader)
		{

			R_DrawStretchPic(x, y, 1.0f, w, h, 0, 0, 1, 1, color, R_RegisterShader(shader, 3, 1, -1));

		}

		static void DrawRect(float x, float y, float w, float h, float * color, int size)
		{

			DrawShader(x, y, w, size, color, "white");
			DrawShader(x, y, size, h, color, "white");

			DrawShader(x - size + w, y, size, h, color, "white");
			DrawShader(x, y - size + h, w, size, color, "white");

		}

		static void FillRect(float x, float y, float w, float h, float * color)
		{
			DrawShader(x, y, w, h, color, "white");
		}

		static void DrawString(const char* pText, float x, float y, float * color, int style)
		{

			style = 0;

			char bug[64];
			Font_s *pFont = RegisterFont("fonts/720/normalFont", 0);

			char buf[300] = "";
			va_list va_alist;

			va_start(va_alist, pText);
			vsnprintf(buf, sizeof(buf), pText, va_alist);
			va_end(va_alist);

			DrawUberText(buf, 0x7FFFFFFFu, pFont, x, y, 0.7f, 0.7f, 0.0f, color, style);
		}

		static void DrawLine(int x1, int y1, int x2, int y2, float* color, float size) {

			void* Shader = R_RegisterShader("white", 3, 1, -1);

			float x, y, angle, l1, l2, h1;
			h1 = y2 - y1;
			l1 = x2 - x1;
			l2 = sqrt(l1 * l1 + h1 * h1);
			x = x1 + ((l1 - l2) / 2);
			y = y1 + (h1 / 2);
			angle = (float)atan(h1 / l1) * (180 / 3.14159265358979323846);



			DrawRotatedPic(x, y, l2, size, 0, 0, 0, 0, angle, color, Shader);

		}

		static void DrawCorneredBox(float x, float y, float w, float h, float * color, float size)
		{

			pFillRect(x, y, w / 3.5, size, color);
			pFillRect(x, y, size, h / 4, color);

			pFillRect(x + w - w / 3.5, y, w / 3.5, size, color);
			pFillRect(x + w - size, y, size, h / 4, color);

			pFillRect(x, y + h - h / 4, size, h / 4, color);
			pFillRect(x, y + h - size, w / 3.5, size, color);

			pFillRect(x + w - size, y + h * 0.75, size, h / 4, color);
			pFillRect(x + w - w / 3.5, y + h - size, w / 3.5, size, color);

		}

		static void DrawStringWithBackground(char * txt, float x, float y, vec4_t StrColor, vec4_t BorderColor, vec4_t BackColor)
		{

			Font_s *Font_s = RegisterFont("fonts/smallDevFont", 0);
			float StringWidth = StrWidth(0, txt, 0x7FFFFFFu, RegisterFont("fonts/smallDevFont", 0)) * 0.7f;
			float StringHeight = 25 * 0.7f;

			pFillRect(x, y - StringHeight, StringWidth, StringHeight, BackColor);
			DrawRect(x, y - StringHeight, StringWidth, StringHeight, BorderColor, 1);
			DrawString(txt, x, y, StrColor, 0);


		}

	};

	class CG
	{
	public:

		static cg_t * Singleton()
		{
			return cg;
		}

		static clientinfo_t GetClient(int index)
		{
			return cg->client[index];
		}

		static float * GetViewanglePtr()
		{
			return Viewangles_Write;
		}

		static float * GetRecoilanglePtr()
		{
			return Recoilangles_Write;
		}
		static void SetViewangles(vec3_t vec)
		{
			Viewangles_Write[0] = vec[0];
			Viewangles_Write[1] = vec[1];
			Viewangles_Write[2] = vec[2];
		}

		static void SetRecoilAngles(vec3_t vec)
		{
			Recoilangles_Write[0] = vec[0];
			Recoilangles_Write[1] = vec[1];
			Recoilangles_Write[2] = vec[2];
		}

		static bool GetTagPos(entity_t* entity, unsigned int Tag, float * vOut)
		{
		
			PVOID DObj = Com_GetClientDObj(entity->clientNum, *(UINT*)(DWORD)entity + 0x4);

			if (!DObj)
			{
				return FALSE;
			}

			return CG_DObjGetWorldTagPos(entity, DObj, Tag, vOut);
		}

		static WORD R_RegisterTag(char* tag, int entityType)
		{
			return RegisterTag(tag, entityType, strlen(tag) + 1, 6);
		}

	};

	class HOOK
	{
	public:
		
		static void HookEndFrame(DWORD offset)
		{

			pEndFrame = (tEndFrame)DetourFunction((PBYTE)offset, (PBYTE)EndFrame);


		}
	};

	//Hook:

	void __declspec(naked) EndFrame(void)
	{
		__asm PUSHAD;

		//Put code under this
		float nullvec[3] = { 0,0,0 };
		CG::SetRecoilAngles(nullvec);

		__asm POPAD;
		__asm JMP[pEndFrame]
	}
