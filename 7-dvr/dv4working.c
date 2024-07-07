#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 20  // Define a maximum number of nodes in the network

// Define a structure to represent the routing table for each node
struct RoutingTable {
    int distance[MAX_NODES];  // Array to store the minimum distances from this node to all other nodes
    int nextHop[MAX_NODES];   // Array to store the next node to reach each destination node
} routingTables[MAX_NODES];  // Array of routing tables, one for each node in the network

int main() {
    int numNodes;  // Number of nodes in the network
    int distanceMatrix[MAX_NODES][MAX_NODES];  // 2D Array to store the initial distances between nodes

    // Prompt the user to enter the number of nodes
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    // Prompt the user to enter the distance matrix
    printf("Enter the distance matrix (use a large number for 'infinity'):\n");
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            scanf("%d", &distanceMatrix[i][j]);  // Input the distance from node i to node j
        }
    }

    // Initialize the routing tables for each node
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            routingTables[i].distance[j] = distanceMatrix[i][j];  // Set initial distance from node i to node j
            routingTables[i].nextHop[j] = j;  // Set the initial next hop to reach node j as itself
        }
    }

    int updateOccurred;  // Flag to check if there were any updates in the distance vectors

    // Main loop to update the routing tables until no more updates occur
    do {
        updateOccurred = 0;  // Assume no updates are made in this iteration
        for (int i = 0; i < numNodes; i++) {  // Iterate through all nodes
            for (int src = 0; src < numNodes; src++) {  // Source node
                for (int dest = 0; dest < numNodes; dest++) {  // Destination node
                    for (int intermediate = 0; intermediate < numNodes; intermediate++) {  // Intermediate node
                        // Check if a shorter path to destination through the intermediate node is found
                        if (routingTables[src].distance[dest] > routingTables[src].distance[intermediate] + routingTables[intermediate].distance[dest]) {
                            // Update the distance to the new, shorter path
                            routingTables[src].distance[dest] = routingTables[src].distance[intermediate] + routingTables[intermediate].distance[dest];
                            // Update the next hop to reach the destination through the intermediate node
                            routingTables[src].nextHop[dest] = routingTables[src].nextHop[intermediate];
                            // Set the flag to indicate that an update has been made
                            updateOccurred = 1;
                        }
                    }
                }
            }
        }
    } while (updateOccurred);  // Continue updating until no more updates are made

    // Print the final routing tables for all nodes
    for (int i = 0; i < numNodes; i++) {
        printf("Routing table for node %c:\n", i + 65);  // Print the node label (A, B, C, etc.)
        printf("Destination\tNext Hop\tDistance\n");  // Print the headers for the routing table
        for (int j = 0; j < numNodes; j++) {
            // Print the destination node, the next hop node, and the distance
            printf("%c\t\t%c\t\t%d\n", j + 65, routingTables[i].nextHop[j] + 65, routingTables[i].distance[j]);
        }
        printf("\n");
    }

    return 0;  // End of the program
}

