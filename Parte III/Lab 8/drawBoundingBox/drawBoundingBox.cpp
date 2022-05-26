#include "drawBoundingBox.h"
#include "glwidget.h"

void DrawBoundingBox::onPluginLoad()
{
	vector<float> vertices;   // (x,y,z)
    vector<float> normals; // (nx,ny,nz)
    vector<float> colors; // (r,g,b)
    vector<float> texCoords; // (s,t)
    vector<unsigned int> indices; //i0,i1,i2, i3,i4,i5...
    for(int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int z = 0; z < 2; z++) {
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                cout << x << " " << y << " " << z << endl;
            }
        }
    }
	// front face
	indices.push_back(1);
	indices.push_back(5);
	indices.push_back(3);
	indices.push_back(5);
	indices.push_back(7);
	indices.push_back(3);
	//back face
	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(2);
    indices.push_back(0);
    indices.push_back(4);
    indices.push_back(2);
	// right face
	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(7);
    indices.push_back(4);
    indices.push_back(6);
    indices.push_back(7);
	// left face
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(3);
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);
	// up face
	indices.push_back(3);
	indices.push_back(7);
	indices.push_back(6);
    indices.push_back(6);
    indices.push_back(2);
    indices.push_back(7);
	// down face
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(4);
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(1);

    numIndices = indices.size();

    GLWidget &g = *glwidget();

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

    g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);

    g.glBindVertexArray(0);

    // Carregar shader, compile & link 
    QString vs_src =
      "#version 330 core\n"
      "layout (location = 0) in vec3 vertex;"
      "uniform mat4 modelViewProjectionMatrix;"
	  "uniform mat4 T;"
      "void main() {"
      "  gl_Position = modelViewProjectionMatrix * T * vec4(vertex,1.0);"
      "}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    cout << "VS log:" << vs->log().toStdString() << endl;

    QString fs_src =
      "#version 330 core\n"
      "out vec4 fragColor;"
      "void main() {"
      "  fragColor = vec4(1, 0, 0, 1);"
      "}";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
}

void DrawBoundingBox::postFrame()
{
    program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
	QMatrix4x4 T;
	T.translate(1., 0., 1.);
	T.scale(2., 2., 2.);
    program->setUniformValue("T", T); 
	GLWidget &g = *glwidget();
    // Draw a single instance of the 3D model
    g.glBindVertexArray(VAO);
    g.glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (GLvoid*)0);
    //numIndices=indices.size()
    g.glBindVertexArray(0);
}

