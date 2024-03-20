#include "Render3DComponent.h"
#include "GLObject.h"

Render3DComponent::Render3DComponent(EventHandler* handler)
{
	handler->AddHandler([&]() {
		RenderUpdate();
		});
}


void Render3DComponent::RenderUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	GLObject* object = GLComponent::GetParent();
	glTranslatef(object->Transform.Position.x, object->Transform.Position.y, object->Transform.Position.z);
	glRotatef(object->Transform.Rotation.y, 1.0f, 0, 0);
	glRotatef(object->Transform.Rotation.x, 0, 1.0f, 0);
	glRotatef(object->Transform.Rotation.z, 0, 0, 1.0f);

	glBegin(GL_QUADS);
	{
		glColor3f(1, 0, 0);

		
		int l = objectMesh.verts.size();
		for (int i = 0; i < l; i++)
		{
			glVertex3f((GLfloat(objectMesh.verts[i].x)), (GLfloat(objectMesh.verts[i].y)), (GLfloat(objectMesh.verts[i].z)));
		}

		glEnd();
	}
	glFlush();
	glPopMatrix();
}



