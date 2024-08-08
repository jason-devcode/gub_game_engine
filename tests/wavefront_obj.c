#include "../include/utils/wavefront_obj.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    MeshGroup *meshes = readWavefrontObj("mock/skull.obj");
    printMeshGroupData(meshes);
    releaseMeshGroupResources(meshes);
    meshes = NULL;
    return EXIT_SUCCESS;
}
