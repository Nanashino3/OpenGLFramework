#include "Shader.h"

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <fstream>

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

// シェーダの読み込み
void Shader::LoadShader()
{
	mShaderProgram = Load("LambertVert.glsl", "LambertFlag.glsl");
}

// ロード処理
unsigned int Load(const char* vertexFile, const char* flagFile)
{
	std::vector<char> vertexSource;
	bool vRet = ReadShaderFile(vertexFile, vertexSource);

	std::vector<char> flagmentSource;
	bool fRet = ReadShaderFile(flagFile, flagmentSource);

	return (vRet && fRet) ? CreateShader(vertexSource.data(), flagmentSource.data()) : 0;
}

// シェーダファイルの読み込み
bool ReadShaderFile(const char* fileName, std::vector<char>& buffer)
{
	std::ifstream file(fileName, std::ios::binary);
	if(file.fail()){
		std::cerr << "Error：Can't open file." << std::endl;
		return false;
	}

	// ファイルサイズを取得
	file.seekg(0, std::ios::beg);
	size_t length = file.tellg();

	// ファイルサイズ分のメモリを確保
	buffer.resize(length + 1);

	// ファイルの先頭からデータを読み込む
	file.seekg(0, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	// 例外処理
	if(file.fail()){
		std::cerr << "Error：Can't not read source file：" << fileName << std::endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

// シェーダを作成
unsigned int CreateShader(const char* vertexSrc, const char* fragmentSrc)
{
	unsigned int program = glCreateProgram();

	// 頂点シェーダを作成
	if(vertexSrc){
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
		glCompileShader(vertexShader);

		if(PrintShaderInfoLog(vertexShader, "Vertex Shader")){
			glAttachShader(program, vertexShader);
		}
		glDeleteShader(vertexShader);
	}

	// 画素シェーダを作成
	if (vertexSrc) {
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
		glCompileShader(fragmentShader);

		if (PrintShaderInfoLog(fragmentShader, "Fragment Shader")) {
			glAttachShader(program, fragmentShader);
		}
		glDeleteShader(fragmentShader);
	}

	// 各種属性をリンクする
	glBindFragDataLocation(program, 0, "outColor");
	glLinkProgram(program);

	if(PrintProgramInfoLog(program)){ return static_cast<unsigned int>(program); }

	glDeleteProgram(program);
	return 0;
}

// シェーダが読み込めたかログを表示
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

// プログラムオブジェクトがリンクできたかログを表示
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