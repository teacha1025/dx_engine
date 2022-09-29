#pragma once
#include <string>
#include <vector>
#include "def.h"
#include "point.h"


namespace dx_engine {
	class csv {
	private:
		std::string name = "";
		std::vector<std::vector<std::string>> data;
		point<uint> _size;
	public:
		/// <summary>
		/// csv���쐬
		/// </summary>
		/// <param name="path">csv�t�@�C���̃p�X</param>
		/// <param name="split">��؂蕶�� �f�t�H���g�ł� ','</param>
		csv(const std::string& path, char split = ',');

		/// <summary>
		/// csv�̃f�[�^���擾
		/// </summary>
		/// <param name="position">�擾����f�[�^�̍��W</param>
		/// <returns>������̃f�[�^</returns>
		std::string at(const point<uint>& position) const;

		/// <summary>
		/// csv�̑傫�����擾
		/// </summary>
		/// <returns>csv�̍s���~1�s�ڂ̗�</returns>
		point<uint> size() const;
	};
}