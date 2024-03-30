#include "Renderer3D.h"
#include "GLObject.h"
#include "GLUTUtils.h"
#include "Image.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "GL/freeglut_ext.h"
#include "GL/freeglut_std.h"


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

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	if(objectMesh->isQuadMesh)
		glBegin(GL_QUADS);
	else
		glBegin(GL_TRIANGLES); 
	{

		for (int i = 0; i < objectMesh->indicies.size(); i++)
		{
			Vector3* vertex = objectMesh->verts[objectMesh->indicies[i] - 1];
			Vector2* UV = objectMesh->textureUVs[objectMesh->UVindicies[i] - 1];

			glTexCoord2f(UV->x, UV->y);
			//glColor3f(vertex->x, vertex->y, vertex->z);
			glVertex3f(vertex->x * object->Transform.Scale.x, vertex->y * object->Transform.Scale.y, vertex->z * object->Transform.Scale.z);
		}

		glDisable(GL_TEXTURE_2D);
		glEnd();
	}
}

void Renderer3D::SetTexture(GLuint image)
{
	this->texture = image;
}
