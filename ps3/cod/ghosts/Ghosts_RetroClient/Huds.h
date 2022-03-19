#define FONT_SMALL_DEV    "fonts/smallDevFont"
#define FONT_BIG_DEV    "fonts/bigDevFont"
#define FONT_CONSOLE    "fonts/consoleFont"
#define FONT_BIG        "fonts/bigFont"
#define FONT_SMALL        "fonts/smallFont"
#define FONT_BOLD        "fonts/boldFont"
#define FONT_NORMAL        "fonts/normalFont"
#define FONT_EXTRA_BIG    "fonts/extraBigFont"
#define FONT_OBJECTIVE    "fonts/objectiveFont" 

int R_RegisterFont_s[2] = { Adr::R_RegisterFont, TOC };
int Material_RegisterHandle[2] = { Adr::Material_RegisterHandle, TOC };
int R_AddCmdDrawText_s[2] = { Adr::R_AddCmdDrawText, TOC };
int R_AddCmdDrawStretchPic_s[2] = { Adr::R_AddCmdDrawStretchPic, TOC };

void*(*R_RegisterFont)(const char * font, int imageTrac) = (void*(*)(const char *, int))&R_RegisterFont_s;
void*(*R_RegisterMaterial)(const char* font, int imageTrac) = (void*(*)(const char*, int))&Material_RegisterHandle;
void(*R_AddCmdDrawStretchPic)(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float *color, void *material) = (void(*)(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float *color, void *material))&R_AddCmdDrawStretchPic_s;
void(*R_AddCmdDrawText)(const char *text, int maxChars, void *font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style) = (void(*)(const char *, int, void *, float, float, float, float, float, const float *color, int))&R_AddCmdDrawText_s;

void drawShader(float x, float y, float width, float height, float* color)
{
	R_AddCmdDrawStretchPic(x, y, width, height, 1, 1, 1, 1, color, R_RegisterMaterial("white", 0));
}

void drawText(const char *xtext, float x, float y, const char *xfont, float xfontSize, const float * color)
{
	R_AddCmdDrawText(xtext, 0x7FFFFFFF, R_RegisterFont(xfont, 0), x, y, xfontSize, xfontSize, 0, color, 0);
}

void drawNumberedShader(int shaderID, float x, float y, float width, float height, float* color)
{
	if (var.scroll == shaderID) // current scroll
		R_AddCmdDrawStretchPic(x, y, width, height, 1, 1, 1, 1, scrollColor, R_RegisterMaterial("white", 0));
	else 
		R_AddCmdDrawStretchPic(x, y, width, height, 1, 1, 1, 1, color, R_RegisterMaterial("white", 0));
}

void drawNumberedText(int textID, const char *xtext, float xx, float xy, const char *xfont, float xfontSize, float* color)
{
	if (var.lrScroll == textID)
		R_AddCmdDrawText(xtext, 0x7FFFFFFF, R_RegisterFont(xfont, 0), xx, xy, xfontSize, xfontSize, 0, Black, 0);
	else 
		R_AddCmdDrawText(xtext, 0x7FFFFFFF, R_RegisterFont(xfont, 0), xx, xy, xfontSize, xfontSize, 0, color, 0);
}

void addOption(char* text, int textIndex, float x)
{
	if (var.scroll == textIndex)
		drawText(text, x, 335 + (26 * textIndex), FONT_SMALL_DEV, 1, White);
	else
		drawText(text, x, 335 + (26 * textIndex), FONT_SMALL_DEV, 0.9, White);
}

void addBool(char* text, int textIndex, bool optionBool, float x)
{
	if (var.scroll == textIndex) // current scroll
	{
		drawText(text, x, 335 + (26 * textIndex), FONT_SMALL_DEV, 1, White);

		if (!optionBool) 
			drawText("OFF", x + 115, 335 + (26 * textIndex), FONT_SMALL_DEV, 1, Red);
		else 
			drawText("ON", x + 115, 335 + (26 * textIndex), FONT_SMALL_DEV, 1, Green);
	}
	else
	{
		drawText(text, x, 335 + (26 * textIndex), FONT_SMALL_DEV, 0.9, White);

		if (!optionBool) 
			drawText("OFF", x + 115, 335 + (26 * textIndex), FONT_SMALL_DEV, 0.9, Red);
		else 
			drawText("ON", x + 115, 335 + (26 * textIndex), FONT_SMALL_DEV, 0.9, Green);
	}
}

void addChar(char* text, int textIndex, char* optionChar, float x){
	if (var.scroll == textIndex) // current scroll
	{
		drawText(text, x, 335 + (26 * textIndex), FONT_SMALL_DEV, 1, White);
		drawText(optionChar, x + 115, 335 + (26 * textIndex), FONT_SMALL_DEV, 1, White);
	}
	else
	{
		drawText(text, x, 335 + (26 * textIndex), FONT_SMALL_DEV, 0.9, White);
		drawText(optionChar, x + 115, 335 + (26 * textIndex), FONT_SMALL_DEV, 0.9, White);
	}
}