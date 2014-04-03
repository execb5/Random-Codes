#pragma once
class Instancia
{
	public:
		Instancia(void);
		~Instancia(void);

		float getTx(void);
		float getTy(void);
		float getEx(void);
		float getEy(void);
		float getAngulo(void);
		void incrementaAngulo();
		void decrementaAngulo();
		void incrementaTx();
		void incrementaTy();
		void incrementaEx();
		void incrementaEy();
		void decrementaTx();
		void decrementaTy();
		void decrementaEx();
		void decrementaEy();

	private:
		float tx, ty;
		float ex, ey;
		float angulo;
};
