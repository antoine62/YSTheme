/*-----------------------------------------------------------------
 Copyright (C) 2005 - 2013
	Michael "Chishm" Chisholm
	Dave "WinterMute" Murphy
	Claudio "sverx"
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
------------------------------------------------------------------*/
//Include part!
#include <nds.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <fat.h>
#include <fstream>
//---------------------------------------------------------------------------------   File management part
    
     
      /*_-_-_-_-_-_-_-_-_-_-_-_-*/
       
        
          
 std::string themename(int themenum){
	std::string themepath = "/theme/" + std::to_string(themenum);
	printf("\x1b[0;1H"+ (access((themepath + "/YSMenu.ini").c_str(), F_OK) == 0));
	
	if ((access((themepath + "/YSMenu.ini").c_str(), F_OK) == 0)) {
		
		
		
		if ((access((themepath + "/name.txt").c_str(), F_OK) == 0)){
			 std::ifstream namefile(themepath + "/name.txt");

			std::string sLine;
			std::getline(namefile, sLine);
			std::string nameofthetheme = sLine;
			namefile.close();
			return sLine;
  		
			} else{
				return "Theme found, please add a name.txt file.";
				}
		} else {
			return "Theme not found";
			}
	}
//---------------------------------------------------------------------------------NDS related
void stop (void) {
//---------------------------------------------------------------------------------
	while (1) {
		swiWaitForVBlank();
	}
}

//---------------------------------------------------------------------------------NDS Code
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------



		if (!fatInitDefault()) {
				iprintf ("fatInitDefault failed!\n");
				stop();
			}
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
	vramSetBankH(VRAM_H_SUB_BG);
	consoleInit(NULL, 1, BgType_Text4bpp, BgSize_T_256x256, 15, 0, false, true);
		int selected = 0;
		std::string path = "./";
		std::string themesname = themename(selected);
		iprintf("\x1b[10;1HA - Install theme\nDpad left / Dpad right - select theme");
	while (true){
		themesname = themename(selected);
		//Scan nds KEY
		scanKeys();
		int pressed = keysDown();
		if (pressed & KEY_RIGHT){
			selected+=1;

			}
		if(pressed & KEY_LEFT){
			selected -=1;
			}
		if(pressed & KEY_A){
			if (themesname != "Theme not found"){
				
				
				
				std::string themepath = "/theme/" + std::to_string(selected);
				std::ifstream source((themepath + "/YSMenu.ini").c_str(), std::ios::binary);
				std::ofstream dest("/TTmenu/YSMenu.ini", std::ios::binary);
    			dest << source.rdbuf();
    			source.close();
    			dest.close();
    			
				
				
				std::ifstream source1((themepath + "/YSmenu1.bmp").c_str(), std::ios::binary);
				std::ofstream dest1("/TTmenu/YSmenu1.bmp", std::ios::binary);
    			dest1 << source1.rdbuf();
    			source1.close();
    			dest1.close();
    			
				
				
				std::ifstream source2((themepath + "/YSmenu2.bmp").c_str(), std::ios::binary);
				std::ofstream dest2("/TTmenu/YSMenu2.bmp", std::ios::binary);
    			dest2 << source2.rdbuf();
    			source2.close();
    			dest2.close();
				printf("Done! Please, restart your NDS.");
				stop();
				}
			}
		if (selected <0){
			selected =20;
			}
		if (selected > 20){
			selected =0;
			}
		iprintf("\x1b[1;1Htheme %i - %s \n", selected, themesname.c_str());
	}
	return 0;
	}
