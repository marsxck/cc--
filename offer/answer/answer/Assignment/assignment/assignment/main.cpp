#include"assign.h"
void main()
{
	MyString s1("À­Á¦ÈüÀ²");
	MyString s2("ll");
	MyString s3("22");
	s1 = s2 = s3;
	s1.show();
	s2.show();
	s3.show();

}