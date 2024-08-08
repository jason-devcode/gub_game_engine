#ifndef FACE_LINEAR_LIST_HELPER_H
#define FACE_LINEAR_LIST_HELPER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../mesh.h"

/**
 * @brief Node of the face linear list.
 */
typedef struct FaceListNode
{
    FaceIndices face;          /**< The face itself. */
    struct FaceListNode *next; /**< Pointer to the next node in the list. */
} FaceListNode;

/**
 * @brief Structure representing a linear list of faces.
 */
typedef struct FaceLinearList
{
    FaceListNode *head; /**< Head of the list, the first node. */
    int countFaces;     /**< Count of faces in the list. */
} FaceLinearList;

/**
 * @brief Creates a new face list.
 *
 * Allocates memory for a new `FaceLinearList`, sets up the list to be empty, and initializes the face count to 0.
 *
 * @return Pointer to the newly created face list structure.
 */
static inline FaceLinearList *createFaceLinearList()
{
    FaceLinearList *list = (FaceLinearList *)malloc(sizeof(FaceLinearList));
    if (!list)
    {
        fprintf(stderr, "Error allocating memory for FaceLinearList\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->countFaces = 0;
    return list;
}

/**
 * @brief Initializes an existing face list.
 *
 * Sets up the list to be empty and initializes the face count to 0. Assumes the list structure has already been allocated.
 *
 * @param list Pointer to the face list structure to initialize.
 */
static inline void initFaceLinearList(FaceLinearList *list)
{
    list->head = NULL;
    list->countFaces = 0;
}

/**
 * @brief Adds a face to the list.
 *
 * Creates a new node with the given face and inserts it at the beginning of the list.
 *
 * @param list Pointer to the face list structure.
 * @param face The face to add to the list.
 */
static inline void addFace(FaceLinearList *list, FaceIndices face)
{
    FaceListNode *newNode = (FaceListNode *)malloc(sizeof(FaceListNode));
    if (!newNode)
    {
        fprintf(stderr, "Error allocating memory for FaceListNode\n");
        exit(EXIT_FAILURE);
    }
    newNode->face = face;
    newNode->next = list->head;
    list->head = newNode;
    list->countFaces++;
}

/**
 * @brief Frees the memory used by the face list.
 *
 * Traverses the list and frees each node, then sets the head to NULL and the count to 0.
 *
 * @param list Pointer to the face list structure.
 */
static inline void freeFaceLinearList(FaceLinearList *list)
{
    FaceListNode *current = list->head;
    FaceListNode *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    list->head = NULL;
    list->countFaces = 0;
}

/**
 * @brief Retrieves a face at a given index.
 *
 * Returns a pointer to the face at the specified index. Returns NULL if the index is out of bounds.
 *
 * @param list Pointer to the face list structure.
 * @param index Index of the face to retrieve.
 * @return Pointer to the face at the given index or NULL if the index is invalid.
 */
static inline FaceIndices *getFace(FaceLinearList *list, int index)
{
    if (index < 0 || index >= list->countFaces)
    {
        return NULL; // Index out of bounds
    }

    FaceListNode *current = list->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return &current->face;
}

/**
 * @brief Finds the index of a face in the list.
 *
 * Searches for a specific face in the list and returns its index. Returns -1 if the face is not found.
 *
 * @param list Pointer to the face list structure.
 * @param face Face to search for in the list.
 * @return Index of the face in the list or -1 if the face is not found.
 */
static inline int findFaceIndex(FaceLinearList *list, FaceIndices face)
{
    FaceListNode *current = list->head;
    int index = 0;

    while (current != NULL)
    {
        if (memcmp(&current->face, &face, sizeof(FaceIndices)) == 0)
        {
            return index; // Face found
        }
        current = current->next;
        index++;
    }

    return -1; // Face not found
}

/**
 * @brief Converts the face list to a dynamic array of faces.
 *
 * Creates a new array containing all the faces from the list in the same order.
 * The memory for the array is allocated dynamically. Returns NULL if the list is empty.
 *
 * @param list Pointer to the face list structure.
 * @return Pointer to the array of faces or NULL if the list is empty.
 */
static inline FaceIndices *convertFaceListToArray(FaceLinearList *list)
{
    if (list->countFaces == 0)
    {
        return NULL; // No faces to convert
    }

    FaceIndices *array = (FaceIndices *)malloc(list->countFaces * sizeof(FaceIndices));
    if (!array)
    {
        fprintf(stderr, "Error allocating memory for face array\n");
        exit(EXIT_FAILURE);
    }

    FaceListNode *current = list->head;
    for (int i = 0; i < list->countFaces; i++)
    {
        memcpy(&array[i], &current->face, sizeof(FaceIndices));
        current = current->next;
    }

    return array;
}

#endif // FACE_LINEAR_LIST_HELPER_H