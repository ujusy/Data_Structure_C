# Binary Search Trees(BST)

>힙에서 특정 노드를 찾으려고 할때 는 빅오 n만큼의 시간 걸린다
>
>특정 노드를 찾으려고 할때는 힙은 오랜시간이 걸리기 때문에 binary seach tree사용
>
>->___heap은 우선순위 정렬에 bst는 탐색에 강점을 지닌 자료구조___

> 특징:
>
> Left subtree의 node들 상위 node보다 작거나 같은 값
>
> Right subree의 node들은 상위node보다 큰 값.

<img width="554" alt="image-20191017155647977" src="https://user-images.githubusercontent.com/49120090/67013038-69a8c000-f12d-11e9-8aa8-e2bfbf74ffb3.png">



> delete할때

> Case 1: delete node==leaf node(자식 node가 없는 경우)
>
> Case 2: delete node==has a one child node(자식 node가 한개인 경우)
>
> Case 3: delete node==has two child nodes



>이 경우는 level로 다운된다 O(log n) 걸린다.=O(H) depth만큼 시간 걸린다.
>
>그러나 worst case: O(n)
>
> for skewed binary tree
>
>

<img width="360" alt="image-20191010172156473" src="https://user-images.githubusercontent.com/49120090/67013064-775e4580-f12d-11e9-9a67-3d4e7318a2d1.png">

<img width="333" alt="image-20191010172206213" src="https://user-images.githubusercontent.com/49120090/67013088-804f1700-f12d-11e9-9b22-2b5729837312.png">



>전체  코드 및 결과

~~~c

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h> 

typedef char element;
typedef struct treeNode {
	char key;				// data field
	struct treeNode* left;	// left subtree link field
	struct treeNode* right;	// right subtree link field
} treeNode;

// find a node that has a key value = x
treeNode* searchBST(treeNode* root, char x) {
	treeNode* p;
	p = root;
	while (p != NULL) {
		if (x < p->key) p = p->left;
		else if (x == p->key) return p;
		else p = p->right;
	}
	printf("\n Cannot find a key!");
	return p;
}

// insert a node with key = x 
treeNode* insertNode(treeNode *p, char x) {
	treeNode *newNode;
	if (p == NULL) {
		newNode = (treeNode*)malloc(sizeof(treeNode));
		newNode->key = x;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else if (p->key > x) p->left = insertNode(p->left, x);
	else if (p->key < x) p->right = insertNode(p->right, x);
	else  printf("\n duplicated! \n");

	return p;
}

// delete a node with a key value 
void deleteNode(treeNode *root, element key) {
	treeNode *parent, *p, *succ, *succ_parent; // succ and succ_parent variables are for the case where a deleted node has two child nodes
	treeNode *child;

	parent = NULL;
	p = root;
	while ((p != NULL) && (p->key != key)) {  // find a location of a node with a key value
											  // note that we know both the p node and p's parent node
		parent = p;
		if (key < p->key) p = p->left;
		else p = p->right;
	}

	// cannot find a node
	if (p == NULL) {
		printf("\n Cannot find a key in the tree!");
		return;
	}

	// delete node == leaf node
	if ((p->left == NULL) && (p->right == NULL)) {
		if (parent != NULL) {
			if (parent->left == p) parent->left = NULL;
			else parent->right = NULL;
		}
		else root = NULL;
	}

	// delete node == has a one child node
	else if ((p->left == NULL) || (p->right == NULL)) {
		if (p->left != NULL) child = p->left;
		else child = p->right;

		if (parent != NULL) {
			if (parent->left == p) parent->left = child;
			else parent->right = child;
		}
		else root = child;
	}

	// delete node == has two child nodes
	else {
		// there are two options for finding a node to be replaced.
		// we consider replacing the deleted node with the predecessor.
		succ_parent = p;
		succ = p->left;

		while (succ->right != NULL) { // find an inorder predecessor
			succ_parent = succ;
			succ = succ->right;
		}
		// attaching succ->left to succ_parent
		if (succ_parent->left == succ)  succ_parent->left=succ->left;
		else succ_parent->right = succ->left;

		p->key = succ->key;
		p = succ;
	}
	free(p);
}

// inorder
void displayInorder(treeNode* root) {
	if (root) {
		displayInorder(root->left);
		printf("%c_", root->key);
		displayInorder(root->right);
	}
}

void menu() {
	printf("\n*---------------------------*");
	printf("\n\t1 : Print Tree");
	printf("\n\t2 : Insert a node");
	printf("\n\t3 : Delete a node");
	printf("\n\t4 : Search a node");
	printf("\n\t5 : Exit");
	printf("\n*---------------------------*");
	printf("\nChoose an option >> ");
}

int main() {
	treeNode* root = NULL;
	treeNode* foundedNode = NULL;
	char choice, key;

	// Building a binary search tree
	// G is a root node
	root = insertNode(root, 'G');
	insertNode(root, 'I');
	insertNode(root, 'H');
	insertNode(root, 'D');
	insertNode(root, 'B');
	insertNode(root, 'M');
	insertNode(root, 'N');
	insertNode(root, 'A');
	insertNode(root, 'J');
	insertNode(root, 'E');
	insertNode(root, 'Q');

	while (1) {
		menu();
		scanf(" %c", &choice);

		switch (choice - '0') {
		case 1:	printf("\t[Print out binary tree]  ");
			displayInorder(root);  printf("\n");
			break;

		case 2:	printf("Type a node to be inserted : ");
			scanf(" %c", &key);
			insertNode(root, key);
			break;

		case 3:	printf("Type a node to be deleted : ");
			scanf(" %c", &key);
			deleteNode(root, key);
			break;

		case 4: printf("Type a node to be searched : ");
			scanf(" %c", &key);
			foundedNode = searchBST(root, key);
			if (foundedNode != NULL)
				printf("\n Found %c! \n", foundedNode->key);
			else  printf("\n Cannot find a char. \n");
			break;

		case 5: return 0;

		default: printf("Try again \n");
			break;
		}
	}
}

~~~



###### searching bst --> recursive 

~~~c

tree_ptr search(tree_ptr root, int key) {
/*
   return a pointer to the node that contains
   key. If there is no such node, return NULL
*/
   if (!root) return NULL;
   if (key == root->data) return root;
   if (key < root->data)
      return search(root->left_child, key);
   return search(root->right_child, key);
}

~~~



-->iterative

~~~c
tree_ptr iter_search(tree_ptr tree, int key) {
   while (tree) {
      if (key == tree->data) return tree;
      if (key < tree->data)
         tree = tree->left_child;
      else
         tree = tree->right_child;
   }
   return NULL;
}

~~~



>
>
>지울때는 삭제하면 다른 노드 위치시켜야돼.
>
>왼쪽에있는거는 다 작으니까 왼쪽에서 가장 큰거 뽑아서 올리면돼..
>
>우측에서 뽑아오면 가장 작은거 뽑아서 올리면 돼.
>
>근데 밑 사진에서 우측의 70을 끌어올리게 되면 높이가 변하지 않아서 시간 복잡도에 변화가 없다,
>
>시간 복잡도는 깊이에 좌지우지하는데 깊이를 변화시켜주는 것이 효율적이다.
>
>만약 70을 올리게되면 skew로 변해서 worst case발생하게된다.

<img width="351" alt="image-20191010171746918" src="https://user-images.githubusercontent.com/49120090/67013124-93fa7d80-f12d-11e9-889b-2331b8288a59.png">

>
>
>승자 트리 패자 트리 존재하는데
>
>패자 트리가 좀더 빨라 왜냐면 옆에 있는 sibiling을 확인하지 않아도 된다.
>



# 