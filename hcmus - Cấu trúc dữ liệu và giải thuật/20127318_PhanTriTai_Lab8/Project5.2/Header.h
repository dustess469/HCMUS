#pragma once
#ifndef bai2
#define bai2

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void readFile(const char* filename, string name[], string num[], int& n);
int changeStr(string s);
int hashFunc(string s, int size, int i);
void add(string hash[][2], string name[], string num[], int& size);
void find(string hash[][2], string name, int size);
void printHash(string hash[][2], int n);
#endif // !bai2
