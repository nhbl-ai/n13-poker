#include <iostream>
#include "window.h"
#include "tittle.h"
#include "word2.h"
#include "RuntimePaths.h"
using namespace std;
sf::Music music;
sf::Sound click;
int main(int argc, char* argv[])
{
	if (!initializeRuntime(argc > 0 ? argv[0] : "")) return 1;
	if (argc == 2 && std::string(argv[1]) == "--check-resources") return 0;
	music.openFromFile("backgroundsong.mp3");
	music.setLoop(true);
	music.setVolume(50.f);
	music.play();
	sf::SoundBuffer takesound;
	takesound.loadFromFile("click.wav");
	click.setBuffer(takesound);
	//word2();
	//tittle();
	window();
	return 0;
}
