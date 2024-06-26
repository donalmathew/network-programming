#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// Definition of a Link structure to represent each edge in the network
struct Link {
    int hop, dest, wt; // hop: source node, dest: destination node, wt: weight of the edge
};

// Definition of a Network structure to represent the network
struct Network {
    int H, L; // H: number of nodes, L: number of links
    struct Link* link; // Array of links in the network
};

void main() {
    int H, L, S, i, j, dist[H];

    // Printing initial message and taking input for the number of nodes
    printf("distance vector algorithm using Bellman-Ford algorithm :\n enter number of nodes\n");
    scanf("%d", &H);

    // Taking input for the number of links
    printf("enter number of links\n");
    scanf("%d", &L);

    // Taking input for the source node
    printf("enter the source \n");
    scanf("%d", &S);

    // Allocating memory for the Network structure
    struct Network* n = (struct Network*)malloc(sizeof(struct Network));
    n->H = H; // Setting number of nodes
    n->L = L; // Setting number of links

    // Allocating memory for the array of links in the network
    n->link = (struct Link*)malloc(n->L * sizeof(struct Link));

    // Loop to take input for each link's source, destination, and weight
    for (i = 0; i < L; i++) {
        printf("\nLink%d: enter source, destination and weight\n", i + 1);
        scanf("%d", &n->link[i].hop);
        scanf("%d", &n->link[i].dest);
        scanf("%d", &n->link[i].wt);
    }

    // Initializing the distance array with maximum value
    for (i = 0; i < H; i++) {
        dist[i] = INT_MAX;
    }
    // Distance to the source is 0
    dist[S] = 0;

    // Relaxing all edges H-1 times
    for (i = 1; i < H; i++) {
        for (j = 0; j < L; j++) {
            int u = n->link[j].hop;
            int v = n->link[j].dest;
            int wt = n->link[j].wt;

            // Relaxing the edge if a shorter path is found
            if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // Checking for negative weight cycles
    for (i = 0; i < L; i++) {
        int u = n->link[i].hop;
        int v = n->link[i].dest;
        int wt = n->link[i].wt;

        // If a shorter path is found, then there is a negative weight cycle
        if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
            printf("network contains negative weight cycle\n");
        }
    }

    // Printing the shortest distance from the source to each node
    printf("\nHop\tDistance from source\n");
    for (i = 0; i < H; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}
