#include <string>
#include <iostream>
#include <Python.h>

using namespace std;

#pragma  comment(lib,"Python35")

class CGeometryBase:public PyObject{
public:
	CGeometryBase():i_xpos(0),i_ypos(0),str_geoname(""){}
	~CGeometryBase(){}

	void setgeopos(int ix, int iy){
		i_xpos = ix;
		i_ypos = iy;
	}

	void setgeoname(string name){
		str_geoname = name;
	}

	string getgeoname() const{
		return str_geoname;
	}

	int getgeoxpos() const{
		return i_xpos;
	}

	int getgeoypos() const{
		return i_ypos;
	}

	virtual double getgeoarea() = 0;
private:
	int i_xpos;
	int i_ypos;
	string str_geoname;
};

class CGeoCircle :public CGeometryBase{
public:
	CGeoCircle(double radius):db_radius(radius){}
	~CGeoCircle(){}

	virtual double getgeoarea(){
		return 3.14*db_radius*db_radius;
	}

	double getcircleradius() const{
		return db_radius;
	}

	void setcircleradius(double dbradius){
		db_radius = dbradius;
	}

private:
	double db_radius;
};

class CGeoRect :public CGeometryBase{
public:
	CGeoRect(){}
	CGeoRect(double dbXlenth,double dbYLenth):
		db_xlenth(dbXlenth), db_ylenth(dbYLenth){}

	~CGeoRect(){}

	virtual double getgeoarea(){
		return db_xlenth*db_ylenth;
	}

	double getrectxlenth() const{
		return db_xlenth;
	}

	double getrectylenth() const{
		return db_ylenth;
	}

	void setrectxlenth(double x){
		db_xlenth = x;
	}

	void setrectylenth(double y){
		db_ylenth = y;
	}
private:
	double db_xlenth;
	double db_ylenth;
};

extern "C"{
	CGeoRect rect;
	
	rect.getgeoarea();

}