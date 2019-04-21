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
std::string path = "/";

inline bool fexist(const char* name) {
    std::ifstream f(name);
    return f.good();
   
    
     
      /*_-_-_-_-_-_-_-_-_-_-_-_-*/
       
        
          
 std::string themename(int themenum){
 	
	std::string strnum = std::to_string(themenum);
	std::string themepath = path +"theme/" + strnum;
	if (fexist( (themepath+ "/YSMenu.ini").c_str()) && fexist((themepath + "/YSmenu1.bmp").c_str()) &&fexist( (themepath +"/YSmenu2.bmp").c_str())){
		if (fexist((themepath+ "/name.txt").c_str())){
			 std::ifstream namefile(themepath + "/name.txt");

			std::string sLine;
			std::getline(namefile, sLine);
			std::string nameofthetheme = sLine;
			namefile.close();
			return nameofthetheme;
  		
			} else{
				return "Theme found, please add a name.txt file.";
				}
		} else {return "Theme not found";}
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
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
	vramSetBankH(VRAM_H_SUB_BG);
	consoleInit(NULL, 1, BgType_Text4bpp, BgSize_T_256x256, 15, 0, false, true);
		int selected = 0;
	while (true){
		std::string path = "./";
		std::string themesname = themename(selected);
		printf("theme %i - %s\n", selected, themesname.c_str());
		//Scan nds KEY
		scanKeys();
		int pressed = keysHeld();
		if (pressed & KEY_RIGHT){
			selected+=1;
			}
		if(pressed & KEY_LEFT){
			selected -=1;
			}
		if(pressed & KEY_A){
			if (themesname != "Theme not found"){
				stop();
				}
			}
		if (selected <0){
			selected =20;
			}
		if (selected > 20){
			selected =0;
			}
	}
	return 0;
	}
