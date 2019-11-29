#pragma once
typedef unsigned char byte;

struct IInputStream {
	std::string filename;
	std::ifstream& in;

	IInputStream(const std::string& name, std::ifstream& _in) :
		filename(name),
		in(_in)
	{
	}
	bool Read(byte& value)
	{
		unsigned char* c = new unsigned char[1]{ value };
		in.read((char*)c, 1);
		if (in.good())
		{	
			value = c[0];
			return true;
		}
		else
			return false;
	}
};

struct IOutputStream {
	IOutputStream(const std::string& name, std::ofstream& _out) :
		filename(name),
		out(_out)
	{
	}
	void Write(byte value)
	{
		unsigned char* c = new unsigned char[1]{ value };
		out.write((char*)c, 1);
	}
	std::string filename;
	std::ofstream& out;
};
