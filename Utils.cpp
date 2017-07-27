// 
// 
// 

#include "Utils.h"
/*
void UtilsClass::init()
{


}*/

String UtilsClass::PadIntWithZeros(int number)
{
	String num = "";
	if (number < 10) { num += "0"; }
	num += String(number);
	return num;
}

UtilsClass Utils;

