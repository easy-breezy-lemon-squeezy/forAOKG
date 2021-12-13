#include "GameObjectFactory.h"

bool GameObjectFactory::init(std::string filename)
{
	setlocale(LC_ALL, "russian");

	std::vector <std::string> firstLevel{ "LightObject", "HeavyObject", "BorderObject", "Player", "Bomb", "Monster" };
	std::vector <std::string> secondLevel{ "mesh", "material" };
	std::vector <std::string> thirdLevel{ "diffuse", "ambient", "specular", "emission", "shininess" };

	std::ifstream fin;
	fin.open(filename);

	if (!fin.is_open())
	{
		std::cout << "Не удается найти файл " << filename << std::endl;
		return false;
	}

	std::string jsonString;
	getline(fin, jsonString, static_cast<char>(0));
	fin.close();

	rapidjson::Document document;
	document.Parse(jsonString.c_str());

	if (document.GetParseError() != 0)
	{
		std::cout << "Неверный формат файла" << std::endl;
		return false;
	}
	std::cout << document["LightObject"]["material"]["type"].GetString() << std::endl;
	std::vector <Mesh> mesh(6);
	std::vector <Texture> texture(3);

	mesh[0].load(document["LightObject"]["mesh"].GetString());
	mesh[1].load(document["BorderObject"]["mesh"].GetString());
	mesh[2].load(document["Player"]["mesh"].GetString());
	mesh[3].load(document["HeavyObject"]["mesh"].GetString());
	mesh[4].load(document["Bomb"]["mesh"].GetString());
	mesh[5].load(document["Monster"]["mesh"].GetString());

	std::vector <Texture> tex(3);
	std::vector <PhongMaterial> material(3);
	std::vector <PhongMaterialWithTexture> materialTexture(3);

	int textureCounter_1 = 0;
	int textureCounter_2 = 0;

	for (int i = 0; i < 6; i++)
	{
		float mas1[4];
		float mas2[4];
		float mas3[4];
		float mas4[4];
		
		GLfloat shininess;

		if (document[firstLevel[i].c_str()][secondLevel[1].c_str()]["type"].GetString()[13] != 'W')
		{
			for (int j = 0; j < 4; j++)
			{
				mas1[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[0].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				mas1[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[1].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				mas1[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[2].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				mas1[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[3].c_str()][j].GetDouble();
			}

			shininess = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[4].c_str()].GetDouble();

			material[textureCounter_1].setDiffuse(mas1[0], mas1[1], mas1[2], mas1[3]);
			material[textureCounter_1].setAmbient(mas2[0], mas2[1], mas2[2], mas2[3]);
			material[textureCounter_1].setSpecular(mas3[0], mas3[1], mas3[2], mas3[3]);
			material[textureCounter_1].setEmission(mas4[0], mas4[1], mas4[2], mas4[3]);
			material[textureCounter_1].setShininess(shininess);

			textureCounter_1++;
		}
		if (document[firstLevel[i].c_str()][secondLevel[1].c_str()]["type"].GetString()[13] == 'W')
		{
			for (int j = 0; j < 4; j++)
			{
				mas1[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[0].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				mas1[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[1].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				mas1[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[2].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				mas1[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[3].c_str()][j].GetDouble();
			}

			shininess = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[4].c_str()].GetDouble();

			materialTexture[textureCounter_2].setDiffuse(mas1[0], mas1[1], mas1[2], mas1[3]);
			materialTexture[textureCounter_2].setAmbient(mas2[0], mas2[1], mas2[2], mas2[3]);
			materialTexture[textureCounter_2].setSpecular(mas3[0], mas3[1], mas3[2], mas3[3]);
			materialTexture[textureCounter_2].setEmission(mas4[0], mas4[1], mas4[2], mas4[3]);
			materialTexture[textureCounter_2].setShininess(shininess);

			std::shared_ptr <Texture> texture = std::make_shared<Texture>(tex[textureCounter_2]);
			texture.get()->load(document[firstLevel[i].c_str()][secondLevel[1].c_str()]["texture"].GetString());
			this->textures.push_back(texture);
			textureCounter_2++;
		}
	}


	this->meshes.push_back(std::make_shared<Mesh>(mesh[0]));
	this->meshes.push_back(std::make_shared<Mesh>(mesh[1]));
	this->meshes.push_back(std::make_shared<Mesh>(mesh[2]));

	materialTexture[0].setTexture(this->textures[0]);
	materialTexture[1].setTexture(this->textures[1]);
	materialTexture[2].setTexture(this->textures[2]);


	this->materials.push_back(std::make_shared<PhongMaterialWithTexture>(materialTexture[0]));
	this->materials.push_back(std::make_shared<PhongMaterialWithTexture>(materialTexture[1]));
	this->materials.push_back(std::make_shared<PhongMaterialWithTexture>(materialTexture[2]));
	this->materials.push_back(std::make_shared<PhongMaterial>(material[0]));
	this->materials.push_back(std::make_shared<PhongMaterial>(material[1]));
	this->materials.push_back(std::make_shared<PhongMaterial>(material[2]));
}

shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y, int z) {
	shared_ptr<GraphicObject> ob = make_shared<GraphicObject>();
	switch (type)
	{
	case GameObjectType::LIGHT_OBJECT:
		ob->setMesh(meshes.at(0));
		ob->setMaterial(materials.at(0));
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
	//ob->setMesh(meshes.at(int(type)));
	//ob->setMaterial(materials.at(int(type)));
	shared_ptr<Monster> el = make_shared<Monster>();
	el->setGraphicObject(ob);
	el->setPosition(x - 10, 0, z - 10);
	return el;
}