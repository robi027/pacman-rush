#ifndef DEMO_H
#define DEMO_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"
#include <Windows.h>

#define NUM_FRAMES 4
#define FRAME_DUR 80

using namespace glm;

class Demo :
	public Engine::Game
{
public:
	Demo();
	~Demo();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	float frame_width = 0, frame_height = 0, frame_width2 = 0, frame_height2 = 0, frame_width3 = 0, frame_height3 = 0, frame_width4 = 0, frame_height4 = 0, frame_width5 = 0, frame_height5= 0;
private:
	float frame_dur = 0, oldxpos = 0, xpos = 0, ypos = 0, xpos2 = 0, ypos2 = 0, xpos3 = 0, ypos3 = 0, xpos4 = 0 , ypos4 = 0, xpos5 = 0 , ypos5 = 0 ,  gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0, gravity2 = 0, xVelocity2 = 0, yVelocity2 = 0, yposGround2 = 0;
	GLuint VBO, VAO, EBO, texture, program, VBO2, VAO2, EBO2, texture2, program2, VBO3, VAO3, EBO3, texture3, program3,VBO4,VAO4,EBO4, texture4 , program4, VBO5, VAO5, EBO5, texture5, program5;
	bool walk_anim = false, onGround = true;
	unsigned int frame_idx = 0, flip = 0;
	void BuildPacmanSprite();
	void BuildGhostSprite();
	void BuildGhostSprite2();
	void BuildGhostSprite3();
	void BuildFloorSprite();
	void DrawGhostSprite();
	void DrawGhostSprite2();
	void DrawGhostSprite3();
	void DrawFloorSprite();
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	void DrawPacmanSprite();
	void UpdatePacmanSpriteAnim(float deltaTime);
	void ControlPacmanSprite(float deltaTime);
};
#endif

