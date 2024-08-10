#include "../include/utils/3DEngine/geometry/plane.h"


int main()
{
    MeshGroup* plane = generatePlane3D(4,4,1);
    printMeshGroupData(plane);
    releaseMeshGroupResources(plane);
}