#include "Shader.h"

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "../02_Library/Matrix.h"
#include "../02_Library/Vector.h"

unsigned int Load(const char* vertexFile, const char* flagFile);
bool ReadShaderFile(const char* fileName, std::vector<char>& buffer);
unsigned int CreateShader(const char* vertexSrc, const char* fragmentSrc);
bool PrintShaderInfoLog(unsigned int shader, const char* logMessage);
bool PrintProgramInfoLog(unsigned int program);

Shader::Shader()
: mShaderProgram(0)
{}

Shader::~Shader()
{}

// �V�F�[�_�̓ǂݍ���
void Shader::LoadShader(const char* vertFileName, const char* fragFileName)
{
	mShaderProgram = Load(vertFileName, fragFileName);
}

// �V�F�[�_��L����
void Shader::ActiveShader()
{
	glUseProgram(mShaderProgram);
}

// �e��f�[�^��GPU�ɐݒ肷��
void Shader::SetMatrixUniform(const char* name, const tkl::Matrix& matrix)
{
	unsigned int location = glGetUniformLocation(mShaderProgram, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix.GetData());
}
void Shader::SetVectorUniform(const char* name, const tkl::Vector3& vector)
{
	unsigned int location = glGetUniformLocation(mShaderProgram, name);
	glUniform3fv(location, 1, vector.GetData());
}
void Shader::SetFloatUniform(const char* name, const float value)
{
	unsigned int location = glGetUniformLocation(mShaderProgram, name);
	glUniform1f(location, value);
}

// ���[�h����
unsigned int Load(const char* vertexFile, const char* flagFile)
{
	std::vector<char> vertexSource;
	bool vRet = ReadShaderFile(vertexFile, vertexSource);
	std::vector<char> flagmentSource;
	bool fRet = ReadShaderFile(flagFile, flagmentSource);

	return (vRet && fRet) ? CreateShader(vertexSource.data(), flagmentSource.data()) : 0;
}

// �V�F�[�_�t�@�C���̓ǂݍ���
bool ReadShaderFile(const char* fileName, std::vector<char>& buffer)
{
	if (fileName == 0) { return false; }

	std::ifstream file(fileName, std::ios::binary);
	if(file.fail()){
		std::cerr << "Error�FCan't open file." << fileName << std::endl;
		return false;
	}

	// �t�@�C���T�C�Y���擾
	file.seekg(0, std::ios::end);
	size_t length = file.tellg();

	// �t�@�C���T�C�Y���̃��������m��
	buffer.resize(length + 1);

	// �t�@�C���̐擪����f�[�^��ǂݍ���
	file.seekg(0, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	// ��O����
	if(file.fail()){
		std::cerr << "Error�FCan't not read source file�F" << fileName << std::endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

// �V�F�[�_���쐬
unsigned int CreateShader(const char* vertexSrc, const char* fragmentSrc)
{
	unsigned int program = glCreateProgram();

	// ���_�V�F�[�_���쐬
	if(vertexSrc){
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
		glCompileShader(vertexShader);

		if(PrintShaderInfoLog(vertexShader, "Vertex Shader")){
			glAttachShader(program, vertexShader);
		}
		glDeleteShader(vertexShader);
	}

	// ��f�V�F�[�_���쐬
	if (vertexSrc) {
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
		glCompileShader(fragmentShader);

		if (PrintShaderInfoLog(fragmentShader, "Fragment Shader")) {
			glAttachShader(program, fragmentShader);
		}
		glDeleteShader(fragmentShader);
	}

	// �e�푮���������N����
	glLinkProgram(program);

	if(PrintProgramInfoLog(program)){ return static_cast<unsigned int>(program); }

	glDeleteProgram(program);
	return 0;
}

// �V�F�[�_���ǂݍ��߂������O��\��
bool PrintShaderInfoLog(unsigned int shader, const char* logMessage)
{
	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE){
		std::cerr << "Compile Error in " << logMessage << std::endl;
	}

	int bufSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
	if(bufSize > 1){
		std::vector<char> infoLog(bufSize);
		int length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<bool>(status);
}

// �v���O�����I�u�W�F�N�g�������N�ł��������O��\��
bool PrintProgramInfoLog(unsigned int program)
{
	int status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if(status == GL_FALSE){
		std::cerr << "Link Error." << std::endl;
	}

	int bufSize;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
	if(bufSize > 1){
		std::vector<char> infoLog(bufSize);
		int length;
		glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<bool>(status);
}