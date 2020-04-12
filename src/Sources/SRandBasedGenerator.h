#pragma once

class SRandBasedGenerator
{
public:
	SRandBasedGenerator();
	SRandBasedGenerator(unsigned seed);
	virtual ~SRandBasedGenerator();
	void initObject();
	int nextInt();
	int nextInt(int low, int high);

private:
	unsigned seed_;
};

