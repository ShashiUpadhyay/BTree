/* 
 * File:   lab7.c
 * Author: shashiupadhyay
 *
 * Created on December 12, 2015, 6:25 PM
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include "BTreeHeader.h"

int main() {
    FILE *file_pointer;
    Tree *binarytree;
    int userinput;
    Node* foundnode;
    Data data;

    binarytree = createTree();
    file_pointer = fopen("data.txt", "r");
    printf("Reading values from file and Inserting the respective values in B-Tree \n");
    //    Reading data from File (Start)
    while (!feof(file_pointer)) {
        fscanf(file_pointer, "%d", &data.number);
        insert(binarytree, data);
    }
    fclose(file_pointer);
    file_pointer = NULL;
    //    Reading data from File (End)

    printf("\nPrinting B-Tree - In      Order\t:  ");
    printInorder(binarytree);
    printf("\nPrinting B-Tree - Post Order \t:  ");
    printpostorder(binarytree);
    printf("\nPrinting B-Tree - Pre   Order \t:  ");
    printpreorder(binarytree);
    printf("\n");
    printf("\n");
    printf("Kindly enter the number you want to search \t Press 0 to exit \n");
    do {
        scanf("%d", &data.number);
        printf("\nSearch data : %d\n", data.number);

        if (data.number == 0) {
            printf("Exiting the Search Logic \n");
        } else {
            foundnode = search(binarytree, data);
            if (foundnode != NULL) {
                if (foundnode->parent == NULL || foundnode == foundnode->parent) {
                    printf("Node is root node = %d\n", foundnode->data.number);
                } else {
                    printf("Parent Node = %d\n", foundnode->parent->data.number);
                }
                printf("\nPrinting Nodes Child Values in In     Order Format\t:  ");
                printInorderdata(foundnode);
                printf("\nPrinting Nodes Child Values in Post Order Format\t:  ");
                printpostorderdata(foundnode);
                printf("\nPrinting Nodes Child Values in Pre   Order Format\t:  ");
                printpostorderdata(foundnode);
            }
            printf("\n");
            printf("Kindly enter the number you want to search\t Press 0 to exit \n");
        }
    } while (data.number != 0);
    printf("\n");

    /*    ------------------  Deletion (Start) ----------------- */
    printf("\nBefore Deletions. \nPrinting B-Tree - In Order format  : ");
    printInorder(binarytree);
    printf("\n\nEnter the values to be deleted \tEnter 0 to exit\n");
    do {
        scanf("%d", &userinput);
        if (userinput == 0) {
            printf("Exiting the deletion logic. No further deletion. \n");
        }else{
            data.number = userinput;
            removeNode(binarytree, data);
            printf("\nPrinting Nodes Child Values in In     Order Format\t:  ");
            printInorder(binarytree);
            printf("\nPrinting Nodes Child Values in Post Order Format\t:  ");
            printpostorder(binarytree);
            printf("\nPrinting Nodes Child Values in Pre   Order Format\t:  ");
            printpreorder(binarytree);
            printf("\n\nEnter the values to be deleted\tEnter 0 to exit\n");
            if (binarytree->root_node == NULL) {
                printf("Tree is Empty. Further Deletion not possible.");
                userinput = 0;
            }
        }
    } while (userinput != 0);
    printf("\n");
    printf("\n");
    deleteTree(binarytree);
    binarytree = NULL;
    /* ------------------ Deletion (END) --------------------- */

    return 0;
}
