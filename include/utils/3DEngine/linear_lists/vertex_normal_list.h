#ifndef VERTEX_NORMAL_LINEAR_LIST_HELPER_H
#define VERTEX_NORMAL_LINEAR_LIST_HELPER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../vectorial_3D.h"

/**
 * @brief Node of the vertex normal linear list.
 */
typedef struct VertexNormalListNode
{
    Vec3f vertexNormal;                /**< The normal vector of the vertex. */
    struct VertexNormalListNode *next; /**< Pointer to the next node in the list. */
} VertexNormalListNode;

/**
 * @brief Structure representing a linear list of vertex normals.
 */
typedef struct VertexNormalLinearList
{
    VertexNormalListNode *head; /**< Head of the list, the first node. */
    VertexNormalListNode *tail; /**< Tail of the list, the last node. */
    int countNormals;           /**< Count of normals in the list. */
} VertexNormalLinearList;

/**
 * @brief Creates a new vertex normal list.
 *
 * Allocates memory for a new `VertexNormalLinearList`, sets up the list to be empty, and initializes the normal count to 0.
 *
 * @return Pointer to the newly created vertex normal list structure.
 */
static inline VertexNormalLinearList *createVertexNormalLinearList()
{
    VertexNormalLinearList *list = (VertexNormalLinearList *)malloc(sizeof(VertexNormalLinearList));
    if (!list)
    {
        perror("Error allocating memory for VertexNormalLinearList");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    list->countNormals = 0;
    return list;
}

/**
 * @brief Initializes an existing vertex normal list.
 *
 * Sets up the list to be empty and initializes the normal count to 0. Assumes the list structure has already been allocated.
 *
 * @param list Pointer to the vertex normal list structure to initialize.
 */
static inline void initVertexNormalLinearList(VertexNormalLinearList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->countNormals = 0;
}

/**
 * @brief Adds a normal vector to the list.
 *
 * Creates a new node with the given normal vector and inserts it at the end of the list.
 *
 * @param list Pointer to the vertex normal list structure.
 * @param vertexNormal The normal vector to add to the list.
 */
static inline void addVertexNormal(VertexNormalLinearList *list, Vec3f vertexNormal)
{
    VertexNormalListNode *newNode = (VertexNormalListNode *)malloc(sizeof(VertexNormalListNode));
    if (!newNode)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    newNode->vertexNormal = vertexNormal;
    newNode->next = NULL;

    if (list->tail)
    {
        list->tail->next = newNode;
    }
    else
    {
        list->head = newNode;
    }
    list->tail = newNode;
    list->countNormals++;
}

/**
 * @brief Frees the memory used by the vertex normal list.
 *
 * Traverses the list and frees each node, then sets the head and tail to NULL and the count to 0.
 *
 * @param list Pointer to the vertex normal list structure.
 */
static inline void freeVertexNormalLinearList(VertexNormalLinearList *list)
{
    VertexNormalListNode *current = list->head;
    VertexNormalListNode *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    list->head = NULL;
    list->tail = NULL;
    list->countNormals = 0;
}

/**
 * @brief Retrieves a normal vector at a given index.
 *
 * Returns a pointer to the normal vector at the specified index. Returns NULL if the index is out of bounds.
 *
 * @param list Pointer to the vertex normal list structure.
 * @param index Index of the normal vector to retrieve.
 * @return Pointer to the normal vector at the given index or NULL if the index is invalid.
 */
static inline Vec3f *getVertexNormal(VertexNormalLinearList *list, int index)
{
    if (index < 0 || index >= list->countNormals)
    {
        return NULL; // Index out of bounds
    }

    VertexNormalListNode *current = list->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return &current->vertexNormal;
}

/**
 * @brief Finds the index of a normal vector in the list.
 *
 * Searches for a specific normal vector in the list and returns its index. Returns -1 if the normal vector is not found.
 *
 * @param list Pointer to the vertex normal list structure.
 * @param vertexNormal Normal vector to search for in the list.
 * @return Index of the normal vector in the list or -1 if the normal vector is not found.
 */
static inline int findVertexNormalIndex(VertexNormalLinearList *list, Vec3f vertexNormal)
{
    VertexNormalListNode *current = list->head;
    int index = 0;

    while (current != NULL)
    {
        if (memcmp(&current->vertexNormal, &vertexNormal, sizeof(Vec3f)) == 0)
        {
            return index; // Normal vector found
        }
        current = current->next;
        index++;
    }

    return -1; // Normal vector not found
}

/**
 * @brief Converts the vertex normal list to a dynamic array of normal vectors.
 *
 * Creates a new array containing all the normal vectors from the list in the same order.
 * The memory for the array is allocated dynamically. Returns NULL if the list is empty.
 *
 * @param list Pointer to the vertex normal list structure.
 * @return Pointer to the array of normal vectors or NULL if the list is empty.
 */
static inline Vec3f *convertNormalListToArray(VertexNormalLinearList *list)
{
    if (list->countNormals == 0)
    {
        return NULL; // No normal vectors to convert
    }

    Vec3f *array = (Vec3f *)malloc(list->countNormals * sizeof(Vec3f));
    if (!array)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    VertexNormalListNode *current = list->head;
    for (int i = 0; i < list->countNormals; i++)
    {
        array[i] = current->vertexNormal;
        current = current->next;
    }

    return array;
}

#endif // VERTEX_NORMAL_LINEAR_LIST_HELPER_H