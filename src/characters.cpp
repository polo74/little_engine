#include "characters.hpp"

Characters::Characters() :
	buffersize(48)
{
	// Load the shader
	
	shader = new Shader("shaders/character2D.vert", "shaders/character2D.frag");
	//shader = new Shader("shaders/texture2D.vert", "shaders/texture2D.frag");
	shader->charger();

	// Init Freetype

	FT_Library ft;
	FT_Face face;

	if (FT_Init_FreeType(&ft))
		fprintf (stderr, "ERROR::FREETYPE: Could not init FreeType Library\n");

	if (FT_New_Face(ft, "fonts/monospace.ttf", 0, &face))
		fprintf(stderr, "ERROR::FREETYPE: Failed to load font\n");

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
		fprintf(stderr, "ERROR::FREETYTPE: Failed to load Glyph\n");

	FT_Set_Pixel_Sizes(face, 0, 48);

	for (int i = 0; i < 221; i++)
	{
		//Load texture
	
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
			fprintf(stdout, "ERROR::FREETYTPE: Failed to load Glyph\n");

		Texture * texture = new Texture;

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		texture->load(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 0);

		// aramètres de a texture

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		//Load vertices

		GLfloat xpos = face->glyph->bitmap_left;
		GLfloat ypos = face->glyph->bitmap.rows - face->glyph->bitmap_top;
		GLfloat w = face->glyph->bitmap.width;
		GLfloat h = face->glyph->bitmap.rows;

		GLfloat vertices[12] = 
		{
			xpos,		ypos,
			xpos,		ypos + h,
			xpos + w,	ypos + h,
			xpos,		ypos,
			xpos + w,	ypos + h,
			xpos + w,	ypos
		};

		GLuint vertexBuffer;

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Put all in the structure

		Character car
		{
			texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				glm::ivec2(face->glyph->advance.x, face->glyph->advance.y),
				vertexBuffer
		};

		// Put the structure in the map

		characters.insert(std::pair<GLchar, Character>(i, car));
	}

	//Load UVs

	GLfloat uvs[12] = 
	{
		0.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
		0.0, 1.0,
		1.0, 0.0,
		1.0, 1.0,
	};

		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Character Characters::getCharacter(GLchar c)
{
	return characters[c];
}

void Characters::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 color, GLchar ch)
{

	glUseProgram(shader->getProgramID());
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniform3f(glGetUniformLocation(shader->getProgramID(), "color"), color.x, color.y, color.z);

	glBindBuffer(GL_ARRAY_BUFFER, characters[ch].vertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindTexture(GL_TEXTURE_2D, characters[ch].texture->getID());

	glDrawArrays(GL_TRIANGLES, 0, buffersize);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
}
