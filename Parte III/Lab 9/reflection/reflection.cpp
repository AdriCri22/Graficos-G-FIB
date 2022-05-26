#include "reflection.h" 
#include <QCoreApplication>
 
const int IMAGE_WIDTH = 512;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void Reflection::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    // Carregar VS
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    QString vsrc = "#version 330 core\n uniform mat4 modelViewProjectionMatrix;\nlayout (location = 0) in vec3 vertex;\n void main() {gl_Position    = modelViewProjectionMatrix * vec4(vertex,1.0); }";
    vs->compileSourceCode(vsrc);
  
  	// Carregar FS (texture mapping)
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    QString fsrc = "#version 330 core\nout vec4 fragColor;\nuniform sampler2D colorMap;\nuniform float SIZE;\nvoid main() {fragColor = texture(colorMap, gl_FragCoord.xy/ SIZE); }";
    fs->compileSourceCode(fsrc);

	// Program
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    // Setup textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glGenTextures( 1, &textureId[0]);

	g.glBindTexture(GL_TEXTURE_2D, textureId[0]);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);

    // Resize to power-of-two viewport
    g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);
}

// draws a quad with vertices V0, V1, V2, V3. 
void drawRect(GLWidget &g, Point V0, Point V1, Point V2, Point V3)
{
	GLuint VAO_rect;

    // 1. Create VAO
    // Create & bind empty VAO
    g.glGenVertexArrays(1, &VAO_rect);
    g.glBindVertexArray(VAO_rect);

    // Create VBO with (x,y,z) coordinates
    float coords[] = { V0.x(), V0.y(), V0.z(),
                       V1.x(), V1.y(), V1.z(),
					   V3.x(), V3.y(), V3.z(),
					   V2.x(), V2.y(), V2.z() };

    GLuint VBO_coords;
    g.glGenBuffers(1, &VBO_coords);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);
    g.glBindVertexArray(0);

    // 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);

	// 3. Clean up
	g.glDeleteBuffers(1, &VBO_coords);
	g.glDeleteVertexArrays(1, &VAO_rect);
}



bool Reflection::paintGL()
{
    GLWidget & g = *glwidget();

    // Pass 1: draw scene reflected onto Y=min.y 
	// Uses default shaders
	g.glClearColor(0.8,0.8,0.8,0);
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Reflection matrix with respect to Y=min.y
	QMatrix4x4 reflection;
	reflection.scale(1,-1,1);
	reflection.translate(0, -2*scene()->boundingBox().min().y(), 0);

	g.defaultProgram()->setUniformValue("modelViewProjectionMatrix", 	
		camera()->projectionMatrix() * camera()->viewMatrix() * reflection);
	if (drawPlugin()) drawPlugin()->drawScene();

	// Get texture for bottom plane
	g.glBindTexture(GL_TEXTURE_2D, textureId[0]);		
	g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
	g.glGenerateMipmap(GL_TEXTURE_2D);

	// Pass 2: draw scene in its real position
	// Uses default shaders
	g.glClearColor(1,1,1,0);
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	g.defaultProgram()->setUniformValue("modelViewProjectionMatrix", 	
		camera()->projectionMatrix() * camera()->viewMatrix() );
	if (drawPlugin()) drawPlugin()->drawScene();


	// Pass 3: Draw mirror (a textured quad)
	// Uses our own texture mapping shader
	Box b = scene()->boundingBox();
    program->bind();
    program->setUniformValue("colorMap", 0);
    program->setUniformValue("SIZE", float(IMAGE_WIDTH));  
    program->setUniformValue("modelViewProjectionMatrix", camera()->projectionMatrix() * camera()->viewMatrix() );  

	// draw quad with texture
	g.glBindTexture(GL_TEXTURE_2D, textureId[0]);
	Point V0 = b.min();
	Point V1 = Point(b.max().x(), b.min().y(), b.min().z());
	Point V2 = Point(b.max().x(), b.min().y(), b.max().z());
	Point V3 = Point(b.min().x(), b.min().y(), b.max().z());
    drawRect(g, V0, V1, V2, V3);

	// restore state
    g.defaultProgram()->bind();
    g.glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

