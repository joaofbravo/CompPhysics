#include "Material.h"
#include <iostream>

using namespace std;

Material::Material(string fname, Double_t fdens): name(fname), density(fdens) {
	cout << __PRETTY_FUNCTION__ << endl;
}

Material::~Material() {
	cout << __PRETTY_FUNCTION__ << endl;
}

string Material::GetName() {
	cout << __PRETTY_FUNCTION__ << endl; 
	return name;
}

Double_t Material::GetDensity() {
	cout << __PRETTY_FUNCTION__ << endl; 
	return density;
}

void Material::SetName(string fname)
{
	name = fname;
	cout << __PRETTY_FUNCTION__ << endl;
}

void Material::SetDensity(Double_t dens)
{
	density = dens;
	cout << __PRETTY_FUNCTION__ << endl;
}

void Material::Print()
{
	cout << endl << endl;
	cout << "The material "<< name << " has a density of " << density << " Kg.m^-3" << endl << endl;
	cout << __PRETTY_FUNCTION__ << endl;
}