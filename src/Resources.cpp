#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable = std::unordered_map<std::string, SDL_Texture*>();
std::unordered_map<std::string, Mix_Music*> Resources::musicTable = std::unordered_map<std::string, Mix_Music*>();
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable = std::unordered_map<std::string, Mix_Chunk*>();

SDL_Texture* Resources::GetImage(std::string file) {

	if(imageTable.find(file) == imageTable.end())
		imageTable.emplace(file, IMG_LoadTexture(Game::getInstance().getRenderer(), file.c_str()));
	
	if(imageTable.at(file) == nullptr) {
		cout << "IMG_LoadTexture failed: " << SDL_GetError() << endl;
		exit(-1);
	}
	
	return imageTable.at(file);
}

void Resources::ClearImages() {

	for(auto& i: imageTable)
		SDL_DestroyTexture(i.second);
	imageTable.clear();

}

Mix_Music* Resources::GetMusic(std::string file) {
	
	if(!musicTable.count(file))
		musicTable.emplace(file, Mix_LoadMUS(file.c_str()));
	
	if(musicTable.at(file) == nullptr) {
		cout << "Mix_LoadMUS failed: " << SDL_GetError() << endl;
		exit(-1);
	}
	
	return musicTable.at(file);
}

void Resources::ClearMusics() {
	
	for(auto& music: musicTable)
		Mix_FreeMusic(music.second);
	
	musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {

	if(!soundTable.count(file))
		soundTable.emplace(file, Mix_LoadWAV(file.c_str()));

	if(soundTable.at(file) == nullptr) {
		cout << "Mix_LoadWAV failed: " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	return soundTable.at(file);
}

void Resources::ClearSounds() {

	for(auto& sound: soundTable)
		Mix_FreeChunk(sound.second);
	
	soundTable.clear();
}
