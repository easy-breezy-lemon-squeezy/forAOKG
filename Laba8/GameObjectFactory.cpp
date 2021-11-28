#include "GameObjectFactory.h"
#include "rapidjson-master/include/rapidjson/document.h"
// указываем используемые пространства имен
using namespace rapidjson;

bool GameObjectFactory::init(const char* file)
{
	string filename = file;
	// открываем файл с заданным именем и проверяем, удалось ли его открыть
	ifstream f(filename);
	if (!f.is_open()) {
		cout << "Не уадется найти файл " << filename << endl;
		return false;
	}
	string jsonString;
	getline(f, jsonString, static_cast<char>(0));
	f.close();
	// парсим - если ошибка, то выходим
	Document document;
	document.Parse(jsonString.c_str());
	if (document.GetParseError() != 0) {
		cout << "неверный формат файла\n";
		return false;
	}
	
	string meshLightObject = document["LightObject"]["mesh"].GetString();
	meshes.emplace_back(new Mesh);
	meshes.at(0)->load(meshLightObject);
	float mas[4];
	for (int i = 0; i < document["LightObject"]["material"]["diffuse"].Size(); i++) {
		mas[i] = document["LightObject"]["material"]["diffuse"][i].GetDouble();
	}
	materials.emplace_back(new PhongMaterial);
	materials.at(0)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["LightObject"]["material"]["ambient"].Size(); i++) {
		mas[i] = document["LightObject"]["material"]["ambient"][i].GetDouble();
	}
	materials.at(0)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["LightObject"]["material"]["specular"].Size(); i++) {
		mas[i] = document["LightObject"]["material"]["specular"][i].GetDouble();
	}
	materials.at(0)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["LightObject"]["material"]["emission"].Size(); i++) {
		mas[i] = document["LightObject"]["material"]["emission"][i].GetDouble();
	}
	materials.at(0)->setEmission(mas[0], mas[1], mas[2], mas[3]);
	double shininessLightObject = document["LightObject"]["material"]["shininess"].GetDouble();
	materials.at(0)->setShininess(shininessLightObject);

	meshLightObject = document["HeavyObject"]["mesh"].GetString();
	meshes.emplace_back(new Mesh);
	meshes.at(1)->load(meshLightObject);
	mas[4];
	for (int i = 0; i < document["HeavyObject"]["material"]["diffuse"].Size(); i++) {
		mas[i] = document["HeavyObject"]["material"]["diffuse"][i].GetDouble();
	}
	materials.emplace_back(new PhongMaterial);
	materials.at(1)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["HeavyObject"]["material"]["ambient"].Size(); i++) {
		mas[i] = document["HeavyObject"]["material"]["ambient"][i].GetDouble();
	}
	materials.at(1)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["HeavyObject"]["material"]["specular"].Size(); i++) {
		mas[i] = document["HeavyObject"]["material"]["specular"][i].GetDouble();
	}
	materials.at(1)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["HeavyObject"]["material"]["emission"].Size(); i++) {
		mas[i] = document["HeavyObject"]["material"]["emission"][i].GetDouble();
	}
	materials.at(1)->setEmission(mas[0], mas[1], mas[2], mas[3]);
	shininessLightObject = document["HeavyObject"]["material"]["shininess"].GetDouble();
	materials.at(1)->setShininess(shininessLightObject);

	meshLightObject = document["BorderObject"]["mesh"].GetString();
	meshes.emplace_back(new Mesh);
	meshes.at(2)->load(meshLightObject);
	mas[4];
	for (int i = 0; i < document["BorderObject"]["material"]["diffuse"].Size(); i++) {
		mas[i] = document["BorderObject"]["material"]["diffuse"][i].GetDouble();
	}
	materials.emplace_back(new PhongMaterial);
	materials.at(2)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["BorderObject"]["material"]["ambient"].Size(); i++) {
		mas[i] = document["BorderObject"]["material"]["ambient"][i].GetDouble();
	}
	materials.at(2)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["BorderObject"]["material"]["specular"].Size(); i++) {
		mas[i] = document["BorderObject"]["material"]["specular"][i].GetDouble();
	}
	materials.at(2)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["BorderObject"]["material"]["emission"].Size(); i++) {
		mas[i] = document["BorderObject"]["material"]["emission"][i].GetDouble();
	}
	materials.at(2)->setEmission(mas[0], mas[1], mas[2], mas[3]);
	shininessLightObject = document["BorderObject"]["material"]["shininess"].GetDouble();
	materials.at(2)->setShininess(shininessLightObject);

	meshLightObject = document["Player"]["mesh"].GetString();
	meshes.emplace_back(new Mesh);
	meshes.at(3)->load(meshLightObject);
	mas[4];
	for (int i = 0; i < document["Player"]["material"]["diffuse"].Size(); i++) {
		mas[i] = document["Player"]["material"]["diffuse"][i].GetDouble();
	}
	materials.emplace_back(new PhongMaterial);
	materials.at(3)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["Player"]["material"]["ambient"].Size(); i++) {
		mas[i] = document["Player"]["material"]["ambient"][i].GetDouble();
	}
	materials.at(3)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["Player"]["material"]["specular"].Size(); i++) {
		mas[i] = document["Player"]["material"]["specular"][i].GetDouble();
	}
	materials.at(3)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["Player"]["material"]["emission"].Size(); i++) {
		mas[i] = document["Player"]["material"]["emission"][i].GetDouble();
	}
	materials.at(3)->setEmission(mas[0], mas[1], mas[2], mas[3]);
	shininessLightObject = document["Player"]["material"]["shininess"].GetDouble();
	materials.at(3)->setShininess(shininessLightObject);

	meshLightObject = document["Bomb"]["mesh"].GetString();
	meshes.emplace_back(new Mesh);
	meshes.at(4)->load(meshLightObject);
	mas[4];
	for (int i = 0; i < document["Bomb"]["material"]["diffuse"].Size(); i++) {
		mas[i] = document["Bomb"]["material"]["diffuse"][i].GetDouble();
	}
	materials.emplace_back(new PhongMaterial);
	materials.at(4)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["Bomb"]["material"]["ambient"].Size(); i++) {
		mas[i] = document["Bomb"]["material"]["ambient"][i].GetDouble();
	}
	materials.at(4)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["Bomb"]["material"]["specular"].Size(); i++) {
		mas[i] = document["Bomb"]["material"]["specular"][i].GetDouble();
	}
	materials.at(4)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["Bomb"]["material"]["emission"].Size(); i++) {
		mas[i] = document["Bomb"]["material"]["emission"][i].GetDouble();
	}
	materials.at(4)->setEmission(mas[0], mas[1], mas[2], mas[3]);
	shininessLightObject = document["Bomb"]["material"]["shininess"].GetDouble();
	materials.at(4)->setShininess(shininessLightObject);

	meshLightObject = document["Monster"]["mesh"].GetString();
	meshes.emplace_back(new Mesh);
	meshes.at(5)->load(meshLightObject);
	mas[4];
	for (int i = 0; i < document["Monster"]["material"]["diffuse"].Size(); i++) {
		mas[i] = document["Monster"]["material"]["diffuse"][i].GetDouble();
	}
	materials.emplace_back(new PhongMaterial);
	materials.at(5)->setDiffuse(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["Monster"]["material"]["ambient"].Size(); i++) {
		mas[i] = document["Monster"]["material"]["ambient"][i].GetDouble();
	}
	materials.at(5)->setAmbient(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["Monster"]["material"]["specular"].Size(); i++) {
		mas[i] = document["Monster"]["material"]["specular"][i].GetDouble();
	}
	materials.at(5)->setSpecular(mas[0], mas[1], mas[2], mas[3]);
	for (int i = 0; i < document["Monster"]["material"]["emission"].Size(); i++) {
		mas[i] = document["Monster"]["material"]["emission"][i].GetDouble();
	}
	materials.at(5)->setEmission(mas[0], mas[1], mas[2], mas[3]);
	shininessLightObject = document["Monster"]["material"]["shininess"].GetDouble();
	materials.at(5)->setShininess(shininessLightObject);
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