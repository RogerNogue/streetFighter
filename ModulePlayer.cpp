#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	/*
	position.x = 100;
	position.y = 216;
	*/
	position.x = 50;
	position.y = 116;
	floor = 116;
	inAir = false;
	flyingSpeed = 0;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({ 542, 131, 61, 87 });
	backward.frames.push_back({ 628, 129, 59, 90 });
	backward.frames.push_back({ 713, 128, 57, 90 });
	backward.frames.push_back({ 797, 127, 57, 90 });
	backward.frames.push_back({ 883, 128, 58, 91 });
	backward.frames.push_back({ 974, 129, 57, 89 });
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({ 9, 136, 53, 83 });
	forward.frames.push_back({ 78, 131, 60, 88 });
	forward.frames.push_back({ 162, 128, 64, 91 });
	forward.frames.push_back({ 259, 128, 63, 90 });
	forward.frames.push_back({ 352, 128, 54, 91 });
	forward.frames.push_back({ 432, 131, 50, 89 });
	forward.speed = 0.1f;

	jump.frames.push_back({ 17, 847, 55, 85 });
	jump.frames.push_back({ 100, 823, 56, 104 });
	jump.frames.push_back({ 176, 805, 50, 89 });
	jump.frames.push_back({ 251, 798, 54, 77 });
	jump.frames.push_back({ 327, 813, 48, 70 });
	jump.frames.push_back({ 397, 810, 48, 89 });
	jump.frames.push_back({ 464, 819, 55, 109 });
	jump.speed = 0.075f;
	
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version

	currentAnimation = &idle;//starting with an idle character

	speed = 1;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	if (inAir) {
		position.y += flyingSpeed;
		//if (position.y <= floor) {
		if (position.y >= floor) {
			//reset the values
			position.y = floor;
			inAir = false;
			flyingSpeed = 0;
			currentAnimation = &idle;
		}
		flyingSpeed += 0.1;
	}
	else {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			App->renderer->camera.x += speed;
			position.x -= speed;
			currentAnimation = &backward;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			App->renderer->camera.x -= speed;
			position.x += speed;
			currentAnimation = &forward;
		}
		else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			//jump
			inAir = true;
			flyingSpeed = -4;
			currentAnimation = &jump;
		}
		else currentAnimation = &idle;
	}
	// TODO 9: Draw the player with its animation
	App->renderer->Blit(graphics, position.x, position.y, &((*currentAnimation).GetCurrentFrame()), 1.0f);
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)

	return UPDATE_CONTINUE;
}