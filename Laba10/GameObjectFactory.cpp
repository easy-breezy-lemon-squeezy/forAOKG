#include "GameObjectFactory.h"
#include <typeinfo>

using namespace rapidjson;

bool GameObjectFactory::init(std::string filename)
{
		ifstream f(filename);
		if (!f.is_open()) {
			cout << "Error((" << filename << endl;
			return false;
		}
		string jsonString;
		getline(f, jsonString, static_cast<char>(0));
		f.close();
		Document document;
		document.Parse(jsonString.c_str());
		if (document.GetParseError() != 0) {
			cout << "Error((\n";
			return false;
		}
		
		meshes.emplace_back(new Mesh);
		meshes.at(0)->load(document["Player"]["mesh"].GetString());
		float mas[4];
		for (int i = 0; i < document["Player"]["material"]["diffuse"].Size(); i++) {
			mas[i] = document["Player"]["material"]["diffuse"][i].GetDouble();
		}
		materials.emplace_back(new PhongMaterial);
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


		meshes.emplace_back(new Mesh);
		meshes.at(1)->load(document["Bomb"]["mesh"].GetString());
		mas[4];
		for (int i = 0; i < document["Bomb"]["material"]["diffuse"].Size(); i++) {
			mas[i] = document["Bomb"]["material"]["diffuse"][i].GetDouble();
		}
		materials.emplace_back(new PhongMaterial);
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


		meshes.emplace_back(new Mesh);
		meshes.at(2)->load(document["Monster"]["mesh"].GetString());
		mas[4];
		for (int i = 0; i < document["Monster"]["material"]["diffuse"].Size(); i++) {
			mas[i] = document["Monster"]["material"]["diffuse"][i].GetDouble();
		}
		materials.emplace_back(new PhongMaterial);
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


		meshes.emplace_back(new Mesh);
		meshes.at(3)->load(document["LightObject"]["mesh"].GetString());
		mas[4];
		
		materialsWithTexture.emplace_back(new PhongMaterialWithTexture);
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
		textures.emplace_back(new Texture);
		textures.at(0)->load(document["LightObject"]["material"]["texture"].GetString());
		

		meshes.emplace_back(new Mesh);

		meshes.at(4)->load(document["HeavyObject"]["mesh"].GetString());
		mas[4];
		materialsWithTexture.emplace_back(new PhongMaterialWithTexture);
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
		materialsWithTexture.at(1)->setShininess(document["HeavyObject"]["material"]["shininess"].GetDouble());
		textures.emplace_back(new Texture);
		textures.at(1)->load(document["HeavyObject"]["material"]["texture"].GetString());

	
		meshes.emplace_back(new Mesh);
		meshes.at(5)->load(document["BorderObject"]["mesh"].GetString());
		mas[4];
		materialsWithTexture.emplace_back(new PhongMaterialWithTexture);
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
		textures.emplace_back(new Texture);
		textures.at(2)->load(document["BorderObject"]["material"]["texture"].GetString());

	}

	

shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y, int z) {
	shared_ptr<GraphicObject> ob = make_shared<GraphicObject>();
	
	switch (type)
	{
	case GameObjectType::PLAYER:
		ob->setMesh(meshes.at(0));
		ob->setMaterial(materials.at(0));
		break;
	case GameObjectType::BOMB:
		ob->setMesh(meshes.at(1));
		ob->setMaterial(materials.at(1));
		break;
	case GameObjectType::MONSTER:
		ob->setMesh(meshes.at(2));
		ob->setMaterial(materials.at(2));
		break;
	case GameObjectType::LIGHT_OBJECT:
		ob->setMesh(meshes.at(3));
		materialsWithTexture.at(0)->setTexture(textures.at(0));
		ob->setMaterial(materialsWithTexture.at(0));
		Texture::disableAll();
		break;
	case GameObjectType::HEAVY_OBJECT:
		ob->setMesh(meshes.at(4));
		materialsWithTexture.at(1)->setTexture(textures.at(1));
		ob->setMaterial(materialsWithTexture.at(1));
		break;
	case GameObjectType::BORDER_OBJECT:
		ob->setMesh(meshes.at(5));
		materialsWithTexture.at(2)->setTexture(textures.at(2));
		ob->setMaterial(materialsWithTexture.at(2));
		break;
	default:
		break;
	}

	shared_ptr<GameObject> el = make_shared<GameObject>();
	el->setGraphicObject(ob);
	el->setPosition(x - 10, 0, z - 10);
	return el;
}
shared_ptr<Monster> GameObjectFactory::create(GameObjectType type, int x, int y, int z, bool monster) {
	shared_ptr<GraphicObject> ob = make_shared<GraphicObject>();
	switch (type)
	{
	case GameObjectType::PLAYER:
		ob->setMesh(meshes.at(0));
		ob->setMaterial(materials.at(0));
		break;
	case GameObjectType::BOMB:
		ob->setMesh(meshes.at(1));
		ob->setMaterial(materials.at(1));
		break;
	case GameObjectType::MONSTER:
		ob->setMesh(meshes.at(2));
		ob->setMaterial(materials.at(2));
		break;
	case GameObjectType::LIGHT_OBJECT:
		ob->setMesh(meshes.at(3));
		materialsWithTexture.at(0)->setTexture(textures.at(0));
		ob->setMaterial(materialsWithTexture.at(0));
		Texture::disableAll();
		break;
	case GameObjectType::HEAVY_OBJECT:
		ob->setMesh(meshes.at(4));
		ob->setMaterial(materialsWithTexture.at(1));
		break;
	case GameObjectType::BORDER_OBJECT:
		ob->setMesh(meshes.at(5));
		ob->setMaterial(materialsWithTexture.at(2));
		break;
	default:
		break;
	}
	shared_ptr<Monster> el = make_shared<Monster>();
	el->setGraphicObject(ob);
	el->setPosition(x - 10, 0, z - 10);
	return el;
}