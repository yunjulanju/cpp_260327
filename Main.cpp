#include <iostream>
#include "Engine.h"
#include "World.h"

using namespace std;

void Selection(int* data, int Insize)
{
	for (int i = 0; i < Insize -1 ; i++)
	{		
		int MinNum = i;
		for (int j = i+1; j < Insize; j++)
		{
			if (data[MinNum] > data[j])
			{
				MinNum = j;
			}
		}
		if (data[i] > data[MinNum])
		{
			int temp = data[i];
			data[i] = data[MinNum];
			data[MinNum] = temp;
		}
	}
}

int main()
{
	GEngine->GetInstance();
	GEngine->GetWorld()->Load("Map.txt");
	GEngine->Run();


	return 0;
}