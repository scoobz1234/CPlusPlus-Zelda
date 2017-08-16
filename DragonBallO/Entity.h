#pragma once
#include <string>
#include <SDL_image.h>
#include "MyMath.h"

class Entity{

friend class SDLInit;
using uInt = unsigned int;

using Int2 = MyMath::Int2;

public:
	//Needs to be virtual so that derived destructor gets called...
	virtual ~Entity();

public:
	void SetTexturePath(const char* texturePath);
	void SetPosition(float x, float y);
	void SetSize(int width, int height);

	//Call InitSPriteSheet before calling SetSpriteClip...
	void InitSpriteSheet(uInt startClipIndex, uInt numSpriteCLipsX, uInt numSpriteClipsY);
	void SetSpriteClip(int x, int y, uInt w, uInt h, uInt index);
	void SetAnchorOffset(Int2 anchorOffset, uInt index);

//		*** Collision setup ***
	void ConfigureCollision(bool pushesOut, Int2 colliderOffset = { 0, 0 }, Int2 originOffset = { 0, 0 }){
		mCollisionBlocks = pushesOut; 
		mColliderOffset = colliderOffset;
		mOriginOffset = originOffset;
	}
		
	bool CheckCollision(Entity &other);

	MyMath::Float2 GetPosition();
	
	SDL_Rect* GetSpriteClip();
	Int2* GetAnchorOffset();


protected:
	//The actual hardware texture
	SDL_Texture* mTexture;
	const char* mTexturePath;

	float mXPos{0}, mYPos{0};
	float eXPos{ 0 }, eYPos{ 0 };
	int mWidth{0}, mHeight{0};

	Int2 mColliderOffset{ 0, 0 };
	Int2 mOriginOffset{ 0, 0 };

	//If this entity can move, it needs a move speed...
	float mMoveSpeed{ 140.f };

	//For pushing back entity (if collision succeeds)
	bool mCollisionBlocks{false};

	int mSpriteClipIndex{0};
	int mNumSpriteClips{0};
	int mNumSpriteClipsX{0};
	int mNumSpriteClipsY{0};

	//nullptr is better for ambiguity purposes...
	SDL_Rect *mSpriteCLips = nullptr;
	Int2 *mAnchorOffsets = nullptr;
};