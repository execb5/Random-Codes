#pragma once
class GameObject
{
	public:
		GameObject(void);
		~GameObject(void);

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

	private:
		float tx, ty;
		float ex, ey;
		float angle;
};
