#pragma once

typedef struct
{
	float x;
	float y;
} Coordenates;

typedef struct
{
	Coordenates position;
	Coordenates scale;
} Transform;

typedef struct
{
	Coordenates v1;
	Coordenates v2;
	Coordenates v3;
	Coordenates v4;
} BoxCollider;

class GameObject
{
	public:
		GameObject(void);
		~GameObject(void);

		virtual void drawSkin(){}

		void setTx(float x);
		void setTy(float y);
		float getTx(void);
		float getTy(void);
		float getEx(void);
		float getEy(void);
		float getAngle(void);
		void incrementAngle();
		void decrementAngle();
		void incrementTx();
		void incrementTy();
		void incrementEx();
		void incrementEy();
		void decrementTx();
		void decrementTy();
		void decrementEx();
		void decrementEy();
		void setCollider(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
		float getMaxX();
		float getMaxY();
		float getMinX();
		float getMinY();

	private:
		float angle;
		Transform transform;
		BoxCollider collider;
};
