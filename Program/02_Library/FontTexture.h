#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <tuple>
#include "Vector.h"

namespace tnl {

	typedef std::tuple<std::shared_ptr<char>, uint32_t, uint32_t, uint32_t, uint32_t> Font;
	//----------------------------------------------------------------------------------------------
	// �t�H���g�e�N�X�`���̐���
	// arg1... �t�H���g�T�C�Y�@�� �e�N�X�`���T�C�Y�ł͂���܂���
	// arg2... �������� 1 ���� 
	// arg3... �c�����p�Ȃ� true
	// arg4... �g�̑����@���ő�T�s�N�Z���ł����������t�H���g�T�C�Y�ɑ�g�͖����ɂȂ�܂�
	// arg5... �g�̐F
	// arg6... �t�H���g�^�C�v�@���w��Ȃ��̏ꍇ�� �l�r �o���� �ɂȂ�܂�
	// arg7... �㕔�̐F ( x = R, y = G, z = B )
	// arg8... �����̐F ( x = R, y = G, z = B )
	// ret....  
	// tuple [ 0 : 4 byte �J���[�z�� ] 
	// tuple [ 1 : �e�N�X�`���̕� ] 
	// tuple [ 2 : �e�N�X�`���̍��� ]
	// tuple [ 3 : �����̕� ]
	// tuple [ 4 : �����̍��� ]
	// tips... �g�p��
	// auto tex1 = tnl::CreateFontTexture(32, tnl::ToOnceWChara("��"));
	//
	Font CreateFontTexture(
			const uint32_t font_size,
			const wchar_t& once,
			bool is_vertical = false,
			int32_t thickness = 0,
			const tkl::Vector3& thickness_color = tkl::Vector3(0, 0, 0),
			const std::string& font_type = "",
			const tkl::Vector3& top_color = tkl::Vector3(1, 1, 1),
			const tkl::Vector3& bottom_color = tkl::Vector3(1, 1, 1));

}