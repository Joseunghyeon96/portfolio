#pragma once
class MyString
{
	string data;

public:
	MyString(const string& data) : data(data) {}
	MyString(const char* data) : data(data) {}
	MyString(const char data) {
		this->data = data + "\0";
	}

};

