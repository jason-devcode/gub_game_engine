#ifndef VERTEX_TEXTURE_LINEAR_LIST_HELPER_H
#define VERTEX_TEXTURE_LINEAR_LIST_HELPER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../vectorial_2D.h"

/**
 * @brief Node of the vertex texture linear list.
 */
typedef struct VertexTextureListNode
{
    Vec2f vertexTexture;                /**< The texture coordinate of the vertex. */
    struct VertexTextureListNode *next; /**< Pointer to the next node in the list. */
} VertexTextureListNode;

/**
 * @brief Structure representing a linear list of vertex textures.
 */
typedef struct VertexTextureLinearList
{
    VertexTextureListNode *head; /**< Head of the list, the first node. */
    VertexTextureListNode *tail; /**< Tail of the list, the last node. */
    int countTextures;           /**< Count of textures in the list. */
} VertexTextureLinearList;

/**
 * @brief Creates a new vertex texture list.
 *
 * Allocates memory for a new `VertexTextureLinearList`, sets up the list to be empty, and initializes the texture count to 0.
 *
 * @return Pointer to the newly created vertex texture list structure.
 */
static inline VertexTextureLinearList *createVertexTextureLinearList()
{
    VertexTextureLinearList *list = (VertexTextureLinearList *)malloc(sizeof(VertexTextureLinearList));
    if (!list)
    {
        perror("Error allocating memory for VertexTextureLinearList");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    list->countTextures = 0;
    return list;
}

/**
 * @brief Initializes an existing vertex texture list.
 *
 * Sets up the list to be empty and initializes the texture count to 0. Assumes the list structure has already been allocated.
 *
 * @param list Pointer to the vertex texture list structure to initialize.
 */
static inline void initVertexTextureLinearList(VertexTextureLinearList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->countTextures = 0;
}

/**
 * @brief Adds a texture coordinate to the list.
 *
 * Creates a new node with the given texture coordinate and inserts it at the end of the list.
 *
 * @param list Pointer to the vertex texture list structure.
 * @param vertexTexture The texture coordinate to add to the list.
 */
static inline void addVertexTexture(VertexTextureLinearList *list, Vec2f vertexTexture)
{
    VertexTextureListNode *newNode = (VertexTextureListNode *)malloc(sizeof(VertexTextureListNode));
    if (!newNode)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    newNode->vertexTexture = vertexTexture;
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
    list->countTextures++;
}

/**
 * @brief Frees the memory used by the vertex texture list.
 *
 * Traverses the list and frees each node, then sets the head and tail to NULL and the count to 0.
 *
 * @param list Pointer to the vertex texture list structure.
 */
static inline void freeVertexTextureLinearList(VertexTextureLinearList *list)
{
    VertexTextureListNode *current = list->head;
    VertexTextureListNode *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    list->head = NULL;
    list->tail = NULL;
    list->countTextures = 0;
}

/**
 * @brief Retrieves a texture coordinate at a given index.
 *
 * Returns a pointer to the texture coordinate at the specified index. Returns NULL if the index is out of bounds.
 *
 * @param list Pointer to the vertex texture list structure.
 * @param index Index of the texture coordinate to retrieve.
 * @return Pointer to the texture coordinate at the given index or NULL if the index is invalid.
 */
static inline Vec2f *getVertexTexture(VertexTextureLinearList *list, int index)
{
    if (index < 0 || index >= list->countTextures)
    {
        return NULL; // Index out of bounds
    }

    VertexTextureListNode *current = list->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return &current->vertexTexture;
}

/**
 * @brief Finds the index of a texture coordinate in the list.
 *
 * Searches for a specific texture coordinate in the list and returns its index. Returns -1 if the texture coordinate is not found.
 *
 * @param list Pointer to the vertex texture list structure.
 * @param vertexTexture Texture coordinate to search for in the list.
 * @return Index of the texture coordinate in the list or -1 if the texture coordinate is not found.
 */
static inline int findVertexTextureIndex(VertexTextureLinearList *list, Vec2f vertexTexture)
{
    VertexTextureListNode *current = list->head;
    int index = 0;

    while (current != NULL)
    {
        if (memcmp(&current->vertexTexture, &vertexTexture, sizeof(Vec2f)) == 0)
        {
            return index; // Texture coordinate found
        }
        current = current->next;
        index++;
    }

    return -1; // Texture coordinate not found
}

/**
 * @brief Converts the vertex texture list to a dynamic array of texture coordinates.
 *
 * Creates a new array containing all the texture coordinates from the list in the same order.
 * The memory for the array is allocated dynamically. Returns NULL if the list is empty.
 *
 * @param list Pointer to the vertex texture list structure.
 * @return Pointer to the array of texture coordinates or NULL if the list is empty.
 */
static inline Vec2f *convertTextureListToArray(VertexTextureLinearList *list)
{
    if (list->countTextures == 0)
    {
        return NULL; // No texture coordinates to convert
    }

    Vec2f *array = (Vec2f *)malloc(list->countTextures * sizeof(Vec2f));
    if (!array)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    VertexTextureListNode *current = list->head;
    for (int i = 0; i < list->countTextures; i++)
    {
        array[i] = current->vertexTexture;
        current = current->next;
    }

    return array;
}

#endif // VERTEX_TEXTURE_LINEAR_LIST_HELPER_H
