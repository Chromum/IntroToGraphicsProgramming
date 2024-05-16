#include "SceneObject.h"
#include "LinkedList.h"
#include "GLObject.h"


void SceneObject::AddChild(SceneObject* child)
{
	if (this->graph == nullptr)
		graph = new LinkedList(this);

	graph->AddNodeToEnd(child);
}
