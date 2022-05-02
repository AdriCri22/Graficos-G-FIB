#include "animateVerticesV2.h"

void AnimateVerticesV2::onPluginLoad()
{
    // Carregar shader, compile & link 
    QString vs_src =
    "#version 330 core\n"
    "layout (location = 0) in vec3 vertex;"
    "layout (location = 1) in vec3 normal;"
    "layout (location = 2) in vec3 color;"
    "out vec4 frontColor;"
    "uniform mat4 modelViewProjectionMatrix;"
    "uniform mat4 modelViewMatrix;"
    "uniform mat3 normalMatrix;"
    "uniform float amplitude = 0.1;"
    "uniform float freq = 1;"
    "uniform float time;"
    "const float PI = 3.141592;"
    "void main() {"
    "   float d = amplitude * sin(freq * 2 * PI * time);"
    "   vec3 N = normalize(normalMatrix * normal);"
    "   vec3 newVertex = vertex + vec3(d) * normal;"
    "   vec4 color2 = modelViewMatrix * vec4(normal, 0);"
    "   frontColor = vec4(vec3(color2.z), 1.0);"
    "   gl_Position = modelViewProjectionMatrix * vec4(newVertex, 1.0);"
    "}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    cout << "VS log:" << vs->log().toStdString() << endl;

    QString fs_src =
    "#version 330 core\n"
    "in vec4 frontColor;"
    "out vec4 fragColor;"
    "void main() {"
    "   fragColor = frontColor;"
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

void AnimateVerticesV2::preFrame() 
{
    // bind shader and define uniforms
    program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
    program->setUniformValue("modelViewMatrix", camera()->viewMatrix()); 
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix()); 
    program->setUniformValue("time", float(elapsedTimer.elapsed() / 1000.0));
}

void AnimateVerticesV2::postFrame() 
{
    // unbind shader
    program->release();
}

