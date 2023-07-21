#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream> 
#include <math.h>
#include <algorithm>
#include <cstring>
#define Maximum(a, b) ((a > b) ? a : b)
#define Minimum(a, b) ((a < b) ? a : b)

std::string Vocabulary[800000];
int count=0;

bool Fullscreen=true;
SDL_DisplayMode DMode;
SDL_Joystick* Pad1[10];
SDL_GameController *controller[10];
SDL_Haptic* ControllerHaptic[10];
SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL; 
SDL_Surface* CurrentSurface = NULL;
SDL_Surface* ScreenSurface = NULL; 
SDL_Rect Reader;
SDL_Rect Writer;
SDL_Event event;
SDL_Texture* Images[50];
SDL_Texture* Wood;
SDL_Texture* Glyphs;
bool AntiA=true;
SDL_Texture* GhostGlyphs;
SDL_Texture* Front;
SDL_Texture* Finger;
SDL_Texture* MenuBG;
Mix_Chunk *Sounds[100];
bool Keyboard=true;
bool ControllerMode=false;
bool ForceJoystick=false;
int Axis[10];
int AxisSelected[10];
bool running=true;
int texturesUsed=0;
std::string speicher;
int LastClick=0;
int TapTime=20;
std::string alphaDef="QJZXVKWWYYFFBBGGGHHHMMMPPPDDDUUUUCCCCCLLLLLSSSSSSNNNNNNNTTTTTTTOOOOOOOIIIIIIIIRRRRRRRRAAAAAAAAAEEEEEEEEEEE";
std::string alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string PowerWord="KILL";
const int TileSize=108;
const int GridW=9;
const int GridH=9;
int minLength=4;
int MageState=0;
int LastAction=0;
int ActionsWOMerit=0;
bool OutOfOrder=false;
bool LockMouse=false;
SDL_Texture *PWordTex;
int Score=0;
int LastScore=0;
float ScoreShower=0;
int TauntOrShock=0;
int Multiplier=0;
int Bonus=0;
float BGX=0;
float BGY=0;
float BGAngle=0;
int BGFlimmer=-75;
bool Awed=false;
int CBG=9;
int BlinkingScore=0;
float AlphaBG=0;
int StartTime=0;
int Seconds=0;
int Minutes=0;
bool Flimmering=true;
int TimeLeft=90;
int Pissed=0;
std::string Pissword="";
int TimeBonus=0;
bool TurnMode=true;
int TurnsLeft=100;
int TurnsModeLimit=100;
int TimeModeLimit=150;
int mouseX=0;
int mouseY=0;
std::string LastWords[11];
int Clicked=0;
bool UseHand=true;
int MainMenuStart=0;
int MainMenuEnd=0;
int OptionsMenuStart=0;
int OptionsMenuEnd=0;
int HighScoreMenuStart=0;
int HighScoreMenuEnd=0;
int HighScoreMenuMode=0;
int HighScoreMenuBook=0;
int HowToPlayMenuStart=0;
int HowToPlayMenuEnd=0;
bool MenuOpen=false;
int ButtonsActive=0;
float MenuBGX=0;
float MenuBGY=0;
float MenuBGAngle=0;
int MusicVolume=130;
int SoundVolume=130;
int WordMode=1;
bool OptionsHelp=false;
int NewGame();
bool EndGame=false;
bool ShowEndScreen=false;
float ToWin=500;
int MadeHighScore=-1;
int EndScreenStart=0;
int EndScreenEnd=0;
int EnterHighScoreStart=0;
int EnterHighScoreEnd=0;
int WinFlasher=500;
int Intro=0;
SDL_Texture *IntroText;
Mix_Music *Music[30]; 
bool EndTaunt=true;

int HSLimitEnter=0;

int MusicCounter=0;
int LoadMusic()
{
	
	
	std::ifstream file;
	std::string str;
	file.open("Music.txt");
	while (std::getline(file, str))
		{
		//std::cout << "Line Loaded" << std::endl;
			char* writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0';
			MusicCounter++;
			Music[MusicCounter]=Mix_LoadMUS(writable);
		delete[] writable;
			
		
		}
		file.close();
		
	return MusicCounter;
}

int MusicMan()
{
	 if(Mix_PlayingMusic()==0)
     {
		 
			 Mix_FadeInMusic(Music[3+(rand()%(MusicCounter-2))], 0, 2000); 
		 
		 
	 }
	return 0;
}

int LoadSounds()
{
	int newCounter=0;
	
	std::ifstream file;
	std::string str;
	file.open("Sounds.txt");
	while (std::getline(file, str))
		{
		//std::cout << "Line Loaded" << std::endl;
			char* writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0';
			newCounter++;
			Sounds[newCounter]=Mix_LoadWAV(writable);
		delete[] writable;
			//std::cout << Stages[newCounter] <<"\n";
		
		}
		file.close();
		
		return 0;
		}

int loadSettings(char* mainfile)
{
			std::ifstream file;
	
			std::string str;
	
			file.open(mainfile);
			int HilfsInteger=0; 
			int HilfsInteger2=0; 
			while (std::getline(file, str))
			{
			char * writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0';
			if(speicher=="Fullscreen"){Fullscreen=atoi(str.c_str());}
			if(speicher=="AA"){AntiA=atoi(str.c_str());}
			if(speicher=="Flimmering"){Flimmering=atoi(str.c_str());}
			if(speicher=="MusicVol"){MusicVolume=atoi(str.c_str());}
			if(speicher=="SoundVol"){SoundVolume=atoi(str.c_str());}
			if(speicher=="CustomCursor"){UseHand=atoi(str.c_str());}
			if(speicher=="WordMode"){WordMode=atoi(str.c_str());}
			if(speicher=="TurnMode"){TurnMode=atoi(str.c_str());}
			if(speicher=="TurnLimit"){TurnsModeLimit=atoi(str.c_str());}
			if(speicher=="TimeLimit"){TimeModeLimit=atoi(str.c_str());}
			if(speicher=="AlphaDef"){alphaDef=str;}								
				delete[] writable;
				speicher=str;
			}
		file.close();	
		return 0;
}

int WriteSettings()
{
  std::ofstream myfile;
  myfile.open ("Settings.txt");
  myfile << "AA\n";
  myfile << AntiA <<"\n";
  myfile << "Fullscreen\n";
  myfile << Fullscreen <<"\n";
  myfile << "Flimmering\n";
  myfile << Flimmering <<"\n";
  myfile << "MusicVol\n";
  myfile << MusicVolume <<"\n";
    myfile << "SoundVol\n";
  myfile << SoundVolume <<"\n";
    myfile << "CustomCursor\n";
  myfile << UseHand <<"\n";
    myfile << "WordMode\n";
  myfile << WordMode <<"\n";
    myfile << "TurnMode\n";
  myfile << TurnMode <<"\n";
    myfile << "TurnLimit\n";
  myfile << TurnsModeLimit <<"\n";
    myfile << "TimeLimit\n";
  myfile << TimeModeLimit <<"\n";
  myfile << "AlphaDef\n";
  myfile << alphaDef <<"\n";

 
  myfile.close();
  return 0;
}

class Highscore
{
	public:
	int Score=0;
	std::string Name="";
};

class HighScoreTable
{
	public: 
	Highscore Scores[11];
	int Wordbook=0;
	int Mode=0;
	int Limit=0;
	
	int CheckForScore(int Score)
	{
		int re=-1;
		for(int i=9; i>-1; i--)
		{
			if(Score>Scores[i].Score)
			 re=i;
		}
		return re;
	}
	
	int InsertScore(Highscore S, int Place)
	{
		for(int i=10; i>Place; i--)
		{
			Scores[i]=Scores[i-1];
		}
		Scores[Place]=S;
			
		return 0;
	}
	
	std::string genString()
	{
		std::string re="";
		if(Wordbook==0)re="Highscores/Redu";
		if(Wordbook==1)re="Highscores/Reco";
		if(Wordbook==2)re="Highscores/Exte";
		if(Mode==0)re=re+"Time";
		if(Mode==1)re=re+"Turn";
		re=re+std::to_string(Limit)+".txt";
		return re;
	}
	
	std::string genContent()
	{
		std::string re="";
		for(int i=0; i<10; i++)
		{
			re=re+" ";
			re=re+Scores[i].Name;
			re=re+" - ";
			re=re+std::to_string(Scores[i].Score)+" \n";
		}
		return re;
	}
	
	int WriteTable()
	{
		std::ofstream myfile;
		myfile.open (genString());

		for(int i=0; i<10; i++)
		{
		myfile << "NewScore\n";
		myfile << Scores[i].Score <<"\n";	
		myfile << "Name\n";
		myfile << Scores[i].Name <<"\n";
		}
		myfile.close();
		return 0;
	}
	
	int LoadTable()
	{
			std::ifstream file;
	
			std::string str;
	
			file.open(genString());
			int HilfsInteger=-1; 
			while (std::getline(file, str))
			{
			char * writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0';
			if(speicher=="NewScore"){HilfsInteger++; Scores[HilfsInteger].Score=atoi(str.c_str());}
			if(speicher=="Name"){Scores[HilfsInteger].Name=str;}
									
				delete[] writable;
				speicher=str;
			}
		file.close();	
		return 0;
}

	
	
};

HighScoreTable Tables[4][3][4]; // Wordbookmode - 0 reduced, 1 reco, 2 ext | Mode: 0 time, 1 limit | Limit: short, medium, long

int DefHighScoreTables()
{
	for(int i=0; i<3; i++)
	{
		for(int i2=0; i2<2; i2++)
		{
			for(int i3=0; i3<3; i3++)
			{
				Tables[i][i2][i3].Wordbook=i;
				Tables[i][i2][i3].Mode=i2;
				if(i2==0)
				{
					if(i3==0)Tables[i][i2][i3].Limit=150;
					if(i3==1)Tables[i][i2][i3].Limit=300;
					if(i3==2)Tables[i][i2][i3].Limit=600;
				}
				if(i2==1)
				{
					if(i3==0)Tables[i][i2][i3].Limit=50;
					if(i3==1)Tables[i][i2][i3].Limit=100;
					if(i3==2)Tables[i][i2][i3].Limit=200;
				}
				Tables[i][i2][i3].LoadTable();
			}
		}
	}
	
	return 0;
}


bool anagram(std::string s1, std::string s2)
{
	bool r=false;
 if(s1.length() != s2.length())
 {
	 //std::cout << "Length exception" << std::endl;
        r=false;
 }
 else
 {
    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    if(s1==s2)
    {	
		//std::cout << "Anagramm" << std::endl;
		r=true;
	}
 }
 return r;
}

int SimiliarWord(std::string comp1, std::string comp2)
{
	int re=0;
	for (int i=0; i<comp1.length(); i++)
	{
		if(comp2.length()>0)
		{
		for (int i2=0; i2<comp2.length(); i2++)
		{
			if(comp1.substr(i, 1)==comp2.substr(i2, 1))
			{
			comp2.erase(i2, 1);
			re++;
			i2=comp2.length()+1;
			}
		}
		}
	}
	float perc=(float)re/comp1.length();
	re=perc*100;
	return re;
}

int ChangePowerWord()
{
	int r=rand()%count;
	bool Selected=false;
	
	while(Selected==false)
	{
		if(Vocabulary[r].length()<11 && Vocabulary[r].length()>4)
		 {
			int c=0;
			//std::cout << std::endl << "Checking " << Vocabulary[r] << " length " << Vocabulary[r].length() << " consisting of ";
			for (int i=0; i<Vocabulary[r].length()+1; i++)
					{
					if(alphabet.find(Vocabulary[r].substr(i, 1)) != std::string::npos)c++;
					//std::cout << c << " " <<Vocabulary[r].substr(i, 1) << " ";
					
					}
					if(c==Vocabulary[r].length()+1)
					{
						if(Vocabulary[r]!="HOLOCAUST" && Vocabulary[r]!="PROGROM" && Vocabulary[r]!="APARTHEID" && Vocabulary[r]!="GENOCIDE" && Vocabulary[r]!="RACISM" && Vocabulary[r]!="NAZISM" && Vocabulary[r]!="HOMOPHOBIA")
						{
						PowerWord=Vocabulary[r];
						Selected=true;
						}
					}
		 }
		r=rand()%count;
	}
	
		SDL_DestroyTexture(PWordTex);
		SDL_Surface* Result=NULL;
		TTF_Font *tFont;
		tFont=TTF_OpenFont( "pathway-gothic-one/PathwayGothicOne-Regular.ttf", 70 );
		SDL_Color FontColor{255, 130, 130, 255};
		Result=TTF_RenderText_Solid(tFont, PowerWord.c_str(), FontColor);	
		PWordTex=SDL_CreateTextureFromSurface(Renderer, Result);		
		SDL_FreeSurface(Result);
		TTF_CloseFont(tFont);
	
	return 0;
}

class RainLetter
{
	public:
	float X=0;
	float Y=0;
	float Zoom=0;
	float Alpha=255;
	float Angle=0;
	float Speed=1;
	float Rot=0;
	float RotSpeed=0.05;
	int Glypher=0;
	bool Stayer=false;
	
	int Create()
	{
		X=-1000+(rand()%4000);
		Y=-1000+(rand()%3000);
		Zoom=(float)(rand()%200)/100;
		Angle=rand()%360;
		Glypher=rand()%26;
		Speed=(float)(rand()%600)/100;
		Rot=(float)(rand()%100)/100;
		RotSpeed=(float)(rand()%100)/100;
		if((rand()%50)<1)Zoom=Zoom+((rand()%200)/100);
		return 0;
	}
	
	int Draw(int alp=240)
		{
			Rot=Rot+RotSpeed;
			float cAngle=0;
			if(Stayer==false)
			cAngle=(float)((Angle*M_PI)/180); 
			else cAngle=(float)((MenuBGAngle*M_PI)/180);
				X=(float)X+(cos(cAngle)*(Speed));
				Y=(float)Y+(sin(cAngle)*(Speed));
				if(X<-1000)X=3000;
				if(X>3000)X=-1000;
				if(Y<-1000)Y=3000;
				if(Y>3000)Y=-1000;
			SDL_Rect Writer;
			Writer.x=(X);
			Writer.y=(Y);
			Writer.w=75*Zoom;
			Writer.h=75*Zoom;
			SDL_Rect Reader;
			Reader.x=Glypher*75;
			Reader.y=0;
			Reader.w=75;
			Reader.h=75;
			SDL_SetTextureAlphaMod(GhostGlyphs, alp);
			SDL_SetTextureBlendMode(GhostGlyphs, SDL_BLENDMODE_BLEND);
			SDL_RenderCopyEx( Renderer, GhostGlyphs, &Reader, &Writer, Rot, NULL, SDL_FLIP_NONE); 
			
			return 0;
		}
	
};

RainLetter MenuLetterEffect[1000];

class Button
{
	public:
	bool Unlocked=false;
	int x=0;
	int y=0;
	int w=200;
	int h=100;
	int fontSize=35;
	int TexMaxSize=0;
	int LastFontSize=35;
	int Action=0;
	SDL_Texture *TitleTex;
	std::string Text="";
	std::string LastText="";
	bool Solid=true;
	bool NoBorder=false;
	SDL_Color BGColor{50, 80, 50, 180};
	SDL_Color FontColor{255, 255, 255, 200};
	SDL_Color LastFontColor{0, 255, 0, 255};
	
	int CreateText(SDL_Renderer* rend=Renderer)
	{
		if(Text!="")
		{
		bool okay=false;
		int cFontSize=fontSize;
		while(okay==false)
		{
		TTF_Font *tFont;
		SDL_DestroyTexture(TitleTex);
		SDL_Surface* Result=NULL;
		tFont=TTF_OpenFont( "pathway-gothic-one/PathwayGothicOne-Regular.ttf", cFontSize );
		Result=TTF_RenderText_Solid_Wrapped(tFont, Text.c_str(), FontColor, w);	
		
		if(TexMaxSize==0 || Result->h<=TexMaxSize || Text=="")
		{
			okay=true;
		}
		else
		{
			cFontSize--;
		}
		TTF_CloseFont(tFont);
		TitleTex=SDL_CreateTextureFromSurface(rend, Result);		
		SDL_FreeSurface(Result);
		
		}
		}
		return 0;
	}
	
	int Draw(SDL_Renderer* rend=Renderer)
	{
		std::transform(Text.begin(), Text.end(), Text.begin(), ::toupper);
		SDL_Rect Drawer;
		Drawer.x=x;
		Drawer.y=y;
		Drawer.w=w;
		Drawer.h=h;

		SDL_SetRenderDrawColor(rend, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
		if(NoBorder==false)
		{
		if(Solid==false)
		SDL_RenderDrawRect(rend, &Drawer);
		else
		SDL_RenderFillRect(rend, &Drawer);
		}
		
		if(strcmp(Text.c_str(), LastText.c_str())!=0 || (LastFontColor.r!=FontColor.r || LastFontColor.g!=FontColor.g||LastFontColor.r!=FontColor.b||LastFontColor.a!=FontColor.a) || (fontSize!=LastFontSize))
		{
			CreateText(rend);
			LastText=Text;
			LastFontColor=FontColor;
			LastFontSize=fontSize;
		}
		if(strcmp(Text.c_str(), "")!=0)
		{
			 SDL_Point size;
			SDL_QueryTexture(TitleTex, NULL, NULL, &size.x, &size.y);
			 Drawer.w=size.x;
			 Drawer.h=size.y;
			 SDL_RenderCopy( rend, TitleTex, NULL, &Drawer);

		}
		
		
		return 0;
	}
	
};


Button ButtonS[500];

std::string reLetter();



bool IsWord(std::string check)
{
	bool r=false;
	for(int i=1; i<count+1; i++)
	{
		if(check==Vocabulary[i])
		{
			i=count+1;
			r=true;
		}
	}
	return r;
}


class Tile
{
	public:
		bool Active=false;
		bool Shivering=false;

		int TexX=0;
		int TexY=0;
		
		int PosX=0;
		int PosY=0;
		
		int Glyph=0;
		
		int Draw()
		{
			if(Active==true)
			{
			SDL_Rect Writer;
			Writer.x=(PosX);
			Writer.y=(PosY);
			if(Shivering==true)
			{
			Writer.x=(PosX)+(rand()%5)-(rand()%5);
			Writer.y=(PosY)+(rand()%5)-(rand()%5);
			}
			Writer.w=TileSize;
			Writer.h=TileSize;
			SDL_Rect Reader;
			Reader.x=TexX;
			Reader.y=TexY;
			Reader.w=TileSize;
			Reader.h=TileSize;
			SDL_RenderCopy( Renderer, Wood, &Reader, &Writer); 
			Reader.x=Glyph*75;
			Reader.y=0;
			Reader.w=75;
			Reader.h=75;
			SDL_RenderCopy( Renderer, Glyphs, &Reader, &Writer); 
			}
			return 0;
		}
		
		int create(int x, int y, std::string letter)
		{
			Glyph=alphabet.find(letter);
			PosX=x;
			PosY=y;
			TexX=(rand()%(975-TileSize));
			TexY=(rand()%(1200-TileSize));
			Active=true;
			return 0;
		}
		
		std::string giveLetter()
		{
			if(Active==true)
			return alphabet.substr(Glyph, 1);
			else
			return " ";
		}
	
};

class GhostTile
{
	public:
		bool Active=false;
		int SizeAdd=0;		
		int PosX=0;
		int PosY=0;
		
		int Glyph=0;
		
		int Draw()
		{
			if(Active==true)
			{
			SDL_Rect Writer;
			Writer.x=(PosX)-(SizeAdd*3);
			Writer.y=(PosY)-(SizeAdd*3);
			Writer.w=TileSize+(SizeAdd*6);
			Writer.h=TileSize+(SizeAdd*6);
			SDL_Rect Reader;
			Reader.x=Glyph*75;
			Reader.y=(rand()%6)*75;
			Reader.w=75;
			Reader.h=75;
			SDL_SetTextureAlphaMod(GhostGlyphs, 100-(SizeAdd/2));
			SDL_SetTextureBlendMode(GhostGlyphs, SDL_BLENDMODE_BLEND);
			SDL_RenderCopy( Renderer, GhostGlyphs, &Reader, &Writer); 
			SizeAdd=SizeAdd+10;
			if(SizeAdd>=200)Active=false;
			}
			return 0;
		}
		
		int create(int x, int y, std::string letter)
		{
			SizeAdd=0;
			
			Glyph=alphabet.find(letter);
			PosX=x;
			PosY=y;
			Active=true;
			return 0;
		}
	
};

 int CalcTime()
  {
	 int a=0;
	int aTime=SDL_GetTicks()-StartTime;
	Seconds=std::floor(aTime/1000);
	//Minutes=std::floor(Seconds/60);
	//Seconds=Seconds-(Minutes*60);
	Score=Score;
	//std::cout << "The time is " << Minutes << " Minutes and " << Seconds << " Seconds." << std::endl;
	return a;
	  
  }
  
 int AddLastWord(std::string in)
 {
	 
	for(int i=10; i>0; i--)
	LastWords[i]=LastWords[i-1];
	LastWords[0]=in;
	ButtonS[5].Text="";
	  for(int i=0; i<10; i++)
	  {
		  ButtonS[5].Text+="   " + LastWords[i]+"\n";
	  }
	 
	 return 0;
 }
 
 bool IsLastWord(std::string in)
 {
	 bool re=false;
	 for(int i=0; i<10; i++)
	  {
		  if(LastWords[i]==in)
		   re=true;
	  }
	 return re;
 }
 
 class CountAlpha
 {
	 public:
	 int AAray[27]={0};
	 
 };

class Grid
{
	public:
	Tile Tiler[GridW+3][GridH+3];
	GhostTile GhostTiler[(GridW*2)*GridH];
	int CurrentGhosts=0;
	std::string Horizontal[GridH+2];
	std::string Vertical[GridW+2];
	
	int SelectedX=-1;
	int SelectedY=-1;
	
	int createTile(int x, int y, std::string letter)
		{
			Tiler[x][y].create(x*TileSize, y*TileSize, letter);
			return 0;
		}
	
	CountAlpha countGlyphes()
	{
		CountAlpha re;
		for(int x=0; x<GridW+1; x++)
		 for(int y=0; y<GridH+1; y++)
		 {
			 re.AAray[Tiler[x][y].Glyph]++;
		 }
	  return re;
	}
	
	int TurnGlyphToGhost(int sx, int sy)
	{
		//Oh no!
		//Clean up
	   if(Flimmering==true)
		{
			bool repeat=true;
			while(repeat==true)
			{
			repeat=false;
			for(int i=0; i<CurrentGhosts+1; i++)
			{
				if(GhostTiler[i].Active==false)
				 {
					 GhostTiler[i]=GhostTiler[CurrentGhosts];
					 CurrentGhosts--;
					 repeat=true;
				 }
			}
			}
	
		 CurrentGhosts++;
		 GhostTiler[CurrentGhosts].create(Tiler[sx][sy].PosX, Tiler[sx][sy].PosY, Tiler[sx][sy].giveLetter()); 
		 }
		 return 0;
	}
	
	int Dissolve()
	{
		int count=0;
		for(int x=0; x<GridW+1; x++)
		 for(int y=0; y<GridH+1; y++)
		 {
			 if(Tiler[x][y].Active==true)count++;
		 }
		 if(count>0)
		 {
			 for(int i=0; i<3; i++)
			 {
			 int sx=rand()%(GridW+1);
			 int sy=rand()%(GridH+1);
			 TurnGlyphToGhost(sx, sy);
			 Tiler[sx][sy].Active=false;
			 }
		 }
		else
		{
			Mix_HaltChannel(4);
			if(ShowEndScreen==false)
			EndTaunt=false;
			ShowEndScreen=true;
			if(MenuOpen==false)
			{

			if(TurnMode==false)MadeHighScore=Tables[WordMode][TurnMode][HSLimitEnter].CheckForScore(Score);
			if(TurnMode==true)MadeHighScore=Tables[WordMode][TurnMode][HSLimitEnter].CheckForScore(Score);
			if(MadeHighScore==-1)
			 {
				for(int i=0; i<ButtonsActive+1; i++)
					{
					 if(i>=EndScreenStart && i<=EndScreenEnd)	 
					 ButtonS[i].Unlocked=true;
					}
			 }
			 else
			 {
				 for(int i=0; i<ButtonsActive+1; i++)
					{
					 if(i>=EnterHighScoreStart && i<=EnterHighScoreEnd)	 
					 ButtonS[i].Unlocked=true;
					}
					if(Score>ToWin)ButtonS[EnterHighScoreStart].Text="GAME WON";
			 }
			}
		}
		return 0;
	}
		
	int Draw()
	{
		SDL_Rect Blinker;
		if(Flimmering==true)
		{
		Blinker.x=0;
		Blinker.y=0;
		Blinker.w=(GridW+1)*TileSize;
		Blinker.h=(GridW+1)*TileSize;
		int BlinkMod=AlphaBG;
		if(BlinkMod>255)BlinkMod=255;
		if(BlinkMod<50)BlinkMod=50;
		SDL_SetRenderDrawColor(Renderer, rand()%BlinkMod, rand()%BlinkMod, rand()%BlinkMod, 255);
		SDL_RenderFillRect(Renderer, &Blinker);
		}
		for(int x=0; x<GridW+1; x++)
		 for(int y=0; y<GridH+1; y++)
		  Tiler[x][y].Draw();
		  
		for(int i=0; i<CurrentGhosts+1; i++)
		  GhostTiler[i].Draw();
		  
		return 0;
	}
	
	int MakeStrings()
	{
		for(int i=0; i<GridH+1; i++)
		{
			Horizontal[i]="";
				for(int i2=0; i2<GridW+1; i2++)
				{

					if(Tiler[i2][i].PosX==(i2*TileSize) && Tiler[i2][i].PosY==(i*TileSize))
					Horizontal[i].append(Tiler[i2][i].giveLetter());
					else
					{
					Horizontal[i].append(" ");
					OutOfOrder=true;
					}
				}
				//std::cout << "Horizontal " << i << " = " << Horizontal[i] << std::endl;
			
		}
		
		for(int i=0; i<GridW+1; i++)
		{
			Vertical[i]="";
				for(int i2=0; i2<GridH+1; i2++)
				{
					if(Tiler[i][i2].PosX==(i*TileSize) && Tiler[i][i2].PosY==(i2*TileSize))
					Vertical[i].append(Tiler[i][i2].giveLetter());
					else
					{
					Horizontal[i].append(" ");
					OutOfOrder=true;
					}
					
				}
				//std::cout << "Vertical " << i << " = " << Vertical[i] << std::endl;
			
		}
		return 0;
	}
	
	int CheckForWords(bool refill=false)
	{
		MakeStrings();
		bool redo=true;
		bool founder=false;
		if(UseHand==false)SDL_ShowCursor(false);
		LockMouse=true;
		while(redo==true)
		{
			redo=false;
		for(int i=1; i<count+1; i++)
		{
	
			if(Vocabulary[i].length()>minLength)
			{
			for(int y=0; y<GridH+1; y++)
			{
				if(Horizontal[y].find(Vocabulary[i]) != std::string::npos)
				{
					//std::cout << "Found String: " << Vocabulary[i] << " On X: " << Horizontal[y].find(Vocabulary[i]) << " Y: " << y << std::endl;
					int start=Horizontal[y].find(Vocabulary[i]);
					founder=true;
					ActionsWOMerit=0;
					if(refill==false)
					{
						Mix_PlayChannel( 2, Sounds[3], 0 );
						Mix_PlayChannel( 3, Sounds[9], 0 );
					}
					
					int length=Vocabulary[i].size();
					int Add=0;
					if(refill==false)
					{
					Multiplier++;
					
					if(Vocabulary[i]==PowerWord)
					 {
						 Bonus++;
						 Add=((length*length)/2)*Bonus;
						 ChangePowerWord();
						 if(BGFlimmer<0)BGFlimmer=0;
						 BGFlimmer=15*length;
					 }
					 else
					 {
					if(IsLastWord(Vocabulary[i])==true)
					{
						Pissword=Vocabulary[i];
						Pissed=350;
					}
					if(SimiliarWord(Vocabulary[i], PowerWord)>50)
						{
							Pissed=-350;
							Pissword=Vocabulary[i];
						}
					}
					AddLastWord(Vocabulary[i]);
					if(Flimmering==true)AlphaBG=AlphaBG+(((length*length)+Add)*Multiplier);
					Score=Score+(((length*length)+Add)*Multiplier);
					//TimeLeft=TimeLeft+(TimeBonus);
					if(Flimmering==true)BlinkingScore=BlinkingScore+((((length*length)+Add)*Multiplier)/2);
					/*if(Bonus>0)
					std::cout << "Scoring! Base Points: " << length*length << " plus Powerwordbonus of " << Add/Bonus << " multiplied with " << Bonus << " for earlier Powerwords. The sum is multiplied with a chain Bonus of " << Multiplier << " for a total of " << (((length*length)+Add)*Multiplier) << std::endl;
					else
					std::cout << "Scoring! Base Points: " << length*length << "  multiplied with a chain Bonus of " << Multiplier << " for a total of " << (((length*length)+Add)*Multiplier) << std::endl;
					*/
					}
					//ButtonS[2].Text=" Points: " + std::to_string(Score);
					div_t divresult=div(length, 2);
					for(int s=start; s<start+length; s++)
					{
					if(refill==false)TurnGlyphToGhost(s, y);
					 if(refill==false)
					 Tiler[s][y].Active=false; 
					 else
					 Tiler[s][y].create(s*TileSize, y*TileSize, reLetter());
					}
					if(refill==false)
					 {
						 
						 for(int s=start-1; s>-1; s--)
						 {
							Tiler[s+divresult.quot][y]=Tiler[s][y];
							//Tiler[s+divresult.quot][y].PosX=(s+divresult.quot)*TileSize;
							Tiler[s][y].Active=false;
						 }
						 for(int s=start+length; s<GridW+1; s++)
						 {
							Tiler[s-divresult.quot][y]=Tiler[s][y];
							//Tiler[s-divresult.quot][y].PosX=(s-divresult.quot)*TileSize;
							Tiler[s][y].Active=false;
						 }
						 
						 //create replacements
						 for(int r=0; r<divresult.quot; r++)
						 {
							  Tiler[r][y].create(0+((r*TileSize)-(divresult.quot*TileSize)), y*TileSize, reLetter());
							  Tiler[GridW-r][y].create(((GridW*TileSize)-(r*TileSize))+(divresult.quot*TileSize), y*TileSize, reLetter());
						 }
						 
						 
						 
						 if(divresult.rem==1)
						  {
							  if(y<floor((GridH+1)/2))
							  {
								   for(int s=y-1; s>-1; s--)
								  {
									 Tiler[start+divresult.quot][s+1]=Tiler[start+divresult.quot][s];
									 //Tiler[start+divresult.quot][s+1].PosY=(s+1)*TileSize;
									 Tiler[start+divresult.quot][s].Active=false; 
								  }
								  Tiler[start+divresult.quot][0].create((start+divresult.quot)*TileSize, 0-TileSize, reLetter());
							  }
							  else
							  {
								for(int s=y+1; s<GridH+1; s++)
								  {
									 Tiler[start+divresult.quot][s-1]=Tiler[start+divresult.quot][s];
									  //Tiler[start+divresult.quot][s-1].PosY=(s-1)*TileSize;
									 Tiler[start+divresult.quot][s].Active=false;
								  }
								  Tiler[start+divresult.quot][GridH].create((start+divresult.quot)*TileSize, (GridH+1)*TileSize, reLetter());
							  }
						  }
					 }
					 y=GridH+2;
					 redo=true;
					 MakeStrings();
				}	
			}
			if(redo==false)
			{
			for(int x=0; x<GridW+1; x++)
			{
				if(Vertical[x].find(Vocabulary[i]) != std::string::npos)
				{
					//std::cout << "Found String: " << Vocabulary[i] << " On X: " << x << " Y: " << Vertical[x].find(Vocabulary[i]) << std::endl;
					founder=true;
					ActionsWOMerit=0;
					int start=Vertical[x].find(Vocabulary[i]);
					if(refill==false)
					{
						Mix_PlayChannel( 2, Sounds[3], 0 );
						Mix_PlayChannel( 3, Sounds[9], 0 );
					}
				
					int length=Vocabulary[i].size();
					int Add=0;
					if(refill==false)
					{
					Multiplier++;
					if(Vocabulary[i]==PowerWord)
					 {
						 Bonus++;
						 Add=((length*length)/2)*Bonus;
						 ChangePowerWord();
						 if(BGFlimmer<0)BGFlimmer=0;
						 BGFlimmer=15*length;
					 }
					 else
					 {
					if(IsLastWord(Vocabulary[i])==true)
					{
						Pissed=350;
						Pissword=Vocabulary[i];
					}
					if(SimiliarWord(Vocabulary[i], PowerWord)>50)
						{
							Pissed=-350;
							Pissword=Vocabulary[i];
						}
					}
					AddLastWord(Vocabulary[i]);
					if(Flimmering==true)AlphaBG=AlphaBG+(((length*length)+Add)*Multiplier);
					Score=Score+(((length*length)+Add)*Multiplier);
					//TimeLeft=TimeLeft+(TimeBonus);
					if(Flimmering==true)BlinkingScore=BlinkingScore+((((length*length)+Add)*Multiplier)/2);
					/*if(Bonus>0)
					std::cout << "Scoring! Base Points: " << length*length << " plus Powerwordbonus of " << Add/Bonus << " multiplied with " << Bonus << " for earlier Powerwords. The sum is multiplied with a chain Bonus of " << Multiplier << " for a total of " << (((length*length)+Add)*Multiplier) << std::endl;
					else
					std::cout << "Scoring! Base Points: " << length*length << "  multiplied with a chain Bonus of " << Multiplier << " for a total of " << (((length*length)+Add)*Multiplier) << std::endl;
					*/
					}
					//ButtonS[2].Text=" Points: " + std::to_string(Score);
					div_t divresult=div(length, 2);
					for(int s=start; s<start+length; s++)
					{
					 if(refill==false)TurnGlyphToGhost(x, s);
					 if(refill==false)
					 {
					 Tiler[x][s].Active=false;
					}
					  else
					 Tiler[x][s].create(x*TileSize, s*TileSize, reLetter()); 
					}
					if(refill==false)
					 {
						
						 for(int s=start-1; s>-1; s--)
						 {
							
							Tiler[x][s+divresult.quot]=Tiler[x][s];
							//Tiler[s+divresult.quot][y].PosX=(s+divresult.quot)*TileSize;
							Tiler[x][s].Active=false;
							
						 }
						
						 for(int s=start+length; s<GridH+1; s++)
						 {
							// std::cout << "What: " << (s-(start+length)) << std::endl;
							Tiler[x][s-divresult.quot]=Tiler[x][s];
							//Tiler[s-divresult.quot][y].PosX=(s-divresult.quot)*TileSize;
							Tiler[x][s].Active=false;
						 }
						  //create replacements
						 for(int r=0; r<divresult.quot; r++)
						 {
							  Tiler[x][r].create(x*TileSize, 0+((r*TileSize)-(divresult.quot*TileSize)), reLetter());
							  Tiler[x][GridH-r].create(x*TileSize, ((GridH*TileSize)-(r*TileSize))+(divresult.quot*TileSize), reLetter());
						 }
						 
						 if(divresult.rem==1)
						  {
							  if(x<floor((GridW+1)/2))
							  {
								   for(int s=x-1; s>-1; s--)
								  {
									 Tiler[s+1][start+divresult.quot]=Tiler[s][start+divresult.quot];
									 //Tiler[start+divresult.quot][s+1].PosY=(s+1)*TileSize;
									 Tiler[s][start+divresult.quot].Active=false;
								  }
								   Tiler[0][start+divresult.quot].create(0-TileSize, (start+divresult.quot)*TileSize, reLetter());
							  }
							  else
							  {
								for(int s=x+1; s<GridW+1; s++)
								  {
									 Tiler[s-1][start+divresult.quot]=Tiler[s][start+divresult.quot];
									  //Tiler[start+divresult.quot][s-1].PosY=(s-1)*TileSize;
									 Tiler[s][start+divresult.quot].Active=false;
								  }
								   Tiler[GridW][start+divresult.quot].create((GridW+1)*TileSize, (start+divresult.quot)*TileSize, reLetter());
							  }
						  }
					 }
					 x=GridW+2;
					 redo=true;
					 MakeStrings();
				}	
			}
			}
			}
		}
		}
		
		if(founder==false || refill==true)
		{
			//std::cout << "Found Something" << std::endl;
			 Multiplier=0;
			 int Reactor=Score-LastScore;
			 if(Reactor<45 && Reactor>0 && BGFlimmer<-75)TauntOrShock=-400;
			 if(Reactor>45 && TauntOrShock<=0)TauntOrShock=0;
			 if(Reactor>666)TauntOrShock=400;
			 if(Awed==false && Score>ToWin)
			 {
				 TauntOrShock=400;
				 Awed=true;
				
			 }
			 LastScore=Score;
			 LockMouse=false;
			if(UseHand==false)SDL_ShowCursor(true);
			if(TurnMode==true && TurnsLeft==0 && EndGame==false)
				{
				EndGame=true;
				Mix_PlayChannel( 4, Sounds[4], 0 );
				}
		 }
		
		
	return 0;
	}
	
	std::string AllTileStr()
	{
		std::string re="";
		for(int x=0; x<GridW+1; x++)
		 for(int y=0; y<GridH+1; y++)
		 {
			 re=re+Tiler[x][y].giveLetter();
		 }
		return re;
	}
	
	int MoveTiles()
	{
		bool everythinginorder=true;
		for(int x=0; x<GridW+1; x++)
		 for(int y=0; y<GridH+1; y++)
		 {
			 //Get diff:
			if(Maximum(Tiler[x][y].PosX, (x*TileSize))-Minimum(Tiler[x][y].PosX, (x*TileSize))<10)Tiler[x][y].PosX=(x*TileSize);
			if(Maximum(Tiler[x][y].PosY, (y*TileSize))-Minimum(Tiler[x][y].PosY, (y*TileSize))<10)Tiler[x][y].PosY=(y*TileSize);
			if(Tiler[x][y].PosX>(x*TileSize))Tiler[x][y].PosX=Tiler[x][y].PosX-10;
			if(Tiler[x][y].PosX<(x*TileSize))Tiler[x][y].PosX=Tiler[x][y].PosX+10;
			if(Tiler[x][y].PosY>(y*TileSize))Tiler[x][y].PosY=Tiler[x][y].PosY-10;
			if(Tiler[x][y].PosY<(y*TileSize))Tiler[x][y].PosY=Tiler[x][y].PosY+10;
			if(Tiler[x][y].PosX!=(x*TileSize) || Tiler[x][y].PosY!=(y*TileSize))
			

			
			 everythinginorder=false;
		 }
		
		if(everythinginorder==true && OutOfOrder==true)
		  {
			 Mix_HaltChannel(2);
			  OutOfOrder=false;
			  CheckForWords();
		  }
		return 0;
	}
	
	int click(int x, int y)
	{
		if(x>0 && x<(GridW+1)*TileSize && y>0 && y<(GridH+1)*TileSize && MenuOpen==false && EndGame==false)
		{
		div_t divresult;
		divresult = div (x, TileSize);
		div_t divresult2;
		divresult2 = div (y, TileSize);
		if(LockMouse==false)
		{
		LastAction=0;
		ActionsWOMerit++;
		if(SelectedX==-1 || SelectedY==-1)
		{
			SelectedX=divresult.quot;
			SelectedY=divresult2.quot;
			Tiler[SelectedX][SelectedY].Shivering=true;
		}
		else
		 {
			 if(divresult.quot!=SelectedX || divresult2.quot!=SelectedY)
			  TurnsLeft--;
			 Tiler[SelectedX][SelectedY].Shivering=false;
			 std::swap(Tiler[SelectedX][SelectedY], Tiler[divresult.quot][divresult2.quot]);
			 Tiler[SelectedX][SelectedY].PosX=SelectedX*TileSize;
			 Tiler[SelectedX][SelectedY].PosY=SelectedY*TileSize;
			 Tiler[divresult.quot][divresult2.quot].PosX=divresult.quot*TileSize;
			 Tiler[divresult.quot][divresult2.quot].PosY=divresult2.quot*TileSize;
			 SelectedX=-1;
			 SelectedY=-1;
			 CheckForWords();
			 
		 }
		}
		}
		
		return 0;
	}
	
	
};

Grid TheGrid;
Grid EmptyGrid;

std::string reLetter()
{
	std::string re;
	std::string alpha=alphaDef;
	std::string checker=TheGrid.AllTileStr();
	//std::cout << checker << std::endl;
	for (int i=0; i<alphabet.length(); i++)
					{
						std::string current=alphabet.substr(i, 1);
						int counter=0;
						for(int i2=0; i2<checker.length(); i2++)
						 {
							 if(current==checker.substr(i2, 1))
							  counter++;
							  
						 }
						 if(counter==0)alpha=alpha+alphabet.substr(i, 1)+alphabet.substr(i, 1);
						 if(counter==1)alpha=alpha+alphabet.substr(i, 1);
						 int PowerWordCounter=0;
						for(int i2=0; i2<PowerWord.length(); i2++)
						 {
							 if(PowerWord.substr(i2, 1)==alphabet.substr(i, 1))
							  PowerWordCounter++;
						 }
						 if(PowerWordCounter>0)
						 //std::cout << "Powerword " << PowerWord << " contains " << PowerWordCounter << " times " << alphabet.substr(i, 1) << std::endl;
						 if(PowerWordCounter>counter && Seconds>5)
							{
								alpha=alpha+alphabet.substr(i, 1)+alphabet.substr(i, 1);
								//std::cout << "Not enough " << alphabet.substr(i, 1) << " tiles to build powerword. Slightly increasing chance" << std::endl;
							}
					}
	
	/*
	std::string alpha="QQJJZZXXVVVVKKKKWWWWYYYYYFFFFFBBBBBGGGGGHHHHHHMMMMMMPPPPPPDDDDDDUUUUUUUCCCCCCCCLLLLLLLLSSSSSSSSNNNNNNNNNTTTTTTTTTOOOOOOOOOIIIIIIIIIRRRRRRRRRAAAAAAAAAAEEEEEEEEEE";
	if(PowerWord.find("Q") != std::string::npos)
		alpha=alpha+"QQQ";
	if(PowerWord.find("J") != std::string::npos)
		alpha=alpha+"JJJ";
	if(PowerWord.find("Z") != std::string::npos)
		alpha=alpha+"ZZZ";
	if(PowerWord.find("X") != std::string::npos)
		alpha=alpha+"XXX";
	if(PowerWord.find("V") != std::string::npos)
		alpha=alpha+"VV";
	if(PowerWord.find("K") != std::string::npos)
		alpha=alpha+"KK";
	if(PowerWord.find("W") != std::string::npos)
		alpha=alpha+"WW";
	if(PowerWord.find("Y") != std::string::npos)
		alpha=alpha+"YY";
	if(PowerWord.find("F") != std::string::npos)
		alpha=alpha+"F";
	if(PowerWord.find("B") != std::string::npos)
		alpha=alpha+"B";
	if(PowerWord.find("G") != std::string::npos)
		alpha=alpha+"G";
	
	*/
	re=alpha.substr(rand()%(alpha.length()-1),1);
	return re;
	
}

bool compdown(std::string str, std::string str2)
 {
     if(str.length()>str2.length())
     return 1;
     else return 0;
 }


int TriggerAction(int A=0)
{
	if(A==1)
	{
	MenuOpen=false;
	NewGame();
	}
	if(A==2)
	{
		A=0;
		HighScoreMenuBook=WordMode;
		HighScoreMenuMode=TurnMode;
		for(int i=0; i<ButtonsActive+1; i++)
			 {
			if(i>=HighScoreMenuStart && i<=HighScoreMenuEnd)	 
				ButtonS[i].Unlocked=true;
			   else
					  ButtonS[i].Unlocked=false;
				}
	}
	if(A==3)
	{
	 A=0;
	for(int i=0; i<ButtonsActive+1; i++)
					 {
					 if(i==OptionsMenuEnd+1 || i==OptionsMenuEnd+2 || i==OptionsMenuEnd+3)	 
					  ButtonS[i].Unlocked=true;
					  else
					  ButtonS[i].Unlocked=false;
					 }
					
	}
	if(A==4)
	{
	 A=0;
	for(int i=0; i<ButtonsActive+1; i++)
					 {
					 if(i>=OptionsMenuStart && i<=OptionsMenuEnd)	 
					  ButtonS[i].Unlocked=true;
					  else
					  ButtonS[i].Unlocked=false;
					 }
					
	}
	if(A==5)
	{
	running=false;
	}
	
	if(A==6)
	{
		if(Fullscreen==true)Fullscreen=false;
		else Fullscreen=true;
		if(Fullscreen==true)
		{
		SDL_SetWindowFullscreen(Window, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL ); 
		SDL_SetWindowDisplayMode(Window, &DMode);
		}
		else
		{
		SDL_SetWindowFullscreen(Window,  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE ); 
		SDL_SetWindowResizable(Window, SDL_TRUE);	
		}
	}
	if(A==7)
	{
		if(TurnMode==true)TurnMode=false;
		else TurnMode=true;
	}
	
	if(A==8)
	{
		if(TurnMode==true)
		{
		  if(TurnsModeLimit==50)
		   {
			   TurnsModeLimit=100;
		   }
		   else if(TurnsModeLimit==100)
		    TurnsModeLimit=200;
		    else
		    TurnsModeLimit=50;
		}
		else 
		{
		 if(TimeModeLimit==150)
		  TimeModeLimit=300;
		  else if(TimeModeLimit==300)
		   TimeModeLimit=600;
		   else
		   TimeModeLimit=150;
		}
	}
	if(A==9)
	{
		MusicVolume=MusicVolume+13;
		if(MusicVolume>130)MusicVolume=0;
		Mix_VolumeMusic(MusicVolume);
	}
	if(A==10)
	{
		SoundVolume=SoundVolume+13;
		if(SoundVolume>130)SoundVolume=0;
		Mix_Volume(-1, SoundVolume);
	}
	if(A==11)
	{
		if(Flimmering==true)Flimmering=false;
		else Flimmering=true;
	}
	if(A==12)
	{
		if(UseHand==true)
		{
			UseHand=false;
			SDL_ShowCursor(true);
		}
		else 
		{
			UseHand=true;
			SDL_ShowCursor(false);
		}
	}
	if(A==13)
	{
		WriteSettings();
		for(int i=0; i<ButtonsActive+1; i++)
					 {
					 if(i>=MainMenuStart && i<=MainMenuEnd)	 
					  ButtonS[i].Unlocked=true;
					  else
					  ButtonS[i].Unlocked=false;
					 }
	}
	if(A==14)
	{
		WordMode++;
		if(WordMode>2)WordMode=0;
		
			for(int i=0; i<count+1; i++)
			 Vocabulary[i]="";
			count=0;
		
			std::ifstream file;
			std::string str;
			if(WordMode==0)file.open("wordbooks/reduced.txt");
			if(WordMode==2)file.open("wordbooks/extended.txt");
			if(WordMode!=0 && WordMode !=2)file.open("wordbooks/recommended.txt");
			
			while (std::getline(file, str))
			{
				count++;
				Vocabulary[count]=str;
			}
			file.close();
			int n = sizeof(Vocabulary)/sizeof(Vocabulary[0]);
			sort(Vocabulary , Vocabulary + n , compdown);
		
	}
	if(A==15)
	{
		for(int i=0; i<ButtonsActive+1; i++)
					 {
					 if(i>=MainMenuStart && i<=MainMenuEnd)	 
					  ButtonS[i].Unlocked=true;
					  else
					  ButtonS[i].Unlocked=false;
					 }
	}
	if(A==16)
	{
		if(OptionsHelp==true)OptionsHelp=false;
		else OptionsHelp=true;
	}
	
	if(A==17)
	{
		HighScoreMenuMode++;
		if(HighScoreMenuMode>1)HighScoreMenuMode=0;
	}
	
	if(A==18)
	{
		HighScoreMenuBook++;
		if(HighScoreMenuBook>2)HighScoreMenuBook=0;
	}
	if(A==19)
	{
		MenuOpen=true;
	    if(UseHand==false)SDL_ShowCursor(true);
		LockMouse=false;
		for(int i=0; i<ButtonsActive+1; i++)
			{
			if(i>=MainMenuStart && i<=MainMenuEnd)	 
			ButtonS[i].Unlocked=true;
			 else
			ButtonS[i].Unlocked=false;
			}
	}
	if(A>99 && A<126)
	 {
		 if(ButtonS[EnterHighScoreStart+2].Text.length()<11)
		 ButtonS[EnterHighScoreStart+2].Text=ButtonS[EnterHighScoreStart+2].Text+alphabet.substr(A-100, 1);
	 }
	 if(A==130)
	 {
		 if(ButtonS[EnterHighScoreStart+2].Text.length()>0)
		  ButtonS[EnterHighScoreStart+2].Text.pop_back();
	 }
	 if(A==131)
	 {
		Highscore Insert;
		Insert.Name=ButtonS[EnterHighScoreStart+2].Text;
		Insert.Score=Score;
		if(TurnMode==false)
		{
			Tables[WordMode][TurnMode][HSLimitEnter].InsertScore(Insert, MadeHighScore);
			Tables[WordMode][TurnMode][HSLimitEnter].WriteTable();
		}
		if(TurnMode==true)
		{
			Tables[WordMode][TurnMode][HSLimitEnter].InsertScore(Insert, MadeHighScore);
			Tables[WordMode][TurnMode][HSLimitEnter].WriteTable();
		}
			A=0;
		HighScoreMenuBook=WordMode;
		HighScoreMenuMode=TurnMode;
		MenuOpen=true;
		for(int i=0; i<ButtonsActive+1; i++)
			 {
			if(i>=HighScoreMenuStart && i<=HighScoreMenuEnd)	 
				ButtonS[i].Unlocked=true;
			   else
					  ButtonS[i].Unlocked=false;
				}
		 
	 }
	
	return 0;
}

int CheckButtonClick(int x, int y)
{
	for(int i=0; i<500; i++)
	{
			if(ButtonS[i].Unlocked==true)
			{
				if(x>=ButtonS[i].x && y>=ButtonS[i].y && x<=ButtonS[i].x+ButtonS[i].w && y<=ButtonS[i].y+ButtonS[i].h)
				{
					//std::cout << "Button " << i << " was smashed!!1" << std::endl;
					if(ButtonS[i].Action!=0){TriggerAction(ButtonS[i].Action); break;}
					
				}
			}
	}
	return 0;
}



SDL_Texture* loadTexture( std::string path ) { 
	SDL_Texture* newTexture = NULL; 
		SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); 
	if( loadedSurface == NULL ) { printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() ); } else { 
		newTexture = SDL_CreateTextureFromSurface( Renderer, loadedSurface ); if( newTexture == NULL ) { printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() ); } 
		
		SDL_FreeSurface( loadedSurface ); } return newTexture; }

int iniSDL(bool AntiA)
{

//Ini Video
	
	
	 if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { printf( "SDL konnte nicht initialisiert werden: %s\n", SDL_GetError() ); }
		else { 
		 if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) { printf( "Warning: Linear texture filtering not enabled!" ); }
		
		if(AntiA==true)
		{
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		}
		  for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
		{
		
		int should_be_zero = SDL_GetCurrentDisplayMode(i, &DMode);

		 if(should_be_zero != 0)
  	
 	    SDL_Log("SDL-Fehler bei der Ausgabe #%d: %s", i, SDL_GetError());

		 else
 	   

		
	   SDL_Log("Anzeige #%d: Modus: %dx%dpx @ %dhz. \n", i, DMode.w, DMode.h, DMode.refresh_rate);
		  }
 
		}
		
		
		if(Fullscreen==true)
			  Window=SDL_CreateWindow("Crumbling Words", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DMode.w, DMode.h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL ); 
		else
			Window=SDL_CreateWindow("Crumbling Words", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DMode.w, DMode.h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE ); 
		
		Renderer = SDL_CreateRenderer( Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ); 
		  if( TTF_Init() == -1 ) { printf( "SDL ttf nicht verfügbar: %s\n", TTF_GetError() ); }	   
		
		SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
		 SDL_RenderSetLogicalSize(Renderer, 1920, 1080);
		 ScreenSurface = SDL_GetWindowSurface( Window );
		if(Fullscreen==true)
			SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
	
//ini Sound!
 if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) { printf( "Ton-Wiedergabe nicht möglich :(: %s\n", Mix_GetError() );}
	Mix_AllocateChannels(48); //1 Mage | 2 Boardrumble | 3 Scorerain | 4 Endgamerumble | 5 Fanfare
			
//ini Joystick!
	   SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	   SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
		SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");
		
	
	if(UseHand==true)SDL_ShowCursor(false);
		Mix_VolumeMusic(MusicVolume);
		Mix_Volume(-1, SoundVolume);
			return 0;
		
}

int Events()
{
//Mouseman

		 int Mx1;
		 int My1;
		 int out=0;
		 int returner=0;
		 float xrel=0;
		 float yrel=0;
		 SDL_DisplayMode DM;
		 int gx, gy;
		 float offsetterY;
		 float offsetterX;
		 
		 //Adjact X/Y-Values to logical Rendersize

		
		SDL_GetWindowSize(Window, &DM.w,  &DM.h);
		SDL_RenderGetLogicalSize(Renderer, &gx, &gy);
			
		
		float DMH=DM.h;
		float DMW=DM.w;
		float GX=gx;
		float GY=gy;
		int Mx=0;
		int My=0;
		if(Fullscreen==true)
		{
		offsetterY=(float)((DMH-((DMW/GX)*GY))/2);
		offsetterX=(float)((DMW-((DMH/GY)*GX))/2);
		
		if(offsetterX<offsetterY)offsetterX=0;
		else offsetterY=0;
		
		//std::cout << "OffsetterX: " << offsetterX << " Offsetter Y: " << offsetterY << std::endl;
		xrel=(float)GX/(DMW-(offsetterX*2));
		yrel=(float)GY/(DMH-(offsetterY*2));
		
		
		 SDL_GetMouseState(&Mx1, &My1); //Get Mouse State,
		 
		  //Adjact to Logical Rendersize
		  Mx=(Mx1-offsetterX)*xrel;
		  My=(My1-offsetterY)*yrel;	
		 }
		  
		  if(Fullscreen==false) //no fullscreen?
		  {
			
			 float ratio=(float)DM.w/DM.h;
			 float nRatio=(float)1920/1080;
			 float Factor=0;
			 int mW=0;
			 int mH=0;
			  //std::cout << "Windowed. Ratio: " << ratio << " ";
			 if(ratio<nRatio)
			 {
				// std::cout << "Thinner than original."; 
				 //getting hight
				 float weidth=DM.w;
				 float adaptor=weidth/GX;
				 Factor=adaptor;
				 float height=GY*adaptor;
				 //std::cout << height << " ";
				 mH=(DM.h-height)/2;
				 //std::cout << " need to remove " << mH << " ";
			 }
			 if(ratio>nRatio) 
			 {
				 //std::cout << "Fatter than original";
				 float height=DM.h;
				 float adaptor=height/GY;
				 Factor=adaptor;
				 float weidth=GX*adaptor;
				 //std::cout << weidth << " ";
				 mW=(DM.w-weidth)/2;
				 //std::cout << " need to remove " << mW << " ";
			 }
			 SDL_GetMouseState(&Mx1, &My1);
			 Mx=((Mx1)-mW)/Factor;
			 My=((My1)-mH)/Factor;
			 //std::cout << std::endl;
		  }
		  //if Button is pressed:
		  mouseX=Mx;
		  mouseY=My;
		  if(SDL_GetMouseState(&Mx1, &My1) & SDL_BUTTON(SDL_BUTTON_LEFT))
		  {
			  
			  if(LastClick<=0)
			  {
			  LastClick=8;
			 // std::cout << "Click X: " << Mx << " Y: " << My << std::endl;
			 if(Intro==-1)
			 {
			  TheGrid.click(Mx, My);
			  CheckButtonClick(Mx, My);
			 }
			 else
			 {
				if(Intro>200)
				{
					Intro=-1; 
					MenuOpen=true;
					 if(UseHand==false)SDL_ShowCursor(true);
					 LockMouse=false;
					 for(int i=0; i<ButtonsActive+1; i++)
					 {
					 if(i>=MainMenuStart && i<=MainMenuEnd)	 
					  ButtonS[i].Unlocked=true;
					  else
					  ButtonS[i].Unlocked=false;
					 }
					 Mix_HaltMusic();
				}
				else if(Intro>1)Intro=199;
			 }
			  //CheckButtonClick(Mx, My);
			}
			  
		  }
		  else if(LastClick>0)LastClick=LastClick-2;
		  //Mouseman end
		  while( SDL_PollEvent( &event ) ){
			switch( event.type ){
      case SDL_KEYDOWN:
      {
		if(event.key.keysym.sym==SDLK_RETURN)
			{
				if(Intro==0)Intro=1;
			} 
		if(event.key.keysym.sym==SDLK_ESCAPE)
			{
				if(MenuOpen==true || Intro!=-1)
				 running=false;
				 else
				 {
					 MenuOpen=true;
					 if(UseHand==false)SDL_ShowCursor(true);
					 LockMouse=false;
					 for(int i=0; i<ButtonsActive+1; i++)
					 {
					 if(i>=MainMenuStart && i<=MainMenuEnd)	 
					  ButtonS[i].Unlocked=true;
					  else
					  ButtonS[i].Unlocked=false;
					 }
				 }
				
			} 
		if(event.key.keysym.sym==SDLK_r)
		{
			NewGame();
		}
		if(event.key.keysym.sym==SDLK_F9)
		{
			Flimmering=false;
		}
			//Add Shortkeys here
	  break;
	  case SDL_WINDOWEVENT:
	  {
	  if(event.window.event==SDL_WINDOWEVENT_CLOSE)running=false;
	  }
	  break;
	}	
}
}
return 0;
}



int ManageButtons(SDL_Renderer* rend=Renderer)
{
	if(EndGame==true && Score>ToWin)
	{
				 ButtonS[EndScreenStart].Text="GAME WON!";
				 ButtonS[EndScreenStart+1].Text="MORE!";	
	}
	if(MenuOpen==true)
	{
		ButtonS[OptionsMenuStart].Text="   Fullscreen                           ";
		if(Fullscreen==true)ButtonS[OptionsMenuStart].Text+="On";
		else ButtonS[OptionsMenuStart].Text+="Off";
		
		ButtonS[OptionsMenuStart+1].Text="   Modus                                     ";
		if(TurnMode==true)ButtonS[OptionsMenuStart+1].Text+="Turns";
		else ButtonS[OptionsMenuStart+1].Text+="Time";
		
		ButtonS[OptionsMenuStart+2].Text="   Limit                                         ";
		if(TurnMode==true)ButtonS[OptionsMenuStart+2].Text+=std::to_string(TurnsModeLimit);
		else ButtonS[OptionsMenuStart+2].Text+=std::to_string(TimeModeLimit);
		
		ButtonS[OptionsMenuStart+3].Text="   Music Volume                     ";
		for(int i=0; i<(MusicVolume/13); i++)ButtonS[OptionsMenuStart+3].Text+="I";
		
		ButtonS[OptionsMenuStart+4].Text="   Sound Volume                    ";
		for(int i=0; i<(SoundVolume/13); i++)ButtonS[OptionsMenuStart+4].Text+="I";
		
		ButtonS[OptionsMenuStart+5].Text="   Flashing                               ";
		if(Flimmering==true)ButtonS[OptionsMenuStart+5].Text+="On";
		else ButtonS[OptionsMenuStart+5].Text+="Off";
		
		ButtonS[OptionsMenuStart+6].Text="   Custom Cursor                 ";
		if(UseHand==true)ButtonS[OptionsMenuStart+6].Text+="On";
		else ButtonS[OptionsMenuStart+6].Text+="Off";
		
		ButtonS[OptionsMenuStart+8].Text="   Wordbook                 ";
		if(WordMode==0)ButtonS[OptionsMenuStart+8].Text+="Reduced";
		if(WordMode==1)ButtonS[OptionsMenuStart+8].Text+="Recommended";
		if(WordMode==2)ButtonS[OptionsMenuStart+8].Text+="Extended";
		
		if(OptionsHelp==false)
		{
		 ButtonS[OptionsMenuEnd+1].Text=" How to play:\n You are a aspiring witch in the magic school of the wicked word-wizard Allyster. He is an old magus who knows the secret to reshape the world through language.\n \n After a few months of teaching, he makes an offer. You prove your abilities to him; if you can prevail, he will make you his master pupil and successor.  Depending on the games mode, which you can select in the options menu, you either have a limited amount of time or moves to convice Allyster of your abilities. Use your mouse to select a glyph on your magic board. Click on another glyph one to swap it with the one that you have selected. As soon you combine a valid word (consisting of 5 or more letters), the letters that form the word will be dissolved and your score for Allyster's test will be increased depending on the words length. New glyphs will appear at the side of the board and push their neighboring tiles into the gap. If these glyphs create new words, they will also be dissolved and a multiplier will be applied.\nBut be warned: As you are a novice word magus, there are many spellwords that you have likely never heard in your life and that might disturb your plans.\n Allyster also has words in mind that he wants you to place; creating these words will produce an additional bonus that will permanently increase for each word that you successfully create (+50% for the first, +100% for the second, +150% for the third and so on). These words are also influenced by your chain multiplier.\n Depending on your settings, you will have to score 1250/2500/5000 Points to convince Allyster of your skill!";
		 ButtonS[OptionsMenuEnd+3].Text="   Options Help";
		}
		if(OptionsHelp==true)
		{
		 ButtonS[OptionsMenuEnd+1].Text=" Options:\n Fullscreen: Toggle Fullscreen On/Off. \n Game Mode: Turn- or time-limited. Using the turn-limit is a more relaxed, strategic experience.\n Limit: The time- or turn-limit, depending on your chosen game mode. There are three settings available for both modes.\n Music/Sound: Volume of music/sound effects.\nFlashing: Flashing lights can be turned on and off; turning them off is strongly recommended for people with photosensitiv epilepsy. Note that these effects can also be turned off ingame by pressing F9.\n Custom Cursor: Turn the hand that replaces your systems native cursor on or off. The ingame cursor’s update frequency is limited by the game’s framerate, so the native cursor might feel more fluent.\n Wordbook: Besides the recommended setting there is also an extended and a reduced word list available. The extended list covers 3,5 times more words than the recommended list and is more likely to contain exotic words. The reduced list is an attempt to represent everyday vernacular. Exotic words are likely not to be included.";
		 ButtonS[OptionsMenuEnd+3].Text="   Game Help";
		}
		
		if(HighScoreMenuBook==0) //Reduced
		{
			ButtonS[HighScoreMenuStart].Text="HIGHSCORES - REDUCED WORDLIST";
		}
		if(HighScoreMenuBook==1) //Reco
		{
			ButtonS[HighScoreMenuStart].Text="HIGHSCORES - RECOMMENDED WORDLIST";
		}
		if(HighScoreMenuBook==2) //Reduced
		{
			ButtonS[HighScoreMenuStart].Text="HIGHSCORES - EXTENDED WORDLIST";
		}
		if(HighScoreMenuMode==0)
		{
			ButtonS[HighScoreMenuStart+1].Text="150 sec";
			ButtonS[HighScoreMenuStart+2].Text="300 sec";
			ButtonS[HighScoreMenuStart+3].Text="600 sec";
		}
		if(HighScoreMenuMode==1)
		{
			ButtonS[HighScoreMenuStart+1].Text="50 turns";
			ButtonS[HighScoreMenuStart+2].Text="100 turns";
			ButtonS[HighScoreMenuStart+3].Text="200 turns";
		}
		
		ButtonS[HighScoreMenuStart+4].Text=Tables[HighScoreMenuBook][HighScoreMenuMode][0].genContent();
		ButtonS[HighScoreMenuStart+5].Text=Tables[HighScoreMenuBook][HighScoreMenuMode][1].genContent();
		ButtonS[HighScoreMenuStart+6].Text=Tables[HighScoreMenuBook][HighScoreMenuMode][2].genContent();
		
	}
	if(MenuOpen==false)
	{
		ButtonS[7].Text="";
		ButtonS[8].Text="";
		ButtonS[9].Text="";
		ButtonS[10].Text="";
		CountAlpha ca;
		ca=TheGrid.countGlyphes();
		for(int i=0; i<7; i++)
		 ButtonS[7].Text=ButtonS[7].Text+"   "+alphabet.substr(i, 1) + "   " + std::to_string(ca.AAray[i]) + "\n";
		for(int i=7; i<14; i++)
		 ButtonS[8].Text=ButtonS[8].Text+"   "+alphabet.substr(i, 1) + "   " + std::to_string(ca.AAray[i]) + "\n";
		for(int i=14; i<21; i++)
		 ButtonS[9].Text=ButtonS[9].Text+"   "+alphabet.substr(i, 1) + "   " + std::to_string(ca.AAray[i]) + "\n";
		for(int i=21; i<26; i++)
		 ButtonS[10].Text=ButtonS[10].Text+"   "+alphabet.substr(i, 1) + "   " + std::to_string(ca.AAray[i]) + "\n";
	}
	if(ScoreShower<Score)ScoreShower=ScoreShower+(((Score-ScoreShower)/50)+0.1);
	{
		if(((float)Score-ScoreShower)<1)ScoreShower=Score;
		if(ScoreShower==Score)Mix_HaltChannel(3);
		int Shower=round(ScoreShower);
		ButtonS[2].Text=" Score " + std::to_string(Shower);
	}
	
	
	
	ButtonS[3].Text= " Time " + std::to_string(TimeLeft);
	if(TurnMode==true)ButtonS[3].Text= " Moves " + std::to_string(TurnsLeft);
	if(BlinkingScore>0)
		 {
			 BlinkingScore--;
		 	  ButtonS[2].BGColor.r=50+(rand()%150);
			  //ButtonS[2].BGColor.g=10+(rand()%30);
			  ButtonS[2].BGColor.b=50+(rand()%160);
		 }
		 else
		 {
			  ButtonS[2].BGColor.r=50;
			  ButtonS[2].BGColor.g=80;
			  ButtonS[2].BGColor.b=50;
		  }
	for(int i=0; i<100; i++)
	{
			if(ButtonS[i].Unlocked==true)
			{
				ButtonS[i].Draw(Renderer);
			}
	}
	return 0;
}

int DefInterface()
{
	int b=1;
	ButtonS[b].Unlocked=true;
	ButtonS[b].x=((GridW+1)*TileSize)+450;
	ButtonS[b].y=10;
	ButtonS[b].w=380;
	ButtonS[b].h=385;
	ButtonS[b].Action=0;
	ButtonS[b].fontSize=50;
	ButtonS[b].Text="Can you spell \n FOOL?";
	ButtonS[b].TexMaxSize=300;
	
	b++;
	
	ButtonS[b].Unlocked=true;
	ButtonS[b].x=((GridW+1)*TileSize)+450;
	ButtonS[b].y=410;
	ButtonS[b].w=380;
	ButtonS[b].h=80;
	ButtonS[b].fontSize=63;
	ButtonS[b].Action=0;
	ButtonS[b].Text=" Points 0";
	
	b++;
	
	ButtonS[b].Unlocked=true;
	ButtonS[b].x=((GridW+1)*TileSize)+450;
	ButtonS[b].y=505;
	ButtonS[b].w=380;
	ButtonS[b].h=80;
	ButtonS[b].fontSize=63;
	ButtonS[b].Action=0;
	ButtonS[b].Text=" Time 0";
	if(TurnMode==true)ButtonS[b].Text=" Turns 0";
	
	b++;
	
	ButtonS[b].Unlocked=true;
	ButtonS[b].x=((GridW+1)*TileSize)+10;
	ButtonS[b].y=610;
	ButtonS[b].w=420;
	ButtonS[b].BGColor.r=50-20;
	ButtonS[b].BGColor.g=80-20;
	ButtonS[b].BGColor.b=50-20;
	ButtonS[b].h=60;
	ButtonS[b].fontSize=48;
	ButtonS[b].Action=0;
	ButtonS[b].Text=" Last Words";
	
	b++;
	
	ButtonS[b].Unlocked=true;
	ButtonS[b].x=((GridW+1)*TileSize)+10;
	ButtonS[b].y=610+60;
	ButtonS[b].w=420;
	ButtonS[b].h=400;
	ButtonS[b].TexMaxSize=400;
	ButtonS[b].fontSize=50;
	ButtonS[b].Action=0;
	ButtonS[b].Text="";
	
	b++;
	
	ButtonS[b].Unlocked=true;
	ButtonS[b].x=((GridW+1)*TileSize)+450;
	ButtonS[b].y=610;
	ButtonS[b].w=380;
	ButtonS[b].BGColor.r=50-20;
	ButtonS[b].BGColor.g=80-20;
	ButtonS[b].BGColor.b=50-20;
	ButtonS[b].h=60;
	ButtonS[b].fontSize=48;
	ButtonS[b].Action=0;
	ButtonS[b].Text=" Available";
	
	b++;
	
	ButtonS[b].Unlocked=true;
	ButtonS[b].x=((GridW+1)*TileSize)+450;
	ButtonS[b].y=610+60;
	ButtonS[b].w=95;
	ButtonS[b].h=300;
	ButtonS[b].TexMaxSize=400;
	ButtonS[b].fontSize=35;
	ButtonS[b].Action=0;
	ButtonS[b].Text="";
	
	b++;
	
	ButtonS[b].Unlocked=true;
	ButtonS[b].x=((GridW+1)*TileSize)+450+95;
	ButtonS[b].y=610+60;
	ButtonS[b].w=95;
	ButtonS[b].h=300;
	ButtonS[b].TexMaxSize=400;
	ButtonS[b].fontSize=35;
	ButtonS[b].Action=0;
	ButtonS[b].Text="";
	
	b++;
	
	ButtonS[b].Unlocked=true;
	ButtonS[b].x=((GridW+1)*TileSize)+450+190;
	ButtonS[b].y=610+60;
	ButtonS[b].w=95;
	ButtonS[b].h=300;
	ButtonS[b].TexMaxSize=400;
	ButtonS[b].fontSize=35;
	ButtonS[b].Action=0;
	ButtonS[b].Text="";
	
	b++;
	
	ButtonS[b].Unlocked=true;
	ButtonS[b].x=((GridW+1)*TileSize)+450+190+95;
	ButtonS[b].y=610+60;
	ButtonS[b].w=95;
	ButtonS[b].h=300;
	ButtonS[b].TexMaxSize=400;
	ButtonS[b].fontSize=35;
	ButtonS[b].Action=0;
	ButtonS[b].Text="";
	
	b++;
	
	ButtonS[b].Unlocked=true;
	ButtonS[b].x=((GridW+1)*TileSize)+450+15+200+50;
	ButtonS[b].y=985+15;
	ButtonS[b].w=115;
	ButtonS[b].BGColor.r=30;
	ButtonS[b].BGColor.g=30;
	ButtonS[b].BGColor.b=30;
	ButtonS[b].h=65;
	ButtonS[b].fontSize=50;
	ButtonS[b].Action=19;
	ButtonS[b].Text=" MENU";
	
	b++;
	EndScreenStart=b;
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=((GridW+1)*TileSize)/4;
	ButtonS[b].y=300;
	ButtonS[b].w=((GridW+1)*TileSize)/2;
	ButtonS[b].h=200;
	ButtonS[b].TexMaxSize=0;
	ButtonS[b].fontSize=100;
	ButtonS[b].Action=0;
	ButtonS[b].BGColor.a=0;
	ButtonS[b].FontColor={255, 255, 255, 255};
	ButtonS[b].Text="GAME OVER";
	
	b++;
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=((GridW+1)*TileSize)/4;
	ButtonS[b].y=600;
	ButtonS[b].w=((GridW+1)*TileSize)/2;
	ButtonS[b].h=100;
	ButtonS[b].TexMaxSize=0;
	ButtonS[b].fontSize=50;
	ButtonS[b].Action=1;
	ButtonS[b].BGColor.a=0;
	ButtonS[b].FontColor={255, 255, 255, 255};
	ButtonS[b].Text="Retry";
	
	b++;
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=((GridW+1)*TileSize)/4;
	ButtonS[b].y=750;
	ButtonS[b].w=((GridW+1)*TileSize)/2;
	ButtonS[b].h=100;
	ButtonS[b].TexMaxSize=0;
	ButtonS[b].fontSize=50;
	ButtonS[b].Action=19;
	ButtonS[b].BGColor.a=0;
	ButtonS[b].FontColor={255, 255, 255, 255};
	ButtonS[b].Text="Menu";
	
	EndScreenEnd=b;
	
	b++;
	EnterHighScoreStart=b;
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=((GridW+1)*TileSize)/4;
	ButtonS[b].y=300;
	ButtonS[b].w=((GridW+1)*TileSize)/2;
	ButtonS[b].h=200;
	ButtonS[b].TexMaxSize=0;
	ButtonS[b].fontSize=100;
	ButtonS[b].Action=0;
	ButtonS[b].BGColor.a=0;
	ButtonS[b].FontColor={255, 255, 255, 255};
	ButtonS[b].Text="NEW HIGHSCORE";

	
	b++;
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=((GridW+1)*TileSize)/4;
	ButtonS[b].y=450;
	ButtonS[b].w=((GridW+1)*TileSize)/2;
	ButtonS[b].h=100;
	ButtonS[b].TexMaxSize=0;
	ButtonS[b].fontSize=40;
	ButtonS[b].Action=0;
	ButtonS[b].BGColor.a=0;
	ButtonS[b].FontColor={255, 255, 255, 255};
	ButtonS[b].Text="Enter Name";
	

	b++;
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=((GridW+1)*TileSize)/4;
	ButtonS[b].y=550;
	ButtonS[b].w=((GridW+1)*TileSize)/2;
	ButtonS[b].h=100;
	ButtonS[b].TexMaxSize=0;
	ButtonS[b].fontSize=70;
	ButtonS[b].Action=0;
	ButtonS[b].BGColor.a=0;
	ButtonS[b].FontColor={255, 255, 255, 255};
	ButtonS[b].Text="";
	b++;
	
	
	for(int i=0; i<26; i++)
	{
		div_t divor=div(i, 13);
			ButtonS[b].Unlocked=false;
			ButtonS[b].x=100+(divor.rem*60);
			ButtonS[b].y=750+(divor.quot*60);
			ButtonS[b].w=60;
			ButtonS[b].h=60;
			ButtonS[b].TexMaxSize=0;
			ButtonS[b].fontSize=40;
			ButtonS[b].Action=100+i;
			ButtonS[b].BGColor.a=230;
			ButtonS[b].NoBorder=false;
			ButtonS[b].Solid=false;
			ButtonS[b].FontColor={255, 255, 255, 255};
			ButtonS[b].Text="    "+alphabet.substr(i, 1);
			b++;
	}
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=40;
	ButtonS[b].y=900;
	ButtonS[b].w=400;
	ButtonS[b].h=100;
	ButtonS[b].TexMaxSize=0;
	ButtonS[b].fontSize=70;
	ButtonS[b].Action=130;
	ButtonS[b].BGColor.a=0;
	ButtonS[b].FontColor={255, 255, 255, 255};
	ButtonS[b].Text="Delete";
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=1080-440;
	ButtonS[b].y=900;
	ButtonS[b].w=400;
	ButtonS[b].h=100;
	ButtonS[b].TexMaxSize=0;
	ButtonS[b].fontSize=70;
	ButtonS[b].Action=131;
	ButtonS[b].BGColor.a=0;
	ButtonS[b].FontColor={255, 255, 255, 255};
	ButtonS[b].Text="              Confirm";
	EnterHighScoreEnd=b;
	b++;

	MainMenuStart=b;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=200+(b-MainMenuStart)*150;
	ButtonS[b].w=1920/4;
	ButtonS[b].h=130;
	ButtonS[b].fontSize=100;
	ButtonS[b].Action=1;
	ButtonS[b].Text="   New Game";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=200+(b-MainMenuStart)*150;
	ButtonS[b].w=1920/4;
	ButtonS[b].h=130;
	ButtonS[b].fontSize=100;
	ButtonS[b].Action=2;
	ButtonS[b].Text="   Highscores";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=200+(b-MainMenuStart)*150;
	ButtonS[b].w=1920/4;
	ButtonS[b].h=130;
	ButtonS[b].fontSize=100;
	ButtonS[b].Action=3;
	ButtonS[b].Text="   Help";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=200+(b-MainMenuStart)*150;
	ButtonS[b].w=1920/4;
	ButtonS[b].h=130;
	ButtonS[b].fontSize=100;
	ButtonS[b].Action=4;
	ButtonS[b].Text="   Options";
	
	
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=200+(b-MainMenuStart)*150;
	ButtonS[b].w=1920/4;
	ButtonS[b].h=130;
	ButtonS[b].fontSize=100;
	ButtonS[b].Action=5;
	ButtonS[b].Text="   Quit";
	
	MainMenuEnd=b;
	b++;
	OptionsMenuStart=b;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=100+(b-OptionsMenuStart)*120;
	ButtonS[b].w=1300;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=6;
	ButtonS[b].Text="   Fullscreen";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=100+(b-OptionsMenuStart)*120;
	ButtonS[b].w=1300;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=7;
	ButtonS[b].Text="   Modus";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=100+(b-OptionsMenuStart)*120;
	ButtonS[b].w=1300;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=8;
	ButtonS[b].Text="   Limit";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=100+(b-OptionsMenuStart)*120;
	ButtonS[b].w=1300;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=9;
	ButtonS[b].Text="   Music";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=100+(b-OptionsMenuStart)*120;
	ButtonS[b].w=1300;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=10;
	ButtonS[b].Text="   Sound";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=100+(b-OptionsMenuStart)*120;
	ButtonS[b].w=1300;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=11;
	ButtonS[b].Text="   Flashing";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=200;
	ButtonS[b].y=100+(b-OptionsMenuStart)*120;
	ButtonS[b].w=1300;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=12;
	ButtonS[b].Text="   Custom Cursor";
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=180;
	ButtonS[b].y=100+(b-OptionsMenuStart)*120;
	ButtonS[b].w=400;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=13;
	ButtonS[b].Text="   Back";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=980;
	ButtonS[b].y=100+(b-OptionsMenuStart-1)*120;
	ButtonS[b].w=900;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=14;
	ButtonS[b].Text="   Wordbook";
	
	OptionsMenuEnd=b;
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=10;
	ButtonS[b].y=10;
	ButtonS[b].w=1900;
	ButtonS[b].h=900;
	ButtonS[b].TexMaxSize=900;
	ButtonS[b].fontSize=50;
	ButtonS[b].Action=0;
	//ButtonS[b].Text=" How to play:\n You are a aspiring witch in the magic school of the wicked wordmage allyster, an old magus who knows the secret to reshape the world through language.\n \n After a few months he offers you to prove your ability to him - if you can prevail, he will make you his master pupil and successor.  Depending on the games modi (selectable in the options menu) you have a limited amount of time or moves to convice Allyster of your ability. Use your mouse to select Glyphes on your magic board. Click another one to swap it with the selected. As soon as a valid spell word is placed on the table, the forming tiles will be dissolved - and your score for Allysters test will be increased depending on the words length - new Glyph tiles will then appear at the side of the board and push their neighboring tiles in the place of the missing ones - if these movements create new words, these will also be dissolved - with multiplier applied that will be increased by one for every additional word of such a chain.\n\n Allyster has words in mind that he wants you to place; creating these words will produce an additional bonus that will permanently increase for every of these words that you successfully create (+50% for the first, +100% for the seconds, +150% for the third and so on) and that is also influenced by your chain multiplier.\n Gain 350/500/1000 Points in short/medium/long mode to convince Allyster of your skill!";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=10;
	ButtonS[b].y=950;
	ButtonS[b].w=600;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=15;
	ButtonS[b].Text="   Back";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=1920-610;
	ButtonS[b].y=950;
	ButtonS[b].w=600;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=16;
	ButtonS[b].Text="   Options Help";
	
	b++;
	HighScoreMenuStart=b;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=15;
	ButtonS[b].y=10;
	ButtonS[b].w=1890;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=0;
	ButtonS[b].BGColor.r=55;
	ButtonS[b].BGColor.b=55;
	ButtonS[b].BGColor.g=55;
	ButtonS[b].Text="   Highscores";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=15;
	ButtonS[b].y=110;
	ButtonS[b].w=630;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=75;
	ButtonS[b].Action=0;
	ButtonS[b].BGColor.r=30;
	ButtonS[b].BGColor.b=30;
	ButtonS[b].BGColor.g=70;
	ButtonS[b].Text="   Limit 1";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=15+630;
	ButtonS[b].y=110;
	ButtonS[b].w=630;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=75;
	ButtonS[b].Action=0;
	ButtonS[b].BGColor.r=35;
	ButtonS[b].BGColor.b=35;
	ButtonS[b].BGColor.g=40;
	ButtonS[b].Text="   Limit 2";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=15+1260;
	ButtonS[b].y=110;
	ButtonS[b].w=630;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=75;
	ButtonS[b].Action=0;
	ButtonS[b].BGColor.r=30;
	ButtonS[b].BGColor.b=30;
	ButtonS[b].BGColor.g=70;
	ButtonS[b].Text="   Limit 3";
	
		b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=15;
	ButtonS[b].y=210;
	ButtonS[b].w=630;
	ButtonS[b].h=750;
	ButtonS[b].fontSize=60;
	ButtonS[b].Action=0;
	ButtonS[b].Text="   Table 1";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=15+630;
	ButtonS[b].y=210;
	ButtonS[b].w=630;
	ButtonS[b].h=750;
	ButtonS[b].fontSize=60;
	ButtonS[b].Action=0;
	ButtonS[b].BGColor.r=55;
	ButtonS[b].BGColor.b=55;
	ButtonS[b].BGColor.g=40;
	ButtonS[b].Text="   Table 2";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=15+1260;
	ButtonS[b].y=210;
	ButtonS[b].w=630;
	ButtonS[b].h=750;
	ButtonS[b].fontSize=60;
	ButtonS[b].Action=0;
	ButtonS[b].Text="   Table 3";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=30;
	ButtonS[b].y=975;
	ButtonS[b].w=600;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=15;
	ButtonS[b].Text="   Back";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=15+630+15;
	ButtonS[b].y=975;
	ButtonS[b].w=600;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=17;
	ButtonS[b].Text="   Change Mode";
	
	b++;
	
	ButtonS[b].Unlocked=false;
	ButtonS[b].x=15+630+15+630;
	ButtonS[b].y=975;
	ButtonS[b].w=600;
	ButtonS[b].h=100;
	ButtonS[b].fontSize=80;
	ButtonS[b].Action=18;
	ButtonS[b].Text="   Change Wordlist";
	
	
	HighScoreMenuEnd=b;
	ButtonsActive=b;
	
	return 0;
}

int loadImages(char* bildliste)
{
			texturesUsed=1;
			std::ifstream file;
			file.open(bildliste);
			std::string str; 
			while (std::getline(file, str))
			{
			    
			  
  			   Images[texturesUsed] = loadTexture( str );

			   texturesUsed++;
			 }
			file.close();
		
		return 0;
}

int DrawMage(int x, int y)
{
	LastAction++;
	
	int PriorMageState=MageState;
	
	MageState=2;
	if(LastAction>800 && BGFlimmer<=-200 && AlphaBG<50 && Awed==false)MageState=3;
	if(ActionsWOMerit>8 && BGFlimmer<=-200 && AlphaBG<50  && Awed==false)MageState=4;
	if(Pissed>0)
	{
		Pissed--;
		if(TauntOrShock<0 )TauntOrShock=0;
		if(Awed==false)MageState=5;
	}
	if(Pissed<0 && Awed==false && TauntOrShock<=0)
	{
		Pissed++;
		if(TauntOrShock<0 )TauntOrShock=0;
		if(Awed==false)MageState=5;
	}
	if(TauntOrShock<0 )
	{
		TauntOrShock++;
		if(Awed==false && Pissed==0)MageState=8;
	}
	
	if(TauntOrShock>0 && BGFlimmer<=-75) //
	{
		TauntOrShock--;
		MageState=7;
		Awed=true;
	}
	
	if(BGFlimmer>-75)
	{
		MageState=6;
		Pissed=0;
	}
	
	if(PriorMageState!=MageState && EndGame==false)
	 {
		 if(MageState==2)
		 {
			 int r=rand()%10;
			 if(r==0)ButtonS[1].Text="Magic destroys mind and body.\nI want you to spell...\n";
			 if(r==1){ButtonS[1].Text="Above the gemmed azure is\nThe naked splendor of Nuit\nSHe bends in ecstasy to kiss\nThe secred ardours of Hadit\nThe winged globe, the starry blue\nAre mine, O Chant";}
			 if(r==2)ButtonS[1].Text="Love is the law, love under will.\n My will is that you spell";
			 if(r==3)ButtonS[1].Text="Come forth, o children, under the stars, and take your fill of love!.\nSpell";
			 if(r==4)ButtonS[1].Text="Aiwass, i call thee ... I feel the connection. Fast, spell \n";
			 if(r==5)ButtonS[1].Text="Liberty stirs once more in the womb of Time. \n";
			 if(r==6)ButtonS[1].Text="I am above you and in you. My ecstasy is in yours. My joy is to see you spell";
			 if(r==7)ButtonS[1].Text="Now, therefore, I am known to ye by my name Nuit, and to him by the name of";
			 if(r==8)ButtonS[1].Text="Also the mantras and spells; the obeah and the wanga; the work of the wand and the work of the sword; these he shall learn and teach. The magic word is ";
			 if(r==9)ButtonS[1].Text="Abrogate are all rituals, all ordeals, all words and signs. Ra-Hoor-Khuit hath taken his seat in the East at the Equinox of the Gods; and let Asar be with Isa, who also are one. Spell";
		 }
		 
		 if(MageState==3)
		 {
			 int r=rand()%9;
			 if(r==0)ButtonS[1].Text="Would you mind to do something?\nThis is boring!\n I would like it if you spell\n";
			 if(r==1)ButtonS[1].Text="Do the letters make you anxious, or what is your Problem?\nSpell\n";
			 if(r==2)ButtonS[1].Text="Do something or I shall turn you into a frog.\nSpell\n";
			 if(r==3)ButtonS[1].Text="I should rather tutor a snail...\nSpell\n";
			 if(r==4)ButtonS[1].Text="My time is precious, you worm. Do something!\n Maybe spell\n";
			 if(r==5)ButtonS[1].Text="Take letters, move them, make a word - it is not that hard after all!\n Spell\n";
			 if(r==6)ButtonS[1].Text="I had high expectations. Seems like I wasted my energy on a dick-eye. \n Try to spell\n";
			 if(r==7)ButtonS[1].Text="Do you mind to SPELL SOMETHING? Best would be\n";
			 if(r==8)ButtonS[1].Text="You have some nerves to let somebody like ME wait. Spell\n";
		 }
		 
		 if(MageState==4)
		 {
			 int r=rand()%9;
			 if(r==0)ButtonS[1].Text="What are you doing? This is bogus!\nTry to spell\n";
			 if(r==1)ButtonS[1].Text="Are you confused by the size of the table or something?? Spell\n";
			 if(r==2)ButtonS[1].Text="You are the worst novice i ever had. Spell\n";
			 if(r==3)ButtonS[1].Text="I should rather tutor a MONKEY!\nSpell\n";
			 if(r==4)ButtonS[1].Text="You FOOL! You are intended to make words, don't you know?\n Spell\n";
			 if(r==5)ButtonS[1].Text="Doing this myself would be less stressful.\n Make yourself useful!\nSpell\n";
			 if(r==6)ButtonS[1].Text="I've had high expectations. Seems like I wasted my energy on a dick-eye.\n Try to spell\n";
			 if(r==7)ButtonS[1].Text="Oh come on. What shall this represent? Spell\n";
			 if(r==8)ButtonS[1].Text="This is frustrating. Do something productive! Spell\n";
		 }
		 
		 if(MageState==5)
		 {
			 if(Pissed>0)
			 {
			 int so=rand()%4;
			 if(so==0)Mix_PlayChannel( 1, Sounds[5], 0 );	 
			 if(so==1)Mix_PlayChannel( 1, Sounds[7], 0 );	
			 if(so==2)Mix_PlayChannel( 1, Sounds[10], 0 );
			 if(so==3)Mix_PlayChannel( 1, Sounds[19], 0 );
			 int r=rand()%7;
			 if(r==0)ButtonS[1].Text="Again? Don't you know any other Words?\n Then maybe just Spell\n";
			 if(r==1)ButtonS[1].Text="What are you thinking? You just did " + Pissword + "\nSpell\n";
			 if(r==2)ButtonS[1].Text="Yet again? Do you try to fool me? Spell\n";
			 if(r==3)ButtonS[1].Text="Again "+Pissword+"? I should rather tutor a MONKEY!\nSpell\n";
			 if(r==4)ButtonS[1].Text="You FOOL! Make different words, not always the same!\n Spell\n";
			 if(r==5)ButtonS[1].Text="Stop wasting my time. you did "+Pissword+" already.\nSpell\n";
			 if(r==6)ButtonS[1].Text="Enough of Because! Be he damned for a dog! \nSpell";
			 }
			 if(Pissed<0)
			 {
			 int so=rand()%4;
			 if(so==0)Mix_PlayChannel( 1, Sounds[5], 0 );	 
			 if(so==1)Mix_PlayChannel( 1, Sounds[7], 0 );	
			 if(so==2)Mix_PlayChannel( 1, Sounds[10], 0 );
			 if(so==3)Mix_PlayChannel( 1, Sounds[19], 0 );
			 int r=rand()%6;
			 if(r==0)ButtonS[1].Text="WRONG, WRONG, WRONG. I want you to do\n";
			 if(r==1)ButtonS[1].Text="Are you trying to make fun of me? This is a grave error.\nSpell\n";
			 if(r==2)ButtonS[1].Text="Are you dumb? I want you to spell " + PowerWord + " yet you spell " + Pissword + ". stop wasting my time and finally write\n";
			 if(r==3)ButtonS[1].Text=Pissword+"? I should rather tutor a MONKEY!\nSpell\n";
			 if(r==4)ButtonS[1].Text=PowerWord +" Not " + Pissword+", you stupid donkey\nSpell";
			 if(r==5)ButtonS[1].Text=Pissword+"? Are you doing this in purpose?\nSpell\n";
			 }
		 }
		 
		 if(MageState==6)
		 {
			 int so=rand()%5;
			 if(so==0)Mix_PlayChannel( 1, Sounds[6], 0 );	 
			 if(so==1)Mix_PlayChannel( 1, Sounds[11], 0 );	
			 if(so==2)Mix_PlayChannel( 1, Sounds[12], 0 );
			 if(so==3)Mix_PlayChannel( 1, Sounds[14], 0 );
			 if(so==4)Mix_PlayChannel( 1, Sounds[16], 0 );
			 int r=rand()%9;
			 if(r==0)ButtonS[1].Text="HARHARHAR. WONDERFULL!";
			 if(r==1)ButtonS[1].Text="YES. YES. YEEEEES!";
			 if(r==2)ButtonS[1].Text="MORE- I NEEED MORE!!";
			 if(r==3)ButtonS[1].Text="THE AEON OF HORUS IS NEIGH!";
			 if(r==4)ButtonS[1].Text="GREAT. MY LIGHT SHALL COME OVER YOU.";
			 if(r==5)ButtonS[1].Text="BURN ABOUT THEIR BROWS, O SPLENDROUS SERPENT";
			 if(r==6)ButtonS[1].Text="I AM NUIT, AND MY WORD IS SIX AND FIFTY\n";
			 if(r==7)ButtonS[1].Text="YAHAHAHAHAHAHAHAR";
			 if(r==8)ButtonS[1].Text="THE YEAR IS ONE\n";
		 }
		  if(MageState==7)
		 {
			
			 int so=rand()%3;
			 if(so==0)Mix_PlayChannel( 1, Sounds[13], 0 );	 
			 if(so==1)Mix_PlayChannel( 1, Sounds[17], 0 );	
			 if(so==2)Mix_PlayChannel( 1, Sounds[22], 0 );
			 int r=rand()%9;
			 if(r==0)ButtonS[1].Text="Impressive! I didn't expected you could pull something like this!\nNow try";
			 if(r==1)ButtonS[1].Text="Splendid. What art!\nNow do";
			 if(r==2)ButtonS[1].Text="When have you become this strong?\nNow try";
			 if(r==3)ButtonS[1].Text="Colossal! Colossal! \nNow do";
			 if(r==4)ButtonS[1].Text="I'm in awe. Together we might rule this world.\nNext Word is";
			 if(r==5)ButtonS[1].Text="Gigantic - what rare power!\nGo on. The Next word is";
			 if(r==6)ButtonS[1].Text="Maybe you are the herald of horuz?\nNext Word is";
			 if(r==7)ButtonS[1].Text="Oh, what ART! \nNext Word is";
			 if(r==8)ButtonS[1].Text="What rare Talent!\nCan you do";
		 }
		 
		 if(MageState==8)
		 {
			 int so=rand()%3;
			 if(so==0)Mix_PlayChannel( 1, Sounds[2], 0 );	 
			 if(so==1)Mix_PlayChannel( 1, Sounds[5], 0 );	
			 if(so==2)Mix_PlayChannel( 1, Sounds[8], 0 );
			 int r=rand()%5;
			 if(r==0)ButtonS[1].Text="HOHOHO. Is this all you can do? \nSPELL";
			 if(r==1)ButtonS[1].Text=LastWords[0]+"? VERY IMPRESSING, HARHAR. \nNow make";
			 if(r==2)ButtonS[1].Text="I HAVE SEEN DOGS WHO CAN DO BETTER THAN THAT.\n Try";
			 if(r==3)ButtonS[1].Text="Pathetic. When do you plan to begin?\nIf you do, make";
			 if(r==4)ButtonS[1].Text="Hahaha. Are you serious?\nDo";
			 if(r==5)ButtonS[1].Text=LastWords[0]+" HILARIOUS. AND YOU WANT TO BE A MAGE?\nTry";
			 if(r==6)ButtonS[1].Text="I AM NUIT, AND YOU ARE MISERABLE\nTry";
			 if(r==7)ButtonS[1].Text="BWHAHAHAHAHAHA\nMa-Make";
			 if(r==8)ButtonS[1].Text="Is this all that you got?\nTry";
		 }
		 

		 
	 }
	 if(EndGame==true)
		 {
			 if(Score>=ToWin)
			 {
				 if(EndTaunt==false)
				 {
				  int so=rand()%3;
				  if(so==0)Mix_PlayChannel( 1, Sounds[24], 0 );	 
			      if(so==1)Mix_PlayChannel( 1, Sounds[18], 0 );	
			      if(so==2)Mix_PlayChannel( 1, Sounds[20], 0 );
			      EndTaunt=true;
				 }
				 MageState=6;
				 ButtonS[1].Text="WONDERFUL! YOU MADE IT.";
				 if(MadeHighScore!=-1)ButtonS[1].Text=ButtonS[1].Text+"\n\nALSO, CONGRATULATIONS ON YOUR HIGHSCORE!";
			 }
			 else if(Score>=ToWin/2)
			 {
				 if(EndTaunt==false)
				 {
				  int so=rand()%2;
				  if(so==0)Mix_PlayChannel( 1, Sounds[18], 0 );	 
			      if(so==1)Mix_PlayChannel( 1, Sounds[15], 0 );	
			      EndTaunt=true;
				 }
				 MageState=3;
				 ButtonS[1].Text="NOT BAD AT ALL. BUT STILL - NOT GOOD ENOUGH!";
				 if(MadeHighScore!=-1)ButtonS[1].Text=ButtonS[1].Text+"\n\nBUT SEEMINGLY, STILL GOOD ENOUGH FOR A HIGHSCORE.";
			 }
			 else
			 {
				  int so=rand()%3;
				  if(EndTaunt==false)
				  {
				  if(so==0)Mix_PlayChannel( 1, Sounds[19], 0 );	 
			      if(so==1)Mix_PlayChannel( 1, Sounds[15], 0 );	
			      if(so==2)Mix_PlayChannel( 1, Sounds[10], 0 );	
			      EndTaunt=true;
				 }
				MageState=4;
				ButtonS[1].Text="NOT QUITE ENOUGH... TRY HARDER NEXT TIME!";
				if(MadeHighScore!=-1)ButtonS[1].Text=ButtonS[1].Text+"\n\nI DON'T GET HOW THIS COULD BE ENOUGH FOR A HIGHSCORE.";
			 }
			 
			 
		 }
	 SDL_Rect Reader;
	 SDL_Rect Writer;
	 

	 
	 
	 

			SDL_QueryTexture(ButtonS[1].TitleTex, NULL, NULL, &Writer.x, &Writer.y);
			SDL_QueryTexture(PWordTex, NULL, NULL, &Writer.w, &Writer.h);
			Writer.x=ButtonS[1].x;
			Writer.y=Writer.y+ButtonS[1].y;
			if(MageState!=6 && EndGame==false)
			SDL_RenderCopy( Renderer, PWordTex, NULL, &Writer);
	
			Writer.x=x;
			Writer.y=y;
			Writer.h=600;
			Writer.w=440;

			int Alpher=0;
			SDL_RenderCopy( Renderer, Images[1], NULL, &Writer);
			if(AlphaBG>0)
			{
				//Move BG
					if(BGX<5){BGAngle=rand()%180; BGX=5;}
					if(BGX>1980){BGAngle=180+(rand()%180); BGX=1980;}
					if(BGY<5){BGAngle=90+(rand()%180); BGY=5;}
					if(BGY>1500){BGAngle=270+(rand()%180); BGY=1500;}
				    float cAngle=((BGAngle*M_PI)/180);
					BGX=BGX+(cos(cAngle)*(AlphaBG/100));
					BGY=BGY+(sin(cAngle)*(AlphaBG/100));
					
						 Reader.x=round(BGX/10)*10;
						 Reader.y=round(BGY/10)*10;
						 Reader.h=570;
						 Reader.w=410;
					
				AlphaBG=AlphaBG*(0.9995);
				if(AlphaBG>255)Alpher=255;
				else Alpher=floor(AlphaBG);
			}
			if(BGFlimmer>-200)
			{
				BGFlimmer--;
				if(BGFlimmer>0)
				{
				CBG=9+(rand()%4);			
				BGX=rand()%1991;
				BGY=rand()%1511;
				Alpher=200+(rand()%56);
				}
				
			}
	
			Writer.x=x+15;
			Writer.y=y+15;
			Writer.h=570;
			Writer.w=410;
			SDL_SetRenderDrawColor(Renderer, 0,0,0,255);
			SDL_RenderFillRect(Renderer, &Writer);
			SDL_SetTextureAlphaMod(Images[CBG], Alpher);
			SDL_SetTextureBlendMode(Images[CBG], SDL_BLENDMODE_BLEND);
			SDL_RenderCopy( Renderer, Images[CBG], &Reader, &Writer);
			SDL_RenderCopy( Renderer, Images[MageState], NULL, &Writer);
	
	return 0;
}

int NewGame()
{
MageState=0;
LastAction=0;
ActionsWOMerit=0;
MadeHighScore=-1;
OutOfOrder=false;
LockMouse=false;
Score=0;
LastScore=0;
ScoreShower=0;
EndGame=false;
EndTaunt=true;
TauntOrShock=0;
Multiplier=0;
WinFlasher=500;
Bonus=0;
BGX=0;
BGY=0;
BGAngle=0;
BGFlimmer=-75;
Awed=false;
CBG=9;
BlinkingScore=0;
AlphaBG=0;
StartTime=0;
Seconds=0;
ShowEndScreen=false;
Minutes=0;
TimeLeft=90;
Pissed=0;
Pissword="";
TheGrid=EmptyGrid;
TurnsLeft=TurnsModeLimit;	

if(TurnMode==0)
 {
	 if(TimeModeLimit==150)HSLimitEnter=0;
	 if(TimeModeLimit==300)HSLimitEnter=1;
	 if(TimeModeLimit==600)HSLimitEnter=2;
  }
  else
  {
	  if(TurnsModeLimit==50)HSLimitEnter=0;
	  if(TurnsModeLimit==100)HSLimitEnter=1;
	  if(TurnsModeLimit==200)HSLimitEnter=2;
  }

if(TurnMode==false)
 {
	ToWin=(float)((TimeModeLimit/150)*1250);
 }
 else
 {
	ToWin=(float)((TimeModeLimit/50)*1250);
 }
for(int i=0; i<11; i++)
 LastWords[i]="";
 
 DefInterface();
ChangePowerWord();
int x=0;
int y=0;
for(int i=0; i<(GridW+1)*(GridH+1); i++)
{
	
	if(x>GridW)
	 {
		 x=0;
		 y++;
	 }
	std::string pass=reLetter();
	//std::cout << std::endl << "sub: " << pass << std::endl;
	TheGrid.createTile(x, y, pass);
	x++;
}




TheGrid.CheckForWords(true);
StartTime=SDL_GetTicks();
TimeLeft=TimeModeLimit;

int so=rand()%3;
if(so==0)Mix_PlayChannel( 1, Sounds[21], 0 );	 
if(so==1)Mix_PlayChannel( 1, Sounds[23], 0 );	
if(so==2)Mix_PlayChannel( 1, Sounds[25], 0 );	

 return 0;
}

float WitchHouseZoom=0.1;
int WitchFrame=0;
int WitchFrameChange=0;
float WitchZoom=0.125;
float WitchCorrectX=390;
float WitchCorrectY=600;
float WitchCorMovX=390;
float WitchCorMovY=600;
float InnerZoom=0.4;
float InnerCorX=0;
float InnerCorY=0;
float WitchHouseCorrectionX=0;
float WitchHouseCorrectionY=0;
float WitchhouseCorMovX=1920;
float WitchhouseCorMovY=0;
float LetEf=0;
float Darken=125;
int LogoBlinker=0;
int DrawIntro()
{
	 if(Intro>200 && Mix_PlayingMusic()==0)
     {
			 Mix_PlayMusic(Music[2], -1);  
	 }
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);
		SDL_Rect Reader;
			Reader.x=0;
			Reader.y=0;
			Reader.h=0;
			Reader.w=1125;
		SDL_Rect Writer;
			Writer.x=0;
			Writer.y=0;
			Writer.h=0;
			Writer.w=0;
		SDL_Rect Blende;
	if(Intro==0)
	{
		SDL_QueryTexture(IntroText, NULL, NULL, &Writer.w, &Writer.h);
			SDL_RenderCopy( Renderer, IntroText, NULL, NULL);
	}
	if(Intro>0)
	{
		Intro++;
		if(Intro==2)Mix_PlayChannel( 1, Sounds[1], 0 );
		if(Intro>0 && Intro<200)SDL_RenderCopy( Renderer, Images[13], NULL, NULL);
		if(Intro==200)Mix_FadeInMusic(Music[1], 0, 2000);
		if(Intro>200)
		{
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, Darken*2);
			Blende.x=0;
			Blende.y=0;
			Blende.w=1920;
			Blende.h=1080;
			//SDL_SetRenderDrawColor(Renderer, 10, 10, 20+(rand()%15), 255);
			//SDL_RenderClear(Renderer);
			Reader.x=0;
			Reader.y=0;
			Reader.h=1080;
			Reader.w=1920;
			Writer.x=InnerCorX;
			Writer.y=InnerCorY;
			Writer.h=1080*InnerZoom;
			Writer.w=1920*InnerZoom;
			SDL_RenderCopy( Renderer, Images[16], &Reader, &Writer);
			SDL_RenderFillRect(Renderer, &Blende);
			if(Intro<1500 || Flimmering==true)WitchFrameChange++;
			if(WitchFrameChange==25)
			 {
				 WitchFrame++;
				 if(WitchFrame==4)WitchFrame=0;
				 WitchFrameChange=0;
			 }
			Reader.x=300*WitchFrame;
			Reader.y=0;
			Reader.h=525;
			Reader.w=300;
			Writer.x=WitchCorrectX;
			Writer.y=WitchCorrectY;
			Writer.h=525*WitchZoom;
			Writer.w=300*WitchZoom;
			if(Intro>200 && Intro<5800)
			{
			InnerZoom=InnerZoom*1.001025; //
			InnerCorX=0-(((1920*InnerZoom)-1920)/2.25);
			InnerCorY=0-(((1080*InnerZoom)-1080)/2);
			WitchZoom=WitchZoom*(1.00165);
			//if(WitchCorMovX<710)WitchCorMovX=WitchCorMovX+1;
			if(WitchCorMovY<390)WitchCorMovY=WitchCorMovY+0.5;
			WitchCorrectX=WitchCorMovX-(((300*WitchZoom)-300)/1.2);
			WitchCorrectY=WitchCorMovY-(((525*WitchZoom)-525)/3.15);
			}
			SDL_RenderCopy( Renderer, Images[15], &Reader, &Writer);
			
			Reader.x=0;
			Reader.y=0;
			Reader.h=1080;
			Reader.w=1920;
			Writer.x=WitchHouseCorrectionX;
			Writer.y=WitchHouseCorrectionY;
			Writer.h=1080*WitchHouseZoom;
			Writer.w=1920*WitchHouseZoom;
			if(Intro<3000)
			{
			WitchHouseZoom=WitchHouseZoom*(1.0035);
			if(WitchhouseCorMovX>920)WitchhouseCorMovX=WitchhouseCorMovX-1.2;
			if(WitchhouseCorMovY<640)WitchhouseCorMovY=WitchhouseCorMovY+2;
			WitchHouseCorrectionX=0-(((WitchhouseCorMovX*WitchHouseZoom)-(1920))/2);
			WitchHouseCorrectionY=0-(((1080*WitchHouseZoom)-1080)/2);
			if(Darken>0)Darken=Darken-0.05;
			}
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, Darken);
			SDL_RenderFillRect(Renderer, &Blende);
			SDL_RenderCopy( Renderer, Images[14], &Reader, &Writer);
		
			Blende.x=0;
			Blende.y=0;
			Blende.w=1920;
			Blende.h=Writer.y;
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(Renderer, &Blende);
			Blende.x=0;
			Blende.y=Writer.y+Writer.h;
			Blende.w=1920;
			Blende.h=1200;
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(Renderer, &Blende);
			Blende.x=0;
			Blende.y=0;
			Blende.w=Writer.x;
			Blende.h=1080;
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(Renderer, &Blende);
			Blende.x=Writer.x+Writer.w;
			Blende.y=0;
			Blende.w=2000;
			Blende.h=1080;
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(Renderer, &Blende);
			
			if(Intro>2750)
			{
			if(LetEf<240)LetEf=LetEf+0.2;
			for(int i=0; i<1000; i++)
				MenuLetterEffect[i].Draw(LetEf);
			}
			
			if(Intro>3333)
			{
			Reader.x=0;
			Reader.y=0;
			LogoBlinker++;
			if(LogoBlinker>100)Reader.x=1980;
			if(LogoBlinker==200)LogoBlinker=0;
			Reader.h=600;
			Reader.w=1920;
			Writer.x=0;
			Writer.y=240;
			Writer.h=600;
			Writer.w=1920;
			SDL_RenderCopy( Renderer, Images[17], &Reader, &Writer);
			}
			
		}
	}
	return 0;
}


int main()
{
	DefHighScoreTables();
	loadSettings("Settings.txt");
			std::ifstream file;
			std::string str;
			if(WordMode==0)file.open("wordbooks/reduced.txt");
			if(WordMode==2)file.open("wordbooks/extended.txt");
			if(WordMode!=0 && WordMode !=2)file.open("wordbooks/recommended.txt");
			
			while (std::getline(file, str))
			{
				count++;
				Vocabulary[count]=str;
			}
			file.close();
			int n = sizeof(Vocabulary)/sizeof(Vocabulary[0]);
			sort(Vocabulary , Vocabulary + n , compdown);
/*
std::cout << "Eiche und Eibe | Anagramm: " << anagram("Eiche", "Eibe");
std::cout << "Elch und Reh | Anagramm: " << anagram("Elch", "Reh");
std::cout << "Steil und Stiel | Anagramm: " << anagram("Steil", "Stiel");
std::cout << "Tisch und Schit | Anagramm: " << anagram("Tisch", "Schit");
*/
/*
std::cout << "First: " << Vocabulary[0] << std::endl;
std::cout << "Last: " << count << " is " << Vocabulary[count-1] << std::endl;*/

std::string checker;

iniSDL(AntiA);
LoadSounds();
for(int i=0; i<1000; i++)
 MenuLetterEffect[i].Create();

for(int i=0; i<11; i++)
 LastWords[i]="";
srand (time(NULL));
Wood=loadTexture("sprites/Wood.png");
Glyphs=loadTexture("sprites/Letters.png");
GhostGlyphs=loadTexture("sprites/GhostLetters.png");
Front=loadTexture("sprites/Front.png");
Finger=loadTexture("sprites/Finger.png");
MenuBG=loadTexture("sprites/MenuBG.png");
loadImages("sprites.txt");
LoadMusic();
DefInterface();
ChangePowerWord();
int x=0;
int y=0;

for(int i=0; i<(GridW+1)*(GridH+1); i++)
{
	
	if(x>GridW)
	 {
		 x=0;
		 y++;
	 }
	std::string pass=reLetter();
	//std::cout << std::endl << "sub: " << pass << std::endl;
	TheGrid.createTile(x, y, pass);
	x++;
}


MenuBGX=5+(rand()%560);
MenuBGY=5+(rand()%2300);
MenuBGAngle=rand()%360;

TheGrid.CheckForWords(true);
int starter=0;
StartTime=SDL_GetTicks();
TimeLeft=TimeModeLimit;

//Intro prep

TTF_Font *tFont;
	
		SDL_Surface* Result=NULL;
		tFont=TTF_OpenFont( "pathway-gothic-one/PathwayGothicOne-Regular.ttf", 80 );
		SDL_Color FCol={255, 255, 255, 255};
		Result=TTF_RenderText_Blended_Wrapped(tFont, "WARNING\n\nEPILEPSY WARNING: This game contains rapidly changing colors and flashing lights! It might be dangerous to people with photosensitive epilepsy, even if they did not experience problems in the past. If you experience problems such as dizziness, disorientation, muscle- or eye-twitching, or any other related symptoms while playing, stop playing the game immediately. There is an option available to heavily reduce flashing effects in the options menu, and it is possible to temporarily disable most them instantly by pressing F9 ingame. Still, we don't give any guarantee for your safety.\n\nTRIGGER WARNING: This game uses automatically generated wordlists. While some offensive words have been removed, are bound to remain - including some words that can't be removed as removing them would be an revisionist act. When playing, you are likely to encounter sexual, obscene, violent, and - in cases where we failed to remove them - discriminating words. Contact us if you feel that a word should be removed from or included in our lists. \n\nPress RETURN to start the game, or ESCAPE to exit. Note: All menus and the game are controlled completely by mouse." , FCol, 1920);	
		TTF_CloseFont(tFont);
		IntroText=SDL_CreateTextureFromSurface(Renderer, Result);		
		SDL_FreeSurface(Result);
SDL_SetTextureScaleMode(Images[14], SDL_ScaleModeNearest);
SDL_SetTextureScaleMode(Images[15], SDL_ScaleModeNearest);
SDL_SetTextureScaleMode(Images[16], SDL_ScaleModeNearest);

while(running==true)
{
	if(Intro>=0)
	{
		Events();
		DrawIntro();
	}
	if(Intro==-1)
	{
	MusicMan();
	CalcTime();
	if(TimeLeft>0)TimeLeft=TimeModeLimit-Seconds;
	if(TimeLeft<=0 && TurnMode==false  && EndGame==false)
	{
		EndGame=true;
		Mix_PlayChannel( 4, Sounds[4], 0 );
		
	}
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	if(Score>ToWin && EndGame==true && MenuOpen==false && Flimmering==true)
	{
	if(WinFlasher>=100)
	SDL_SetRenderDrawColor(Renderer, 50+(rand()%100), 50+(rand()%100), 100+(rand()%100), 255);
	if(WinFlasher<100 && WinFlasher>0)
	SDL_SetRenderDrawColor(Renderer, 50+(WinFlasher), 50+(WinFlasher), 100+(WinFlasher), 255);
	WinFlasher--;
	}
	SDL_RenderClear( Renderer );	
	Events();
		TheGrid.MoveTiles();
		if(ShowEndScreen==false)TheGrid.Draw();
		//Draw Interface
		SDL_Rect Reader;
			Reader.x=0;
			Reader.y=0;
			Reader.h=1200;
			Reader.w=1125;
		SDL_Rect Writer;
			Writer.x=((GridW+1)*TileSize)-150;
			Writer.y=0;
			Writer.h=1200;
			Writer.w=1125;
			if(EndGame==true)
			{
				Reader.x=150;
				Writer.x=((GridW+1)*TileSize);
				Reader.w=1125-150;
				Writer.w=1125-150;
				
			}
			
		SDL_RenderCopy( Renderer, Front, &Reader, &Writer);
		if(EndGame==true)
		{
			TheGrid.Dissolve();
			
		}
		
		if(MenuOpen==true)
		{
				if(MenuBGX<5){MenuBGAngle=rand()%180; MenuBGX=5;}
				if(MenuBGX>565){MenuBGAngle=180+(rand()%180); MenuBGX=565;}
				if(MenuBGY<5){MenuBGAngle=90+(rand()%180); BGY=5;}
				if(MenuBGY>2355){MenuBGAngle=270+(rand()%180); BGY=2355;}
				float cAngle=(float)((MenuBGAngle*M_PI)/180);
				MenuBGX=(float)MenuBGX+(cos(cAngle)*(2));
				MenuBGY=(float)MenuBGY+(sin(cAngle)*(2));
			
				Reader.x=MenuBGX;
				Reader.y=MenuBGY;
				Reader.h=1080;
				Reader.w=1920;
				SDL_RenderCopy( Renderer, MenuBG, &Reader, NULL);
				for(int i=0; i<1000; i++)
				MenuLetterEffect[i].Draw();
		}
		
		ManageButtons(Renderer);
		
		if(MenuOpen==false)
		DrawMage(((GridW+1)*TileSize), 0);
			
		if(LockMouse==false && UseHand==true)
		{
		Writer.x=mouseX-LastClick;
		Writer.y=mouseY-LastClick;
		Writer.w=70;
		Writer.h=70;
		SDL_RenderCopy( Renderer, Finger, NULL, &Writer);
		}
		}	
	
	SDL_RenderPresent( Renderer );
	starter=SDL_GetTicks()-starter;
	if(starter<15)SDL_Delay(15-starter);
	starter=SDL_GetTicks();
}
return 0;
}
