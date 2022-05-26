#include "emerging.h"
#include "glwidget.h"

void Emerging::onPluginLoad()
{
	QString vs_src =
    "#version 330 core\n" 
    "layout (location = 0) in vec3 vertex;"
    "layout (location = 1) in vec3 normal;"
    "layout (location = 2) in vec3 color;"
    "out vec4 frontColor;"
    "uniform mat4 modelViewProjectionMatrix;"
	"uniform mat3 normalMatrix;"
    "void main() {"
	"	vec3 N = normalize(normalMatrix * normal);"
    "	frontColor = vec4(color,1.0) * N.z;"
    "   gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);"
    "}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    cout << "VS log:" << vs->log().toStdString() << endl;

    QString fs_src =
    "#version 330 core\n"
    "in vec4 frontColor;"
    "out vec4 fragColor;"
    "uniform float files;"
    "void main() {"
    "   if (gl_FragCoord.y >= files) fragColor = frontColor;"
    "   else discard;"
    "}";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

    elapsedTimer.start();
}

void Emerging::preFrame()
{
	// bind shader and define uniforms
    program->bind();

    GLWidget & g = *glwidget();
    float time = float(elapsedTimer.elapsed() / 1000.0);
    int timeInt = int(time);
    if (timeInt % 2 == 0)
        program->setUniformValue("files", g.height() * (time - timeInt));
    else
        program->setUniformValue("files", g.height() - g.height() * (time - timeInt));

    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());
}

void Emerging::postFrame()
{
	// unbind shader
    program->release();
}

void Emerging::onObjectAdd()
{
	
}

bool Emerging::drawScene()
{
	return false; // return true only if implemented
}

bool Emerging::drawObject(int)
{
	return false; // return true only if implemented
}

bool Emerging::paintGL()
{
	return false; // return true only if implemented
}

void Emerging::keyPressEvent(QKeyEvent *)
{
	
}

void Emerging::mouseMoveEvent(QMouseEvent *)
{
	
}

