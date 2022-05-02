#include "iluminacioFragment.h"
#include "glwidget.h"

void IluminacioFragment::onPluginLoad()
{
	// Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(glwidget()->getPluginPath()+"/../iluminacioFragment/lighting4.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(glwidget()->getPluginPath()+"/../iluminacioFragment/lighting4.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
}

void IluminacioFragment::preFrame()
{
	program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
    program->setUniformValue("modelViewMatrix", camera()->viewMatrix()); 
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());
    
    program->setUniformValue("matAmbient", QVector4D(0.8,0.8,0.6,1.0)); 
    program->setUniformValue("matDiffuse", QVector4D(0.8,0.8,0.6,1.0));
    program->setUniformValue("matSpecular", QVector4D(1.0,1.0,1.0,1.0));
    program->setUniformValue("matShininess", GLfloat(64.0));
    
    program->setUniformValue("lightAmbient", QVector4D(0.1,0.1,0.1,1.0));
    program->setUniformValue("lightDiffuse", QVector4D(1.0,1.0,1.0,1.0));
    program->setUniformValue("lightSpecular", QVector4D(1.0,1.0,1.0,1.0));
    program->setUniformValue("lightPosition", QVector4D(0.0,0.0,0.0,1.0));
}

void IluminacioFragment::postFrame()
{
	program->release();
}