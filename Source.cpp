#include <iostream>;
#include <stdlib.h>  
#include <crtdbg.h>  


using namespace std;

int memory_created=0;
int memory_deleted=0;
const int SIZE = 6;


struct node {
	node *left=NULL;
	node *right=NULL;
	char data;
};

void tree_insert(node **root, char data) {
	if ((*root) == NULL) {
		node *new_node = new node;
		memory_created++;
		new_node->data = data;
		*root = new_node;
	}
	else if ((*root)->data == NULL) {
		node *new_node = new node;
		memory_created++;
		new_node->data = data;
		*root = new_node;
	}
	else {
		if (data <= (*root)->data) {
			tree_insert(&(*root)->left, data);
		}
		else {
			tree_insert(&(*root)->right, data);
		}
	}

	return;
}

node* tree_search(node* root, char data) {
	if (root == NULL){
		return NULL;
	}

	if (data == root->data) {
		return root;
	}
	else if (data < root->data) {
		tree_search(root->left, data);
	}
	else {
		tree_search(root->right, data);
	}


}

void tree_print_sorted(node* root) {
	if (root!=NULL) {
		if (root->left != NULL) {
			tree_print_sorted(root->left);
		}

		cout << root->data << ", ";

		if (root->right != NULL) {
			tree_print_sorted(root->right);
		}
	}
}

void tree_delete(node *root) {
	if (root != NULL) {
		if (root->left != NULL) {
			tree_delete(root->left);
		}
		if (root->right != NULL) {
			tree_delete(root->right);
		}
		delete root;
		memory_deleted++;
		root = NULL;
	}

}

int partition(char *array, int l, int r) {

	//create a wall, index which everything to left of, is less than the pivot
	int wall = l - 1;
	//create pivot. 
	int pivot = r;
	//traverse through the array
	for (int i = l; i < r; i++) {
		//if the array[i] is less then the pivot, move the wall up one, and swap the values in [wall] and [i]
		if (array[i] <= array[pivot]) {
			wall++;
			swap(array[wall], array[i]);
		}
	}
	//move pivot to it's correct location
	swap(array[wall + 1], array[pivot]);
	//return pivot
	return wall + 1;
}

void quick_sort(char *array, int l, int r) {
	//checks to make sure inputs are valid, and that l is indeed to the left of r
	if (l < r) {
		//create a pivot
		int pivot = partition(array, l, r);
		//recurse, and sort arrays either side of pivot
		quick_sort(array, l, pivot - 1);
		quick_sort(array, pivot + 1, r);
	}

}

node* add_mid(char *array, int l, int r) {
	if (l > r) {
		return NULL;
	}
	int mid = l + (r - l) / 2;
	//node *new_node = new node;
	//memory_created++;
	node *new_node = NULL;
	tree_insert(&new_node, array[mid]);
	new_node->left = add_mid(array, l, mid - 1);
	new_node->right = add_mid(array, mid + 1, r);
	return new_node;
}

node* make_balanced_BST(char *array) {
	quick_sort(array, 0, SIZE - 1);

	node *root = add_mid(array, 0, SIZE - 1);
	
	return root;
}



int main() {

	char array[SIZE] = { 'X', 'Z', 'C', 'B', 'A', 'Y' };

	node *head = NULL;
	
	tree_insert(&head, 'g');
	tree_insert(&head, 'a');
	tree_insert(&head, 'r');
	tree_insert(&head, 'f');
	tree_insert(&head, 'g');
	tree_insert(&head, 'a');
	tree_insert(&head, 'g');
	tree_insert(&head, 'w');
	tree_insert(&head, 'h');
	tree_insert(&head, 'l'); 
	
	if (tree_search(head, 'r')) {
		cout << "BOO YA SAECH WORKS";
	}
	if (tree_search(head, '1')) {
		cout << "NEVER MIND ITS BROKEn";
	}


	cout << "Binary Search Tree in ascending order :" << endl;
	tree_print_sorted(head);
	cout << endl;
	tree_delete(head);
	cout << "Binary Search Tree deleted." << endl << endl;


	node* head_balanced = make_balanced_BST(array);
	cout << "Binary Search Tree in ascending order :" << endl;
	tree_print_sorted(head_balanced);
	cout << endl;
	tree_delete(head_balanced);
	cout << "Binary Search Tree deleted." << endl;



	cout << endl;
	cout << "memory created in programe = " << memory_created << endl;
	cout << "memory deleted in programe = " << memory_deleted << endl;
	cout << "memory leaks = " << memory_created - memory_deleted << endl;
	return 0;
}