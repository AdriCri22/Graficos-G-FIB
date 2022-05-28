#include "skyplane.h"
#include "glwidget.h"

void Skyplane::onPluginLoad()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    vector<float> vertices;   // (x,y,z)
    vector<float> texCoords; // (s,t)
    vector<unsigned int> indices;

    vertices.push_back(-1);
    vertices.push_back(1);
    vertices.push_back(-5);
    texCoords.push_back(0);
    texCoords.push_back(1);
 
    vertices.push_back(-1);
    vertices.push_back(-1);
    vertices.push_back(-5);
    texCoords.push_back(0);
    texCoords.push_back(0);

    vertices.push_back(1);
    vertices.push_back(-1);
    vertices.push_back(-5);
    texCoords.push_back(1);
    texCoords.push_back(0);

    vertices.push_back(1);
    vertices.push_back(1);
    vertices.push_back(-5);
    texCoords.push_back(1);
    texCoords.push_back(1);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(1);

    //GLuint VAO;
    g.glGenVertexArrays(1,&VAO);
    
    GLuint coordBufferID;
    g.glGenBuffers(1, &coordBufferID);
    
    GLuint indexBufferID;
    g.glGenBuffers(1, &indexBufferID);

    g.glBindVertexArray(VAO);
    g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);

    // Coordenades de textura ( no se com es diu el buffer per textures)
    /*g.glBindVertexArray(VAO);
    g.glBindBuffer(GL_ARRAY_BUFFER, texBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);*/

    g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);

    g.glBindVertexArray(0);

    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(glwidget()->getPluginPath()+"/../skyplane/sky.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(glwidget()->getPluginPath()+"/../skyplane/sky.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

    // Carregar shader, compile & link 
    vs2 = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs2->compileSourceFile(glwidget()->getPluginPath()+"/../skyplane/mirror.vert");
    cout << "VS log:" << vs2->log().toStdString() << endl;

    fs2 = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs2->compileSourceFile(glwidget()->getPluginPath()+"/../skyplane/mirror.frag");
    cout << "FS log:" << fs2->log().toStdString() << endl;

    program2 = new QOpenGLShaderProgram(this);
    program2->addShader(vs2);
    program2->addShader(fs2);
    program2->link();
    cout << "Link log:" << program2->log().toStdString() << endl;

    QString filename = QFileDialog::getOpenFileName(0, "Sky image", "../skyplane", "Image file (*.png *.jpg)");	
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
}

void Skyplane::preFrame()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
    
    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("sampler0", 0);

    program2->bind();
    program2->setUniformValue("sampler0", 0);

    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
    program->setUniformValue("modelViewMatrix", camera()->viewMatrix());

    program2->setUniformValue("modelViewProjectionMatrix", MVP); 
    program2->setUniformValue("modelViewMatrix", camera()->viewMatrix());

    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);
}

void Skyplane::postFrame()
{
    // unbind shader
    program->release();

    program2->release();
}

bool Skyplane::paintGL()
{
	return false; // return true only if implemented
}

