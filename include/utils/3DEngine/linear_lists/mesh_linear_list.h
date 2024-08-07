#ifndef MESH_LINEAR_LIST_HELPER_H
#define MESH_LINEAR_LIST_HELPER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../mesh.h"

/**
 * @brief Node of the mesh linear list.
 */
typedef struct MeshListNode
{
    Mesh3D mesh;                  /**< The mesh itself. */
    struct MeshListNode *next; /**< Pointer to the next node in the list. */
} MeshListNode;

/**
 * @brief Structure representing a linear list of meshes.
 */
typedef struct MeshLinearList
{
    MeshListNode *head; /**< Head of the list, the first node. */
    int countMeshes;    /**< Count of meshes in the list. */
} MeshLinearList;

/**
 * @brief Creates a new mesh list.
 *
 * Allocates memory for a new `MeshLinearList`, sets up the list to be empty, and initializes the mesh count to 0.
 *
 * @return Pointer to the newly created mesh list structure.
 */
static inline MeshLinearList *createMeshLinearList()
{
    MeshLinearList *list = (MeshLinearList *)malloc(sizeof(MeshLinearList));
    if (!list)
    {
        perror("Error allocating memory for MeshLinearList");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->countMeshes = 0;
    return list;
}

/**
 * @brief Initializes an existing mesh list.
 *
 * Sets up the list to be empty and initializes the mesh count to 0. Assumes the list structure has already been allocated.
 *
 * @param list Pointer to the mesh list structure to initialize.
 */
static inline void initMeshLinearList(MeshLinearList *list)
{
    list->head = NULL;
    list->countMeshes = 0;
}

/**
 * @brief Adds a mesh to the list.
 *
 * Creates a new node with the given mesh and inserts it at the beginning of the list.
 *
 * @param list Pointer to the mesh list structure.
 * @param mesh The mesh to add to the list.
 */
static inline void addMesh(MeshLinearList *list, Mesh3D mesh)
{
    MeshListNode *newNode = (MeshListNode *)malloc(sizeof(MeshListNode));
    if (!newNode)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    newNode->mesh = mesh;
    newNode->next = list->head;
    list->head = newNode;
    list->countMeshes++;
}

/**
 * @brief Frees the memory used by the mesh list.
 *
 * Traverses the list and frees each node, then sets the head to NULL and the count to 0.
 *
 * @param list Pointer to the mesh list structure.
 */
static inline void freeMeshLinearList(MeshLinearList *list)
{
    MeshListNode *current = list->head;
    MeshListNode *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        // Free the mesh's dynamically allocated data if needed
        // e.g., freeMeshData(&current->mesh);
        free(current);
        current = nextNode;
    }

    list->head = NULL;
    list->countMeshes = 0;
}

/**
 * @brief Retrieves a mesh at a given index.
 *
 * Returns a pointer to the mesh at the specified index. Returns NULL if the index is out of bounds.
 *
 * @param list Pointer to the mesh list structure.
 * @param index Index of the mesh to retrieve.
 * @return Pointer to the mesh at the given index or NULL if the index is invalid.
 */
static inline Mesh3D *getMesh(MeshLinearList *list, int index)
{
    if (index < 0 || index >= list->countMeshes)
    {
        return NULL; // Index out of bounds
    }

    MeshListNode *current = list->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return &current->mesh;
}

/**
 * @brief Finds the index of a mesh in the list.
 *
 * Searches for a specific mesh in the list and returns its index. Returns -1 if the mesh is not found.
 *
 * @param list Pointer to the mesh list structure.
 * @param mesh Mesh to search for in the list.
 * @return Index of the mesh in the list or -1 if the mesh is not found.
 */
static inline int findMeshIndex(MeshLinearList *list, Mesh3D mesh)
{
    MeshListNode *current = list->head;
    int index = 0;

    while (current != NULL)
    {
        // Comparison should be adapted to compare Mesh3D structures correctly
        // e.g., if (compareMeshes(&current->mesh, &mesh) == 0)
        if (memcmp(&current->mesh, &mesh, sizeof(Mesh3D)) == 0)
        {
            return index; // Mesh found
        }
        current = current->next;
        index++;
    }

    return -1; // Mesh not found
}

/**
 * @brief Converts the mesh list to a dynamic array of meshes.
 *
 * Creates a new array containing all the meshes from the list in the same order.
 * The memory for the array is allocated dynamically. Returns NULL if the list is empty.
 *
 * @param list Pointer to the mesh list structure.
 * @return Pointer to the array of meshes or NULL if the list is empty.
 */
static inline Mesh3D *convertMeshListToArray(MeshLinearList *list)
{
    if (list->countMeshes == 0)
    {
        return NULL; // No meshes to convert
    }

    Mesh3D *array = (Mesh3D *)malloc(list->countMeshes * sizeof(Mesh3D));
    if (!array)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    MeshListNode *current = list->head;
    for (int i = 0; i < list->countMeshes; i++)
    {
        array[i] = current->mesh;
        current = current->next;
    }

    return array;
}

#endif // MESH_LINEAR_LIST_HELPER_H