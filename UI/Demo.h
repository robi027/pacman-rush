#ifndef DEMO_H
#define DEMO_H


#include <SOIL/SOIL.h>

#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <map>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

using namespace glm;

#define FONTSIZE 40
#define FONTNAME "hongkonghustle.ttf"
#define NUM_BUTTON 4
#define NUM_IMG 1

struct Character {
	GLuint TextureID; // ID handle of the glyph texture
	ivec2 Size; // Size of glyph
	ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance; // Offset to advance to next glyph
};

class Demo :
	public Engine::Game
{
public:
	Demo();
	~Demo();
	virtual void Init();
	virtual void DeInit();
	virtual void Update(float deltaTime);
	virtual void Render();
private:
	void InitText();
	void RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
	void InitButton();
	void RenderButton();
	void InitImg();
	void RenderImg();
	map<GLchar, Character> Characters;
	GLuint texture[NUM_BUTTON], hover_texture[NUM_BUTTON], img[NUM_IMG], VBO, VBO2, VAO, VAO2, program;
	float button_width[NUM_BUTTON], button_height[NUM_BUTTON], hover_button_width[NUM_BUTTON], hover_button_height[NUM_BUTTON], img_width[NUM_IMG], img_height[NUM_IMG];
	int activeButtonIndex = 0;
	int gameState = 0;

	//background Process
	GLuint VAOback, VBOback, EBOback, Textureback1, textureback2;
	float frame_widthBack = 0, frame_heightBack = 0;
	void buildBackground(GLuint *texture, char *file);
	void drawBackground(GLuint *texture);
};
#endif

