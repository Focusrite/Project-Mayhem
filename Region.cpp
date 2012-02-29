#include "Region.h"
#include "Graphics.h"
#include "Level.h"
#include "Player.h"
#include "Trigger.h"
#include <vector>
#include "Rect.h"

Region::Region(float x, float y, int width, int height)
	: Object(x+(width/2), y+(height/2), width, height, REGION)
{
	setLayer(TOP);
	setCollidable(false);
	//setTrigger(new Trigger("", PLAYER_IN_RECT, this));
}

Region::Region(Rect r)
	: Object(r.left+(r.getWidth()/2), (r.top+r.getHeight()/2), r.getWidth(), r.getHeight(), REGION)
{
	setLayer(TOP);
	setCollidable(false);
	//setTrigger(new Trigger("", PLAYER_IN_RECT, this));
}

Region::~Region()
{
	//delete mTrigger;
}

void Region::draw() {
	if(getLevel()->isInEditor()) {
		gGraphics->drawRect(getRect(), D3DCOLOR_ARGB(100, 20,150,200));
	}
}

void Region::update(float dt) 
{
	switch (getTrigger()->getEvent()) 
	{
	case PLAYER_IN_RECT:
		if(gMath->pointInsideRect(getLevel()->getPlayer()->getPos(), getBoundingBox()))
		{
			getTrigger()->doActions(getLevel()->getPlayer());
		}
		break;
	case ENEMY_IN_RECT:
		for(int i = 0; i < getLevel()->getObjectList()->size(); i++) 
		{
			if(getLevel()->getObjectList()->at(i)->getType() != ENEMY)
				continue;
			if(gMath->pointInsideRect(getLevel()->getObjectList()->at(i)->getPos(), getBoundingBox()))
			{
				getTrigger()->doActions(getLevel()->getObjectList()->at(i));
			}
		}
		break;
	case PERIODICALLY:
		//if(
		break;
	default:

		break;
	}

	//case other event
	/*
	Event list:
		PLAYER_IN_RECT
		ENEMY_IN_RECT
		PERIODICALLY
		AFTER_TIME_ELAPSED
		//ON_ENEMY_DEATH

	Action list:
		Advance level
		Defeat level
		Dialog
		Move to
		Add FX
		Spawn enemy
		Spawn loot

		switch state:
		unmovable (collision = true)
		moveable (collision =false)
	*/
}

void Region::setTrigger(Trigger *trig)
{
	mTrigger = trig;
}