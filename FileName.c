#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Node {
	char world[50];
	char world_tran[50];
	struct Node* right;
	struct Node* left;

};
struct Node* root = NULL;
struct Node* create(const char* data, const char* data1) {
	if(strlen(data) >= 50 || strlen(data1) >= 50) {
		printf("Error: String too long in create()\n");
		return NULL;
	}
	struct Node* NewNode = (struct Node*)malloc(sizeof(struct Node));
	if (NewNode == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}
	strcpy(NewNode->world, data);
	strcpy(NewNode->world_tran, data1);
	NewNode->left = NULL;
	NewNode->right = NULL;
	return NewNode;




}
struct Node* Insert(struct Node* Node, const char* data1, const char* data2) {
	if (Node == NULL) {
		return create(data1, data2);
	}
	if (strcmp(data1, Node->world) < 0) {
		Node->left = Insert(Node->left, data1, data2);

	}
	else if (strcmp(data1, Node->world) > 0) {
		Node->right = Insert(Node->right, data1, data2);
	}
	else {
		strcpy(Node->world_tran, data2);
		printf("Word '%s' already exists. Updating translation...\n", data1);
		
	}
	
	
	return Node;

}
struct Node* Search(struct Node* Node, const char* data1) {
	if (Node == NULL) {
		return NULL;
	}
	if (strcmp(Node->world, data1) == 0) {
		return Node;
	}
	if (strcmp(Node->world, data1) < 0) {
		 return Search(Node->left, data1);

	}
	else if (strcmp(data1, Node->world) > 0) {
		return Search(Node->right, data1);
	}
}
struct Node* translate(struct Node* Node, const char* data1) {
	if (Node == NULL) {
		return NULL;
	}
	if (strcmp(Node->world, data1) == 0) {
		return Node;
	}
	if (strcmp(Node->world, data1) < 0) {
		return translate(Node->left, data1);
	}
	else {
		return translate(Node->right, data1);
	}

}
void Show_all(struct Node* root) {
	if (root == NULL) {
		return;

	}
	Show_all(root->left);
	printf("Word:%s->%s\n",  root->world, root->world_tran);
	Show_all(root->right);
	
}
int Count_words(struct Node* node) {
	if (node == NULL) return 0;
	return 1 + Count_words(node->left) + Count_words(node->right);
}
void Auto_complete(struct Node* root, const char* prefix) {
	if (root == NULL) {
		return;
	}
	int prefix_len = strlen(prefix);
	if (strncmp(root->world, prefix, prefix_len)==0) {
		printf("%s->%s\n", root->world, root->world_tran);


	}
	int cmp = strcmp(prefix, root->world);
	if (cmp <= 0) {
		Auto_complete(root->left, prefix);
	}
    if(cmp>=0) {
		Auto_complete(root->right, prefix);
	}
}
void Save_data_to_fie(struct Node* root,FILE* fp) {
	if (root == NULL) {
		return;

	}
	
	Save_data_to_fie(root->left,fp);
	fprintf(fp,"%s|%s\n",root->world, root->world_tran);
	Save_data_to_fie(root->right,fp);


}
struct Node* Load_data_from_file(struct Node* root, FILE* fp1) {
	char line[100];
	while (fgets(line, 100, fp1) != NULL) {
		line[strcspn(line, "\n")] = '\0';
		char* sep = strchr(line, '|');
		*sep = '\0';
		char* world = line;
		char* world_tran = sep + 1;
		root=Insert(root, world, world_tran);

		
		


	}
	return root;
}
void freeTree(struct Node* root) {
	if (root == NULL) return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}
struct Node* Find_min(struct Node* root) {
	if (root== NULL) return NULL;
	struct Node*Node = root;
	while (Node->left != NULL) {
		Node=Node->left;


	}
	return Node;

}
struct Node* Delete(struct Node* root, const char* del) {
	if (root == NULL) {
		printf("No data yet\n");
		return NULL;

	}
	int cmm = strcmp(del,root->world);
	if (cmm < 0) {
		root->left = Delete(root->left,del);
		return root;

	}
	else if (cmm > 0) {
		root->right = Delete(root->right, del);
		return root;

	}
	else if (cmm == 0) {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			return NULL;
		}
		else if (root->left==NULL) {
			struct Node* tmp = root->right;
			free(root);
			return tmp;


		}
		else if (root->right == NULL) {
			struct Node* temp;
			temp = root->left;
			free(root);
			return temp;

		}
		else {
			struct Node* tmmm = Find_min(root->right);
			char t1[50];
			char t2[50];
			
			strcpy(t1, tmmm->world);
			strcpy(t2, tmmm->world_tran);
			root->right = Delete(root->right, t1);
			strcpy(root->world,t1);
			strcpy(root->world_tran,t2);
			



		}
	}
	return root;

}

int main() {
	int op;
	char word[50], translation[50];
	char pre[10];
	char del[50];

	
	
	
	while (1) {
		printf("\n----------------------------\n");
		printf("  ***ENGLISH DICTIONARY***\n");
		printf("----------------------------\n");
		printf("1.  Add word\n");
		printf("2.  Search word\n");
		printf("3.  Show all words\n");
		printf("4.  Translate word\n");
		printf("5.  Auto-complete\n");
		printf("6.  Statistics\n");
		printf("7.  Save to file\n");
		printf("8.  Load from file\n");
		printf("9.  Delete word\n");
		printf("0.  Exit\n");
		printf("\n>> ");
		scanf_s("%d", &op);
		getchar();
		switch (op) {
		case 1:
			printf("Enter English word: \n");
			gets_s(word, 50);
			

			printf("Enter translation: \n");
			gets_s(translation, 50);
			

			root = Insert(root, word, translation);
			if (root == NULL) {
				printf("Error adding word!\n");
			}
			printf("Word added!\n");
			break;
		case 2:
			printf("Enter word to search: ");
			gets_s(word, 50);
			

			struct Node* found = Search(root, word);
			if (found != NULL) {
				printf("Found: %s -> %s\n", found->world, found->world_tran);
			}
			else {
				printf(" Word not found!\n");
			}
			break;
		case 3:
			printf("List of all words:\n");
			Show_all(root);
			break;

		case 4:
			printf("Enter English word to translate: ");
			gets_s(word, 50);
			struct Node* tran = translate(root, word);
			if (tran != NULL) {
				printf("Translate: %s\n",tran->world_tran);

			}
			else {
				printf(" Word not found!\n");

			}
			break;
		case 5:
			printf("Enter intersted prefix\n");
			gets_s(pre, 10);
			Auto_complete(root, pre);
			break;

		case 6:
			printf("STATISTICS:\n");
			printf("Total words: %d\n", Count_words(root));
			break;
		case 7:
			
			
			printf("Saving data...\n");
			FILE* fp = fopen("translate.txt", "w");

			if (fp == NULL) {
				printf("Error opening file!\n");
				break;

			}
			Save_data_to_fie(root,fp);
			fclose(fp);
			printf("Data saved succesfully\n");
			break;
		case 8:
			printf("Loading data...\n");
			FILE* fp1 = fopen("translate.txt", "r");
			if (fp1 == NULL) {
				printf("Error reading file!\n");
				break;

			}
			root=Load_data_from_file(root, fp1);
			fclose(fp1);
			printf("Data loaded succesfully\n");
			break;
		case 9:
			printf("Enter word you want to delete\n");
			gets_s(del, 50);
			root = Delete(root, del);
			printf("World was delete succesfully\n");
			break;

		case 0:
			printf("Exiting...\n");
			freeTree(root);
			system("pause");
			return(0);

		
			



			

			
			


		}
	}
}
	