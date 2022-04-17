#pragma once

class SRandBasedGenerator
{
public:
	SRandBasedGenerator();
	SRandBasedGenerator(unsigned seed);
	virtual ~SRandBasedGenerator();
	void initObject();
	int nextInt();
	/// <summary>
	/// Genera un numero aleatorio entre low y high
	/// </summary>
	/// <param name="low">Incluido</param>
	/// <param name="high">Excluido</param>
	/// <returns></returns>
	int nextInt(int low, int high);

private:
	unsigned seed_;
};

