#include "Renderer3D.h"
#include "GLObject.h"
#include "GLUTUtils.h"
#include "Image.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "GL/freeglut_ext.h"
#include "GL/freeglut_std.h"
#include "ModelLoader.h"
#include "LinkedList.h"
#include "SceneObject.h"

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

	glTranslated(object->Transform.Position.x, object->Transform.Position.y, object->Transform.Position.z);

    if (object->Transform.Rotation.x >= 360.0f)
        object->Transform.Rotation.x = 0.0f;

    if (object->Transform.Rotation.y >= 360.0f)
        object->Transform.Rotation.y = 0.0f;

    if (object->Transform.Rotation.z >= 360.0f)
        object->Transform.Rotation.z = 0.0f;

	glRotatef(object->Transform.Rotation.y, 1.0f, 0, 0);
	glRotatef(object->Transform.Rotation.x, 0, 1.0f, 0);
	glRotatef(object->Transform.Rotation.z, 0, 0, 1.0f);
    glScalef(object->Transform.Scale.x, object->Transform.Scale.y, object->Transform.Scale.z);
    glEnable(GL_TEXTURE_2D);


    int previousLastVertex = 0;
    int previousLastUV = 0;
    int previousLastNormal = 0;

    for (int j = 0; j < objectMeshes.size(); j++)
    {
        Mesh* objectMesh = objectMeshes[j];
        glEnable(GL_TEXTURE_2D);
        if(objectMesh->texture != 0)
            glBindTexture(GL_TEXTURE_2D, (GLuint)objectMesh->texture);
        else
            glBindTexture(GL_TEXTURE_2D, 2);

        glMaterialfv(GL_FRONT, GL_AMBIENT, &(objectMesh->matData->ambient.x));
        glMaterialfv(GL_FRONT, GL_SPECULAR, &(objectMesh->matData->specular.x));
        glMaterialfv(GL_FRONT, GL_DIFFUSE, &(objectMesh->matData->diffuse.x));



        if (objectMesh->verts.empty() || objectMesh->verts.data() == nullptr)
            continue;  // Skip empty mesh

        if (objectMesh->isQuadMesh)
            glBegin(GL_QUADS);
        else
            glBegin(GL_TRIANGLES);

        for (int i = 0; i < objectMesh->indicies.size(); i++)
        {
            

            int VertexIndicie = objectMesh->indicies[i] - 1 - previousLastVertex;
            int UVVertexIndicie = objectMesh->UVindicies[i] - 1 - previousLastUV;
            int NormalIndicie = objectMesh->Normalindicies[i] - 1 - previousLastNormal;

            if (0 <= NormalIndicie && NormalIndicie < objectMesh->Normalindicies.size())
            {
                Vector3* normal = objectMesh->normals[NormalIndicie];
                glNormal3f(normal->x, normal->y, normal->z);
            }

            if (0 <= UVVertexIndicie && UVVertexIndicie < objectMesh->textureUVs.size())
            {
                Vector2* UV = objectMesh->textureUVs[UVVertexIndicie];
                glTexCoord2f(UV->x, UV->y);
            }

            if (0 <= VertexIndicie && VertexIndicie < objectMesh->verts.size())
            {
                Vector3* vertex = objectMesh->verts[VertexIndicie];
                glVertex3f(vertex->x, vertex->y, vertex->z);
            }
        }

        glEnd();

        // Update previous last indices
        previousLastVertex += objectMesh->verts.size();
        previousLastUV += objectMesh->textureUVs.size();
        previousLastNormal += objectMesh->normals.size();

    }
}


void Renderer3D::SetTexture(GLuint image)
{
	this->texture = image;



}
