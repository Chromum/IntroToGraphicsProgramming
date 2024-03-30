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
	//std::cout << "fdsfd" << endl;
	glTranslatef(object->Transform.Position.x, object->Transform.Position.y, object->Transform.Position.z);
	glRotatef(object->Transform.Rotation.y, 1.0f, 0, 0);
	glRotatef(object->Transform.Rotation.x, 0, 1.0f, 0);
	glRotatef(object->Transform.Rotation.z, 0, 0, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	int previousLastIndicie = 0;
	int previousLastIndicieUV = 0;
    for (int j = 0; j < objectMeshes.size(); j++)
    {
        if (objectMeshes[j]->verts.empty() || objectMeshes[j]->verts.data() == NULL)
            continue;  // Skip empty mesh

        if (objectMeshes[j]->isQuadMesh)
            glBegin(GL_QUADS);
        else
            glBegin(GL_TRIANGLES);

        for (int i = 0; i < objectMeshes[j]->indicies.size(); i++)
        {
            int VertexIndicie = objectMeshes[j]->indicies[i] - 1 - previousLastIndicie;
            int UVVertexIndicie = objectMeshes[j]->UVindicies[i] - 1 - previousLastIndicieUV;

            if (0 <= UVVertexIndicie && UVVertexIndicie < objectMeshes[j]->textureUVs.size())
            {
                Vector2* UV = objectMeshes[j]->textureUVs[UVVertexIndicie];
                glTexCoord2f(
                    UV->x,
                    UV->y
                );
            }

            if (0 <= VertexIndicie && VertexIndicie < objectMeshes[j]->verts.size())
            {
                Vector3* vertex = objectMeshes[j]->verts[VertexIndicie];
                glVertex3f(
                    vertex->x * object->Transform.Scale.x,
                    vertex->y * object->Transform.Scale.y,
                    vertex->z * object->Transform.Scale.z
                );
            }

        }

        glEnd();

        previousLastIndicie = objectMeshes[j]->indicies.size() - 1 ;
        previousLastIndicieUV = objectMeshes[j]->UVindicies.size() - 1;
    }
	
}

void Renderer3D::SetTexture(GLuint image)
{
	this->texture = image;
}
