#include "isafloor.h"
#include "glwidget.h"

float Isafloor::getSuperficie(Vector a, Vector b, Vector c) {
	Vector u = b - a;
	Vector v = c - a;
	Vector w;
	w[0] = u[1] * v[2] - u[2] * v[1];
	w[1] = u[2] * v[0] - u[0] * v[2];
	w[2] = u[0] * v[1] - u[1] * v[0];
	return qSqrt(w[0] * w[0] + w[1] * w[1] + w[2] * w[2]) / 2.; 
}

void Isafloor::calculate() {
	if (scene()->objects().size() == 1) {
		float supTerra = 0.0;
		float supTotal = 0.0;
		const Object &obj = scene()->objects()[0];
		for (int i = 0; i < obj.faces().size(); i++) {
			int index0 = obj.faces()[i].vertexIndex(0);
			int index1 = obj.faces()[i].vertexIndex(1);
			int index2 = obj.faces()[i].vertexIndex(2);
			Point p0 = obj.vertices()[index0].coord();
			Point p1 = obj.vertices()[index1].coord();
			Point p2 = obj.vertices()[index2].coord();
			
			float sup = getSuperficie(p0, p1, p2);

			Vector norm = obj.faces()[i].normal();
			Vector vec = Vector(0., 0., 1.);
			float res = norm[0] * vec[0] + norm[1] * vec[1] + norm[2] * vec[2];
			if (res > 0.7)
				supTerra += sup;
			supTotal += sup;
		}
		lambda = (float) supTerra / supTotal;
		cout << "TERRA: " << lambda << endl;
	}
}

void Isafloor::onPluginLoad()
{
	QString vs_src =
    "#version 330 core\n"
    "layout (location = 0) in vec3 vertex;"
    "layout (location = 1) in vec3 normal;"
    "layout (location = 2) in vec3 color;"
    "out vec4 frontColor;"
    "uniform mat4 modelViewProjectionMatrix;"
	"uniform mat3 normalMatrix;"
	"uniform float lambda;"
	"const vec4 R = vec4(1, 0, 0, 1);"
	"const vec4 G = vec4(0, 1, 0, 1);"
    "void main() {"
	"	vec3 N = normalize(normalMatrix * normal);"
    "	frontColor = mix(R, G, lambda) * N.z;"
    "   gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);"
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

	calculate();
}

void Isafloor::preFrame()
{
	program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix()); 
	program->setUniformValue("lambda", lambda); 
}

void Isafloor::postFrame()
{
	program->release();
}

void Isafloor::onObjectAdd()
{
	calculate();
}

bool Isafloor::drawScene()
{
	return false; // return true only if implemented
}

bool Isafloor::drawObject(int)
{
	return false; // return true only if implemented
}

bool Isafloor::paintGL()
{
	return false; // return true only if implemented
}

void Isafloor::keyPressEvent(QKeyEvent *)
{
	
}

void Isafloor::mouseMoveEvent(QMouseEvent *)
{
	
}

