#include "stdafx.h"
#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>
#include"objectcl.h"

#define ENEMY_FRICTION 0.95
class enemy : public objectcl
{
private:
	static HGE*		hge;
	hgeVector		Position;
	hgeVector		Velocity;
	hgeAnimation*	Sprite;
	hgeRect			BoundingBox;
	float			Speed;

	float			CenterY;
	float			Radius;
	float			Angle;
	bool			bCenterYSet;
	bool			bOscillate;
public:
	enemy(hgeVector position, hgeVector velocity, HTEXTURE &Texture,float sp) : Position(position), Velocity(velocity)
	{
		hge = hgeCreate(HGE_VERSION);

		Sprite	= new hgeAnimation(Texture,4,4,0,0,128,57);
		Sprite->SetHotSpot(20,15);
		Sprite->Play();

		Speed		= sp;

	//	CenterY		= 0;
		Radius		= hge->Random_Float(50.0f,80.0f);
		Angle		= 0.0f;
		bCenterYSet	= false;
		bOscillate	= false;
	}

	bool Update(float delta)
	{
		Velocity.x *= ENEMY_FRICTION;
		Velocity.y *= ENEMY_FRICTION;

		Position.x += Velocity.x;
		if(!bOscillate) Position.y += Velocity.y;
		else
		{
			if(!bCenterYSet)
			{
				if(Velocity.y > -0.000001f && Velocity.y < 0.000001f)
				{
					CenterY = Position.y;
					bCenterYSet = true;
				}
			}

			Position.y = CenterY + sin(Angle) * Radius;
			Angle += 2 * delta;
		}

		Sprite->Update(delta);

		Velocity.x -= Speed;

		Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
		return false;
	}

	void Render()
	{
		Sprite->Render(Position.x, Position.y);
	};

	float		GetSpeed() { return Speed; };
	void		SetSpeed(float speed) { Speed = speed; };
	hgeRect		GetBoundingBox() { return BoundingBox; };
	hgeVector	GetPosition() { return Position; };

	~enemy()
	{
		delete Sprite;
		hge->Release();
	}
};
