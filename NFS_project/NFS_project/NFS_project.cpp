#include "stdafx.h"
#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <list>
#include <vector>
#include <hgefont.h>
#include "Player.h"
#include "enemy.h"

HGE* Player::hge = NULL;
HGE*	hge	= NULL;
HGE* enemy::hge = 0;
hgeFont* fnt; 
Player*	Player1				= NULL;
int score =0;  
#define BACKGROUND_SCROLLING_SPEED	10.0f
int level =1;
std::vector<enemy*> Enemies;
HTEXTURE	g_tEColors[5]		= { 0 };
//Background
HTEXTURE	g_tBackground		= 0;
HTEXTURE	g_tBGGapFix			= 0;
hgeSprite*	g_sBackground		= NULL;
hgeSprite*	g_sBGGapFix			= NULL;
hgeVector	g_vBGPosition		= hgeVector(0,0);

//Explosion
HTEXTURE	g_tExplosion		= 0;

struct explosion
{
	hgeAnimation*	Animation;
	hgeVector		Position;
};
std::list<explosion> Explosions;

void		CreateExplosion(hgeVector Position);
void		Save_Game();
void		Load_Game();

//Sound
HEFFECT		g_eBGMusic			= 0;
HEFFECT		g_eExplosion		= 0;

bool FrameFunc()
{
	float delta = hge->Timer_GetDelta();

	if (hge->Input_KeyDown(VK_F5))
		Save_Game();
	if (hge->Input_KeyDown(VK_F6))
		Load_Game();



	//Background
	if(g_vBGPosition.x> 0) g_vBGPosition.x -= BACKGROUND_SCROLLING_SPEED;
	else g_vBGPosition	= hgeVector(1780,0);

	//Explosionsdeleteanimation
	for(auto i = Explosions.begin(); i != Explosions.end();)
	{
		if((*i).Animation->GetFrame() == 2)
		{
			delete (*i).Animation;
			i = Explosions.erase(i);
		}
		else 
		{
			(*i).Animation->Update(delta);
			i++;
		}
	}
		double nitr=0.18;
	//Enemies 
	int ij=1;
	if (score>10){
	nitr=nitr+0.04;
	ij++;}
	if(score>50)
		{
	nitr=nitr+0.04;
		ij++;}
	if(score>100)
		{
	nitr=nitr+0.04;
		ij++;}
	if(score>200)
		{
	nitr=nitr+0.04;
		ij++;}
	if(score>500)
		{
	nitr=nitr+0.04;
		ij++;}
	if(score>1000)
		{
	nitr=nitr+0.04;
		ij++;}
	if(score>1500)
		{
		nitr=nitr+0.04;
		ij++;}
	level=ij;


	
	for (int i=Enemies.size();i < ij;i++)
	{

		enemy* Enemy = new enemy(hgeVector(hge->Random_Int(1200,1690), hge->Random_Int(60,530)), 
								hgeVector(-hge->Random_Int(1,7), hge->Random_Int(-3,2)),
								g_tEColors[hge->Random_Int(0,4)],
								(nitr));
		Enemies.push_back(Enemy);
	}

	for(auto i = Enemies.begin(); i != Enemies.end();)
	{
		if((*i)->GetPosition().x < -	100 || (*i)->GetPosition().y > 1680 || (*i)->GetPosition().y < 20)
		{
			score++;
			delete (*i);
			i = Enemies.erase(i);
		}
		else
		{
			(*i)->Update(delta);
			i++;
		}
	}

	//Player
	Player1->Update(delta);

	//Enemy vs Player
	for(auto i = Enemies.begin(); i != Enemies.end();) //
	{
		if((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))  //Intersect _ проверяет координаты
		{
			CreateExplosion((*i)->GetPosition());
			score-=8;

			delete (*i);
			i = Enemies.erase(i);

			Player1->SetPosition(hgeVector(150,268));
			Player1->SetVelocity(hgeVector(0,0));
		}
		else i++;
	}

	//Enemy vs Enemy

	for(int i =0; i<Enemies.size(); i++) //
	{
		for (int j= i+1; j<Enemies.size();j++)
		{
			if(Enemies[i]->GetBoundingBox().Intersect(&(Enemies[j]->GetBoundingBox())))  //Intersect _ проверяет координаты
			{
				//CreateExplosion((*i)->GetPosition());
				CreateExplosion((Enemies[i])->GetPosition());
				delete (Enemies[j]);
				Enemies.erase(Enemies.begin()+j);
				delete (Enemies[i]);
				Enemies.erase(Enemies.begin()+i);
				break;
				break;
			}
		}
	}


	//Score
	if(score<=0)
	{
		score =0;
	}
	return false;


}

bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

	//Background
	g_sBackground->Render(g_vBGPosition.x,g_vBGPosition.y);
	if(g_vBGPosition.x > -1) 	g_sBackground->Render(g_vBGPosition.x - 982 - 800, 0);
	g_sBGGapFix->Render(g_vBGPosition.x - 28, 0);

	//Player
	Player1->Render();

	//Enemies
	for(auto i = Enemies.begin(); i != Enemies.end(); i++)
	{
		(*i)->Render();
	}

	//Explosions
	for(auto i = Explosions.begin(); i != Explosions.end(); i++)
	{
		(*i).Animation->Render((*i).Position.x, (*i).Position.y);
	}
	fnt->SetColor(ARGB(255,255,255,255));
	fnt->printf(25,30,HGETEXT_LEFT,"Final score %d", score);
	fnt->printf(25,70,HGETEXT_LEFT,"Level %d", level);
	fnt->printf(940,30,HGETEXT_LEFT,"F5 - save, F6-load            %d");


	hge->Gfx_EndScene();
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, true);
	hge->System_SetState(HGE_FPS, HGEFPS_VSYNC);
	hge->System_SetState(HGE_TITLE, "NFS_project");
	    hge->System_SetState(HGE_SCREENWIDTH,1220);
    hge->System_SetState(HGE_SCREENHEIGHT,600);

	if(hge->System_Initiate())
	{
		fnt=new hgeFont("font1.fnt");

		//Background
		g_tBackground	= hge->Texture_Load("images/TheRoad.jpg");
		g_tBGGapFix		= hge->Texture_Load("images/Strips.jpg");
		g_eExplosion	= hge->Effect_Load("sounds/21410__heigh-hoo__blow.aif");
		g_sBackground	= new hgeSprite(g_tBackground, 0, 0, 1780, 600);
		g_sBGGapFix		= new hgeSprite(g_tBGGapFix, 0, 0, 64, 600);
		g_vBGPosition	= hgeVector(-982, 0);
		
		//Sounds
		g_eBGMusic		= hge->Effect_Load("sounds/mix_17m52s.mp3");
		hge->Effect_PlayEx(g_eBGMusic, 40, 0, 0, true);

		//Player
		Player1			= new Player(hgeVector(150, 268));

		//Enemies
		g_tEColors[0]	= hge->Texture_Load("images/car1.png");
		g_tEColors[1]	= hge->Texture_Load("images/car2.png");
		g_tEColors[2]	= hge->Texture_Load("images/car3.png");
		g_tEColors[3]	= hge->Texture_Load("images/car4.png");
		g_tEColors[4]	= hge->Texture_Load("images/car5.png");

		//Explosion

		g_tExplosion	= hge->Texture_Load("images/Explosion-Sprite-Sheet.png");

		hge->System_Start();
		
	}
	
	return 0;
}

void CreateExplosion(hgeVector Position)
{
	explosion exp;
	exp.Animation = new hgeAnimation(g_tExplosion,5,10,0,0,118,118);
	exp.Animation->Play();
	exp.Position = Position;
	Explosions.push_back(exp);
		hge->Effect_PlayEx(g_eExplosion,100,0,hge->Random_Float(1,3));
}




void Save_Game()
{
	FILE *f= fopen("saved.game","wb");
	int n = Enemies.size();
	fwrite(&n,sizeof(int),1,f);
	for (int i=0;i<n;i++)
	{
		fwrite(Enemies[i],sizeof(enemy),1,f);
	}
	fwrite(&score,sizeof(int),1,f);
	fwrite(Player1,sizeof(Player ),1,f);
	fclose(f);
}

void Load_Game()
{

	Enemies.clear();

	FILE *f= fopen("saved.game","rb");
	int n;
	fread(&n,sizeof(int),1,f);
	for (int i=0;i<n;i++)
	{
		enemy* Enemy = new enemy(hgeVector(hge->Random_Int(800,1670), hge->Random_Int(60,530)), 
								hgeVector(-hge->Random_Int(1,7), hge->Random_Int(-3,2)),
								g_tEColors[hge->Random_Int(0,4)],
								0.1);
		fread(Enemy,sizeof(enemy),1,f);
		Enemies.push_back(Enemy);
	}
	fread(&score,sizeof(int),1,f);
	fread(Player1,sizeof(Player),1,f);
	

}