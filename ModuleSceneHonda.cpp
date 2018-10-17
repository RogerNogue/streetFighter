#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"


ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;
	/*
	// TODO 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png
	foreground.x = 7;
	foreground.y = 376;
	foreground.w = 849;
	foreground.h = 64;
	*/
	// Background / sky
	background.x = 120;
	background.y = 128;
	background.w = 673;
	background.h = 199;

	pool.x = 164;
	pool.y = 66;
	pool.w = 336;
	pool.h = 51;

	roof.x = 91;
	roof.y = 8;
	roof.w = 765;
	roof.h = 48;

	towel.x = 542;
	towel.y = 85;
	towel.w = 32;
	towel.h = 26;

	//water animation
	water.frames.push_back({ 8, 480, 285, 0 });
	water.frames.push_back({ 296, 448, 285, 12 });
	water.frames.push_back({ 8, 448, 285, 18 });
	water.speed = 0.08f;
}

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");

	graphics = App->textures->Load("honda_stage2.png");

	// TODO 7: Enable the player module
	App->player->Enable();

	// TODO 0: trigger background music
	unsigned int song = App->audio->LoadFx("honda.ogg");
	music = App->audio->PlayFx(song, 99);

	return music;
}

// UnLoad assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	App->renderer->Blit(graphics, -50, 176, &ground, 1.0f);//floor
	App->renderer->Blit(graphics, 0, 0, &background, 1.0f);//walls
	App->renderer->Blit(graphics, 238, 130, &pool, 1.0f);//pool
	App->renderer->Blit(graphics, -50, 0, &roof, 1.0f);//roof
	App->renderer->Blit(graphics, 125, 160, &towel, 1.0f);//towel

	App->renderer->Blit(graphics, 263, 142, &(water.GetCurrentFrame()), 1.0f); // water animation

	return UPDATE_CONTINUE;
}