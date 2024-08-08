#ifndef VERTEX_LINEAR_LIST_HELPER_H
#define VERTEX_LINEAR_LIST_HELPER_H

#include "../vectorial_3D.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Node of the vertex linear list.
 */
typedef struct VertexListNode
{
    Vec3f vertex;                /**< The vertex itself. */
    struct VertexListNode *next; /**< Pointer to the next node in the list. */
} VertexListNode;

/**
 * @brief Structure representing a linear list of vertices.
 */
typedef struct VertexLinearList
{
    VertexListNode *head; /**< Head of the list, the first node. */
    int countVertices;    /**< Count of vertices in the list. */
} VertexLinearList;

/**
 * @brief Creates a new vertex list.
 *
 * Allocates memory for a new `VertexLinearList`, sets up the list to be empty, and initializes the vertex count to 0.
 *
 * @return Pointer to the newly created vertex list structure.
 */
static inline VertexLinearList *createVertexLinearList()
{
    VertexLinearList *list = (VertexLinearList *)malloc(sizeof(VertexLinearList));
    if (!list)
    {
        perror("Error allocating memory for VertexLinearList");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->countVertices = 0;
    return list;
}

/**
 * @brief Initializes an existing vertex list.
 *
 * Sets up the list to be empty and initializes the vertex count to 0. Assumes the list structure has already been allocated.
 *
 * @param list Pointer to the vertex list structure to initialize.
 */
static inline void initVertexLinearList(VertexLinearList *list)
{
    list->head = NULL;
    list->countVertices = 0;
}

/**
 * @brief Adds a vertex to the list.
 *
 * Creates a new node with the given vertex and inserts it at the beginning of the list.
 *
 * @param list Pointer to the vertex list structure.
 * @param vertex The vertex to add to the list.
 */
static inline void addVertex(VertexLinearList *list, Vec3f vertex)
{
    VertexListNode *newNode = (VertexListNode *)malloc(sizeof(VertexListNode));
    if (!newNode)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = vertex;
    newNode->next = list->head;
    list->head = newNode;
    list->countVertices++;
}

/**
 * @brief Frees the memory used by the vertex list.
 *
 * Traverses the list and frees each node, then sets the head to NULL and the count to 0.
 *
 * @param list Pointer to the vertex list structure.
 */
static inline void freeVertexLinearList(VertexLinearList *list)
{
    VertexListNode *current = list->head;
    VertexListNode *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    list->head = NULL;
    list->countVertices = 0;
}

/**
 * @brief Retrieves a vertex at a given index.
 *
 * Returns a pointer to the vertex at the specified index. Returns NULL if the index is out of bounds.
 *
 * @param list Pointer to the vertex list structure.
 * @param index Index of the vertex to retrieve.
 * @return Pointer to the vertex at the given index or NULL if the index is invalid.
 */
static inline Vec3f *getVertex(VertexLinearList *list, int index)
{
    if (index < 0 || index >= list->countVertices)
    {
        return NULL; // Index out of bounds
    }

    VertexListNode *current = list->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return &current->vertex;
}

/**
 * @brief Finds the index of a vertex in the list.
 *
 * Searches for a specific vertex in the list and returns its index. Returns -1 if the vertex is not found.
 *
 * @param list Pointer to the vertex list structure.
 * @param vertex Vertex to search for in the list.
 * @return Index of the vertex in the list or -1 if the vertex is not found.
 */
static inline int findVertexIndex(VertexLinearList *list, Vec3f vertex)
{
    VertexListNode *current = list->head;
    int index = 0;

    while (current != NULL)
    {
        if (memcmp(&current->vertex, &vertex, sizeof(Vec3f)) == 0)
        {
            return index; // Vertex found
        }
        current = current->next;
        index++;
    }

    return -1; // Vertex not found
}

/**
 * @brief Converts the vertex list to a dynamic array of vertices.
 *
 * Creates a new array containing all the vertices from the list in the same order.
 * The memory for the array is allocated dynamically. Returns NULL if the list is empty.
 *
 * @param list Pointer to the vertex list structure.
 * @return Pointer to the array of vertices or NULL if the list is empty.
 */
static inline Vec3f *convertVertexListToArray(VertexLinearList *list)
{
    if (list->countVertices == 0)
    {
        return NULL; // No vertices to convert
    }

    Vec3f *array = (Vec3f *)malloc(list->countVertices * sizeof(Vec3f));
    if (!array)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    VertexListNode *current = list->head;
    for (int i = 0; i < list->countVertices; i++)
    {
        array[i] = current->vertex;
        current = current->next;
    }

    return array;
}

#endif // VERTEX_LINEAR_LIST_HELPER_H