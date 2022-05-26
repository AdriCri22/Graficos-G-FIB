#include "textureSplatting.h"
#include <QFileDialog>
 
void TextureSplatting::onPluginLoad()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
	// VS
    QString vs_src = \
      "#version 330 core\n"
      "layout (location=0) in vec3 vertex;"
      "layout (location=1) in vec3 normal;"
      "layout (location=3) in vec2 texCoord;"
      "out vec3 vNormal;"
      "out vec2 vtexCoord;"
      "uniform mat4 modelViewProjectionMatrix;"
      "uniform mat3 normalMatrix;"
      "void main() {"
      " vNormal=normalize(normalMatrix*normal);"
      " vtexCoord=texCoord;"
      " gl_Position=modelViewProjectionMatrix*vec4(vertex, 1);"
      "}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);

	// FS
    QString fs_src =
      "#version 330 core\n"
      "in vec3 vNormal;"
      "in vec2 vtexCoord;"
      "out vec4 fragColor;"
      "uniform sampler2D noise0;"
      "uniform sampler2D rock1;"
      "uniform sampler2D grass2;"
      "void main() {"
      " float f=texture(noise0, vtexCoord).r;"
      " vec4 rock=texture(rock1, vtexCoord);"
      " vec4 grass=texture(grass2, vtexCoord);"
      " fragColor=mix(rock, grass, fract(f))*vNormal.z;"
      "}";  
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);

	// Program  
  	program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
	program->addShader(fs);
	program->link();

     // Load Noise
	QString noiseFilename = QFileDialog::getOpenFileName(0, "Open Noise Image", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img2(noiseFilename);	
	QImage im2 = img2.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
        g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE2);
	g.glGenTextures( 1, &noiseId);
	g.glBindTexture(GL_TEXTURE_2D, noiseId);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im2.width(), im2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im2.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
    
	// Load Texture 1
    QString filename = QFileDialog::getOpenFileName(0, "Open Rock Image", "../../Textures", "Image file (*.png *.jpg)");	
	QImage img0(filename);	
	QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
        g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &textureId0);
	g.glBindTexture(GL_TEXTURE_2D, textureId0);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);

	// Load Texture 2
	QString filename2 = QFileDialog::getOpenFileName(0, "Open Grass Image", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img1(filename2);	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
        g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE1);
	g.glGenTextures( 1, &textureId1);
	g.glBindTexture(GL_TEXTURE_2D, textureId1);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureSplatting::preFrame() 
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("noise0", 0);  // texture unit del primer sampler 
    program->setUniformValue("rock1", 1);  // texture unit del segon  sampler 
    program->setUniformValue("grass2", 2);  // texture unit del tercer  sampler
    program->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() * g.camera()->viewMatrix());
    program->setUniformValue("normalMatrix", g.camera()->viewMatrix().normalMatrix());
    // bind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, noiseId);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);
    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, textureId1);
}

void TextureSplatting::postFrame() 
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind default shaders
    g.defaultProgram()->bind();
    // unbind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, 0);
}
