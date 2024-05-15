#include "Renderer3D.h"
#include "GLObject.h"
#include "GLUTUtils.h"
#include "Image.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "GL/freeglut_ext.h"
#include "GL/freeglut_std.h"
#include "ModelLoader.h"


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
    glMatrixMode(GL_MODELVIEW);
    glColor3f(1,1,1);
	glTranslatef(object->Transform.Position.x, object->Transform.Position.y, object->Transform.Position.z);
	glRotatef(object->Transform.Rotation.y, 1.0f, 0, 0);
	glRotatef(object->Transform.Rotation.x, 0, 1.0f, 0);
	glRotatef(object->Transform.Rotation.z, 0, 0, 1.0f);
    glScalef(object->Transform.Scale.x, object->Transform.Scale.y, object->Transform.Scale.z);
    glEnable(GL_TEXTURE_2D);


    int previousLastVertex = 0;
    int previousLastUV = 0;

    for (int j = 0; j < objectMeshes.size(); j++)
    {
        glEnable(GL_TEXTURE_2D);
        if(objectMeshes[j]->texture != 0)
            glBindTexture(GL_TEXTURE_2D, (GLuint)objectMeshes[j]->texture);
        else
            glBindTexture(GL_TEXTURE_2D, 1);

        glMaterialfv(GL_FRONT, GL_AMBIENT, &(objectMeshes[j]->matData->ambient.x));
        glMaterialfv(GL_FRONT, GL_SPECULAR, &(objectMeshes[j]->matData->specular.x));
        glMaterialfv(GL_FRONT, GL_DIFFUSE, &(objectMeshes[j]->matData->diffuse.x));



        if (objectMeshes[j]->verts.empty() || objectMeshes[j]->verts.data() == nullptr)
            continue;  // Skip empty mesh

        if (objectMeshes[j]->isQuadMesh)
            glBegin(GL_QUADS);
        else
            glBegin(GL_TRIANGLES);

        for (int i = 0; i < objectMeshes[j]->indicies.size(); i++)
        {
            int VertexIndicie = objectMeshes[j]->indicies[i] - 1 - previousLastVertex;
            int UVVertexIndicie = objectMeshes[j]->UVindicies[i] - 1 - previousLastUV;

            if (0 <= UVVertexIndicie && UVVertexIndicie < objectMeshes[j]->textureUVs.size())
            {
                Vector2* UV = objectMeshes[j]->textureUVs[UVVertexIndicie];
                glTexCoord2f(UV->x, UV->y);
            }

            if (0 <= VertexIndicie && VertexIndicie < objectMeshes[j]->verts.size())
            {
                Vector3* vertex = objectMeshes[j]->verts[VertexIndicie];
                glVertex3f(vertex->x, vertex->y, vertex->z);
            }
        }

        glEnd();

        // Update previous last indices
        previousLastVertex += objectMeshes[j]->verts.size();
        previousLastUV += objectMeshes[j]->textureUVs.size();
    }



}

void Renderer3D::SetTexture(GLuint image)
{
	this->texture = image;
}
