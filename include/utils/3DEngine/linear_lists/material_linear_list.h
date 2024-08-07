#ifndef MATERIAL_LINEAR_LIST_HELPER_H
#define MATERIAL_LINEAR_LIST_HELPER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../material.h"

/**
 * @brief Node of the material linear list.
 */
typedef struct MaterialListNode
{
    Material material;             /**< The material itself. */
    struct MaterialListNode *next; /**< Pointer to the next node in the list. */
} MaterialListNode;

/**
 * @brief Structure representing a linear list of materials.
 */
typedef struct MaterialLinearList
{
    MaterialListNode *head; /**< Head of the list, the first node. */
    int countMaterials;     /**< Count of materials in the list. */
} MaterialLinearList;

/**
 * @brief Creates a new material list.
 *
 * Allocates memory for a new `MaterialLinearList`, sets up the list to be empty, and initializes the material count to 0.
 *
 * @return Pointer to the newly created material list structure.
 */
static inline MaterialLinearList *createMaterialLinearList()
{
    MaterialLinearList *list = (MaterialLinearList *)malloc(sizeof(MaterialLinearList));
    if (!list)
    {
        perror("Error allocating memory for MaterialLinearList");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->countMaterials = 0;
    return list;
}

/**
 * @brief Initializes an existing material list.
 *
 * Sets up the list to be empty and initializes the material count to 0. Assumes the list structure has already been allocated.
 *
 * @param list Pointer to the material list structure to initialize.
 */
static inline void initMaterialLinearList(MaterialLinearList *list)
{
    list->head = NULL;
    list->countMaterials = 0;
}

/**
 * @brief Adds a material to the list.
 *
 * Creates a new node with the given material and inserts it at the beginning of the list.
 *
 * @param list Pointer to the material list structure.
 * @param material The material to add to the list.
 */
static inline void addMaterial(MaterialLinearList *list, Material material)
{
    MaterialListNode *newNode = (MaterialListNode *)malloc(sizeof(MaterialListNode));
    if (!newNode)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    newNode->material = material;
    newNode->next = list->head;
    list->head = newNode;
    list->countMaterials++;
}

/**
 * @brief Frees the memory used by the material list.
 *
 * Traverses the list and frees each node, then sets the head to NULL and the count to 0.
 *
 * @param list Pointer to the material list structure.
 */
static inline void freeMaterialLinearList(MaterialLinearList *list)
{
    MaterialListNode *current = list->head;
    MaterialListNode *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        // Free the material's dynamically allocated data if needed
        // e.g., freeMaterialData(&current->material);
        free(current);
        current = nextNode;
    }

    list->head = NULL;
    list->countMaterials = 0;
}

/**
 * @brief Retrieves a material at a given index.
 *
 * Returns a pointer to the material at the specified index. Returns NULL if the index is out of bounds.
 *
 * @param list Pointer to the material list structure.
 * @param index Index of the material to retrieve.
 * @return Pointer to the material at the given index or NULL if the index is invalid.
 */
static inline Material *getMaterial(MaterialLinearList *list, int index)
{
    if (index < 0 || index >= list->countMaterials)
    {
        return NULL; // Index out of bounds
    }

    MaterialListNode *current = list->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return &current->material;
}

/**
 * @brief Finds the index of a material in the list.
 *
 * Searches for a specific material in the list and returns its index. Returns -1 if the material is not found.
 *
 * @param list Pointer to the material list structure.
 * @param material Material to search for in the list.
 * @return Index of the material in the list or -1 if the material is not found.
 */
static inline int findMaterialIndex(MaterialLinearList *list, Material material)
{
    MaterialListNode *current = list->head;
    int index = 0;

    while (current != NULL)
    {
        // Comparison should be adapted to compare Material structures correctly
        // e.g., if (compareMaterials(&current->material, &material) == 0)
        if (memcmp(&current->material, &material, sizeof(Material)) == 0)
        {
            return index; // Material found
        }
        current = current->next;
        index++;
    }

    return -1; // Material not found
}

/**
 * @brief Converts the material list to a dynamic array of materials.
 *
 * Creates a new array containing all the materials from the list in the same order.
 * The memory for the array is allocated dynamically. Returns NULL if the list is empty.
 *
 * @param list Pointer to the material list structure.
 * @return Pointer to the array of materials or NULL if the list is empty.
 */
static inline Material *convertMaterialListToArray(MaterialLinearList *list)
{
    if (list->countMaterials == 0)
    {
        return NULL; // No materials to convert
    }

    Material *array = (Material *)malloc(list->countMaterials * sizeof(Material));
    if (!array)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    MaterialListNode *current = list->head;
    for (int i = 0; i < list->countMaterials; i++)
    {
        array[i] = current->material;
        current = current->next;
    }

    return array;
}

#endif // MATERIAL_LINEAR_LIST_HELPER_H