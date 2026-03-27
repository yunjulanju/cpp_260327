#include <iostream>
#include "Engine.h"
#include "World.h"

using namespace std;

int main()
{
	GEngine->GetInstance();
	GEngine->GetWorld()->Load("Map.txt");
	GEngine->Run();


	return 0;
}