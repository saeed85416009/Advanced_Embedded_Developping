
#ifndef MY_LINKEDLIST_H
#define MY_LINKEDLIST_H



 struct people_tag {

	char first_name[16];
	char last_name[16];
	unsigned int age;
	struct people_tag *next;
};


//prototypes
int main_linkedList(int argc, char *argv[]);


#endif
