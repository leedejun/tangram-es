#include "tangram.h"

struct posColVertex {
	GLfloat pos_x;
	GLfloat pos_y;
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

const posColVertex vertices[] = {
	{ 0.0f, 1.0f, 93, 141, 148, 255},
	{-1.0f, 0.0f, 93, 141, 148, 255},
	{ 1.0f, 0.0f, 93, 141, 148, 255}
};

const std::string vertShaderSrc =
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"
    "attribute vec4 a_position;\n"
    "attribute vec4 a_color;\n"
    "varying vec4 v_color;\n"
	"void main() {\n"
	"  v_color = a_color;\n"
	"  gl_Position = a_position;\n"
	"}\n";

const std::string fragShaderSrc =
	"#ifdef GL_ES\n"
	"precision mediump float;\n"
	"#endif\n"
	"varying vec4 v_color;\n"
	"void main(void) {\n"
	"  gl_FragColor = v_color;\n"
	"}\n";

std::shared_ptr<ShaderProgram> shader (nullptr);
std::shared_ptr<VertexLayout> layout (nullptr);
std::unique_ptr<VboMesh> mesh (nullptr);
float t;

void initializeOpenGL()
{

	// Make a mesh
	layout = std::shared_ptr<VertexLayout>(new VertexLayout({
		{"a_position", 2, GL_FLOAT, false, 0},
		{"a_color", 4, GL_UNSIGNED_BYTE, true, 0}
	}));
	mesh.reset(new VboMesh(layout));
	mesh->addVertices((GLbyte*)&vertices, 3);

	// Make a shader program
	shader = std::make_shared<ShaderProgram>();
	shader->buildFromSourceStrings(fragShaderSrc, vertShaderSrc);

	t = 0;

	logMsg("%s\n", "initialize");
}

void resizeViewport(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	logMsg("%s\n", "resizeViewport");
}

void renderFrame()
{

	// Draw a triangle!
	t += 0.016;
	float sintsqr = pow(sin(t), 2);
	glClearColor(0.8f * sintsqr, 0.32f * sintsqr, 0.3f * sintsqr, 1.0f);
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	mesh->draw(shader);

	GLenum glError = glGetError();
	if (glError) {
		logMsg("%s\n", "glError!!");
	}

}
