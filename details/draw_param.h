#pragma once
namespace dx_engine {
	enum class blend {
		none = 0, //�m�[�u�����h
		alpha = 1, //���u�����h
		add = 2, //���Z�u�����h
		sub = 3, //���Z�u�����h
		mul = 4, //��Z�u�����h
		dest = 8, //�J���[�͍X�V����Ȃ�
		inv_dest = 9, //�`���̐F�̔��]�l���|����
		inv_src = 10, //�`�挳�̐F�𔽓]����
		mul_alpha = 11,	//�A���t�@�`�����l���l���t����Z�u�����h
		pma_alpha = 17, //��Z�ς݃��u�����h���[�h�̃��u�����h
		pma_add = 18, //��Z�ς݃��u�����h���[�h�̉��Z�u�����h
		pma_sub = 19, //��Z�ς݃��u�����h���[�h�̌��Z�u�����h
		pma_inv_src = 20, //��Z�ς݃��u�����h���[�h�̕`�挳�̐F�𔽓]����
	};

	enum class font_type {
		normal = 0, //�m�[�}���t�H���g
		edge = 1, //�G�b�W�t���t�H���g
		anti_aliasing = 2, //�A���`�G�C���A�V���O�t�H���g
		edged_anti_aliasing = 3, //�G�b�W�t���A���`�G�C���A�V���O�t�H���g
	};
}