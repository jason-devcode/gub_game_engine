#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H
/**
 * @file event_manager.h
 * @brief EventManager module for managing event listeners in a flexible and efficient manner.
 *
 * This module provides functionality to create, manage, and destroy an EventManager,
 * which can handle multiple lists of event listeners. It allows adding, removing, and
 * clearing listeners for specific events or all events.
 */

#include <string.h>  // For memset
#include <stdlib.h>  // For malloc, free
#include <stdbool.h> // For bool type
#include <stdio.h>   // For fputs
#include <stdint.h>  // For uint32_t

/**
 * @struct NodeEventListener
 * @brief Represents a node in the linked list of event listeners.
 *
 * This structure holds a pointer to an event handler function and a pointer
 * to the next node in the list.
 */
typedef struct NodeEventListener
{
    void (*listener)();             // Pointer to the event handler function
    struct NodeEventListener *next; // Pointer to the next node in the list
} NodeEventListener;

/**
 * @struct EventManager
 * @brief Represents the event manager.
 *
 * This structure holds an array of pointers to lists of event listeners and
 * the number of lists in the array.
 */
typedef struct
{
    NodeEventListener **listeners_lists; // Array of pointers to lists of event listeners
    uint32_t listsCount;                 // Number of lists in the array
} EventManager;

/**
 * @brief Initializes an already created EventManager.
 *
 * This function initializes the fields of an already created EventManager. It allocates
 * memory for the array of listener lists and initializes all list pointers to NULL.
 *
 * @param manager Pointer to the EventManager to be initialized.
 * @param maxPossibleListenerLists Maximum number of listener lists the manager can hold.
 * @return true if the EventManager was successfully initialized, false otherwise.
 */
bool initializeEventManager(EventManager *manager, uint32_t maxPossibleListenerLists)
{
    if (manager == NULL)
    {
        fputs("ERROR: EventManager is NULL!", stderr);
        return false;
    }

    manager->listsCount = maxPossibleListenerLists;
    manager->listeners_lists = (NodeEventListener **)malloc(maxPossibleListenerLists * sizeof(NodeEventListener *));

    if (manager->listeners_lists == NULL)
    {
        fputs("ERROR: Cannot allocate memory space for listeners lists!", stderr);
        return false;
    }

    // Clear memory for listener lists to avoid garbage values
    memset(manager->listeners_lists, 0, maxPossibleListenerLists * sizeof(NodeEventListener *));

    return true;
}

/**
 * @brief Creates a new EventManager with the specified maximum number of listener lists.
 *
 * This function allocates memory for a new EventManager and initializes its fields. It also
 * allocates memory for the array of listener lists and initializes all list pointers to NULL.
 *
 * @param maxPossibleListenerLists Maximum number of listener lists the manager can hold.
 * @return Pointer to the newly created EventManager, or NULL if memory allocation fails.
 */
EventManager *createEventManager(uint32_t maxPossibleListenerLists)
{
    EventManager *manager = (EventManager *)malloc(sizeof(EventManager));

    initializeEventManager(manager, maxPossibleListenerLists);

    return manager;
}

/**
 * @brief Adds a listener to the specified list in the EventManager.
 *
 * This function creates a new NodeEventListener and appends it to the list of listeners
 * for the specified key.
 *
 * @param manager Pointer to the EventManager.
 * @param key Index of the listener list to add the listener to.
 * @param listener Pointer to the listener function to add.
 * @return true if the listener was successfully added, false otherwise.
 */
bool addEventListener(EventManager *manager, uint32_t key, void (*listener)())
{
    if (key >= manager->listsCount || listener == NULL)
        return false;

    NodeEventListener *newListener = (NodeEventListener *)malloc(sizeof(NodeEventListener));

    if (newListener == NULL)
        return false;

    newListener->listener = listener;
    newListener->next = manager->listeners_lists[key];
    manager->listeners_lists[key] = newListener;
    return true;
}

/**
 * @brief Removes a listener from the specified list in the EventManager.
 *
 * This function searches for a NodeEventListener with the specified listener function
 * and removes it from the list of listeners for the specified key.
 *
 * @param manager Pointer to the EventManager.
 * @param key Index of the listener list to remove the listener from.
 * @param listener Pointer to the listener function to remove.
 * @return true if the listener was successfully removed, false otherwise.
 */
bool removeEventListener(EventManager *manager, uint32_t key, void (*listener)())
{
    if (key >= manager->listsCount)
        return false;

    NodeEventListener *current = manager->listeners_lists[key];
    NodeEventListener *previous = NULL;

    while (current != NULL)
    {
        if (current->listener == listener)
        {
            if (previous == NULL)
                manager->listeners_lists[key] = current->next;
            else
                previous->next = current->next;
            memset(current, 0, sizeof(NodeEventListener));
            free(current);
            return true;
        }
        previous = current;
        current = current->next;
    }

    return false;
}

/**
 * @brief Clears all listeners from the specified list in the EventManager.
 *
 * This function removes and deallocates all NodeEventListener nodes from the list
 * of listeners for the specified key.
 *
 * @param manager Pointer to the EventManager.
 * @param key Index of the listener list to clear.
 * @return true if the list was successfully cleared, false otherwise.
 */
bool clearEventListeners(EventManager *manager, uint32_t key)
{
    if (key >= manager->listsCount)
        return false;

    NodeEventListener *current = manager->listeners_lists[key];

    while (current != NULL)
    {
        NodeEventListener *toFree = current;
        current = current->next;
        memset(toFree, 0, sizeof(NodeEventListener)); // Clear memory before free
        free(toFree);
    }

    manager->listeners_lists[key] = NULL;
    return true;
}

/**
 * @brief Clears all listener lists in the EventManager.
 *
 * This function removes and deallocates all NodeEventListener nodes from all the lists
 * in the EventManager.
 *
 * @param manager Pointer to the EventManager.
 * @return true if all lists were successfully cleared, false otherwise.
 */
bool clearAllEventListeners(EventManager *manager)
{
    for (uint32_t key = 0; key < manager->listsCount; ++key)
        clearEventListeners(manager, key);

    return true;
}

/**
 * @brief Frees the memory allocated for the EventManager and its listener lists.
 *
 * This function deallocates all memory associated with the EventManager, including
 * the memory for each event listener and the array of listener lists. It also clears
 * the memory of each node before freeing it to ensure no garbage values are left behind.
 *
 * If the EventManager was created as a stack variable, the `isStackElement` parameter
 * should be set to `true` to avoid attempting to free memory that was not allocated
 * dynamically.
 *
 * @param manager Pointer to the EventManager to be freed.
 * @param isStackElement Set to true if the EventManager was created as a stack variable.
 * @return true if the EventManager was successfully freed or was already NULL, false otherwise.
 */
bool freeEventManager(EventManager *manager, bool isStackElement)
{
    uint32_t maxPossibleListenerLists = manager->listsCount;

    if (manager == NULL)
        return true; // already is free

    for (int listListenerIndex = 0; listListenerIndex < manager->listsCount; ++listListenerIndex)
    {
        NodeEventListener *current = manager->listeners_lists[listListenerIndex];

        if (current != NULL)
        {
            do
            {
                NodeEventListener *toFree = current;
                current = current->next;
                memset(toFree, 0, sizeof(NodeEventListener)); // clear memory before free
                free(toFree);
            } while (current != NULL);
        }
    }

    memset(manager, 0, sizeof(EventManager));

    if (!isStackElement)
        free(manager);

    return true;
}
/**
 * @brief Triggers an event for all listeners in the specified list of the EventManager.
 *
 * This macro iterates through all the nodes in the listener list for the specified key
 * and calls the listener functions.
 *
 * @param manager EventManager instance that holds the listener lists.
 * @param key Index of the listener list to trigger the event for.
 */
#define triggerEvent(manager, key)                                  \
    NodeEventListener *nodeListener = manager.listeners_lists[key]; \
    while (nodeListener)                                            \
    {                                                               \
        nodeListener->listener();                                   \
        nodeListener = nodeListener->next;                          \
    }

#endif