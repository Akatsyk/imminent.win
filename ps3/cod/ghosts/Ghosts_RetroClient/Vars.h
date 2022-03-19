struct _nvar{
	int scroll, preScroll, maxScroll, subMenu, preSub, lrScroll, tickTock;
	bool isOpen, isInASubMenu;
	float* selectedTheme;

	// esp
	bool uav;
	bool redBoxes;
	bool chromePlayer;
	bool glow;

	// visuals
	char* fov;
	bool crossHair;
	bool laser;

	// misc
	bool noRecoil;
	bool steadyAim;

	// settings
	int menuX;
	int menuY;
	// todo; changable menu keybinds
}var;

enum subMenus{
	null,
	Main,
	Sub1,
	Sub2,
	Sub3,
	Sub4,
};

// preset colors because i don't know how the fuck float coloring works lmao
float* enemyEspBoxColor;
float Red[4] = { 1, 0, 0, 1 };
float LightRed[4] = { 1, 0, 0, 0.6f };
float Green[4] = { 0, 1, 0, 1 };
float LightGreen[4] = { 0, 1, 0, 0.2f };
float Blue[4] = { 0, 0, 1, 0.4 };
float LightBlue[4] = { 0, 0, 1, 0.2f };
float Yellow[4] = { 1, 1, 0, 1 };
float LightYellow[4] = { 1, 1, 0, 0.2f };
float Purple[4] = { 0.4, 0, 0.7, 1 };
float LightPurple[4] = { 0.4, 0, 0.7, 0.2f };
float Pink[4] = { 0.9, 0, 0.9, 1 };
float LightPink[4] = { 0.9, 0, 0.9, 0.2f };
float Orange[4] = { 1, 0.4, 0, 1 };
float LightOrange[4] = { 1, 0.4, 0, 0.2f };
float Cyan[4] = { 0, 1, 0.9, 1 };
float White[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float Black[4] = { 0, 0, 0, 1.0f };
float LightBlack[4] = { 0, 0, 0, 0.2f };
float Mint[4] = { 0.04, 0.82, 0.43, 1 };
float Grey[4] = { 0.32, 0.33, 0.34, 1 };
float mainBlue[4] = { 0, 0.67f, 0.54f, 0.7f };
float mainBlueESP[4] = { 0, 0.67f, 0.54f, 0.2f };
float WhiteESP[4] = { 1.0f, 1.0f, 1.0f, 0.2f };
float mainBlueAlpha[4] = { 0, 0.67f, 0.54f, 1 };

// menu colors
float* titleBackground = LightBlack;
float* title = White;
float* optionsBackground = LightBlack;
float* scrollColor = LightRed;
float* outerBoarder = Black;
float* mainBoarder = Red;
float* innerBoarder = Black;