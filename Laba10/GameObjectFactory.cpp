#include "GameObjectFactory.h"
#include <typeinfo>
// указываем используемые пространства имен
using namespace rapidjson;

bool GameObjectFactory::init()
{
	string filename = "data//GameObjectsDescription.json";
	// открываем файл с заданным именем и проверяем, удалось ли его открыть
	ifstream fin;
	fin.open(filename);

	if (!fin.is_open())
	{
		cout << "Не удается найти файл " << filename << std::endl;
		return false;
	}

	string jsonString;
	getline(fin, jsonString, static_cast<char>(0));
	fin.close();

	rapidjson::Document document;
	document.Parse(jsonString.c_str());

	if (document.GetParseError() != 0)
	{
		cout << "Неверный формат файла" << std::endl;
		return false;
	}

	
	meshes.emplace_back(new Mesh);
	meshes.at(0)->load(document["LightObject"]["mesh"].GetString());
	
	if (document["LightObject"]["material"]["type"].GetString() == "PhongMaterialWithTexture") {
		materialsWithTexture.emplace_back(new PhongMaterialWithTexture);
		textures.at(0)->load(document["LightObject"]["material"]["texture"].GetString());
		float mas[4];
		for (int i = 0; i < document["LightObject"]["material"]["diffuse"].Size(); i++) {
			mas[i] = document["LightObject"]["material"]["diffuse"][i].GetDouble();
		}
		materialsWithTexture.at(0)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["LightObject"]["material"]["ambient"].Size(); i++) {
			mas[i] = document["LightObject"]["material"]["ambient"][i].GetDouble();
		}
		materialsWithTexture.at(0)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["LightObject"]["material"]["specular"].Size(); i++) {
			mas[i] = document["LightObject"]["material"]["specular"][i].GetDouble();
		}
		materialsWithTexture.at(0)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["LightObject"]["material"]["emission"].Size(); i++) {
			mas[i] = document["LightObject"]["material"]["emission"][i].GetDouble();
		}
		materialsWithTexture.at(0)->setEmission(mas[0], mas[1], mas[2], mas[3]);
		materialsWithTexture.at(0)->setShininess(document["LightObject"]["material"]["shininess"].GetDouble());
	}
	

	meshes.emplace_back(new Mesh);
	meshes.at(1)->load(document["HeavyObject"]["mesh"].GetString());
	if (document["HeavyObject"]["material"]["type"].GetString() == "PhongMaterialWithTexture") {
		materialsWithTexture.emplace_back(new PhongMaterialWithTexture);
		textures.at(1)->load(document["HeavyObject"]["material"]["texture"].GetString());
		float mas[4];
		for (int i = 0; i < document["HeavyObject"]["material"]["diffuse"].Size(); i++) {
			mas[i] = document["HeavyObject"]["material"]["diffuse"][i].GetDouble();
		}
		materialsWithTexture.at(1)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["HeavyObject"]["material"]["ambient"].Size(); i++) {
			mas[i] = document["HeavyObject"]["material"]["ambient"][i].GetDouble();
		}
		materialsWithTexture.at(1)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["HeavyObject"]["material"]["specular"].Size(); i++) {
			mas[i] = document["HeavyObject"]["material"]["specular"][i].GetDouble();
		}
		materialsWithTexture.at(1)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["HeavyObject"]["material"]["emission"].Size(); i++) {
			mas[i] = document["HeavyObject"]["material"]["emission"][i].GetDouble();
		}
		materialsWithTexture.at(1)->setEmission(mas[0], mas[1], mas[2], mas[3]);
		materialsWithTexture.at(1)->setShininess(document["Monster"]["material"]["shininess"].GetDouble());
	}
	

	meshes.emplace_back(new Mesh);
	meshes.at(2)->load(document["BorderObject"]["mesh"].GetString());

	if (document["BorderObject"]["material"]["type"].GetString() == "PhongMaterialWithTexture") {
		materialsWithTexture.emplace_back(new PhongMaterialWithTexture);
		textures.at(2)->load(document["BorderObject"]["material"]["texture"].GetString());
		float mas[4];
		for (int i = 0; i < document["BorderObject"]["material"]["diffuse"].Size(); i++) {
			mas[i] = document["BorderObject"]["material"]["diffuse"][i].GetDouble();
		}
		materialsWithTexture.at(2)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["BorderObject"]["material"]["ambient"].Size(); i++) {
			mas[i] = document["BorderObject"]["material"]["ambient"][i].GetDouble();
		}
		materialsWithTexture.at(2)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["BorderObject"]["material"]["specular"].Size(); i++) {
			mas[i] = document["BorderObject"]["material"]["specular"][i].GetDouble();
		}
		materialsWithTexture.at(2)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["BorderObject"]["material"]["emission"].Size(); i++) {
			mas[i] = document["BorderObject"]["material"]["emission"][i].GetDouble();
		}
		materialsWithTexture.at(2)->setEmission(mas[0], mas[1], mas[2], mas[3]);
		materialsWithTexture.at(2)->setShininess(document["BorderObject"]["material"]["shininess"].GetDouble());
	}
	
	

	meshes.emplace_back(new Mesh);
	meshes.at(3)->load(document["Player"]["mesh"].GetString());
	
	if (document["Player"]["material"]["type"].GetString() == "PhongMaterial") {
		materials.emplace_back(new PhongMaterial);
		float mas[4];
		for (int i = 0; i < document["Player"]["material"]["diffuse"].Size(); i++) {
			mas[i] = document["Player"]["material"]["diffuse"][i].GetDouble();
		}
		materials.at(0)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["Player"]["material"]["ambient"].Size(); i++) {
			mas[i] = document["Player"]["material"]["ambient"][i].GetDouble();
		}
		materials.at(0)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["Player"]["material"]["specular"].Size(); i++) {
			mas[i] = document["Player"]["material"]["specular"][i].GetDouble();
		}
		materials.at(0)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["Player"]["material"]["emission"].Size(); i++) {
			mas[i] = document["Player"]["material"]["emission"][i].GetDouble();
		}
		materials.at(0)->setEmission(mas[0], mas[1], mas[2], mas[3]);
		materials.at(0)->setShininess(document["Player"]["material"]["shininess"].GetDouble());
	}

	

	meshes.emplace_back(new Mesh);
	meshes.at(4)->load(document["Bomb"]["mesh"].GetString());
	
	if (document["Bomb"]["material"]["type"].GetString() == "PhongMaterial") {
		materials.emplace_back(new PhongMaterial);
		float mas[4];
		for (int i = 0; i < document["Bomb"]["material"]["diffuse"].Size(); i++) {
			mas[i] = document["Bomb"]["material"]["diffuse"][i].GetDouble();
		}

		materials.at(1)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["Bomb"]["material"]["ambient"].Size(); i++) {
			mas[i] = document["Bomb"]["material"]["ambient"][i].GetDouble();
		}
		materials.at(1)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["Bomb"]["material"]["specular"].Size(); i++) {
			mas[i] = document["Bomb"]["material"]["specular"][i].GetDouble();
		}
		materials.at(1)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["Bomb"]["material"]["emission"].Size(); i++) {
			mas[i] = document["Bomb"]["material"]["emission"][i].GetDouble();
		}
		materials.at(1)->setEmission(mas[0], mas[1], mas[2], mas[3]);
		materials.at(1)->setShininess(document["Bomb"]["material"]["shininess"].GetDouble());
	}

	meshes.emplace_back(new Mesh);
	meshes.at(5)->load(document["Monster"]["mesh"].GetString());
	
	if (document["Monster"]["material"]["type"].GetString() == "PhongMaterial") {
		materials.emplace_back(new PhongMaterial);
		float mas[4];
		for (int i = 0; i < document["Monster"]["material"]["diffuse"].Size(); i++) {
			mas[i] = document["Monster"]["material"]["diffuse"][i].GetDouble();
		}
		materials.at(2)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["Monster"]["material"]["ambient"].Size(); i++) {
			mas[i] = document["Monster"]["material"]["ambient"][i].GetDouble();
		}
		materials.at(2)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["Monster"]["material"]["specular"].Size(); i++) {
			mas[i] = document["Monster"]["material"]["specular"][i].GetDouble();
		}
		materials.at(2)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
		for (int i = 0; i < document["Monster"]["material"]["emission"].Size(); i++) {
			mas[i] = document["Monster"]["material"]["emission"][i].GetDouble();
		}
		materials.at(2)->setEmission(mas[0], mas[1], mas[2], mas[3]);
		materials.at(2)->setShininess(document["Monster"]["material"]["shininess"].GetDouble());
	}

	
}

shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y, int z) {
	shared_ptr<GraphicObject> ob = make_shared<GraphicObject>();
	ob->setMesh(meshes.at(int(type)));
	ob->setMaterial(materials.at(int(type)));
	shared_ptr<GameObject> el = make_shared<GameObject>();
	el->setGraphicObject(ob);
	el->setPosition(x - 10, 0, z - 10);
	return el;
}
shared_ptr<Monster> GameObjectFactory::create(GameObjectType type, int x, int y, int z, bool monster){
	shared_ptr<GraphicObject> ob = make_shared<GraphicObject>();
	ob->setMesh(meshes.at(int(type)));
	ob->setMaterial(materials.at(int(type)));
	shared_ptr<Monster> el = make_shared<Monster>();
	el->setGraphicObject(ob);
	el->setPosition(x - 10, 0, z - 10);
	return el;
}