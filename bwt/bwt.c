#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store info of a node of
// linked list
struct node
{
    int data;
    struct node *next;
};

// Compares the characters of bwt_encoded[]
// and sorts them alphabetically
int cmpfunc(const void *a, const void *b)
{
    const char *ia = (const char *)a;
    const char *ib = (const char *)b;
    return strcmp(ia, ib);
}

// Creates the new node
struct node *getNode(int i)
{
    struct node *nn = (struct node *)malloc(sizeof(struct node));
    nn->data = i;
    nn->next = NULL;
    return nn;
}

void addAtLast(struct node **head, struct node *nn)
{
    if (*head == NULL)
    {
        *head = nn;
        return;
    }
    struct node *temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = nn;
}

// Computes l_shift[]
void *computeLShift(struct node **head, int index, int *l_shift)
{
    l_shift[index] = (*head)->data;
    (*head) = (*head)->next;
}

int main()
{
    printf("\n");
    printf("---------------------------------------- INPUT ----------------------------------------------------");
    printf("\n");
    char str[100], bwt[100][100], bwt2[100][100];
    printf("\nEnter the string to be encoded (ending with $): ");
    gets(str);
    printf("\n");
    printf("---------------------------------------- BWT operations going on ----------------------------------------------------");
    printf("\n");
    printf("\n");
    int n = strlen(str), k = 0, j, index = 0;
    for (int i = 0; i < n; i++)
    {
        j = i;
        printf("j = %d | ", j + 1);
        do
        {

            printf("%d ", j % n);
            bwt[i][index++] = str[j % n];
            j++;

        } while ((j % n) != k);
        index = 0;
        printf("| k = %d ", k);
        printf("\n");
        k++;
    }

    printf("\n");
    printf("Rotations (left rotation): ");
    printf("\n");
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // printf("bwt[%d][%d] = %c ", i, j, bwt[i][j]);
            printf("%c ", bwt[i][j]);
        }
        printf("\n");
    }

    int min, temp;
    // k = 0;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (bwt[j][0] < bwt[min][0])
            {
                min = j;
            }
            else if (bwt[j][0] == bwt[min][0])
            {
                for (int z = 1; z < n; z++)
                {
                    if (bwt[j][z] < bwt[min][z])
                        min = j;
                    else if (bwt[j][z] > bwt[min][z])
                        break;
                }
            }
        }

        // Insertion sort
        for (int j = 0; j < n; j++)
        {
            temp = bwt[i][j];
            bwt[i][j] = bwt[min][j];
            bwt[min][j] = temp;
        }
        // k = 0;
    }

    printf("\n");
    printf("Sorted Rotations (sorted lexicographically by starting letters of each rotations): ");
    printf("\n");
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // printf("bwt[%d][%d] = %c ", i, j, bwt[i][j]);
            printf("%c ", bwt[i][j]);
        }
        printf("\n");
    }

    printf("\nBWT encoded string is : ");
    char *bwt_encoded = (char *)malloc(n * sizeof(char));
    for (int i = 0; i < n; i++)
    {
        printf("%c", bwt[i][n - 1]);
        bwt_encoded[i] = bwt[i][n - 1];
    }

    printf("\n\n");

    // Time Complexity : O(n^3)

    printf("---------------------------------------- BWT inversion operations going on ----------------------------------------------------");
    // BWT inversion

    int i, len_bwt = strlen(bwt_encoded);
    char *sorted_bwt = (char *)malloc(len_bwt * sizeof(char));
    strcpy(sorted_bwt, bwt_encoded);
    int *l_shift = (int *)malloc(len_bwt * sizeof(int));

    // Index at which original string appears in the sorted rotations list
    // debug
    // a n n b $ a a (bwt_encoded)
    //        x=4
    // printf("\ndebbug:\n");
    // finding out the index where $ appears and storing it in x
    int x;
    for (int i = 0; i < n; i++)
    {
        // debug
        // printf("%c ", bwt_encoded[i]);
        if (bwt_encoded[i] == '$')
        {
            x = i;

            break;
        }
    }

    printf("\n\nIndex where '$' is present in BWT encoded string : %d", x);
    printf("\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("%c ", bwt_encoded[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", i);
    }

    printf("\n\n\t|\n\t|\n\tV\n\n");
    // Sorts the characters of bwt_encoded[] alphabetically
    qsort(sorted_bwt, len_bwt, sizeof(char), cmpfunc);

    for (int i = 0; i < n; i++)
    {
        printf("%c ", sorted_bwt[i]);
    }
    printf("\t(Sorted BWT encoded string) ");
    printf("\n");

    // Array of pointers that act as head nodes to linked lists created to compute l_shift[]
    struct node *arr[128] = {NULL};

    /*
    void addAtLast(struct node **head, struct node *nn)
    {
        if (*head == NULL)
        {
            *head = nn;
            return;
        }
        struct node *temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = nn;
    }*/
    // Takes each distinct character of bwt_encoded[] as head of a linked list and appends to it the new node whose data part contains index at which character occurs in bwt_encoded[]
    // a n n b $ a a bwt_encoded           |}arr[]
    // 0 1 2 3 4 5 6                       |}
    for (i = 0; i < len_bwt; i++)
    {
        struct node *nn = getNode(i);
        addAtLast(&arr[bwt_encoded[i]], nn);
    }
    // printf("\nCreating an array which stores the character and index of BWT encoded string : ", x);
    // printf("\ncharacter : ");
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%c ", bwt_encoded[i]);
    // }
    // struct node *temp[128];
    // temp = arr;
    // printf("\nindex : ");
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d ", temp->data);

    // }
    // printf("\n");

    // Takes each distinct character of sorted_arr[] as head of a linked list and finds l_shift[]
    /*
    void *computeLShift(struct node **head, int index, int *l_shift)
    {
        l_shift[index] = (*head)->data;
        (*head) = (*head)->next;
    }
    */
    //
    // a n n b $ a a bwt_encoded           |}arr[]
    // 0 1 2 3 4 5 6                       |}
    // $ a a a b n n sorted_bwt[i]
    // 4 0 5 6 3 1 2 arr[sorted_bwt[i]]
    // 4 0 5 6 3 1 2 (l_shift)
    for (i = 0; i < len_bwt; i++)
        computeLShift(&arr[sorted_bwt[i]], i, l_shift);

    // debug
    // printf("\nl_shift:\n");
    for (i = 0; i < len_bwt; i++)
    {
        printf("%d ", l_shift[i]);
    }

    int t = x;
    printf("\n\n\t|\n\t|\n\tV\n\n");

    for (i = 0; i < len_bwt; i++)
    {
        x = l_shift[x];
        printf("%c ", bwt_encoded[x]);
    }
    printf("\n");
    for (i = 0; i < len_bwt; i++)
    {
        printf("%d ", l_shift[t]);
        t = l_shift[t];
    }
    printf("\n");

    // printf("\nBurrows - Wheeler Transform: %s\n", bwt_encoded);
    printf("\nBWT inverse decoded string is : ");
    // Decodes the bwt

    // a n n b $ a a bwt_encoded           |}arr[]
    // 0 1 2 3 4 5 6                       |}
    // 4 0 5 6 3 1 2 (l_shift)
    // 3 6 2 5 1 0 4 (x)
    // b a n a n a $ bwt_encoded[x]
    for (i = 0; i < len_bwt; i++)
    {
        x = l_shift[x];
        printf("%c", bwt_encoded[x]);
    }

    printf("\n\n");

    // Time Complexity : O(nlogn)
    printf("---------------------------------------- FINAL OUTPUT ----------------------------------------------------");
    printf("\n");

    printf("\nBWT encoded string is : ");
    for (int i = 0; i < n; i++)
    {
        printf("%c", bwt[i][n - 1]);
        bwt_encoded[i] = bwt[i][n - 1];
    }

    // printf("\nBurrows - Wheeler Transform: %s\n", bwt_encoded);
    printf("\nBWT inverse decoded string is : ");
    // Decodes the bwt
    for (i = 0; i < len_bwt; i++)
    {
        x = l_shift[x];
        printf("%c", bwt_encoded[x]);
    }
    printf("\n");
    printf("\n");

    printf("---------------------------------------- EXTRA INFO ----------------------------------------------------");
}