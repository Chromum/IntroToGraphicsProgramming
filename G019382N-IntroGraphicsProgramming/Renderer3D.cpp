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

	if(objectMesh->isQuadMesh)
		glBegin(GL_QUADS);
	else
		glBegin(GL_TRIANGLES); 
	{
		glEnable(GL_TEXTURE_2D);
		//glColor3f(color.r,color.g,color.b);
		std::cout << objectMesh->textureUVs[0];
		GLuint tex;
		glGenTextures(1, &tex);
		//glactivetexture()
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE,texture.colors.data());
		glBindTexture(GL_TEXTURE_2D, tex);


			for (int i = 0; i < objectMesh->indicies.size(); i++)
		{
			Vector3* vertex = objectMesh->verts[objectMesh->indicies[i] - 1];
			Vector2* UV = objectMesh->textureUVs[objectMesh->indicies[i] - 1];
			//float r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
			//float g = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
			//float b = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));

			//glColor3f(r, g, b);
			glTexCoord2f(UV->x, UV->y);
			glVertex3f(vertex->x*object->Transform.Scale.x, vertex->y  * object->Transform.Scale.y, vertex->z * object->Transform.Scale.z);
		}
		glDisable(GL_TEXTURE_2D);
		glEnd();
	}
}

void Renderer3D::SetTexture(Image* image)
{
	this->texture = *image;
}
