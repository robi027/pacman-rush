#include "Demo.h"


Demo::Demo()
{
}


Demo::~Demo()
{

}


void Demo::Init()
{
	InitText();
	this->program = BuildShader("shader.vert", "shader.frag");
	InputMapping("SelectButton", SDLK_RETURN);
	InputMapping("NextButton", SDLK_DOWN);
	InputMapping("PrevButton", SDLK_UP);
	InputMapping("Quit", SDLK_ESCAPE);
	buildBackground(&Textureback1, "mainmenuplay.png");
}

void Demo::DeInit() {

}

void Demo::Update(float deltaTime)
{
	if (gameState == 0) {
		if (IsKeyDown("SelectButton")) {
			gameState = 1;
		}
		if (IsKeyDown("Quit")) {
			SDL_Quit();
			exit(0);
		}
	}

	if (gameState == 1) {
		Render();
	}

	if (IsKeyUp("PrevButton")) {
		if (activeButtonIndex > 0) {
			activeButtonIndex = activeButtonIndex - 1;
			SDL_Delay(150);
		}
	}

}

void Demo::Render()
{
	//Setting Viewport
	glViewport(0, 0, GetScreenWidth(), GetScreenHeight());

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if (gameState == 0)
	{
		drawBackground(&Textureback1);
	}
	else if (gameState == 1)
	{
		RenderText("PacmanRUSH", 10, 10, 1.0f, vec3(244.0f / 255.0f, 12.0f / 255.0f, 116.0f / 255.0f));
	}
	// Set orthographic projection
	//mat4 projection;
	//projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	//glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));


}

void Demo::buildBackground(GLuint *texture, char* file) {
	this->program = BuildShader("normal.vert", "normal.frag");
	UseShader(this->program);

	// Load and create a texture 
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	// All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // Set up vertex data (and buffer(s)) and attribute pointers
									 /*frame_widthBack = width;
									 frame_heightBack = height;*/
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAOback);
	glGenBuffers(1, &VBOback);
	glGenBuffers(1, &EBOback);

	glBindVertexArray(VAOback);

	glBindBuffer(GL_ARRAY_BUFFER, VBOback);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOback);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

						  // Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));
}
void Demo::drawBackground(GLuint *texture) {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, *texture);
	// Activate shader
	UseShader(this->program);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 3);

	mat4 model;
	// Translate sprite along x-axis
	// Scale sprite 
	model = scale(model, vec3(GetScreenWidth(), GetScreenHeight(), 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAOback);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

}

void Demo::InitText() {
	// Init Freetype
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		Err("ERROR::FREETYPE: Could not init FreeType Library");
	}
	FT_Face face;
	if (FT_New_Face(ft, FONTNAME, 0, &face)) {
		Err("ERROR::FREETYPE: Failed to load font");
	}

	FT_Set_Pixel_Sizes(face, 0, FONTSIZE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(pair<GLchar, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL,
		GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Demo::RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color)
{
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));
	// Activate corresponding render state
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	UseShader(this->program);

	glUniform3f(glGetUniformLocation(this->program, "ourColor"), color.x, color.y, color.z);
	glUniform1i(glGetUniformLocation(this->program, "text"), 1);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 0);
	mat4 model;
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));
	glBindVertexArray(VAO);

	// Iterate through all characters
	string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];
		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;
		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character

		GLfloat vertices[] = {
			// Positions   // Texture Coords
			xpos + w,	ypos + h,	1.0f, 1.0f, // Bottom Right
			xpos + w,	ypos,		1.0f, 0.0f, // Top Right
			xpos,		ypos,		0.0f, 0.0f, // Top Left
			xpos,		ypos + h,	0.0f, 1.0f  // Bottom Left 
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_QUADS, 0, 4);
		// Now advance cursors for next glyph (note that advance is number of 1 / 64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels(2 ^ 6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}

int main(int argc, char** argv) {

	Engine::Game &game = Demo();
	game.Start("User Interface Demo", 1280, 720, false, WindowFlag::WINDOWED, 60, 1);

	return 0;
}
