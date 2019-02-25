// StringADT demonstration file main.cpp
#include <stdio.h>
#include <string.h> // declares the built-in C string library functions, like strcat
#include "String.h" // declares our new improved String functions, like utstrcat
#include <stdlib.h>

void testStage1(void) {
	char p[12];
	const char* q = "Hello World";
	UTString* s; 
	UTString* t;
	
	printf("this test should print Hello World three times\n");

	for (unsigned k = 0; k < 12; k += 1) {
		p[k] = q[k];
	}
	s = utstrdup(p);
	printf("%s\n", s->string);

	q = "you goofed!";
	for (unsigned k = 0; k < 12; k += 1) {
		p[k] = q[k];
	}
	printf("%s\n", s->string);
	
	t = utstrdup(s->string);
	utstrfree(s);
	printf("%s\n", t->string);
	utstrfree(t);
}	

void testStage2(void) {
	char c_str1[20] = "hello";
	UTString* ut_str1;
	UTString* ut_str2;

	printf("Starting stage 2 tests\n");
	strcat(c_str1, " world");
	printf("%s\n", c_str1); // nothing exciting, prints "hello world"

	ut_str1 = utstrdup("hello ");
	ut_str1 = utstrrealloc(ut_str1, 20);

	utstrcat(ut_str1, c_str1);
	printf("%s\n", ut_str1->string); // slightly more exciting, prints "hello hello world"
	utstrcat(ut_str1, " world");
	printf("%s\n", ut_str1->string); // exciting, should print "hello hello world wo", 'cause there's not enough room for the second world

	ut_str2 = utstrdup("");
	ut_str2 = utstrrealloc(ut_str2, 11);
	utstrcpy(ut_str2, ut_str1->string + 6);
	printf("%s\n", ut_str2->string); // back to "hello world"

	ut_str2 = utstrrealloc(ut_str2, 23);
	utstrcat(ut_str2, " ");
	utstrcat(ut_str2, ut_str1->string);
	printf("%s\n", ut_str2->string); // now should be "hello world hello hello"
 
	utstrfree(ut_str1);
	utstrfree(ut_str2);
}

#define BIG 1000000
void testStage3(void) {
	int k;
	UTString* ut_str1 = utstrdup("");
	ut_str1 = utstrrealloc(ut_str1, BIG); // big, big string

	printf("attempting stage 3 test. This shouldn't take long...\n");
	printf("(no really, it shouldn't take long, if it does, you fail this test)\n");
	fflush(stdout);

	for (k = 0; k < BIG; k += 1) {
		utstrcat(ut_str1, "*");
	}
	if (ut_str1->string[BIG-1] != '*') {
		printf("stage3 fails for not copying all the characters\n");
	} else if (strlen(ut_str1->string) != BIG) {
		printf("Hmmm, stage3 has something wrong\n");
	} else {
		printf("grats, stage 3 passed (unless it took a long time to print this message)\n");
	}
	utstrfree(ut_str1);
}

#define BAD_SIGNATURE (~0xbaadbeef)

/*
 * This is an important test that likely sounds strange: 
 * Each of the following lines should crash the program by failling an assert. 
 * Try each, one at a time, to make sure your program acts as expected.
 * If your program does not crash, you are doing something wrong and will lose points. 
 */
void testStage4(void) {
     char p[20] = "Hello World!";
	 UTString* utstr1 = utstrdup("Hello World");
     *(uint32_t*)( utstr1->string + utstr1->length + 1 ) = BAD_SIGNATURE;
   //printf("crashing with utstrlen\n\n\n"); utstrlen(utstr1);
   //printf("Crashing with utstrcpy\n\n\n"); utstrcpy(utstr1, p);
   printf("crashing with utstrcat\n\n\n"); utstrcat(utstr1, p);
   //printf("crashing with utstrfree\n\n\n"); utstrfree(utstr1);
   //printf("crashing with utstrrealloc\n\n\n"); utstrrealloc(utstr1, 40);
}

void testStage5(void) {

    UTString* s = utstrdup("");

    printf("%s\n",s->string);
    printf("%d\n", utstrlen(s));
    //should print 0
    utstrcat(s,"");
    printf("%s\n",s->string);
    //shouldnt add anything
    utstrcpy(s,"");
    printf("%s\n",s->string);
    //shouldnt change anything
    utstrcat(s,"HI");
    printf("%s\n",s->string);
    //shouldnt add anything
    utstrcpy(s,"HI");
    printf("%s\n",s->string);
    //shouldnt add anything


    utstrrealloc(s,10);
    printf("%s\n",s->string);
    printf("%d\n", utstrlen(s));
    //should print 0
    utstrcat(s,"");
    printf("%s\n",s->string);
    //shouldnt add anything
    utstrcpy(s,"");
    printf("%s\n",s->string);
    //shouldnt change anything
    utstrcat(s,"HI");
    printf("%s\n",s->string);
    //should be hi
    utstrcpy(s,"IH");
    //now should be IH
    printf("%s\n",s->string);
    printf("%d\n", utstrlen(s));
    //should be 2

    utstrrealloc(s,5);
    utstrcpy(s,"12345678910");
    printf("%s\n",s->string);
    //shouldnt put the last 0 on there
    printf("%d\n", utstrlen(s));
    //print 10
    utstrcat(s,"helloworld");
    printf("%s\n",s->string);
    //should be the same
    utstrcpy(s,"54321");
    printf("%s\n",s->string);
    //all changed

    utstrrealloc(s,15);
    utstrcat(s,"yoyo honey singh");
    printf("%s\n",s->string);
    //should add yoyohoney
    printf("%d\n", utstrlen(s));
    //14
    utstrcpy(s,"hellohellohello");
    printf("%s\n",s->string);
    //should all be hello now
    utstrcpy(s,"hey");
    printf("%d",utstrlen(s));
    printf("\n\n\n");


    UTString* n = utstrdup(" ");
    printf("%d\n",utstrlen(n));
    //should print 1
    utstrcpy(n,"hi");
    printf("%s\n",n->string);
    //should have h
    utstrcpy(n,"");
    printf("%s",n->string);
    //should be clear
    utstrcat(n,"");
    printf("%s",n->string);
    //no change
    utstrcat(n,"'");
    printf("%s\n",n->string);
    //print '
    utstrcpy(n," ");
    printf("%s",n->string);
    //should be cleared now
    utstrrealloc(n,10);
    printf("%d\n",n->capacity);
    //should be 10
    utstrcpy(n,"");
    printf("%s",n->string);
    //should be same as before
    utstrcpy(n,s->string);
    printf("%s\n",n->string);
    //should make it hellohello
    utstrrealloc(n,25);
    utstrcat(n,s->string);
    printf("%s\n",n->string);
    //should make it hellohellohellohellohello
    utstrcpy(n,s->string+1);
    printf("%s\n",n->string);
    //should be ellohellohello
    printf("%d\n",utstrlen(n));
    //should be 14
    printf("%d\n",n->capacity);
    //should be 10

    utstrfree(s);
    utstrfree(n);
}

int main(void) {
	testStage1();
	testStage2();
	testStage3();
	//testStage4();
	//testStage5();
	return 0;
}
