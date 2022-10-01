#include <bits/stdc++.h>

using namespace std;
struct rightThreadedBSTNode
{
    int key;
    int size;        // Total no of nodes in the subtree rooted at the node.
    int rightThread; // 1, if right link is a thread to its inorder successor
    struct rightThreadedBSTNode *left;
    struct rightThreadedBSTNode *right;
};
typedef struct rightThreadedBSTNode rTBSTNode;
typedef struct rightThreadedBSTNode *rTBSTNodePtr;

// [15 points] void inorder(rTBSTNodePtr root, int *List); // Non-recursive and without using stack
// [10 points] int rtbstInsert(rTBSTNodePtr *root, int data) - O(h)
// [40 points] int rtbstDelete(rTBSTNodePtr *root, int data) - O(h)
// [20 points] rTBSTNodePtr kthElement(rTBSTNodePtr *root, int k) - O(h) // returns the pointer of the node having the k-th smallest key value ow returns NULL
// /////////////////////////////////////PASTE ALL FUNCTIONS HERE CAREFULLY../////////////////////////////////////////////
void createRightThreadedBST(rTBSTNodePtr *root)
{
    *root = NULL;
}

rTBSTNodePtr getRightThreadedBST(int value)
{
    rTBSTNodePtr node = (rTBSTNodePtr)malloc(sizeof(rTBSTNode));
    node->key = value;
    // node->right = NULL;
    // node->left = NULL;
    node->rightThread = 1;
    node->size = 1;

    return node;
}

int rtbstInsert(rTBSTNodePtr *root, int data)
{
    rTBSTNodePtr ptr = *root;
    rTBSTNodePtr parent = NULL;

    while (ptr != NULL)
    {
        if (data == (ptr->key))
        {
            printf("Duplicate Key !\n");
            return 0;
        }

        parent = ptr;

        if (data < ptr->key)
        {
            ptr->size++;
            ptr = ptr->left;
        }
        else
        {
            if (ptr->rightThread != 1)
            {
                ptr->size++;
                ptr = ptr->right;
            }
            else
            {
                ptr->size++;
                break;
            }
        }
    }

    rTBSTNodePtr element = getRightThreadedBST(data);

    if (parent == NULL)
    {
        // printf("\ncreating root\n");
        *root = element;
        element->left = NULL;
        element->right = NULL;
    }
    else if (data < (parent->key))
    {
        element->right = parent;
        parent->left = element;
        element->rightThread = 1;
    }
    else
    {
        element->right = parent->right;
        parent->right = element;
        parent->rightThread = 0;
    }

    return 1;
}

rTBSTNodePtr inorderSuccessor(rTBSTNodePtr node)
{
    if (node == NULL)
        return node;
    if (node->rightThread == 1)
        return node->right;

    node = node->right;

    while (node->left != NULL)
        node = node->left;

    return node;
}

rTBSTNodePtr inorderPred(rTBSTNodePtr current)
{
    if (current == NULL)
        return NULL;

    current = current->left;
    while (current->rightThread == 0)
        current = current->right;
    return current;
}

rTBSTNodePtr find_node(rTBSTNodePtr root, int value)
{
    // struct Node *parent = NULL;
    // printf("here pow\n");
    rTBSTNodePtr current = root;

    while (current != NULL)
    {
        if (value == current->key)
        {
            return current;
        }
        if (current->key < value)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    return NULL;
}

int rtbstDelete(rTBSTNodePtr *root, int data)
{

    if (find_node(*root, data) == NULL)
    {
        return 0;
    }

    int found = 0;

    rTBSTNodePtr temp = *root, parent = NULL;

    while (temp != NULL)
    {
        if (temp->key == data)
        {
            found = 1;
            break;
        }

        parent = temp;
        if (temp->key > data)
        {
            // printf("temp value %d\n", temp->key);
            temp->size--;
            temp = temp->left;
        }
        else
        {
            if (temp->rightThread == 0)
            {
                temp->size--;
                temp = temp->right;
            }

            else
                break;
        }
    }

    if (found == 1)
    {
        // printf("\nFound!!!\n");

        if (parent == NULL && ((*root)->right == NULL || (*root)->left == NULL))
        {
            // printf("here in the new part!!!");
            if ((*root)->right == NULL)
            {
                rTBSTNodePtr predecessor = inorderPred(*root);
                *root = (*root)->left;
                predecessor->right = NULL;
                predecessor->rightThread = 0;
            }
            else
            {
                *root = (*root)->right;
            }
        }
        else
        {

            if (temp->left == NULL && temp->rightThread == 1)
            {
                if (parent->left == temp)
                {
                    parent->left = NULL;
                    free(temp);
                }
                else
                {
                    parent->right = temp->right;
                    parent->rightThread = 1;
                    free(temp);
                }
            }
            else if (temp->left == NULL || temp->rightThread == 1)
            {
                if (temp->rightThread == 1)
                {
                    rTBSTNodePtr successor = inorderSuccessor(temp);
                    rTBSTNodePtr predecessor = inorderPred(temp);
                    rTBSTNodePtr child = temp->left;

                    predecessor->right = successor;
                    predecessor->rightThread = 1;

                    if (parent->left == temp)
                        parent->left = child;
                    else
                        parent->right = child;
                }
                else
                {
                    rTBSTNodePtr child = temp->right;

                    if (parent->left == temp)
                        parent->left = child;
                    else
                        parent->right = child;
                }
            }
            else
            {
                rTBSTNodePtr succ = inorderSuccessor(temp);
                int k = succ->key;
                rtbstDelete(root, k);
                temp->key = k;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void displayTreeHelper(rTBSTNodePtr T, FILE *fp)
{
    if (T != NULL)
    {
        fprintf(fp, "%d[label=\"%d, size:%d\"];", T->key, T->key, T->size);
        if (T->left != NULL)
        {
            fprintf(fp, "%d -> %d [color = red, style=dotted];\n", T->key, T->left->key);
            displayTreeHelper(T->left, fp);
        }
        if (T->right != NULL && (T->rightThread != 1))
        {
            fprintf(fp, "%d -> %d ;\n", T->key, T->right->key);
            displayTreeHelper(T->right, fp);
        }
        if (T->right != NULL && (T->rightThread == 1))
        {
            fprintf(fp, "%d -> %d [color = blue, style=dotted];\n", T->key, T->right->key);
        }
    }
}

int displayRightThreadedTree(rTBSTNodePtr T, char *filename)
{
    FILE *fp;

    fp = fopen(filename, "w+");
    if (fp == NULL)
    {
        printf("displayTree(): Unable to open file %s", filename);
        return -1;
    }
    fprintf(fp, "digraph g{\n");
    displayTreeHelper(T, fp);
    fprintf(fp, "}\n");

    fclose(fp);

    return 0;
}

void inorder(rTBSTNodePtr *root, int *List)
{
    rTBSTNodePtr temp = *root;
    int index = 0;

    while (temp->left != NULL)
        temp = temp->left;

    while (temp != NULL)
    {
        List[index++] = temp->key;

        temp = inorderSuccessor(temp);
    }
    return;
}

int sizeOfTree(rTBSTNodePtr root)
{
    if (!root)
        return 0;
    return root->size;
}

rTBSTNodePtr kthElement(rTBSTNodePtr *root, int k)
{
    if (!(*root))
        return NULL;
    int size = sizeOfTree((*root)) - sizeOfTree((*root)->right);
    //  printf("%d %d %d\n", root->key, size, root->size);

    if (size == k)
        return *root;
    if (size < k && (*root)->rightThread != 1)
        return kthElement(&((*root)->right), k - size);
    else
        return kthElement(&((*root)->left), k);

    return NULL;
}

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printInorder(rTBSTNodePtr root, int *list) // write this function and pass the list to print inorder
{
    if (sizeof(list) < 1)
    {
        return; // The list is empty
    }
    printf("Inorder list = ");
    for (int i = 0; i < root->size; i++)
    {
        printf("%d -> ", list[i]);
        printf("\n");
    }
    printf("\n");
}

int main()
{
    rTBSTNodePtr root;
    createRightThreadedBST(&root);
    int *arr; // list

    vector<int> v;
    long long int n = 0;
    cout << "enter no of nodes: ";
    cin >> n;
    int size = n;
    srand(time(0));
    cout << "inserting...\n";
    while (n != 0) // insert
    {
        int data = rand() % 100000;
        if (find(v.begin(), v.end(), data) == v.end())
        {
            v.push_back(data);
            rtbstInsert(&root, data);
            n--;
        }
    }
    cout << "..................................checking inorder...\n";

    // arr = (int *)malloc(sizeof(int) * size);

    displayRightThreadedTree(root, "tree.dot");
    system("dot -Tpng tree.dot -o tree.png");
    // inorder(&root, arr);
    //    printInorder(root,arr);
    if (is_sorted(arr, arr + size))
    {
        // cout << "Sorted \n";
    }
    else
        std::cout << "Not Sorted \n";

    cout << "checking KTH...\n";
    for (int i = 0; i < size; i++)
    {

        rTBSTNodePtr res = kthElement(&root, i + 1);
        if (res)
        {
            if (arr[i] != res->key)
                cout << "wrong kth \n";
        }
        else
        {
            cout << "not present\n";
        }
    }

    ////////////////////////////////////////////////////////////
    cout << "\n\nenter no of nodes to delete: ";
    cin >> n;
    // deleting
    int *ar;
    // for(auto i:v)cout<<i<<" ";cout<<"\n";
    cout << ".....................................deleting and checking inorder\n";
    for (int i = 0; i < n; i++)
    {

        rtbstDelete(&root, v[i]);

        size--;
        ar = (int *)malloc(sizeof(int) * (size));
        if (!ar)
            cout << "\nerror in ar\n";
        inorder(&root, ar);
        // printInorder(root,ar);
        // cout<<"\n";
        if (std::is_sorted(ar, ar + size))
        { // cout << "Sorted \n";
        }
        else
        {
            cout << "for i=" << i;
            std::cout << " Not Sorted \n";
        }
    }
    //////////////////////////////////////////////////////////////

    cout << ".....................................checking KTH...\n";
    for (int i = 0; i < size; i++)
    {

        rTBSTNodePtr res = kthElement(&root, i + 1);
        // cout<<res->key<<"\n";
        if (res) // cheking for kth rsmalest
        {
            if (ar[i] != res->key)
            {
                cout << ar[i] << "-" << res->key << " wrong kth \n";
            }
        }
        else
        {
            cout << "not present\n";
        }
    }

    return 0;
}
