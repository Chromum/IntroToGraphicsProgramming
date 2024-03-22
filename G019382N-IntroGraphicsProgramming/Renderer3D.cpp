#include "Renderer3D.h"
#include "GLObject.h"
#include "GLUTUtils.h"

Renderer3D::Renderer3D(GLObject* object)
{
	this->object = object;
}

Renderer3D::Renderer3D(EventHandler* handler, GLObject* object)
{
	this->object = object;
	handler->AddHandler([&]() {
		RenderUpdate();
		});
}

void Renderer3D::RenderUpdate()
{
	glLoadIdentity();

	glTranslatef(object->Transform.Position.x, object->Transform.Position.y, object->Transform.Position.z);
	glRotatef(object->Transform.Rotation.y, 1.0f, 0, 0);
	glRotatef(object->Transform.Rotation.x, 0, 1.0f, 0);
	glRotatef(object->Transform.Rotation.z, 0, 0, 1.0f);

	glBegin(GL_QUADS);
	{
		glColor3f(color.r,color.g,color.b);


		int l = objectMesh.verts.size();
		for (int i = 0; i < l; i++)
		{
			glVertex3f((GLfloat(objectMesh.verts[i].x)), (GLfloat(objectMesh.verts[i].y)), (GLfloat(objectMesh.verts[i].z)));
		}

		glEnd();
	}
}
