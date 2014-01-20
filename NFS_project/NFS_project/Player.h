#include "stdafx.h"
#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>
#include"objectcl.h"


class Player : public objectcl
{
private:
	static HGE*		hge;
	hgeVector		Position;
	hgeVector		Velocity;
	HTEXTURE		Texture;
	hgeAnimation*	Sprite;
	hgeRect			BoundingBox;
public:
	Player(hgeVector placement) : Position(placement)
	{
		hge = hgeCreate(HGE_VERSION);

	Texture = hge->Texture_Load("images/MainCar.png");
	Sprite	= new hgeAnimation(Texture,4,4,0,0,128,54);
	Sprite->Play();
	};

	bool Update(float delta)
	{
		{
		Velocity.x *= 0.95;
    Velocity.y *= 0.95;
 
    Position.x += Velocity.x;
    Position.y += Velocity.y;

	if(hge->Input_GetKeyState(HGEK_UP)) Velocity.y -= 0.5;
	if(hge->Input_GetKeyState(HGEK_DOWN)) Velocity.y += 0.5;
	if(hge->Input_GetKeyState(HGEK_LEFT)) Velocity.x -= 0.5;
	if(hge->Input_GetKeyState(HGEK_RIGHT)) Velocity.x += 0.5;


if(Position.x > 1090) { Position.x -= 1; Velocity.x = -Velocity.x; };
if(Position.x < 0)   { Position.x += 1; Velocity.x = -Velocity.x; };
if(Position.y < 0)    { Position.y += 1; Velocity.y = -Velocity.y; };
if(Position.y > 550) { Position.y -= 1; Velocity.y = -Velocity.y; };


	Sprite->Update(delta);

	Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
	return false;
}
	};

	void Render()
	{
		Sprite->Render(Position.x,Position.y);
	};


	void		SetVelocity(hgeVector velocity) { Velocity = velocity; };
	void		SetPosition(hgeVector placement) { Position = placement; };
	hgeRect		GetBoundingBox() { return BoundingBox; };
	hgeVector	GetPosition() { return Position; };
	~Player()
	{
		hge->Texture_Free(Texture);
	delete Sprite;

	hge->Release();
	};

};
