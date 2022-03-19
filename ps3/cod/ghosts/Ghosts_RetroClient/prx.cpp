#include "PS3.h"
#include "Structures.h"
#include "Vars.h"
#include "TOC.h"
#include "Huds.h"
#include "Funcs.h"
#include "Menu_Base.h"

void paintHook(int x, int xx)
{
	Menu_PaintAll_Stub(x, xx);
	if (*(char*)0x2357DF0 == 0x01) // check to see if we are in game or not
	{
		if (var.isOpen) 
			draw();

		var.tickTock += 1;
		if (var.tickTock > 30) // time inbetween keypresses
		{
			// opening keypress
			if (detect(R3)) 
				openClose();
			// make it open to the main menu
			else if (detect(Left) && var.isOpen && var.isInASubMenu)
			{
				// make sure to change this too if we change the amount of menu subtabs
				var.subMenu = Main;
				var.scroll = 0;
				var.maxScroll = 3;
				var.preSub = null;
				var.isInASubMenu = false;
			}
			// scroll up
			else if (detect(Up) && var.isOpen)
			{
				var.scroll--;
				if (var.scroll < 0) 
					var.scroll = var.maxScroll;
				var.tickTock = 0; // reset the button timer so it doesn't keep overlapping; do this after every registered key press.
			}
			// scroll down
			else if (detect(Down) && var.isOpen)
			{
				var.scroll++;
				if (var.scroll > var.maxScroll) 
					var.scroll = 0;
				var.tickTock = 0;
			}
			// toggle keypress
			else if (detect(Right) && var.isOpen)
			{
				execute();
				var.tickTock = 0;
			}
		}
	}
	else
	{
		// todo; make a pregame menu here!

	}
}

//void DoNotify(char *szFormat, int id = 0)
//{
//	char _notify_buffer[512];
//	fixSpaces(&szFormat);
//	snprintf(_notify_buffer, 512, "/notify.ps3mapi?msg=%s", szFormat);
//	send_wm_request(_notify_buffer);
//}

extern "C" int _entry(void)
{
	hookFunctionStart((int)0x36DBC4, (int)Menu_PaintAll_Stub, (int)paintHook);
	//if (DrawOkayMessageDialog("Imminent Client Loaded Successfully!"))
	//{
	//	DoNotify("Time to go fuck up Ghosts", 4);
	//}
	return SYS_PRX_RESIDENT;
}