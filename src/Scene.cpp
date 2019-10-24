#include <fstream>

#include "PrimTriangle.h"
#include "ShaderPhong.h"
#include "Scene.h"
#include "ShaderEyelight.h"

// Done with Group Work 

void CScene::ParseOBJ(const std::string& name_of_file) {
	std::cout << "OBJFile : " << name_of_file << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
	std::vector <unsigned int> indices;
	std::vector <Vec3f> vertices;

	std::ifstream file;
	file.open(name_of_file);
	if (!file.is_open()) {
		std::cout << "We have error opening the file" << std::endl;
		return;
	}

	while(!file.eof()) {
		char current_line = file.get();
		if (current_line == 'v') {
			Vec3f vertex;
			float a, b ,c;
			file >> a >> b >> c;
			vertex[0] = a * 99.99f;
			vertex[1] = b * 99.99f;
			vertex[2] = c * 99.99f;
			vertices.push_back(vertex);
		}
		else if(current_line == 'f') {
			unsigned int vertex_index[3];
			unsigned int a, b, c;
			file >>a >> b >> c;
			vertex_index[0] = a;
			vertex_index[1] = b;
			vertex_index[2] = c;
			indices.push_back(vertex_index[0]);
			indices.push_back(vertex_index[1]);
			indices.push_back(vertex_index[2]);
		}
	}

	int i = 0;
	while(i < indices.size()) {
		Vec3f v1, v2, v3;
		v1 = vertices[indices[i] - 1];
		i++;
		v2 = vertices[indices[i] - 1];
		i++;
		v3 = vertices[indices[i] - 1];
		i++;
		Add(std::make_shared<CPrimTriangle>(v1, v2, v3,pShader));
	}

	// close the file
	file.close();
	std::cout << "Parsing is finished" << std::endl;

	return;
}
