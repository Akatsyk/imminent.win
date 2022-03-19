/*
[ BASE INFORMATION ]

- draw() is where your huds are displayed
- openClose() controls what happens when Open/Close the menu
- execute() is where you put your functions (Uav, Laser, Etc)

- Color Editing made easy for the noobies goto (Vars.h)
- Add a Sub Menu? (Go to Vars.h add your submenu name into the submenu enum)

- Adding Options (addBool, addChar, addOption) Should be basic to understand.

- Make something cool. bye :p

[ By oStankyModz ]
*/

// draws our menu
void draw()
{
	drawShader(158, 278, 194, 42 + (26 * var.maxScroll), outerBoarder);
	drawShader(161, 281, 188, 39 + (26 * var.maxScroll), mainBoarder);
	drawShader(167, 287, 176, 30 + (26 * var.maxScroll), innerBoarder);
	drawShader(170, 290, 150, 25, titleBackground);
	drawText("Imminent.win", 185, 317, FONT_BOLD, 0., title);
	for (int x = 0; x < var.maxScroll + 1; x++) 
		drawNumberedShader(x, 170, 317 + (26 * x), 150, 24, optionsBackground);

	switch (var.subMenu)
	{
	case Main:
		addOption("ESP", 0, 175);
		addOption("Visuals", 1, 175);
		addOption("Misc", 2, 175);
		addOption("Settings", 3, 175);
		break;
	case Sub1:
		addBool("Force Advanced UAV", 0, var.uav, 175);
		addBool("Red Boxes", 1, var.redBoxes, 175);
		addBool("Chrome Player", 2, var.chromePlayer, 175);
		addBool("Glow", 3, var.glow, 175);
		break;
	case Sub2:
		addChar("Fov", 0, var.fov, 175);
		addBool("Crosshair", 1, var.crossHair, 175);
		addBool("Laser", 2, var.laser, 175);
		addOption("Option 4", 3, 175);
		break;
	case Sub3:
		addBool("No Recoil", 0, var.noRecoil, 175);
		addBool("Steady Aim", 1, var.steadyAim, 175);
		addOption("Option 3", 2, 175);
		addOption("Option 4", 3, 175);
		break;
	case Sub4:
		addOption("Option 1", 0, 175);
		addOption("Option 2", 1, 175);
		addOption("Option 3", 2, 175);
		addOption("Option 4", 3, 175);
		break;
	}
}

void openClose()
{
	if (!var.isOpen)
	{
		// make it open to the main menu
		var.subMenu = Main; 
		var.scroll = 0; 
		var.maxScroll = 3; 
		var.preSub = null; 
		var.isInASubMenu = false; // this might not be needed.
		var.isOpen = true;
	}

	// do our scroller rememberance
	else
	{
		switch (var.subMenu)
		{
		case Sub1: var.subMenu = var.preSub; var.scroll = 0; var.maxScroll = 3; break;
		case Sub2: var.subMenu = var.preSub; var.scroll = 1; var.maxScroll = 3; break;
		case Sub3: var.subMenu = var.preSub; var.scroll = 2; var.maxScroll = 3; break;
		case Sub4: var.subMenu = var.preSub; var.scroll = 3; var.maxScroll = 3; break;
		// removing this may cause issues but who knows
		// i did it mainly because i want to be able to go back into the subtabs 
		// without having to close the menu as it not possible with the current api;
		// currently trying to change that fact now.
		default: var.isOpen = false; break; // if already on main menu it closes menu
		}
	}
	var.tickTock = 0;
}

void execute()
{
	switch (var.subMenu)
	{
	case Main:
		var.isInASubMenu = false;
		switch (var.scroll)
		{
		case 0: var.subMenu = Sub1; var.scroll = 0; var.maxScroll = 3; var.preSub = Main; break;
		case 1: var.subMenu = Sub2; var.scroll = 0; var.maxScroll = 3; var.preSub = Main; var.fov = "65"; break;
		case 2: var.subMenu = Sub3; var.scroll = 0; var.maxScroll = 3; var.preSub = Main; break;
		case 3: var.subMenu = Sub4; var.scroll = 0; var.maxScroll = 3; var.preSub = Main; break;
		}
		break;
	case Sub1:
		var.isInASubMenu = true;
		switch (var.scroll)
		{
		case 0:
			if (!var.uav)
			{
				unsigned char byte[1] = { 0x02 };
				write_process(0x140A3A, byte, sizeof(byte));
				var.uav = true;
			}
			else
			{
				unsigned char byte[1] = { 0x01 };
				write_process(0x140A3A, byte, sizeof(byte));
				var.uav = false;
			}
			break;
		case 1: 
			if (!var.redBoxes)
			{
				unsigned char byte[1] = { 0x40 };
				write_process(0x149134, byte, sizeof(byte));
				var.redBoxes = true;
			}
			else
			{
				unsigned char byte[4] = { 0x41, 0x82, 0X00, 0X0C };
				write_process(0x149134, byte, sizeof(byte));
				var.redBoxes = false;
			}
			break;
		case 2: 			
			if (!var.chromePlayer)
			{
				unsigned char byte[1] = { 0x02 };
				write_process(0x478D5B, byte, sizeof(byte));
				var.chromePlayer = true;
			}
			else
			{
				unsigned char byte[1] = { 0x01 };
				write_process(0x478D5B, byte, sizeof(byte));
				var.chromePlayer = false;
			} 
			break;
		case 3: 
			if (!var.glow)
			{
				unsigned char byte[1] = { 0x02 };
				write_process(0x16AB63, byte, sizeof(byte));
				var.glow = true;
			}
			else
			{
				unsigned char byte[1] = { 0x01 };
				write_process(0x16AB63, byte, sizeof(byte));
				var.glow = false;
			}
			break;
		}
		break;
	case Sub2:
		var.isInASubMenu = true;
		switch (var.scroll)
		{
		case 0:
			if (var.fov == "65")
			{
				var.fov = "90";
				cBuf_Addtext(0, "cg_fov 90");
			}
			else
			{
				var.fov = "65";
				cBuf_Addtext(0, "cg_fov 65");
			}
			break;
		case 1: 
			if (!var.crossHair)
			{
				unsigned char byte[1] = { 0x02 };
				write_process(0x1215CC, byte, sizeof(byte));
				var.crossHair = true;
			}
			else
			{
				unsigned char byte[1] = { 0x01 };
				write_process(0x1215CC, byte, sizeof(byte));
				var.crossHair = false;
			}
			break;
		case 2:
			if (!var.laser)
			{
				unsigned char byte[1] = { 0x02 };
				write_process(0x52DDE7, byte, sizeof(byte));
				var.laser = true;
			}
			else
			{
				unsigned char byte[1] = { 0x01 };
				write_process(0x52DDE7, byte, sizeof(byte));
				var.laser = false;
			}
			break;
		case 3: break; // todo; add a function here!
		}
		break;
	case Sub3:
		var.isInASubMenu = true;
		switch (var.scroll)
		{
		case 0: 
			if (!var.noRecoil)
			{
				unsigned char byte[4] = { 0x60, 0x00, 0x00, 0x00 };
				write_process(0x6C65C0, byte, sizeof(byte));
				var.noRecoil = true;
			}
			else
			{
				unsigned char byte[4] = { 0x4B, 0xB9, 0x7D, 0xCD };
				write_process(0x6C65C0, byte, sizeof(byte));
				var.noRecoil = false;
			}
			break;
		case 1:
			if (!var.steadyAim)
			{
				unsigned char byte[4] = { 0x2C, 0x03, 0x00, 0x00 };
				write_process(0x1215CC, byte, sizeof(byte));
				var.steadyAim = true;
			}
			else
			{
				unsigned char byte[4] = { 0x2C, 0x03, 0x00, 0x02 };
				write_process(0x1215CC, byte, sizeof(byte));
				var.steadyAim = false;
			}
			break;
		case 2: break; // same goes as above for the rest of these
		case 3: break;
		}
		break;
	case Sub4:
		var.isInASubMenu = true;
		switch (var.scroll)
		{
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		}
		break;
	}
}