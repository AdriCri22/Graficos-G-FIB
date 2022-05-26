#include "resaltatObjecteTeclat.h"
#include "glwidget.h"

void ResaltatObjecteTeclat::onPluginLoad()
{
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(glwidget()->getPluginPath()+"/../resaltatObjecteTeclat/resaltatObjecteTeclat.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(glwidget()->getPluginPath()+"/../resaltatObjecteTeclat/resaltatObjecteTeclat.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

	created = false;
}

void ResaltatObjecteTeclat::postFrame() {
	int sel = scene()->selectedObject();
	if (sel >= 0 && sel < (int) scene()->objects().size()) {
		program->bind();

		// Create buffers
		GLWidget& g = *glwidget();
		g.makeCurrent();
		if (!created) {
			created = true;

			GLfloat cube_vertices[] = {
				0, 0, 0,
				0, 0, 1,
				0, 1, 0,

				0, 0, 1,
				0, 1, 0,
				0, 1, 1,

				1, 0, 0,
				1, 0, 1,
				1, 1, 0,

				1, 0, 1,
				1, 1, 0,
				1, 1, 1,

				0, 0, 0,
				0, 0, 1,
				1, 0, 0,

				0, 0, 1,
				1, 0, 0,
				1, 0, 1,

				0, 1, 0,
				0, 1, 1,
				1, 1, 0,

				0, 1, 1,
				1, 1, 0,
				1, 1, 1,

				0, 0, 0,
				0, 1, 0,
				1, 0, 0,

				0, 1, 0,
				1, 0, 0,
				1, 1, 0,

				0, 0, 1,
				0, 1, 1,
				1, 0, 1,

				0, 1, 1,
				1, 0, 1,
				1, 1, 1
			};

			GLfloat cube_colors[] = {
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0
			};

			// VAO Box
			g.glGenVertexArrays(1, &cubeVAO);
			g.glBindVertexArray(cubeVAO);

			// VBOs Box
			g.glGenBuffers(1, &verticesVBO);
			g.glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
			g.glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
			g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			g.glEnableVertexAttribArray(0);

			g.glGenBuffers(1, &colorVBO);
			g.glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
			g.glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
			g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
			g.glEnableVertexAttribArray(2);

			g.glBindVertexArray(0);
		}

		program->setUniformValue("modelViewProjectionMatrix", camera()->projectionMatrix() * camera()->viewMatrix());
		const Object &obj = scene()->objects()[sel];
		program->setUniformValue("boundingBoxMin", obj.boundingBox().min());
		program->setUniformValue("boundingBoxMax", obj.boundingBox().max());
		g.glBindVertexArray(cubeVAO);
		g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		g.glDrawArrays(GL_TRIANGLES, 0, 36);
		g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		g.glBindVertexArray(0);
	}
}

void ResaltatObjecteTeclat::keyPressEvent(QKeyEvent *e) {
    if (e->key()>=Qt::Key_0 && e->key()<=Qt::Key_9){
        int obj = e->key()-Qt::Key_0;
        if (obj<0 || obj>=(int)scene()->objects().size()) obj = -1;
        scene()->setSelectedObject(obj);
        glwidget()->update();
    }
}